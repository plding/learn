// newio/GetChannel.java
import java.nio.*;
import java.nio.channels.*;
import java.io.*;

public class GetChannel {
    private static String name = "data.txt";
    private static final int BSIZE = 1024;
    public static void main(String[] args) {
        try (FileChannel fc = new FileOutputStream(name).getChannel()) {
            fc.write(ByteBuffer.wrap("Some text ".getBytes()));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        try (FileChannel fc = new RandomAccessFile(name, "rw").getChannel()) {
            fc.position(fc.size());
            fc.write(ByteBuffer.wrap("Some more".getBytes()));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        try (FileChannel fc = new FileInputStream(name).getChannel()) {
            ByteBuffer buff = ByteBuffer.allocate(BSIZE);
            fc.read(buff);
            buff.flip();
            while (buff.hasRemaining())
                System.out.write(buff.get());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        System.out.flush();
    }
}
