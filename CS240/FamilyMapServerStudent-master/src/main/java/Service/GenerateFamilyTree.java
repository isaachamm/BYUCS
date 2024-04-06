package Service;

import JsonHolders.JsonHolder;
import JsonHolders.Location;
import model.Event;
import model.Person;
import model.User;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.UUID;

public class GenerateFamilyTree {

    int eventsAdded;
    int personsAdded;
    int generations;
    String currUsername;
    private ArrayList<Event> events;
    private HashMap<String, Person> ancestors;
    private JsonHolder jsonHolder;

    public int getEventsAdded() {
        return eventsAdded;
    }

    public void setEventsAdded(int eventsAdded) {
        this.eventsAdded = eventsAdded;
    }

    public int getPersonsAdded() {
        return personsAdded;
    }

    public void setPersonsAdded(int personsAdded) {
        this.personsAdded = personsAdded;
    }

    public int getGenerations() {
        return generations;
    }

    public void setGenerations(int generations) {
        this.generations = generations;
    }

    public ArrayList<Event> getEvents() {
        return events;
    }

    public void setEvents(ArrayList<Event> events) {
        this.events = events;
    }

    public HashMap<String, Person> getAncestors() {
        return ancestors;
    }

    public void setAncestors(HashMap<String, Person> ancestors) {
        this.ancestors = ancestors;
    }

    public String getCurrUsername() {
        return currUsername;
    }

    public void setCurrUsername(String currUsername) {
        this.currUsername = currUsername;
    }

    public void generateAncestors(String gender, int generations, User user) throws FileNotFoundException {
        jsonHolder = new JsonHolder();
        jsonHolder.fillData();
        events = new ArrayList<>();
        ancestors = new HashMap<>();
        this.generations = generations;

        makeNewPerson(gender, generations, user);
    }

    public Person makeNewPerson(String gender, int generations, User user) {

        Person mother = null;
        Person father = null;

        if(generations > 0) {
            mother = makeNewPerson("f", generations - 1, user);
            father = makeNewPerson("m", generations - 1, user);

            ancestors.get(father.getPersonID()).setSpouseID(mother.getPersonID());
            ancestors.get(mother.getPersonID()).setSpouseID(father.getPersonID());

            String fatherMarriageID = UUID.randomUUID().toString();
            String motherMarriageID = UUID.randomUUID().toString();

            Location marriageLocation = getRandomLocation(jsonHolder);

            int fatherMarriageYear = (1900 + ((generations * 30) + 24));
            int motherMarriageYear = (1900 + ((generations* 30) + 24));

            Event fatherMarriage = new Event(fatherMarriageID, user.getUsername(), father.getPersonID(),
                    marriageLocation.getLatitude(), marriageLocation.getLongitude(), marriageLocation.getCountry(),
                    marriageLocation.getCity(), "marriage", fatherMarriageYear);
            events.add(fatherMarriage);

            Event motherMarriage = new Event(motherMarriageID, user.getUsername(), mother.getPersonID(),
                    marriageLocation.getLatitude(), marriageLocation.getLongitude(), marriageLocation.getCountry(),
                    marriageLocation.getCity(), "marriage", motherMarriageYear);
            events.add(motherMarriage);

        }

        String personID = UUID.randomUUID().toString();
        String firstName = null;
        int randomInt;

        if(gender.compareTo("f") == 0) {
            randomInt = (int) Math.floor(Math.random()*(jsonHolder.getFemaleNames().getFemaleNames().length));
            firstName = jsonHolder.getFemaleNames().getFemaleNames()[randomInt];
        }
        else {
            randomInt = (int) Math.floor(Math.random()*(jsonHolder.getMaleNames().getMaleNames().length));
            firstName = jsonHolder.getMaleNames().getMaleNames()[randomInt];
        }

        randomInt = (int) Math.floor(Math.random()*(jsonHolder.getSurnames().getSurnames().length));
        String lastName = jsonHolder.getSurnames().getSurnames()[randomInt];

        //this is to check to generate the person for the current user
        if(this.generations == generations) {
            personID = user.getPersonID();
            firstName = user.getFirstName();
            lastName = user.getLastName();
            gender = user.getGender();
        }

        Person person = new Person(personID, user.getUsername(), firstName, lastName, gender,
                null, null, null);
        if(father != null) {
            person.setFatherID(father.getPersonID());
            person.setMotherID(mother.getPersonID());
        }

        int personBirthYear = (1900 + (generations * 30));
        Location birthLocation = getRandomLocation(jsonHolder);
        String birthEventID = UUID.randomUUID().toString();
        Event birth = new Event(birthEventID, user.getUsername(), person.getPersonID(), birthLocation.getLatitude(),
                birthLocation.getLongitude(), birthLocation.getCountry(), birthLocation.getCity(), "birth",
                personBirthYear);
        events.add(birth);

        String deathEventID = UUID.randomUUID().toString();
        Location deathLocation = getRandomLocation(jsonHolder);
        int personDeathYear = personBirthYear + 70;
        Event death = new Event(deathEventID, user.getUsername(), person.getPersonID(), deathLocation.getLatitude(),
                deathLocation.getLongitude(), deathLocation.getCountry(), deathLocation.getCity(), "death",
                personDeathYear);
        events.add(death);

        ancestors.put(person.getPersonID(), person);

        return person;
    }

    public Location getRandomLocation(JsonHolder jsonHolder) {
        int randomInt = (int) Math.floor(Math.random()*(jsonHolder.getLocationData().getData().length));
        Location location = jsonHolder.getLocationData().getData()[randomInt];
        return location;
    }
}
