package Service;

import Response.PersonIdResponse;
import dao.DataAccessException;
import dao.Database;
import dao.PersonDAO;
import model.Person;

/**
 * functionality for the personID /person/[personID]
 */
public class PersonIdService {

    /**
     * Returns the single person object with the specified ID if associated with current user (validated by authtoken)
     *
     * @return response of the GET request
     */
    public PersonIdResponse getPerson(String id, String currUser) {

        Database db = new Database();

        try {
            db.openConnection();

            PersonDAO personDAO = new PersonDAO(db.getConnection());
            Person person = personDAO.find(id);

            if(person == null) {

                PersonIdResponse response = new PersonIdResponse("Error: invalid personID parameter", false);
                db.closeConnection(false);

                return response;
            }
            else if(person.getAssociatedUsername().equals(currUser)) {

                PersonIdResponse response = new PersonIdResponse(person.getAssociatedUsername(), person.getPersonID(),
                        person.getFirstName(), person.getLastName(), person.getGender(), person.getFatherID(),
                        person.getMotherID(), person.getSpouseID());
                db.closeConnection(true);

                return response;
            }
            else {

                PersonIdResponse response = new PersonIdResponse("Error: person does not match user", false);
                db.closeConnection(false);

                return response;
            }
        } catch (DataAccessException e) {
            e.printStackTrace();
            db.closeConnection(false);

            PersonIdResponse response = new PersonIdResponse("Error: problem occurred trying to retrieve " +
                    id + "person id from the database", false);
            return response;
        }
    }
}
