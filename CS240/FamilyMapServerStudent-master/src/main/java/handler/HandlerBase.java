package handler;

import com.sun.net.httpserver.HttpHandler;
import dao.AuthtokenDAO;
import dao.DataAccessException;
import dao.Database;
import model.AuthToken;

import java.io.*;

public abstract class HandlerBase implements HttpHandler {

    /**
     * This function accesses the database to validate authtokens for the handler classes
     * Handler classes that need to use this: login, person, event,
     *
     * @param authtokenString - the authtoken that we will pass to the database to get the username
     * @return authtoken of the user associated with the authtoken string
     */
    public AuthToken validateAuthtoken(String authtokenString) {
        Database db = new Database();
        try {
            AuthtokenDAO authtokenDAO = new AuthtokenDAO(db.getConnection());
            AuthToken authToken = authtokenDAO.findAuthtoken(authtokenString);
            db.closeConnection(true);
            return authToken;
        } catch (DataAccessException e) {
            e.printStackTrace();
            db.closeConnection(false);
            return null;
        }
    }

    /**
     * Used in the handler classes to read from json objects (deserialization)
     *
     * @param is - input stream (to write from exchange body)
     * @return - a string of the json object
     * @throws IOException - if errors occur while reading in the string
     */
    protected String readString(InputStream is) throws IOException {
        StringBuilder sb = new StringBuilder();
        InputStreamReader sr = new InputStreamReader(is);
        char[] buf = new char[1024];
        int len;
        while ((len = sr.read(buf)) > 0) {
            sb.append(buf, 0, len);
        }
        return sb.toString();
    }

    /**
     * Used in the handler classes to write responses as JSON objects (serialization)
     *
     * @param str - the string we build from the json objects
     * @param os - outputstream (to write to exchange body)
     * @throws IOException - if error occurs while writing to output stream
     */
    protected void writeString(String str, OutputStream os) throws IOException {
        OutputStreamWriter sw = new OutputStreamWriter(os);
        sw.write(str);
        sw.flush();
    }

}
