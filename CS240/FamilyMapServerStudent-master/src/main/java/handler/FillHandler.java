package handler;

import Service.FillService;
import Response.FillResponse;
import com.google.gson.Gson;
import com.sun.net.httpserver.HttpExchange;
import dao.DataAccessException;
import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;

public class FillHandler extends HandlerBase {

    @Override
    public void handle(HttpExchange exchange) throws IOException {
        boolean success = false;

        if (exchange.getRequestMethod().equalsIgnoreCase("post")) {

            try {
                Gson gson = new Gson();
                FillResponse response = null;
                FillService service = new FillService();

                String requestData = exchange.getRequestURI().toString();
                System.out.print("Fill request: ");
                System.out.println(requestData);

                String[] urlParts = requestData.split("/");

                int generationsToFill = 0;

                if (urlParts.length == 3) {
                    generationsToFill = 4;
                }
                else if (urlParts.length == 4) {
                    generationsToFill = Integer.parseInt(urlParts[3]);
                }
                String currUser = urlParts[2];

                response = service.fill(currUser, generationsToFill);

                if (response.isSuccess()) {
                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                    String responseData = gson.toJson(response);
                    System.out.print("Successful Fill! ");
                    System.out.println(responseData);

                    OutputStream responseBody = exchange.getResponseBody();
                    writeString(responseData, responseBody);
                    responseBody.close();

                    success = true;
                }
                if (!success) {
                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                    String responseData = gson.toJson(response);

                    OutputStream responseBody = exchange.getResponseBody();
                    writeString(responseData, responseBody);

                    exchange.getResponseBody().close();
                }
            } catch (IOException | DataAccessException e) {
                exchange.sendResponseHeaders(HttpURLConnection.HTTP_SERVER_ERROR, 0);
                exchange.getResponseBody().close();
                e.printStackTrace();
            }
        }
    }
}