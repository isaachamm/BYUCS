package Response;

import model.Event;

/**
 * result of /event
 */
public class EventResponse extends ResponseBase{

    public EventResponse(String message, boolean success) {
        this.message = message;
        this.success = success;
    }

    public EventResponse(Event[] data) {
        this.data = data;
        this.success = true;
    }

    /**
     * array of all event objects associated with a user
     */
    Event[] data;

    public Event[] getData() {
        return data;
    }

    public void setData(Event[] data) {
        this.data = data;
    }
}
