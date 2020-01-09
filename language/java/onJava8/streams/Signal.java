// streams/Signal.java
import java.util.*;
import java.util.stream.*;
import java.util.function.*;

public class Signal {
    private final String msg;
    static Random rand = new Random(47);

    public Signal(String msg) { this.msg = msg; }
    public String getMsg() { return msg; }

    @Override
    public String toString() {
        return "Signal(" + msg + ")";
    }

    public static Signal morse() {
        switch (rand.nextInt(4)) {
        case 1: return new Signal("dot");
        case 2: return new Signal("dash");
        default: return null;
        }
    }

    public static Stream<Optional<Signal>> stream() {
        return Stream.generate(Signal::morse)
                .map(signal -> Optional.ofNullable(signal));
    }
}
