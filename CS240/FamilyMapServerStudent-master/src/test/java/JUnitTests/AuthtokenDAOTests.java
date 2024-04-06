package JUnitTests;

import dao.AuthtokenDAO;
import dao.DataAccessException;
import dao.Database;
import model.AuthToken;
import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;

public class AuthtokenDAOTests {

    private Database db = new Database();

    @AfterEach
    public void cleanup() throws DataAccessException {
        db.closeConnection(false);
    }

    @Test
    @DisplayName("Try to find an authtoken not in db")
    public void findFail() throws DataAccessException{
        AuthtokenDAO authtokenDAO = new AuthtokenDAO(db.getConnection());
        assertNull(authtokenDAO.findAuthtoken("jkl"));
    }

    @Test
    @DisplayName("Find an authtoken in DB")
    public void find() throws DataAccessException{
        AuthtokenDAO authtokenDAO = new AuthtokenDAO(db.getConnection());
        AuthToken authToken = new AuthToken("heyo", "hiya");
        authtokenDAO.insert(authToken);
        assertNotNull(authtokenDAO.findAuthtoken("heyo"));
        assertEquals(authToken, authtokenDAO.findAuthtoken("heyo"));
    }

    @Test
    @DisplayName("Insert an authtoken into db then find it")
    public void insert() throws DataAccessException {
        AuthtokenDAO authtokenDAO = new AuthtokenDAO(db.getConnection());
        AuthToken authToken = new AuthToken("israel", "jacob");
        AuthToken test = new AuthToken("israel", "jacob");
        authtokenDAO.insert(authToken);
        assertNotNull(authtokenDAO.findAuthtoken("israel"));
        assertEquals(test, authtokenDAO.findAuthtoken("israel"));
    }

    @Test
    @DisplayName("Insert duplicate authtoken in db")
    public void insertDuplicate() throws DataAccessException {
        AuthtokenDAO authtokenDAO = new AuthtokenDAO(db.getConnection());
        AuthToken authToken = new AuthToken("heyo", "hiya");
        authtokenDAO.insert(authToken);
        assertThrows(DataAccessException.class, () -> {authtokenDAO.insert(authToken);});
    }

    @Test
    @DisplayName("clear authtoken table from db")
    public void clear() throws DataAccessException {
        AuthtokenDAO authtokenDAO = new AuthtokenDAO(db.getConnection());
        AuthToken authToken = new AuthToken("heyo", "hiya");
        authtokenDAO.insert(authToken);
        assertNotNull(authtokenDAO.findAuthtoken("heyo"));
        authtokenDAO.clear();
        assertNull(authtokenDAO.findAuthtoken("heyo"));
    }

}
