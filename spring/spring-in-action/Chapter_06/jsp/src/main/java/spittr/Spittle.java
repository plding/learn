package spittr;

import java.util.Date;

public class Spittle {

    private final Long id;
    private final String message;
    private final Date time;
    private final Double latitude;
    private final Double longitude;

    public Spittle(String message, Date time) {
        this(message, time, null, null);
    }

    public Spittle(String message, Date time, Double latitude, Double longitude) {
        this.id = null;
        this.message = message;
        this.time = time;
        this.latitude = latitude;
        this.longitude = longitude;
    }
}
