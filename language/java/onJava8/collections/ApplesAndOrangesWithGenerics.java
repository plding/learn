// collections/ApplesAndOrangesWithGenerics.java
import java.util.*;

public class ApplesAndOrangesWithGenerics {
    public static void main(String[] args) {
        ArrayList<Apple> apples = new ArrayList<>();
        for (int i = 0; i < 3; i++) {
            apples.add(new Apple());
        }
        // Compile-time error:
        // apples.add(new Orange());
        for (Apple apple : apples) {
            System.out.println(apple.id());
        }
    }
}
