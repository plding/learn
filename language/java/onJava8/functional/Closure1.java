// functional/Closure1.java
import java.util.function.*;

public class Closure1 {
    int i;

    IntSupplier makeFun(int x) {
        return () -> x + i++;
    }
}
