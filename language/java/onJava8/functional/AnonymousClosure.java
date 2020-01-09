// functional/AnonymousClosure.java
import java.util.function.*;

public class AnonymousClosure {
    IntSupplier makeFun(int x) {
        int i = 0;
        // i++;
        return new IntSupplier() {
            @Override public int getAsInt() { return x + i; }
        };
    }
}
