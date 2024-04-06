package JUnitTests;

import dao.DataAccessException;
import dao.Database;
import dao.PersonDAO;
import model.Person;
import org.junit.jupiter.api.*;

import static org.junit.jupiter.api.Assertions.*;

public class PersonDAOTests {

    private Database db = new Database();

    @BeforeEach
    public void setup() throws DataAccessException{
        db.getConnection();
    }

    @AfterEach
    public void cleanup() throws DataAccessException {
        db.closeConnection(false);
    }

    @Test
    @DisplayName("Try to find a person not in DB")
    public void cantFind() throws DataAccessException {
        PersonDAO personDAO = new PersonDAO(db.getConnection());
        assertNull(personDAO.find("abc"));
    }

    @Test
    @DisplayName("Find a person in the DB")
    public void findPerson() throws DataAccessException {
        PersonDAO personDAO = new PersonDAO(db.getConnection());
        Person person = new Person("abc", "jumpman", "Michael", "Jordan",
                "m", "def", "hig", "jfk");
        personDAO.insert(person);
        assertNotNull(personDAO.find("abc"));
    }

    @Test
    @DisplayName("Insert and find a person in the DB")
    public void insertPerson() throws DataAccessException {
        PersonDAO personDAO = new PersonDAO(db.getConnection());
        Person person = new Person("abc", "jumpman", "Michael", "Jordan",
                "m", "def", "hig", "jfk");
        Person test = new Person("abc", "jumpman", "Michael", "Jordan",
                "m", "def", "hig", "jfk");
        personDAO.insert(person);
        assertEquals(test, person);
    }

    @Test
    @DisplayName("Try and insert a duplicate name")
    public void insertDuplicate() throws DataAccessException {
        PersonDAO personDAO = new PersonDAO(db.getConnection());
        Person test = new Person("mr", "jumpman", "Michael", "Jordan",
                "m", "def", "hig", "jfk");
        personDAO.insert(test);
        assertThrows(DataAccessException.class, () -> {personDAO.insert(test);});
    }

    @Test
    @DisplayName("Clear")
    public void clear() throws DataAccessException{
        PersonDAO personDAO = new PersonDAO(db.getConnection());
        Person person = new Person("abc", "jumpman", "Michael", "Jordan",
                "m", "def", "hig", "jfk");
        personDAO.insert(person);
        assertNotNull(personDAO.find("abc"));
        personDAO.clear();
        assertNull(personDAO.find("abc"));
    }

}
