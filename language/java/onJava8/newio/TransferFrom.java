// newio/TransferFrom.java
// {java TransferFrom TransferFrom.java TransferFrom.txt}
import java.nio.channels.*;
import java.io.*;

public class TransferFrom {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("arguments: sourcefile destfile");
            System.exit(1);
        }

        try (
            FileChannel in  = new FileInputStream(args[0]).getChannel();        
            FileChannel out = new FileOutputStream(args[1]).getChannel();        
        ) {
            out.transferFrom(in, 0, in.size());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
