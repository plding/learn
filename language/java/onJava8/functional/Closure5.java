// functional/Closure5.java
// {WillNotCompile}
import java.util.function.*;

public class Closure5 {
    IntSupplier makeFun(int x) {
        int i = 0;
        i++;
        x++;
        return () -> x + i;
    }
}
