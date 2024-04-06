package dao;

import model.Person;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * this is the DAO to access the Person table in the db
 */
public class PersonDAO {

    private final Connection conn;

    public PersonDAO(Connection conn) {
        this.conn = conn;
    }

    /**
     * This function inserts a person object into the person table
     *
     * @param person this person object contains all the information that will go into the person table
     * @throws DataAccessException if there's a problem accessing the SQL database
     */
    public void insert(Person person) throws DataAccessException {
        String sql = "INSERT INTO person (personID, associatedUsername, firstName, lastName, gender," +
                "fatherID, motherID, spouseID) VALUES (?,?,?,?,?,?,?,?)";

        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, person.getPersonID());
            stmt.setString(2, person.getAssociatedUsername());
            stmt.setString(3, person.getFirstName());
            stmt.setString(4, person.getLastName());
            stmt.setString(5, person.getGender());
            stmt.setString(6, person.getFatherID());
            stmt.setString(7, person.getMotherID());
            stmt.setString(8, person.getSpouseID());

            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error ecountered trying to insert Person into DB");
        }
    }

    /**
     * This function queries the database to find a person based off of their personID
     *
     * @param personID a string that holds the personID used to identify the person to find
     * @return a Person object of the person if found; else null
     * @throws DataAccessException if there's a problem accessing the SQL database
     */
    public Person find(String personID) throws DataAccessException {

        String sql = "SELECT * FROM person WHERE personID = ?";
        ResultSet rs;
        Person person;

        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, personID);
            rs = stmt.executeQuery();
            if (rs.next()) {
                person = new Person(rs.getString("personID"), rs.getString("associatedUsername"),
                        rs.getString("firstName"), rs.getString("lastName"),
                        rs.getString("gender"), rs.getString("fatherID"),
                        rs.getString("motherID"), rs.getString("spouseID"));
                return person;
            } else {
                return null;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error occurred trying to query person from db");
        }
    }

    /**
     * clears the person table in the database
     *
     * @throws DataAccessException if there's a problem accessing the SQL database
     */
    public void clear() throws DataAccessException {
        String sql = "DELETE FROM person";

        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered trying to clear person table from db");
        }
    }

    /**
     * Clears all events for the user with the provided username
     *
     * @param username username of the associated user
     * @throws DataAccessException if there's a problem with SQL or database
     */
    public void clear(String username) throws DataAccessException {
        String sql = "DELETE FROM person WHERE associatedUsername = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);

            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered while clearing the event table");
        }
    }

    /**
     * This function gets all the person objects associated with a user (i.e., that user's ancestors)
     *
     * @param username string of the user to get
     * @return a list of Person objects for the indicated user; else null
     * @throws DataAccessException if there's a problem accessing the SQL database
     */
    public List<Person> findAncestorsForUser(String username) throws DataAccessException {

        String sql = "SELECT * FROM person WHERE associatedUsername = ?";
        ResultSet rs;
        List<Person> people = new ArrayList<Person>();

        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            rs = stmt.executeQuery();
            while (rs.next()) {
                Person person = new Person(rs.getString("personID"), rs.getString("associatedUsername"),
                        rs.getString("firstName"), rs.getString("lastName"),
                        rs.getString("gender"), rs.getString("fatherID"),
                        rs.getString("motherID"), rs.getString("spouseID"));
                people.add(person);
            }
            return people;
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered trying to query people from db");
        }
    }
}
