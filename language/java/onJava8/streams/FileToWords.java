// streams/FileToWords.java
import java.nio.file.*;
import java.util.stream.*;
import java.util.regex.Pattern;

public class FileToWords {
    public static Stream<String> stream(String filePath) throws Exception {
        return Files.lines(Paths.get(filePath))
                    .skip(1)
                    .flatMap(line -> Pattern.compile("\\W+").splitAsStream(line));
    }
}
