// files/PartsOfPaths.java
import java.nio.file.*;

public class PartsOfPaths {
    public static void main(String[] args) {
        System.out.println(System.getProperty("os.name"));

        Path p = Paths.get("PartsOfPaths.java").toAbsolutePath();
        for (int i = 0; i < p.getNameCount(); ++i)
            System.out.println(p.getName(i));
        System.out.println("ends with '.java': " + p.endsWith(".java"));

        for (Path pp : p) {
            System.out.print(pp + ": ");
            System.out.print(p.startsWith(pp) + " : ");
            System.out.println(p.endsWith(pp));
        }
        System.out.println("Starts with " + p.getRoot() + " " + p.startsWith(p.getRoot()));
    }
}
