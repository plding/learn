// streams/StreamOfRandoms.java
import java.util.*;
import java.util.stream.*;

public class StreamOfRandoms {
    static Random rand = new Random(47);

    public static void main(String[] args) {
        Stream.of(1, 2, 3, 4, 5)
            .flatMapToInt(i -> IntStream.concat(
                    rand.ints(0, 100).limit(1), IntStream.of(-1)))
            .forEach(n -> System.out.format("%d ", n));
    }
}
