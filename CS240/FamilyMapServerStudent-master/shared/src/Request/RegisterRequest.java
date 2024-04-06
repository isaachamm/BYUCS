package Request;

/**
 * Receives info from the RegisterHandler through /user/register. Holds
 *  the data for the RegisterService.
 */
public class RegisterRequest {
    public RegisterRequest(String username, String password, String email, String firstName, String lastName, String gender) {
        this.username = username;
        this.password = password;
        this.email = email;
        this.firstName = firstName;
        this.lastName = lastName;
        this.gender = gender;
    }

    /**
     * the user-to-register's username
     */
    private String username;

    /**
     * the user-to-register's password
     */
    private String password;

    /**
     * the user-to-register's email
     */
    private String email;

    /**
     * the user-to-register's first name
     */
    private String firstName;

    /**
     * the user-to-register's last name
     */
    private String lastName;

    /**
     * the user-to-register's gender (either "f" or "m")
     */
    private String gender;

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

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }
}
