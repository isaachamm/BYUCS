package handler;

import Service.RegisterService;
import Request.RegisterRequest;
import Response.RegisterResponse;
import com.google.gson.Gson;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.HttpURLConnection;

public class RegisterUserHandler extends HandlerBase {

    @Override
    public void handle(HttpExchange exchange) throws IOException {

        boolean success = false;

        try {

            RegisterResponse response = null;
            Gson gson = new Gson();

            if (exchange.getRequestMethod().equalsIgnoreCase("post")) {

                InputStream reqBody = exchange.getRequestBody();

                // Read JSON string from the input stream
                String requestData = readString(reqBody);

                // Display/log the request JSON data
                System.out.print("Register User Request: ");
                System.out.println(requestData);
                
                RegisterRequest request = gson.fromJson(requestData, RegisterRequest.class);
                RegisterService service = new RegisterService();
                response = service.register(request);

                if(response.isSuccess()) {

                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                    OutputStream responseBody = exchange.getResponseBody();
                    String responseData = gson.toJson(response);
                    writeString(responseData, responseBody);

                    // display/log the response JSON data
                    System.out.print("Successful Register user Response: ");
                    System.out.println(responseData);

                    responseBody.close();

                    success = true;
                }

            }

            if (!success) {
                exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);

                OutputStream responseBody = exchange.getResponseBody();
                String responseData = gson.toJson(response);
                writeString(responseData, responseBody);

                responseBody.close();
            }
        }
        catch (IOException e) {
            exchange.sendResponseHeaders(HttpURLConnection.HTTP_SERVER_ERROR, 0);
            exchange.getResponseBody().close();
            e.printStackTrace();
        }
    }

}
