package Response;

/**
 * response to /user/register
 */
public class RegisterResponse extends ResponseBase {

    /**
     * the returned authtoken
     */
    private String authtoken;

    /**
     * username of the created user
     */
    private String username;

    /**
     * ID for the new user
     */
    private String personID;

    public RegisterResponse(String authtoken, String username, String personID, boolean success) {
        this.authtoken = authtoken;
        this.username = username;
        this.personID = personID;
        this.success = success;
    }

    public RegisterResponse(boolean success, String message) {
        this.authtoken = null;
        this.username = null;
        this.personID = null;
        this.success = success;
        this.message = message;
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

    public String getPersonID() {
        return personID;
    }

    public void setPersonID(String personID) {
        this.personID = personID;
    }
}
