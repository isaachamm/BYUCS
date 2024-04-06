package Response;

import model.Person;

/**
 * result of /person
 */
public class PersonResponse extends ResponseBase {


    public PersonResponse(Person[] data, boolean success) {
        this.data = data;
        this.success = success;
    }

    public PersonResponse(String message, boolean success) {
        this.message = message;
        this.success = success;
    }

    /**
     * array of persons related to the person (family members of the person)
     */
    private Person[] data;

    public Person[] getAncestors() {
        return data;
    }

    public void setAncestors(Person[] ancestors) {
        this.data = ancestors;
    }
}
