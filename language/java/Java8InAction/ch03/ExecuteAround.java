// ch03/ExecuteAround.java
import java.io.*;

public class ExecuteAround {
    public static void main(String[] args) throws IOException {
        String result = processFileLimited();
        System.out.println(result);

        System.out.println("---");

        String oneLine = processFile((BufferedReader b) -> b.readLine());
        System.out.println(oneLine);

        String twoLine = processFile((BufferedReader b) -> b.readLine() + b.readLine());
        System.out.println(twoLine);
    }

    public static String processFileLimited() throws IOException {
        try (BufferedReader br = new BufferedReader(new FileReader("data.txt"))) {
            return br.readLine();
        }
    }

    public static String processFile(BufferedReaderProcessor p) throws IOException {
        try (BufferedReader br = new BufferedReader(new FileReader("data.txt"))) {
            return p.process(br);
        }
    }

    public interface BufferedReaderProcessor {
        String process(BufferedReader br) throws IOException;
    }
}
