package JUnitTests;

import dao.DataAccessException;
import dao.Database;
import dao.UserDAO;
import model.User;
import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;


public class UserDAOTests {

    private static Database db = new Database();


    @BeforeEach
    public void setup() throws DataAccessException{
        db.getConnection();
    }

    @AfterEach
    public void cleanup() {
        db.closeConnection(false);
    }

    @Test
    @DisplayName("Find a user that's in the DB")
    public void findUser() throws DataAccessException {
        UserDAO userDAO = new UserDAO(db.getConnection());

        User user = new User("isaac", "isuck", "hamm4", "isaacrh",
                "hamm", "m", "123456");
        userDAO.insert(user);
        User test = userDAO.find("isaac");
        assertEquals(user, test);
    }

    @Test
    @DisplayName("Try to find a user that's not in the DB")
    public void wrongFind() throws DataAccessException {
        UserDAO userDAO = new UserDAO(db.getConnection());
        User test = userDAO.find("isaaaaac");
        assertNull(test);
    }

    @Test
    @DisplayName("Insert and find check")
    public void insertUser() throws DataAccessException {
        UserDAO userDAO = new UserDAO(db.getConnection());
        User user = new User("joe", "joemama", "joe1", "joesahoe",
                "joecool", "m", "abcd123");
        userDAO.insert(user);
        User test = new User("joe", "joemama", "joe1", "joesahoe",
                "joecool", "m", "abcd123");
        assertEquals(test, userDAO.find("joe"));
    }

    @Test
    @DisplayName("Try to insert user that's already in DB")
    public void insertDuplicate() throws DataAccessException {
        UserDAO userDAO = new UserDAO(db.getConnection());
        User user = new User("isaac", "isuck", "hamm4", "isaacrh",
                "hamm", "m", "123456");
        userDAO.insert(user);
        assertThrows(DataAccessException.class, () -> {userDAO.insert(user);});
    }

    @Test
    @DisplayName("Validate an actual user w/ username and password")
    public void validate() throws DataAccessException {
        UserDAO userDAO = new UserDAO(db.getConnection());
        User user = new User("joe", "joemama", "joe1", "joesahoe",
                "joecool", "m", "abcd123");
        userDAO.insert(user);
        assertTrue(userDAO.validate("joe", "joemama"));
    }

    @Test
    @DisplayName("Fail validation of user")
    public void failValidate() throws DataAccessException {
        UserDAO userDAO = new UserDAO(db.getConnection());
        assertFalse(userDAO.validate("iamadirtybum", "not me!"));
    }

    @Test
    @DisplayName("Clear function")
    public void clear() throws DataAccessException {
        UserDAO userDAO = new UserDAO(db.getConnection());
        User user = new User("isaac", "isuck", "hamm4", "isaacrh",
                "hamm", "m", "123456");
        userDAO.insert(user);
        assertNotNull(userDAO.find("isaac"));
        userDAO.clear();
        assertNull(userDAO.find("isaac"));
    }

}
