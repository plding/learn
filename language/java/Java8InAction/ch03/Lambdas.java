// ch03/Lambdas.java
import java.util.*;

public class Lambdas {
    public static void main(String[] args) {
        Runnable r = () -> System.out.println("Hello!");
        r.run();

        List<Apple> inventory = Arrays.asList(new Apple(80, "green"), new Apple(155, "green"), new Apple(120, "red"));

        List<Apple> greenApples = filter(inventory, (Apple a) -> "green".equals(a.getColor()));
        System.out.println(greenApples);

        Comparator<Apple> c = (Apple a1, Apple a2) -> a1.getWeight().compareTo(a2.getWeight());
        inventory.sort(c);
        System.out.println(inventory);
    }

    public static List<Apple> filter(List<Apple> inventory, ApplePredicate p) {
        List<Apple> result = new ArrayList<>();
        for (Apple apple : inventory) {
            if (p.test(apple)) {
                result.add(apple);
            }
        }
        return result;
    }

    private interface ApplePredicate {
        boolean test(Apple a);
    }
}
