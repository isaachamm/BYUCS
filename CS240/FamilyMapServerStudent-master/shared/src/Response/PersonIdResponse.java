package Response;

/**
 * result of /person/[personID]
 */
public class PersonIdResponse extends ResponseBase{

    public PersonIdResponse(String associatedUsername, String personID, String firstName, String lastName, String gender,
                            String fatherID, String motherID, String spouseID) {
        this.associatedUsername = associatedUsername;
        this.personID = personID;
        this.firstName = firstName;
        this.lastName = lastName;
        this.gender = gender;
        this.fatherID = fatherID;
        this.motherID = motherID;
        this.spouseID = spouseID;
        this.success = true;
    }

    public PersonIdResponse(String message, boolean success) {
        this.message = message;
        this.success = success;
    }

    /**
     * username of the person
     */
    private String associatedUsername;

    /**
     * the same ID given in the / request
     */
    private String personID;

    /**
     * first name of the person to get
     */
    private String firstName;

    /**
     * last name of the person to get
     */
    private String lastName;

    /**
     * gender either "f" or "m"
     */
    private String gender;

    /**
     * ID for the person's father
     */
    private String fatherID; //optional

    /**
     * ID for the person's mother
     */
    private String motherID; //optional

    /**
     * ID for the person's spouse
     */
    private String spouseID; //optional

    public String getAssociatedUsername() {
        return associatedUsername;
    }

    public void setAssociatedUsername(String associatedUsername) {
        this.associatedUsername = associatedUsername;
    }

    public String getPersonID() {
        return personID;
    }

    public void setPersonID(String personID) {
        this.personID = personID;
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

    public String getFatherID() {
        return fatherID;
    }

    public void setFatherID(String fatherID) {
        this.fatherID = fatherID;
    }

    public String getMotherID() {
        return motherID;
    }

    public void setMotherID(String motherID) {
        this.motherID = motherID;
    }

    public String getSpouseID() {
        return spouseID;
    }

    public void setSpouseID(String spouseID) {
        this.spouseID = spouseID;
    }
}
