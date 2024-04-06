package JUnitTests;

import dao.DataAccessException;
import dao.Database;
import dao.EventDAO;
import model.Event;
import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;

public class EventDAOTests {

    private Database db = new Database();

    @AfterEach
    public void cleanup() {
        db.closeConnection(false);
    }

    @Test
    @DisplayName("Try to find an event not in db")
    public void cantFind() throws DataAccessException {
        EventDAO eventDAO = new EventDAO(db.getConnection());
        assertNull(eventDAO.find("abc"));
    }

    @Test
    @DisplayName("Find and return an event in db")
    public void find() throws DataAccessException {
        EventDAO eventDAO = new EventDAO(db.getConnection());
        Event event = new Event("abc123", "isaac", "123456", (float) 25, (float) 25,
                "USA", "grantsville", "birthday", 1999);
        eventDAO.insert(event);
        Event test = eventDAO.find("abc123");
        assertNotNull(test);
        assertEquals(event, test);
    }

    @Test
    @DisplayName("Insert and find an event in db")
    public void insert() throws DataAccessException {
        EventDAO eventDAO = new EventDAO(db.getConnection());
        Event event = new Event("asdf", "hamm", "56789", (float) 30, (float) 30,
                "Ukraine", "tooele", "holiday", 2001);
        Event test = new Event("asdf", "hamm", "56789", (float) 30, (float) 30,
                "Ukraine", "tooele", "holiday", 2001);
        eventDAO.insert(event);
        assertNotNull(eventDAO.find("asdf"));
        assertEquals(test, eventDAO.find("asdf"));
    }

    @Test
    @DisplayName("Insert duplicate event")
    public void insertDuplicate() throws DataAccessException {
        EventDAO eventDAO = new EventDAO(db.getConnection());
        Event event = new Event("abc123", "isaac", "123456", (float) 25, (float) 25,
                "USA", "grantsville", "birthday", 1999);
        eventDAO.insert(event);
        assertThrows(DataAccessException.class, () -> {eventDAO.insert(event);});
    }

    @Test
    @DisplayName("Clear events")
    public void clear() throws DataAccessException {
        EventDAO eventDAO = new EventDAO(db.getConnection());
        Event event = new Event("abc123", "isaac", "123456", (float) 25, (float) 25,
                "USA", "grantsville", "birthday", 1999);
        eventDAO.insert(event);
        assertNotNull(eventDAO.find("abc123"));
        eventDAO.clear();
        assertNull(eventDAO.find("abc123"));
    }
}
