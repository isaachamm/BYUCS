package model;

import java.util.Objects;

/**
 * model class for the authtoken objects.
 * Stores data needed for authtoken validation
 */
public class AuthToken {

    /**
     * this is where the authtoken is stored in java
     */
    private String authtoken;

    /**
     * the username associated with the above authtoken
     */
    private String username;

    /**
     * this constructor fills the data for an authtoken and user
     *
     * @param authtoken the authtoken associated with the user
     * @param username the user associated with the authtoken
     */
    public AuthToken(String authtoken, String username) {
        this.authtoken = authtoken;
        this.username = username;
    }

    public String getAuthtoken() {
        return authtoken;
    }

    public void setAuthtoken(String authtoken) {
        this.authtoken = authtoken;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AuthToken authToken = (AuthToken) o;
        return Objects.equals(authtoken, authToken.authtoken) && Objects.equals(username, authToken.username);
    }

}
