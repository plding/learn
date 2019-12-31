package spittr.data;

import org.springframework.stereotype.Component;
import spittr.Spitter;

@Component
public class SimpleSpitterRepository implements SpitterRepository {

    @Override
    public Spitter save(Spitter spitter) {
        return spitter;
    }

    @Override
    public Spitter findByUsername(String username) {
        return new Spitter(24L, "jbauer", "24hours", "Jack", "Bauer");
    }
}
