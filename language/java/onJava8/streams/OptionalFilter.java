// streams/OptionalFilter.java
import java.util.*;
import java.util.stream.*;
import java.util.function.*;

class OptionalFilter {
    static String[] elements = { "Foo", "", "Bar", "Baz", "Bingo" };

    static Stream<String> testStream() {
        return Arrays.stream(elements);
    }

    static void test(String descr, Predicate<String> pred) {
        System.out.println(" ---( " + descr + " )---"); 
        for (int i = 0; i <= elements.length; ++i) {
            System.out.println(testStream().skip(i)
                                           .findFirst()
                                           .filter(pred));
        }
    }

    public static void main(String[] args) {
        test("true", str -> true);
        test("false", str -> false);
        test("str != \"\"", str -> str != "");
        test("str.length() == 3", str -> str.length() == 3);
        test("startsWith(\"B\")", str -> str.startsWith("B"));
    }
}
