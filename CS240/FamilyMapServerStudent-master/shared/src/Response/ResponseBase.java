package Response;

public abstract class ResponseBase {


    /**
     * error message
     */
    protected String message;

    /**
     * true for success, false for failure
     */
    protected boolean success;

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
