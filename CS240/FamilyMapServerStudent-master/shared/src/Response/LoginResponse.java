package Response;

/**
 * result of /user/login
 */
public class LoginResponse extends ResponseBase {

    public LoginResponse(String authtoken, String username, String personID, boolean success) {
        this.authtoken = authtoken;
        this.username = username;
        this.personID = personID;
        this.message = null;
        this.success = success;
    }

    public LoginResponse(String message, boolean success) {
        this.message = message;
        this.success = success;
    }

    /**
     * the authtoken associated with the user
     */
    private String authtoken;

    /**
     * username of the user
     */
    private String username;

    /**
     * id associated with the user
     */
    private String personID;

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

    public String getPersonID() {
        return personID;
    }

    public void setPersonID(String personID) {
        this.personID = personID;
    }
}
