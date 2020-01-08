// iostreams/BasicFileOutput.java
// {VisuallyInspectOutput}
import java.io.*;

public class BasicFileOutput {
    static String file = "BasicFileOutput.dat";

    public static void main(String[] args) {
        try (
            BufferedReader in = new BufferedReader(
                    new StringReader(BufferedInputFile.read("BasicFileOutput.java")));
            PrintWriter out = new PrintWriter(
                    new BufferedWriter(new FileWriter(file)))
        ) {
            in.lines().forEach(out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        System.out.println(BufferedInputFile.read(file));
    }
}
