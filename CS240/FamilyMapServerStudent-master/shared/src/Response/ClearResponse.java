package Response;

/**
 * result of calling clear
 */
public class ClearResponse {

    /**
     * either "Clear Succeeded" or Error
     */
    private String message;

    /**
     * true for success, false for failure
     */
    private boolean success;

    public ClearResponse(String message, boolean success) {
        this.message = message;
        this.success = success;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public boolean isSuccess() {
        return success;
    }

    public void setSuccess(boolean success) {
        this.success = success;
    }
}
