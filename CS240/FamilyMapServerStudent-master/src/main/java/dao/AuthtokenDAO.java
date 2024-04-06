package dao;

import model.AuthToken;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class AuthtokenDAO {

    private final Connection conn;

    public AuthtokenDAO(Connection conn) {
        this.conn = conn;
    }

    public void insert(AuthToken authToken) throws DataAccessException {

        String sql = "INSERT INTO authtoken (authtoken, username) VALUES(?,?)";

        try(PreparedStatement statement = conn.prepareStatement(sql)) {
            statement.setString(1, authToken.getAuthtoken());
            statement.setString(2, authToken.getUsername());

            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error occurred while trying to insert authtoken into db");
        }
    }

    public AuthToken findAuthtoken(String authTokenString) throws DataAccessException {
        AuthToken authToken;
        ResultSet rs;
        String sql = "SELECT * FROM authtoken WHERE authtoken = ?";

        try(PreparedStatement statement = conn.prepareStatement(sql)) {
            statement.setString(1, authTokenString);
            rs = statement.executeQuery();
            if(rs.next()) {
                authToken = new AuthToken(rs.getString("authtoken"), rs.getString("username"));
                return authToken;
            }
            else return null;
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error occurred while trying to retrieve authtoken from db");
        }
    }

    public AuthToken findUser(String username) throws DataAccessException {
        AuthToken authToken;
        ResultSet rs;
        String sql = "SELECT * FROM authtoken WHERE username = ?";

        try(PreparedStatement statement = conn.prepareStatement(sql)) {
            statement.setString(1, username);
            rs = statement.executeQuery();
            if(rs.next()) {
                authToken = new AuthToken(rs.getString("authtoken"), rs.getString("username"));
                return authToken;
            }
            else return null;
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error occurred while trying to retrieve authtoken from db");
        }
    }

    public void clear() throws DataAccessException {
        String sql = "DELETE FROM authtoken";

        try(PreparedStatement statement = conn.prepareStatement(sql)) {
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error occurred while trying to clear authtoken table");
        }
    }
}
