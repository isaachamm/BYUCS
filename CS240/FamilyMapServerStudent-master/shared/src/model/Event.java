package model;

import java.util.Objects;

/**
 * The model class for Event objects.
 * Contains all of the same data that the SQL Event table in the db will have
 */
public class Event {

    /**
     * this event's id
     */
    private String eventID;

    /**
     * username of the user associated with this event
     */
    private String associatedUsername;

    /**
     * id of the person associated with this event
     */
    private String personID;

    /**
     * latitude of event's location
     */
    private Float latitude;

    /**
     * longitude of event's location
     */
    private Float longitude;

    /**
     * country of event's location
     */
    private String country;

    /**
     * city of event's location
     */
    private String city;

    /**
     * the type of event
     */
    private String eventType;

    /**
     * the year the event occurred
     */
    private Integer year;

    /**
     * constructor to fill an Event object with full data
     *
     * @param eventID id of this event
     * @param username username of user associated with this event
     * @param personID id of person associated with this event
     * @param latitude latitude of this event
     * @param longitude longitude of event
     * @param country country where event took place
     * @param city city where event took place
     * @param eventType the type of event
     * @param year year the event occurred
     */
    public Event(String eventID, String username, String personID, Float latitude, Float longitude,
                 String country, String city, String eventType, Integer year) {
        this.eventID = eventID;
        this.associatedUsername = username;
        this.personID = personID;
        this.latitude = latitude;
        this.longitude = longitude;
        this.country = country;
        this.city = city;
        this.eventType = eventType;
        this.year = year;
    }

    public String getEventID() {
        return eventID;
    }

    public void setEventID(String eventID) {
        this.eventID = eventID;
    }

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

    public Float getLatitude() {
        return latitude;
    }

    public void setLatitude(Float latitude) {
        this.latitude = latitude;
    }

    public Float getLongitude() {
        return longitude;
    }

    public void setLongitude(Float longitude) {
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

    public Integer getYear() {
        return year;
    }

    public void setYear(Integer year) {
        this.year = year;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Event event = (Event) o;
        return Objects.equals(eventID, event.eventID) && Objects.equals(associatedUsername, event.associatedUsername) && Objects.equals(personID, event.personID) && Objects.equals(latitude, event.latitude) && Objects.equals(longitude, event.longitude) && Objects.equals(country, event.country) && Objects.equals(city, event.city) && Objects.equals(eventType, event.eventType) && Objects.equals(year, event.year);
    }

}
