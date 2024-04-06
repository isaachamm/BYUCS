package handler;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;

public class FileHandler implements HttpHandler {

    @Override
    public void handle(HttpExchange exchange) throws IOException {

        boolean success = false;

        try {
            if (exchange.getRequestMethod().equalsIgnoreCase("get")) {

                String urlPath;
                urlPath = exchange.getRequestURI().toString();
                if(urlPath.compareTo("/") == 0 ||
                    urlPath == null) {
                    urlPath = "/index.html";
                }

                File file = new File("web" + urlPath);
                if (!file.exists()) {
                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_NOT_FOUND, 0);

                    Path failPath = FileSystems.getDefault().getPath("web/HTML/404.html");
                    OutputStream responseBody = exchange.getResponseBody();
                    Files.copy(failPath, responseBody);

                    exchange.getResponseBody().close();
                }
                else {

                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                    OutputStream responseBody = exchange.getResponseBody();
                    Files.copy(file.toPath(), responseBody);
                    responseBody.close();

                    success = true;
                }
            }

            if (!success) {

                exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_METHOD, 0);
                exchange.getResponseBody().close();
            }
        }
        catch (IOException e) {

            exchange.sendResponseHeaders(HttpURLConnection.HTTP_SERVER_ERROR, 0);
            exchange.getResponseBody().close();
            e.printStackTrace();
        }
    }

}
