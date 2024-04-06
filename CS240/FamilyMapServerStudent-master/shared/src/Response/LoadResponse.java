package Response;

/**
 * result of /load
 */
public class LoadResponse extends ResponseBase{


    public LoadResponse(String message, boolean success) {
        this.message = message;
        this.success = success;
    }

}
