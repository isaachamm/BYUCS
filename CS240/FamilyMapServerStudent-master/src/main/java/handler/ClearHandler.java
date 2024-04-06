package handler;

import Service.ClearService;
import Response.ClearResponse;
import com.google.gson.Gson;
import com.sun.net.httpserver.HttpExchange;
import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;

public class ClearHandler extends HandlerBase {

    @Override
    public void handle(HttpExchange exchange) throws IOException {

        boolean success = false;

        try {
            if(exchange.getRequestMethod().equalsIgnoreCase("post")) {

                ClearService clearService = new ClearService();
                ClearResponse response = clearService.clear();

                exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                Gson gson = new Gson();

                String responseData = gson.toJson(response);

                OutputStream respBody = exchange.getResponseBody();
                writeString(responseData, respBody);
                respBody.close();

                System.out.println("Successful Clear!");

                success = true;
            }

            if(!success) {
                exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                exchange.getResponseBody().close();
            }

        } catch (IOException e) {
            exchange.sendResponseHeaders(HttpURLConnection.HTTP_SERVER_ERROR, 0);
            exchange.getResponseBody().close();
            e.printStackTrace();
        }
    }
}
