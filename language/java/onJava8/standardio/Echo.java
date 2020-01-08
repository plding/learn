// standardio/Echo.java
// How to read from standard input
import java.io.*;
import onjava.TimedAbort;

public class Echo {
    public static void main(String[] args) {
        TimedAbort abort = new TimedAbort(2);
        new BufferedReader(new InputStreamReader(System.in))
            .lines()
            .peek(ln -> abort.restart())
            .forEach(System.out::println);
    }
}
