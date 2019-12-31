package spittr.web;

import javax.validation.constraints.*;

public class SpittleForm {

    @NotNull
    @Size(min=1, max=140)
    private String message;

    private Double longitude;

    private Double latitude;

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public Double getLongitude() {
        return longitude;
    }

    public void setLongitude(Double longitude) {
        this.longitude = longitude;
    }

    public Double getLatitude() {
        return latitude;
    }

    public void setLatitude(Double latitude) {
        this.latitude = latitude;
    }
}
