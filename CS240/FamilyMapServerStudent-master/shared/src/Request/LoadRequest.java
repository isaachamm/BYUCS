package Request;

import model.Event;
import model.Person;
import model.User;

/**
 * Receives info from the LoadHandler through /load. Holds
 *  the data for the LoadService class.
 */
public class LoadRequest {

    /**
     * Holds an array of users that will be uploaded to the database after clear
     */
    private User[] users;

    /**
     * Holds an array of persons that will be uploaded to the database after clear
     */
    private Person[] persons;

    /**
     * Holds an array of events that will be uploaded to the database after clear
     */
    private Event[] events;

    public User[] getUsers() {
        return users;
    }

    public void setUsers(User[] users) {
        this.users = users;
    }

    public Person[] getPersons() {
        return persons;
    }

    public void setPersons(Person[] persons) {
        this.persons = persons;
    }

    public Event[] getEvents() {
        return events;
    }

    public void setEvents(Event[] events) {
        this.events = events;
    }
}
