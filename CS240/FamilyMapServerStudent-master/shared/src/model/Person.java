package model;

import java.util.Objects;

/**
 * The model class for Person objects.
 * Contains all of the same data that the SQL Person table in the db will have
 */
public class Person {

    /**
     * the person's id
     */
    private String personID;

    /**
     * username of this person
     */
    private String associatedUsername;

    /**
     * this person's first name
     */
    private String firstName;

    /**
     * this person's last name
     */
    private String lastName;

    /**
     * this person's gender - either "f" or "m"
     */
    private String gender;

    /**
     * the id of this person's father
     */
    private String fatherID;

    /**
     * the id of this person's mother
     */
    private String motherID;

    /**
     * the id of this person's spouse
     */
    private String spouseID;

    /**
     * constructor to fill in all data for a person object
     * @param personID person's id
     * @param associatedUsername person's username
     * @param firstName person's first name
     * @param lastName person's last name
     * @param gender person's gender - either "f" or "m"
     * @param fatherID the id of this person's father
     * @param motherID the id of this person's mother
     * @param spouseID the id of this person's spouse
     */
    public Person(String personID, String associatedUsername, String firstName, String lastName, String gender, String fatherID, String motherID, String spouseID) {
        this.personID = personID;
        this.associatedUsername = associatedUsername;
        this.firstName = firstName;
        this.lastName = lastName;
        this.gender = gender;
        this.fatherID = fatherID;
        this.motherID = motherID;
        this.spouseID = spouseID;
    }

    public String getPersonID() {
        return personID;
    }

    public void setPersonID(String personID) {
        this.personID = personID;
    }

    public String getAssociatedUsername() {
        return associatedUsername;
    }

    public void setAssociatedUsername(String associatedUsername) {
        this.associatedUsername = associatedUsername;
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

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Person person = (Person) o;
        return Objects.equals(personID, person.personID) && Objects.equals(associatedUsername, person.associatedUsername) && Objects.equals(firstName, person.firstName) && Objects.equals(lastName, person.lastName) && Objects.equals(gender, person.gender) && Objects.equals(fatherID, person.fatherID) && Objects.equals(motherID, person.motherID) && Objects.equals(spouseID, person.spouseID);
    }


}
