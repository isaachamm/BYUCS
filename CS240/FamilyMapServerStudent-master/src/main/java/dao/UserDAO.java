package dao;

import model.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * This is the DAO to access the user table in the db
 */

public class UserDAO {

    private final Connection conn;

    public UserDAO(Connection conn) {
        this.conn = conn;
    }

    /**
     * This function inserts a User object into the user table
     *
     * @param user contains the information that will get added to the user table
     * @throws DataAccessException if there's a problem accessing the SQL database
     */
    public void insert(User user) throws DataAccessException {

        String sql = "INSERT INTO user (username, password, email, firstName, lastName," +
                "gender, personID) VALUES(?,?,?,?,?,?,?)";

        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, user.getUsername());
            stmt.setString(2, user.getPassword());
            stmt.setString(3, user.getEmail());
            stmt.setString(4, user.getFirstName());
            stmt.setString(5, user.getLastName());
            stmt.setString(6, user.getGender());
            stmt.setString(7, user.getPersonID());

            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered while inserting a user into the database");
        }
    }

    /**
     * Validates a user – checks to see if username and password are in database
     *
     * @param username string for the username
     * @param password string for the password
     * @return true/false after checking if user and password are in the database
     * @throws DataAccessException if there's a problem accessing the SQL database
     */
    public boolean validate(String username, String password) throws DataAccessException {
        String sql = "SELECT * FROM user WHERE username = ? AND password = ?";
        ResultSet rs;

        try (PreparedStatement statement = conn.prepareStatement(sql)) {
            statement.setString(1, username);
            statement.setString(2, password);
            rs = statement.executeQuery();
            return rs.next();

        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error occurred while trying to validate user");
        }
    }

    /**
     * This function queries the database to find a User based off of their userID
     *
     * @param userID a string that holds the userID used to identify the user to find
     * @return a User object of the found user; else null
     * @throws DataAccessException thrown if there's a problem accessing the SQL database
     */
    public User find(String userID) throws DataAccessException {
        User user;
        ResultSet rs;
        String sql = "SELECT * FROM user WHERE username = ?";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, userID);
            rs = stmt.executeQuery();
            if(rs.next()) {
                user = new User(rs.getString("username"), rs.getString("password"),
                        rs.getString("email"), rs.getString("firstName"), rs.getString("lastName"),
                        rs.getString("gender"), rs.getString("personID"));
                return user;
            } else {
                return null;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered trying to find a user in the database");
        }
    }

    /**
     * clears the user table in the database
     *
     * @throws DataAccessException if there's a problem accessing the SQL database
     */
    public void clear() throws DataAccessException {
        String sql = "DELETE FROM user";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered while clearing the event table");
        }
    }
}
