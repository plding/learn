// functional/Closure9.java
// {WillNotCompile}
import java.util.*;
import java.util.function.*;

public class Closure9 {
    Supplier<List<Integer>> makeFun() {
        List<Integer> ai = new ArrayList<>();
        ai = new ArrayList<>();
        return () -> ai;
    }
}
