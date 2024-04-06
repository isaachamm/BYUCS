package JUnitTests;

import Response.*;
import Service.*;
import Request.LoadRequest;
import Request.LoginRequest;
import Request.RegisterRequest;
import Response.*;
import com.google.gson.Gson;
import dao.*;
import model.AuthToken;
import model.Event;
import model.Person;
import model.User;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import static org.junit.jupiter.api.Assertions.*;

public class ServiceTests {

    private RegisterRequest registerRequest = new RegisterRequest("HARRY", "POTTER",
            "harrypot@gmail.com", "ron", "weasley", "m");
    private LoginRequest loginRequest = new LoginRequest("HARRY", "POTTER");


    @BeforeEach
    public void setup() {
        ClearService service = new ClearService();
        service.clear();
    }

    @Test
    @DisplayName("Valid Load")
    public void validLoad() {
        LoadRequest loadRequest = requestLoadData();
        LoadService loadService = new LoadService();
        LoadResponse loadResponse = loadService.load(loadRequest);

        String message = "Successfully added " + loadRequest.getUsers().length + " users, " +
                loadRequest.getPersons().length + " persons, and " +
                loadRequest.getEvents().length + " events to the database";

        assertEquals(loadResponse.getMessage(), message);
        assertTrue(loadResponse.isSuccess());
    }

    @Test
    @DisplayName("Fail Load")
    public void failLoad() {
        LoadRequest loadRequest = new LoadRequest();

        User user = createUser();
        User user1 = createUser();
        User[] users = new User[2];
        users[0] = user;
        users[1] = user1;

        Event event = createEvent();
        Event event1 = createEvent();
        Event[] events = new Event[2];
        events[0] = event;
        events[1] = event1;

        Person person = createPerson();
        Person person1 = createPerson();
        Person[] persons = new Person[2];
        persons[0] = person;
        persons[1] = person1;

        loadRequest.setEvents(events);
        loadRequest.setPersons(persons);
        loadRequest.setUsers(users);
        LoadService loadService = new LoadService();
        LoadResponse actualResponse = loadService.load(loadRequest);
        LoadResponse expectedResponse = new LoadResponse("Error: could not load data to database", false);
        assertEquals(expectedResponse.getMessage(), actualResponse.getMessage());
        assertFalse(actualResponse.isSuccess());
    }

    @Test
    @DisplayName("Valid Login Test")
    public void validLogin() {
        loadData();

        LoginRequest loginRequest = new LoginRequest("sheila", "parker");

        LoginService loginService = new LoginService();
        LoginResponse actualResponse = loginService.login(loginRequest);
        assertTrue(actualResponse.isSuccess());
        assertEquals("sheila", actualResponse.getUsername());

    }

    @Test
    @DisplayName("Invalid Login (User not in db)")
    public void invalidLogin() {

        //tries to find a user not in db

        loadData();

        LoginRequest loginRequest = new LoginRequest("harry", "shutterspeed");

        LoginService loginService = new LoginService();
        LoginResponse actualResponse = loginService.login(loginRequest);

        assertFalse(actualResponse.isSuccess());
        assertEquals("Error: User not found in db", actualResponse.getMessage());

    }

    @Test
    @DisplayName("Valid Register Test")
    public void validRegister() {

        RegisterService registerService = new RegisterService();
        RegisterResponse actualResponse = registerService.register(this.registerRequest);

        assertTrue(actualResponse.isSuccess());
        assertEquals("HARRY", actualResponse.getUsername());

    }

    @Test
    @DisplayName("Invalid Register Test")
    public void invalidRegister() {

        //tries to register a user twice

        RegisterService registerService = new RegisterService();
        registerService.register(this.registerRequest);
        RegisterResponse actualResponse = registerService.register(this.registerRequest);

        assertFalse(actualResponse.isSuccess());
        assertEquals("Error: Data Access Exception in Register Service", actualResponse.getMessage());
    }

    @Test
    @DisplayName("Valid EventID Test")
    public void validEventID() {

        loadData();

        LoginRequest loginRequest1 = new LoginRequest("sheila", "parker");
        LoginService loginService = new LoginService();
        loginService.login(loginRequest1);

        EventIdService eventIdService = new EventIdService();
        //this eventID comes from the load data
        EventIdResponse eventIdResponse = eventIdService.getEvent("Betty_Death", "sheila");

        assertTrue(eventIdResponse.isSuccess());
        assertEquals("sheila", eventIdResponse.getAssociatedUsername());

    }

    @Test
    @DisplayName("Invalid EventID Test")
    public void invalidEventID() {

        loadData();

        LoginRequest loginRequest1 = new LoginRequest("sheila", "parker");
        LoginService loginService = new LoginService();
        loginService.login(loginRequest1);

        EventIdService eventIdService = new EventIdService();
        EventIdResponse eventIdResponse = eventIdService.getEvent("Not an event", "sheila");

        assertFalse(eventIdResponse.isSuccess());
        assertEquals("Error: invalid eventID parameter", eventIdResponse.getMessage());
    }

    @Test
    @DisplayName("Valid Events test")
    public void validEvents() {

        loadData();

        LoginRequest loginRequest1 = new LoginRequest("sheila", "parker");
        LoginService loginService = new LoginService();
        LoginResponse loginResponse = loginService.login(loginRequest1);

        String authTokenString = loginResponse.getAuthtoken();
        AuthToken authToken = new AuthToken(authTokenString, "sheila");

        EventService eventService = new EventService();
        assertEquals(16, eventService.getEvents(authToken).getData().length);

    }

    @Test
    @DisplayName("Invalid Events Test")
    public void invalidEvents() {

        // Event service returns 0 events for somebody not in db

        AuthToken authToken = new AuthToken("fake authtoken", "sheila");

        EventService eventService = new EventService();
        EventResponse eventResponse = eventService.getEvents(authToken);

        assertEquals(0, eventResponse.getData().length);


    }

    @Test
    @DisplayName("Valid personID Test")
    public void validPersonID() {

        loadData();

        LoginRequest loginRequest1 = new LoginRequest("sheila", "parker");
        LoginService loginService = new LoginService();
        loginService.login(loginRequest1);

        PersonIdService personIdService = new PersonIdService();
        PersonIdResponse personIdResponse = personIdService.getPerson("Davis_Hyer", "sheila");

        assertTrue(personIdResponse.isSuccess());
        assertEquals("sheila", personIdResponse.getAssociatedUsername());

    }

    @Test
    @DisplayName("Invalid personID Test")
    public void invalidPersonID() {

        PersonIdService personIdService = new PersonIdService();
        PersonIdResponse personIdResponse = personIdService.getPerson("Not a person", "sheila");

        assertFalse(personIdResponse.isSuccess());
        assertEquals("Error: invalid personID parameter", personIdResponse.getMessage());
    }

    @Test
    @DisplayName("Valid Persons Test")
    public void validPersons() {

        loadData();

        LoginRequest loginRequest1 = new LoginRequest("sheila", "parker");
        LoginService loginService = new LoginService();
        LoginResponse loginResponse = loginService.login(loginRequest1);

        String authTokenString = loginResponse.getAuthtoken();
        AuthToken authToken = new AuthToken(authTokenString, "sheila");

        PersonService personService = new PersonService();
        assertEquals(8, personService.getPeople(authToken).getAncestors().length);
    }

    @Test
    @DisplayName("Invalid Persons Test")
    public void invalidPersons() {

        // Person service returns 0 persons for somebody not in db

        AuthToken authToken = new AuthToken("fake authtoken", "sheila");

        PersonService personService = new PersonService();
        PersonResponse personResponse = personService.getPeople(authToken);

        assertEquals(0, personResponse.getAncestors().length);
    }

    @Test
    @DisplayName("Valid Fill Test")
    public void validFill() throws DataAccessException {

        RegisterService registerService = new RegisterService();
        registerService.register(this.registerRequest);

        FillService fillService = new FillService();
        FillResponse fillResponse = fillService.fill("HARRY", 4);

        assertTrue(fillResponse.isSuccess());
        assertEquals("Successfully added 31 persons and 92 events to the database.", fillResponse.getMessage());

        LoginService loginService = new LoginService();
        LoginResponse loginResponse = loginService.login(this.loginRequest);

        String authTokenString = loginResponse.getAuthtoken();
        AuthToken authToken = new AuthToken(authTokenString, "HARRY");

        PersonService personService = new PersonService();
        assertEquals(31, personService.getPeople(authToken).getAncestors().length);

        EventService eventService = new EventService();
        assertEquals(92, eventService.getEvents(authToken).getData().length);

    }

    @Test
    @DisplayName("Invalid Fill Test")
    public void invalidFill() throws DataAccessException {

        //tries to run fill with a negative integer
        loadData();

        FillService fillService = new FillService();
        FillResponse fillResponse = fillService.fill("sheila", -4);

        assertFalse(fillResponse.isSuccess());
        assertEquals("Error: generations to fill must be non-negative", fillResponse.getMessage());

    }

    @Test
    @DisplayName("Clear test 1")
    public void clearTestOne() throws DataAccessException {
        loadData();

        ClearService service = new ClearService();
        ClearResponse actualResponse = service.clear();
        ClearResponse expectedResponse = new ClearResponse("Clear Succeeded", true);

        assertEquals(actualResponse.getMessage(), expectedResponse.getMessage());
        assertTrue(actualResponse.isSuccess());
    }


    @Test
    @DisplayName("Clear Test 2")
    public void clearTestTwo() {

        loadData();

        LoginRequest loginRequest1 = new LoginRequest("sheila", "parker");
        LoginService loginService = new LoginService();
        LoginResponse loginResponse = loginService.login(loginRequest1);

        assertTrue(loginResponse.isSuccess());

        ClearService service = new ClearService();
        ClearResponse actualResponse = service.clear();

        loginResponse = loginService.login(this.loginRequest);

        assertFalse(loginResponse.isSuccess());

    }

    private LoadRequest requestLoadData() {
        try {
            Gson gson = new Gson();
            String loadString = readData("passoffFiles/LoadData.json");
            LoadRequest loadRequest = gson.fromJson(loadString, LoadRequest.class);
            return loadRequest;
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return null;
        }

    }

    private void loadData() {
        LoadRequest loadRequest = requestLoadData();
        LoadService loadService = new LoadService();
        LoadResponse loadResponse = loadService.load(loadRequest);
    }

    private String readData(String filePath) throws FileNotFoundException {
        File file = new File(filePath);

        Scanner scanner = new Scanner(file);
        StringBuilder sb = new StringBuilder();

        while(scanner.hasNext()) {
            sb.append(scanner.nextLine());
        }

        return sb.toString();
    }

    private User createUser() {
        User user = new User("isaac", "isuck", "hamm4", "isaacrh",
                "hamm", "m", "123456");
        return user;
    }

    private Person createPerson() {
        Person person = new Person("123456", "isaac", "Michael", "Jordan",
                "m", "def", "hig", "jfk");
        return person;
    }

    private Event createEvent() {
        Event event = new Event("abc123", "isaac", "123456", (float) 25, (float) 25,
                "USA", "grantsville", "birthday", 1999);
        return event;
    }



}
