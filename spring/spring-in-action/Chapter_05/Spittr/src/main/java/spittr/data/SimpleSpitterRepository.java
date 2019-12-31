package spittr.data;

import org.springframework.stereotype.Repository;

import spittr.Spitter;

@Repository
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
