package handler;

import Service.PersonIdService;
import Service.PersonService;
import Response.PersonIdResponse;
import Response.PersonResponse;
import com.google.gson.Gson;
import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpExchange;
import model.AuthToken;

import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;

public class PersonHandler extends HandlerBase {


    @Override
    public void handle(HttpExchange exchange) throws IOException {
        boolean success = false;

        if(exchange.getRequestMethod().equalsIgnoreCase("get")) {

            try {
                Gson gson = new Gson();
                Headers reqHeaders = exchange.getRequestHeaders();

                if (reqHeaders.containsKey("Authorization")) {

                    String authtokenString = reqHeaders.getFirst("Authorization");
                    AuthToken authToken = validateAuthtoken(authtokenString);

                    //Getting the request URI
                    String reqData = exchange.getRequestURI().toString();
                    System.out.print("Person Request: ");
                    System.out.println(reqData);
                    String[] urlParts = reqData.split("/");

                    if (authToken != null) {

                        //first branch is for person request, second for person/id
                        if (urlParts.length == 2) {

                            //person service
                            PersonService service = new PersonService();
                            PersonResponse response = service.getPeople(authToken);

                            if (response.isSuccess()) {
                                exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                                String responseData = gson.toJson(response);
                                System.out.println("Successful Persons query");

                                OutputStream responseBody = exchange.getResponseBody();
                                writeString(responseData, responseBody);
                                responseBody.close();

                                success = true;
                            } else {
                                exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                                String responseData = gson.toJson(response);

                                OutputStream responseBody = exchange.getResponseBody();
                                writeString(responseData, responseBody);
                                responseBody.close();
                            }
                        } else if (urlParts.length == 3) {

                            //person/personid service
                            String personId = urlParts[2];
                            PersonIdService service = new PersonIdService();
                            PersonIdResponse response = service.getPerson(personId, authToken.getUsername());

                            if (response.isSuccess()) {
                                exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                                String responseData = gson.toJson(response);
                                System.out.print("Successful Person query: ");
                                System.out.println(responseData);

                                OutputStream responseBody = exchange.getResponseBody();
                                writeString(responseData, responseBody);
                                responseBody.close();

                                success = true;
                            } else {
                                exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                                String responseData = gson.toJson(response);

                                OutputStream responseBody = exchange.getResponseBody();
                                writeString(responseData, responseBody);
                                responseBody.close();
                            }
                        }
                    } else {
                        //arbitrary response again (like in event handler), but should work for both if there's
                        // an invalid authtoken
                        PersonIdResponse response = new PersonIdResponse("Error: invalid authtoken", false);
                        exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                        String responseData = gson.toJson(response);

                        OutputStream responseBody = exchange.getResponseBody();
                        writeString(responseData, responseBody);
                        responseBody.close();
                    }
                }

            } catch (Exception e) {
                exchange.sendResponseHeaders(HttpURLConnection.HTTP_SERVER_ERROR, 0);
                exchange.getResponseBody().close();
                e.printStackTrace();
            }

        }
    }
}
