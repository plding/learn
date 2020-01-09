// ch03/Sorting.java
import java.util.*;
import static java.util.Comparator.comparing;

public class Sorting {
    public static void main(String[] args) {
        Apple[] apples = { new Apple(80, "green"), new Apple(155, "green"), new Apple(120, "red") };

        List<Apple> inventory1 = Arrays.asList(apples);
        inventory1.sort(new Comparator<Apple>() {
            @Override
            public int compare(Apple a1, Apple a2) {
                return a1.getWeight().compareTo(a2.getWeight());
            }
        });
        System.out.println(inventory1);

        List<Apple> inventory2 = Arrays.asList(apples);
        inventory2.sort((Apple a1, Apple a2) -> a1.getWeight().compareTo(a2.getWeight()));
        System.out.println(inventory2);

        List<Apple> inventory3 = Arrays.asList(apples);
        inventory3.sort(comparing(Apple::getWeight));
        System.out.println(inventory3);
    }
}
