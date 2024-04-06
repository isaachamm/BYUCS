package handler;

import Service.LoadService;
import Request.LoadRequest;
import Response.LoadResponse;
import com.google.gson.Gson;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;

public class LoadHandler extends HandlerBase {
    @Override
    public void handle(HttpExchange exchange) throws IOException {

        boolean success = false;

        try{
            if(exchange.getRequestMethod().equalsIgnoreCase("post")) {

                InputStream requestBody = exchange.getRequestBody();
                String requestData = readString(requestBody);

                Gson gson = new Gson();

                LoadRequest request = gson.fromJson(requestData, LoadRequest.class);
                LoadService service = new LoadService();
                LoadResponse response = service.load(request);

                exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                String responseData = gson.toJson(response);

                System.out.print("Successful Load Response: ");
                System.out.println(responseData);

                OutputStream responseBody = exchange.getResponseBody();
                writeString(responseData, responseBody);
                responseBody.close();
                success = true;
            }

            if(!success) {
                exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                exchange.getRequestBody().close();
            }
        } catch (IOException e) {
            e.printStackTrace();
            exchange.sendResponseHeaders(HttpURLConnection.HTTP_SERVER_ERROR, 0);
            exchange.getResponseBody().close();
        }

    }
}
