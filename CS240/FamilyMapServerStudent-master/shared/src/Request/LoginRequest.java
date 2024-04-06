package Request;

/**
 * Receives info from the LoginHandler through /user/login. Holds
 *  the data for the LoginService.
 */
public class LoginRequest {

    public LoginRequest(String username, String password) {
        this.username = username;
        this.password = password;
    }

    /**
     * the username for login
     */
    private String username;

    /**
     * the password for login
     */
    private String password;

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
