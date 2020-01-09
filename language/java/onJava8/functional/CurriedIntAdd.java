// functional/CurriedIntAdd.java
import java.util.function.*;

public class CurriedIntAdd {
    public static void main(String[] args) {
        IntFunction<IntUnaryOperator> CurriedIntAdd = a -> b -> a + b;
        IntUnaryOperator add4 = CurriedIntAdd.apply(4);
        System.out.println(add4.applyAsInt(5));
    }
}
