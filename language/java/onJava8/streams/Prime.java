// streams/Prime.java
import java.util.stream.LongStream;
import static java.util.stream.LongStream.iterate;
import static java.util.stream.LongStream.rangeClosed;

public class Prime {
    public static Boolean isPrime(long n) {
        return rangeClosed(2, (long) Math.sqrt(n)).noneMatch(i -> n % i == 0);
    }

    public LongStream numbers() {
        return iterate(2, i -> i + 1).filter(Prime::isPrime);
    }

    public static void main(String[] args) {
        new Prime().numbers()
                   .limit(10)
                   .forEach(n -> System.out.format("%d ", n));
        System.out.println();

        new Prime().numbers()
                   .skip(90)
                   .limit(10)
                   .forEach(n -> System.out.format("%d ", n));
        System.out.println();
    }
}
