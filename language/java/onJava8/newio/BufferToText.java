// newio/BufferToText.java
import java.nio.*;
import java.nio.channels.*;
import java.nio.charset.*;
import java.io.*;

public class BufferToText {
    private static final int BSIZE = 1024;
    
    public static void main(String[] args) {
        try (FileChannel fc = new FileOutputStream("data2.txt").getChannel()) {
            fc.write(ByteBuffer.wrap("Some text".getBytes()));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        ByteBuffer buff = ByteBuffer.allocate(BSIZE);
        try (FileChannel fc = new FileInputStream("data2.txt").getChannel()) {
            fc.read(buff);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        buff.flip();
        System.out.println(buff.asCharBuffer());

        buff.rewind();
        String encoding = System.getProperty("file.encoding");
        System.out.println("Decoded using " + encoding + ": " + Charset.forName(encoding).decode(buff));

        try (FileChannel fc = new FileOutputStream("data2.txt").getChannel()) {
            fc.write(ByteBuffer.wrap("Some text".getBytes("UTF-16BE")));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        buff.clear();
        try (FileChannel fc = new FileInputStream("data2.txt").getChannel()) {
            fc.read(buff);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        buff.flip();
        System.out.println(buff.asCharBuffer());

        buff = ByteBuffer.allocate(24);
        buff.asCharBuffer().put("Some text");
        try (FileChannel fc = new FileOutputStream("data2.txt").getChannel()) {
            fc.write(buff);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        buff.clear();
        try (FileChannel fc = new FileInputStream("data2.txt").getChannel()) {
            fc.read(buff);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        buff.flip();
        System.out.println(buff.asCharBuffer());
    }
}
