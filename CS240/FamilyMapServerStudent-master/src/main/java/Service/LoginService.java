package Service;

import Request.LoginRequest;
import Response.LoginResponse;
import dao.AuthtokenDAO;
import dao.DataAccessException;
import dao.Database;
import dao.UserDAO;
import model.AuthToken;
import model.User;

import java.util.UUID;


/**
 * The connection between the handlers and the DAO. This is where functionality occurs for login
 */
public class LoginService {
    /**
     * logs the user in
     *
     * @param loginRequest receive this from the handler, holds all the login information
     * @return the result of the login
     */
    public LoginResponse login(LoginRequest loginRequest) {

        Database db = new Database();

        try {
            //open db connection
            db.getConnection();

            UserDAO userDAO = new UserDAO(db.getConnection());
            AuthtokenDAO authtokenDAO = new AuthtokenDAO(db.getConnection());

            if (userDAO.validate(loginRequest.getUsername(), loginRequest.getPassword())) {

                User user = userDAO.find(loginRequest.getUsername());

                String authtoken = UUID.randomUUID().toString();
                AuthToken authT = new AuthToken(authtoken, loginRequest.getUsername());
                authtokenDAO.insert(authT);

                String username = user.getUsername();
                String personID = user.getPersonID();

                LoginResponse response = new LoginResponse(authtoken, username,
                        personID, true);
                db.closeConnection(true);

                return response;
            }
            else {
                LoginResponse response = new LoginResponse("Error: User not found in db", false);
                db.closeConnection(false);
                return response;
            }
        } catch (DataAccessException e) {
            e.printStackTrace();

            //close db connection and rollback with (false)
            db.closeConnection(false);

            //create failure response
            LoginResponse response = new LoginResponse("Error: Data Access Exception on Login Service", false);
            return response;
        }
    }
}
