package Service;

import Request.RegisterRequest;
import Response.RegisterResponse;
import dao.*;
import model.AuthToken;
import model.Event;
import model.Person;
import model.User;
import java.io.FileNotFoundException;
import java.util.Map;
import java.util.UUID;

/**
 * functionality for register /user/register
 */
public class RegisterService {

    /**
     * creates a new user account in the database
     * genereates 4 generations of data
     * Logs the user in
     * returns an authtoken
     *
     * @param registerRequest Holds the info needed to create a new user
     * @return the result of the POST request, including a new authtoken for this user
     */
    public RegisterResponse register(RegisterRequest registerRequest) {

        Database db = new Database();

        try {
            db.openConnection();

            String personId = UUID.randomUUID().toString();
            String authtoken = UUID.randomUUID().toString();

            UserDAO userDAO = new UserDAO(db.getConnection());
            User user = new User(registerRequest.getUsername(), registerRequest.getPassword(), registerRequest.getEmail(),
                    registerRequest.getFirstName(), registerRequest.getLastName(), registerRequest.getGender(),
                    personId);
            userDAO.insert(user);

            AuthToken authT = new AuthToken(authtoken, registerRequest.getUsername());
            AuthtokenDAO authtokenDAO = new AuthtokenDAO(db.getConnection());
            authtokenDAO.insert(authT);

            GenerateFamilyTree gft = new GenerateFamilyTree();
            gft.setCurrUsername(user.getUsername());
            gft.generateAncestors(user.getGender(), 4, user);

            PersonDAO personDAO = new PersonDAO(db.getConnection());
            EventDAO eventDAO = new EventDAO(db.getConnection());

            for(Event e : gft.getEvents()) {
                eventDAO.insert(e);
            }
            for(Map.Entry<String, Person> entry : gft.getAncestors().entrySet()) {
                personDAO.insert(entry.getValue());
            }

            db.closeConnection(true);

            RegisterResponse response = new RegisterResponse(authtoken, registerRequest.getUsername(), personId,
                    true);
            return response;

        } catch (DataAccessException | FileNotFoundException e) {

            e.printStackTrace();
            db.closeConnection(false);

            RegisterResponse response = new RegisterResponse(false, "Error: Data Access Exception in Register Service");
            return response;
        }
    }
}
