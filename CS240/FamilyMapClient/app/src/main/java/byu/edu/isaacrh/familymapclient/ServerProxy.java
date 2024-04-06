package byu.edu.isaacrh.familymapclient;

import com.google.gson.Gson;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;

import Request.LoginRequest;
import Request.RegisterRequest;
import Response.ClearResponse;
import Response.EventResponse;
import Response.LoginResponse;
import Response.PersonResponse;
import Response.RegisterResponse;
import model.AuthToken;
import model.Event;

public class ServerProxy {

    //register user
    public static RegisterResponse register(RegisterRequest registerRequest) {

        try{
            URL url = new URL("http://" + DataCache.getServerHost() + ":" +
                    DataCache.getServerPort() + "/user/register");

            HttpURLConnection http = (HttpURLConnection) url.openConnection();
            http.setRequestMethod("POST");
            http.setDoOutput(true);
            http.connect();

            Gson gson = new Gson();
            String requestData = gson.toJson(registerRequest);
            OutputStream requestBody = http.getOutputStream();
            writeString(requestData, requestBody);

            requestBody.close();

            if(http.getResponseCode() == HttpURLConnection.HTTP_OK) {
                System.out.println("Register Successful");

                InputStream responseBody = http.getInputStream();
                String responseData = readString(responseBody);

                RegisterResponse registerResponse = gson.fromJson(responseData, RegisterResponse.class);
                return registerResponse;
            }
            else {
                RegisterResponse response = new RegisterResponse(false, "Error: register failed");
                return response;
            }

        } catch (IOException e) {
            e.printStackTrace();
            RegisterResponse response = new RegisterResponse(false, "Error: register failed");
            return response;
        }
    }

    //login user
    public static LoginResponse login(LoginRequest loginRequest) {

        try {
            URL url = new URL("http://" + DataCache.getServerHost() + ":" +
                    DataCache.getServerPort() + "/user/login");

            HttpURLConnection http = (HttpURLConnection) url.openConnection();
            http.setRequestMethod("POST");
            http.setDoOutput(true);
            http.connect();

            Gson gson = new Gson();
            String requestData = gson.toJson(loginRequest);
            OutputStream requestBody = http.getOutputStream();
            writeString(requestData, requestBody);

            requestBody.close();

            if(http.getResponseCode() == HttpURLConnection.HTTP_OK) {
                System.out.println("Login Successful");

                InputStream responseBody = http.getInputStream();
                String responseData = readString(responseBody);

                LoginResponse loginResponse = gson.fromJson(responseData, LoginResponse.class);
                return loginResponse;
            }
            else {
                LoginResponse response = new LoginResponse("Error: login failed", false);
                return response;
            }

        } catch (IOException e) {
            e.printStackTrace();
            LoginResponse response = new LoginResponse("Error: login failed", false);
            return response;
        }
    }

        //get people
    public static PersonResponse getPeopleForUser(String authToken) {
        try {
            URL url = new URL("http://" + DataCache.getServerHost() + ":" +
                    DataCache.getServerPort() + "/person");

            HttpURLConnection http = (HttpURLConnection) url.openConnection();
            http.setRequestMethod("GET");
            http.setDoOutput(false);
            http.addRequestProperty("Authorization", authToken);
            http.connect();

            if(http.getResponseCode() == HttpURLConnection.HTTP_OK) {
                System.out.println("Person datacache Successful");

                InputStream responseBody = http.getInputStream();
                String responseData = readString(responseBody);

                Gson gson = new Gson();
                PersonResponse loginResponse = gson.fromJson(responseData, PersonResponse.class);
                return loginResponse;
            }
            else {
                PersonResponse response = new PersonResponse("Error: problem getting people", true);
                return response;
            }

        } catch (IOException e) {
            e.printStackTrace();
            PersonResponse response = new PersonResponse("Error: problem getting people", true);
            return response;
        }
    }

    //get events
    public static EventResponse getEventsForUser(String authToken) {
        try {
            URL url = new URL("http://" + DataCache.getServerHost() + ":" +
                    DataCache.getServerPort() + "/event");

            HttpURLConnection http = (HttpURLConnection) url.openConnection();
            http.setRequestMethod("GET");
            http.setDoOutput(false);
            http.addRequestProperty("Authorization", authToken);
            http.connect();

            if(http.getResponseCode() == HttpURLConnection.HTTP_OK) {
                System.out.println("Event datacache Successful");

                InputStream responseBody = http.getInputStream();
                String responseData = readString(responseBody);

                Gson gson = new Gson();
                EventResponse eventResponse = gson.fromJson(responseData, EventResponse.class);
                return eventResponse;
            }
            else {
                EventResponse response = new EventResponse("Error: problem getting events", true);
                return response;
            }

        } catch (IOException e) {
            e.printStackTrace();
            EventResponse response = new EventResponse("Error: problem getting events", true);
            return response;
        }
    }

    public static ClearResponse clear() {
        try{
            URL url = new URL("http://" + DataCache.getServerHost() + ":" +
                    DataCache.getServerPort() + "/clear");

            HttpURLConnection http = (HttpURLConnection) url.openConnection();
            http.setRequestMethod("POST");
            http.setDoOutput(true);
            http.connect();

            if(http.getResponseCode() == HttpURLConnection.HTTP_OK) {
                System.out.println("Clear Successful");

                InputStream responseBody = http.getInputStream();
                String responseData = readString(responseBody);

                Gson gson = new Gson();
                ClearResponse clearResponse = gson.fromJson(responseData, ClearResponse.class);
                return clearResponse;
            }
            else {
                ClearResponse response = new ClearResponse("Clear Failed", false);
                return response;
            }

        } catch (IOException e) {
            e.printStackTrace();

            ClearResponse response = new ClearResponse("Clear Failed", false);
            return response;
        }

    }

    private static String readString(InputStream is) throws IOException {
        StringBuilder sb = new StringBuilder();
        InputStreamReader sr = new InputStreamReader(is);
        char[] buf = new char[1024];
        int len;
        while ((len = sr.read(buf)) > 0) {
            sb.append(buf, 0, len);
        }
        return sb.toString();
    }

    private static void writeString(String str, OutputStream os) throws IOException {
        OutputStreamWriter sw = new OutputStreamWriter(os);
        sw.write(str);
        sw.flush();
    }

}
