package Service;

import Response.FillResponse;
import dao.*;
import model.Event;
import model.Person;
import model.User;

import java.io.FileNotFoundException;
import java.util.Map;

/**
 * functionality for fill /fill/[username]/{generations}
 */
public class FillService {

    /**
     * populates database with generated information for a user
     * populates to the number of generations specified, or 4 is default
     * Generates new persons and events
     *
     * @return response of the POST requests (must include number of persons and events created)
     */
    public FillResponse fill(String username, int generationsToFill) throws DataAccessException {

        if(generationsToFill < 0) {

            FillResponse response = new FillResponse("Error: generations to fill " +
                    "must be non-negative", false);

            return response;
        }

        Database database = new Database();
        try {

            database.openConnection();

            PersonDAO personDAO = new PersonDAO(database.getConnection());
            EventDAO eventDAO = new EventDAO(database.getConnection());
            UserDAO userDAO = new UserDAO(database.getConnection());

            User user = userDAO.find(username);

            eventDAO.clear(user.getUsername());
            personDAO.clear(user.getUsername());

            GenerateFamilyTree gft = new GenerateFamilyTree();
            gft.setCurrUsername(user.getUsername());
            gft.generateAncestors(user.getGender(), generationsToFill, user);

            for(Event e : gft.getEvents()) {
                eventDAO.insert(e);
            }
            for(Map.Entry<String, Person> entry : gft.getAncestors().entrySet()) {
                personDAO.insert(entry.getValue());
            }

            database.closeConnection(true);

            FillResponse response = new FillResponse("Successfully added " + gft.getAncestors().size() +
                    " persons and " + gft.getEvents().size() + " events to the database.", true);

            return response;

        } catch (DataAccessException | FileNotFoundException e) {

            FillResponse response = new FillResponse("Error: could not fill data to database", false);

            database.closeConnection(false);
            e.printStackTrace();

            return response;
        }

    }
}
