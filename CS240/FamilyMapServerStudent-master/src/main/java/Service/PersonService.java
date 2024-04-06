package Service;

import Response.PersonResponse;
import dao.DataAccessException;
import dao.Database;
import dao.PersonDAO;
import model.AuthToken;
import model.Person;

import java.util.List;

/**
 * functionality for person /person
 */
public class PersonService {

    /**
     * Returns all persons (family members) for the current user
     *
     * @return response of the GET request
     */
    public PersonResponse getPeople(AuthToken authToken) {

        Database db = new Database();

        try {
            db.openConnection();

            PersonDAO personDAO = new PersonDAO(db.getConnection());

            List<Person> people = personDAO.findAncestorsForUser(authToken.getUsername());
            Person[] ancestors = new Person[people.size()];
            ancestors = people.toArray(ancestors);

            PersonResponse response = new PersonResponse(ancestors, true);

            db.closeConnection(true);

            return response;

        } catch (DataAccessException e) {
            e.printStackTrace();
            db.closeConnection(false);

            PersonResponse response = new PersonResponse("Error: problem getting people from db", true);
            return response;
        }
    }
}
