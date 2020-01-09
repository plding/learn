// functional/Closure7.java
// {WillNotCompile}
import java.util.function.*;

public class Closure7 {
    IntSupplier makeFun(int x) {
        Integer i = 0;
        i = i + 1;
        return () -> x + i;
    }
}
