// collections/SetOfInteger.java
import java.util.*;

public class SetOfInteger {
    public static void main(String[] args) {
        Random rand = new Random(47);
        Set<Integer> intset = new HashSet<>();
        for (int i = 0; i < 10000; ++i)
            intset.add(rand.nextInt(30));
        System.out.println(intset);
    }
}
