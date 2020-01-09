// functional/Closure3.java
// {WillNotCompile}
import java.util.function.*;

public class Closure3 {
    IntSupplier makeFun(int x) {
        int i = 0;
        return () -> x++ + i++;
    }
}
