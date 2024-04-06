package handler;

import Service.LoginService;
import Request.LoginRequest;
import Response.LoginResponse;
import com.google.gson.Gson;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;

public class LoginUserHandler extends HandlerBase {
    @Override
    public void handle(HttpExchange exchange) throws IOException {

        boolean success = false;

        try {
            Gson gson = new Gson();
            LoginResponse response = null;

            if(exchange.getRequestMethod().equalsIgnoreCase("post")) {

                InputStream requestBody = exchange.getRequestBody();

                String requestData = readString(requestBody);

                System.out.print("Login User Request: ");
                System.out.println(requestData);


                LoginRequest request = gson.fromJson(requestData, LoginRequest.class);
                LoginService loginService = new LoginService();
                response = loginService.login(request);


                if(response.isSuccess()) {
                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
                    String responseData = gson.toJson(response);

                    System.out.print("Successful Login Response: ");
                    System.out.println(responseData);

                    OutputStream responseBody = exchange.getResponseBody();
                    writeString(responseData, responseBody);
                    responseBody.close();
                    success = true;
                }

            }

            if (!success) {
                exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);

                String responseData = gson.toJson(response);
                System.out.println(responseData);
                OutputStream responseBody = exchange.getResponseBody();

                writeString(responseData, responseBody);
                exchange.getResponseBody().close();
            }
        } catch(IOException e) {
            exchange.sendResponseHeaders(HttpURLConnection.HTTP_SERVER_ERROR, 0);
            exchange.getResponseBody().close();
            e.printStackTrace();
        }

    }
}
