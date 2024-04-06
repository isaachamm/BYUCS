package Response;

/**
 * result of /fill/[username]/{generations}
 */
public class FillResponse extends ResponseBase {

    public FillResponse(String message, boolean success) {
        this.message = message;
        this.success = success;
    }

}
