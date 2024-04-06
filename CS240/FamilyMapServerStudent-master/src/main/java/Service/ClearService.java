package Service;

import Response.ClearResponse;
import dao.*;

/**
 * functionality for service
 */
public class ClearService {

    /**
     * clears all the data in the table
     *
     * @return the response of the clear function
     */
    public ClearResponse clear() {

        Database db = new Database();

        try {
            db.openConnection();

            AuthtokenDAO authtokenDAO = new AuthtokenDAO(db.getConnection());
            EventDAO eventDAO = new EventDAO(db.getConnection());
            PersonDAO personDAO = new PersonDAO(db.getConnection());
            UserDAO userDAO = new UserDAO(db.getConnection());

            authtokenDAO.clear();
            eventDAO.clear();
            personDAO.clear();
            userDAO.clear();

            db.closeConnection(true);

            ClearResponse response = new ClearResponse("Clear Succeeded", true);
            return response;

        } catch (DataAccessException e) {

            e.printStackTrace();
            db.closeConnection(false);

            ClearResponse response = new ClearResponse("Clear Failed", false);
            return response;
        }
    }

}
