// iostreams/UsingRandomAccessFile.java
import java.io.*;

public class UsingRandomAccessFile {
    static String file = "rtest.dat";

    public static void display() {
        try (RandomAccessFile rf = new RandomAccessFile(file, "r")) {
            for (int i = 0; i < 7; ++i)
                System.out.println("Value " + i + ": " + rf.readDouble());
            System.out.println(rf.readUTF());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        try (RandomAccessFile rf = new RandomAccessFile(file, "rw")) {
            for (int i = 0; i < 7; ++i)
                rf.writeDouble(i * 1.414);
            rf.writeUTF("The end of the file");
            rf.close();
            display();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        try (RandomAccessFile rf = new RandomAccessFile(file, "rw")) {
            rf.seek(5 * 8);
            rf.writeDouble(47.0001);
            rf.close();
            display();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
