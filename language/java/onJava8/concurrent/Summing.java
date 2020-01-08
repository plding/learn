// concurrent/Summing.java
import java.util.stream.*;
import java.util.function.*;
import onjava.Timer;

public class Summing {

    static void timeTest(String id, long checkValue, LongSupplier operation) {
        System.out.print(id + ": ");
        Timer timer = new Timer();
        long result = operation.getAsLong();
        if (result == checkValue)
            System.out.println(timer.duration() + "ms");
        else
            System.out.format("result: %d%ncheckValue: %d%n", result, checkValue);
    }

    public static final int SZ = 1_000_000_000;
    public static final long CHECK = (long) SZ * ((long) SZ + 1) / 2;

    public static void main(String[] args) {
        System.out.println(CHECK);
        timeTest("Sum Stream", CHECK, () -> LongStream.rangeClosed(0, SZ).sum());
        timeTest("Sum Stream Parallel", CHECK, () -> LongStream.rangeClosed(0, SZ).parallel().sum());
        timeTest("Sum Iterated", CHECK, () -> LongStream.iterate(0, i -> i + 1).limit(SZ + 1).sum());
        // Slower & runs out of memory
        // timeTest("Sum Iterated Parallel", CHECK, () ->
        //        LongStream.iterate(0, i -> i + 1).parallel().limit(SZ + 1).sum());
    }
}
