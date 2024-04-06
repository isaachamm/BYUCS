package Response;

/**
 * Result of /event/[eventID]
 */
public class EventIdResponse extends ResponseBase {

    /**
     * the user requesting the event
     */
    private String associatedUsername;

    /**
     * the event's id
     */
    private String eventID;

    /**
     * the id of the person with whom the event is associated
     */
    private String personID;

    /**
     * latitude coordinate of the event
     */
    private float latitude;

    /**
     * longitude coordiante of the event
     */
    private float longitude;

    /**
     * country where the event took place
     */
    private String country;

    /**
     * city where the event took place
     */
    private String city;

    /**
     * the type of event (e.g., "birth")
     */
    private String eventType;

    /**
     * the year that the event took place
     */
    private int year;

    public EventIdResponse(String message, boolean success) {
        this.message = message;
        this.success = success;
    }

    public EventIdResponse(String associatedUsername, String eventID, String personID, float latitude, float longitude, String country, String city, String eventType, int year) {
        this.associatedUsername = associatedUsername;
        this.eventID = eventID;
        this.personID = personID;
        this.latitude = latitude;
        this.longitude = longitude;
        this.country = country;
        this.city = city;
        this.eventType = eventType;
        this.year = year;
        this.success = true;
    }

    public EventIdResponse(String associatedUsername, String eventID, String personID, float latitude, float longitude, String country, String city, String eventType, int year, String message, boolean success) {
        this.associatedUsername = associatedUsername;
        this.eventID = eventID;
        this.personID = personID;
        this.latitude = latitude;
        this.longitude = longitude;
        this.country = country;
        this.city = city;
        this.eventType = eventType;
        this.year = year;
        this.message = message;
        this.success = success;
    }

    public String getAssociatedUsername() {
        return associatedUsername;
    }

    public void setAssociatedUsername(String associatedUsername) {
        this.associatedUsername = associatedUsername;
    }

    public String getEventID() {
        return eventID;
    }

    public void setEventID(String eventID) {
        this.eventID = eventID;
    }

    public String getPersonID() {
        return personID;
    }

    public void setPersonID(String personID) {
        this.personID = personID;
    }

    public float getLatitude() {
        return latitude;
    }

    public void setLatitude(float latitude) {
        this.latitude = latitude;
    }

    public float getLongitude() {
        return longitude;
    }

    public void setLongitude(float longitude) {
        this.longitude = longitude;
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getEventType() {
        return eventType;
    }

    public void setEventType(String eventType) {
        this.eventType = eventType;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

}
