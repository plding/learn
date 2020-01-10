// streams/SpecialCollector.java
import java.util.*;
import java.util.stream.*;

public class SpecialCollector {
    public static void main(String[] args) throws Exception {
        ArrayList<String> words =
                FileToWords.stream("Cheese.dat")
                           .collect(ArrayList::new, ArrayList::add, ArrayList::addAll);
        words.stream()
             .filter(s -> s.equals("cheese"))
             .forEach(System.out::println);
    }
}
