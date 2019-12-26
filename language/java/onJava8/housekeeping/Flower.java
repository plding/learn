// housekeeping/Flower.java

public class Flower {
    int petalCount = 0;
    String s = "initial value";

    Flower(int petals) {
        petalCount = petals;
        System.out.println("Constructor w/ int arg only, petalCount = " + petalCount);
    }

    Flower(String ss) {
        System.out.println("Constructor w/ string arg only, s = " + ss);
        s = ss;
    }

    Flower(String s, int petals) {
        this(petals);
        //- this(s); // Can't call two!
        this.s = s;
        System.out.println("String & int args");
    }

    Flower() {
        this("hi", 47);
        System.out.println("no-arg constructor");
    }

    void printPetalCount() {
        //- this(11); // Not inside constructor!
        System.out.println("petalCount = " + petalCount + " s = " + s);
    }

    public static void main(String[] args) {
        Flower x = new Flower();
        x.printPetalCount();
    }
}
