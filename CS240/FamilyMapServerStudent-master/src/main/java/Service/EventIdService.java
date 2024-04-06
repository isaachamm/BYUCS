package Service;

import Response.EventIdResponse;
import dao.DataAccessException;
import dao.Database;
import dao.EventDAO;
import model.Event;

/**
 * functionality for EventId /event/[eventid]
 */
public class EventIdService {

    /**
     * returns a single event object with the specified ID for the current user (validates with authtoken)
     *
     * @return the response of the GET request
     */
    public EventIdResponse getEvent(String id, String currUser) {
        Database db = new Database();

        try {
            db.openConnection();

            EventDAO eventDAO = new EventDAO(db.getConnection());
            Event event = eventDAO.find(id);

            if(event == null) {

                EventIdResponse response = new EventIdResponse("Error: invalid eventID parameter", false);

                db.closeConnection(true);

                return response;
            }
            else if(event.getAssociatedUsername().equals(currUser)) {

                EventIdResponse response = new EventIdResponse(event.getAssociatedUsername(), event.getEventID(),
                        event.getPersonID(), event.getLatitude(), event.getLongitude(), event.getCountry(), event.getCity(),
                        event.getEventType(), event.getYear());

                db.closeConnection(true);

                return response;
            }
            else {

                EventIdResponse response = new EventIdResponse("Error: event does not match user", false);

                db.closeConnection(true);

                return response;
            }
        } catch (DataAccessException e) {

            e.printStackTrace();
            db.closeConnection(false);

            EventIdResponse response = new EventIdResponse("Error: problem occurred trying to retrieve " +
                    id + "event id from the database", false);
            return response;
        }
    }
}
