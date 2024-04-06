package Service;

import Request.LoadRequest;
import Response.LoadResponse;
import dao.*;
import model.Event;
import model.Person;
import model.User;

/**
 * functionality for load /load
 */
public class LoadService {

    /**
     * clears all data from the database
     * then loads user, event, and person data from the loadrequest into the database
     *
     * @param loadRequest holds arrays of users, persons, and events to upload to the database
     * @return the response of the POST request
     */
    public LoadResponse load(LoadRequest loadRequest) {

        Database db = new Database();

        try {
            db.openConnection();

            UserDAO userDAO = new UserDAO(db.getConnection());
            PersonDAO personDAO = new PersonDAO(db.getConnection());
            EventDAO eventDAO = new EventDAO(db.getConnection());
            AuthtokenDAO authtokenDAO = new AuthtokenDAO(db.getConnection());

            userDAO.clear();
            personDAO.clear();
            eventDAO.clear();
            authtokenDAO.clear();

            for (User user : loadRequest.getUsers()) {
                userDAO.insert(user);
            }
            for(Person person : loadRequest.getPersons()) {
                personDAO.insert(person);
            }
            for(Event event : loadRequest.getEvents()) {
                eventDAO.insert(event);
            }

            db.closeConnection(true);

            String message = "Successfully added " + loadRequest.getUsers().length + " users, " +
                    loadRequest.getPersons().length + " persons, and " +
                    loadRequest.getEvents().length + " events to the database";
            LoadResponse response = new LoadResponse(message, true);

            return response;

        } catch (DataAccessException e) {

            db.closeConnection(false);
            e.printStackTrace();

            LoadResponse response = new LoadResponse("Error: could not load data to database", false);
            return response;
        }
    }
}
