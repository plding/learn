// onjava/OSExecute.java
package onjava;

import java.io.*;

public class OSExecute {
    public static void command(String command) {
        boolean err = false;
        try {
            Process process = new ProcessBuilder(command.split(" ")).start();
            try (
                BufferedReader results = new BufferedReader(new InputStreamReader(process.getInputStream()));
                BufferedReader errors  = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            ) {
                results.lines().forEach(System.out::println);
                err = errors.lines().peek(System.err::println).count() > 0;
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        if (err) {
            throw new OSExecuteException("Errors executing " + command);
        }
    }
}
