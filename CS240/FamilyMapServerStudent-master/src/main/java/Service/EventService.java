package Service;

import Response.EventResponse;
import dao.DataAccessException;
import dao.Database;
import dao.EventDAO;
import model.AuthToken;
import model.Event;

import java.util.List;

/**
 * functionality for event /event
 */
public class EventService {

    /**
     * returns all events for all family members of the current user (validated by authtoken)
     *
     * @return the response of the GET request
     */
    public EventResponse getEvents(AuthToken authToken) {
        Database db = new Database();

        try {
            db.openConnection();

            EventDAO eventDAO = new EventDAO(db.getConnection());

            List<Event> eventsList = eventDAO.findEventsForUser(authToken.getUsername());
            Event[] eventsArray = new Event[eventsList.size()];
            eventsArray = eventsList.toArray(eventsArray);

            EventResponse response = new EventResponse(eventsArray);

            db.closeConnection(true);

            return response;

        } catch (DataAccessException e) {

            e.printStackTrace();
            db.closeConnection(false);

            EventResponse response = new EventResponse("Error: problem getting events from db", true);
            return response;
        }
    }
}
