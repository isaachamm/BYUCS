package handler;

import Service.EventIdService;
import Service.EventService;
import Response.EventIdResponse;
import Response.EventResponse;
import com.google.gson.Gson;
import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpExchange;
import model.AuthToken;

import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;

public class EventHandler extends HandlerBase {


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

                    if (authToken != null) {


                        //Getting and splitting the request URI
                        String requestData = exchange.getRequestURI().toString();
                        System.out.print("Event Request: ");
                        System.out.println(requestData);
                        String[] urlParts = requestData.split("/");

                        //First branch is for the allevents service, second is for event/id service
                        if (urlParts.length == 2) {

                            EventService service = new EventService();
                            EventResponse response = service.getEvents(authToken);

                            if (response.isSuccess()) {
                                exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                                String responseData = gson.toJson(response);
                                System.out.println("Successful query of events");

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

                            //event/eventid service
                            String eventId = urlParts[2];
                            EventIdService service = new EventIdService();
                            EventIdResponse response = service.getEvent(eventId, authToken.getUsername());

                            if (response.isSuccess()) {
                                exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                                String responseData = gson.toJson(response);
                                System.out.print("Successful event query");
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
                        //I think this could be an event response too because it has the same data -- an
                        // arbitrary decision I suppose
                        EventIdResponse response = new EventIdResponse("Error: invalid authtoken", false);
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
