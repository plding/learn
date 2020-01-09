// streams/ForEach.java
import java.util.*;
import java.util.stream.*;
import static streams.RandInts.*;

public class ForEach {
    static final int SZ = 14;
    public static void main(String[] args) {
        rands().limit(SZ).forEach(n -> System.out.format("%d ", n));
        System.out.println();

        rands().limit(SZ).parallel().forEach(n -> System.out.format("%d ", n));
        System.out.println();

        rands().limit(SZ).parallel().forEachOrdered(n -> System.out.format("%d ", n));
        System.out.println();
    }
}
