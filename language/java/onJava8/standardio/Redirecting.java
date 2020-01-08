// standardio/Redirecting.java
// Demonstrates standard I/O redirection
import java.io.*;

public class Redirecting {
    public static void main(String[] args) {
        PrintStream console = System.out;
        try (
            BufferedInputStream in = new BufferedInputStream(
                    new FileInputStream("Redirecting.java"));
            PrintStream out = new PrintStream(
                    new BufferedOutputStream(new FileOutputStream("Redirecting.txt")))
        ) {
            System.setIn(in);
            System.setOut(out);
            System.setErr(out);
            new BufferedReader(new InputStreamReader(System.in))
                .lines()
                .forEach(System.out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            System.setOut(console);
        }
    }
}
