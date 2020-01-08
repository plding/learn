// iostreams/TestEOF.java
// Testing for end of file
// {VisuallyInspectOutput} 
import java.io.*;

public class TestEOF {
    public static void main(String[] args) {
        try (
            DataInputStream in = new DataInputStream(
                    new BufferedInputStream(new FileInputStream("TestEOF.java")))
        ) {
            while (in.available() != 0)
                System.out.write(in.readByte());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
