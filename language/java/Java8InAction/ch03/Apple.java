// ch03/Apple.java

public class Apple {
    private int weight;
    private String color;

    public Apple(int weight, String color) {
        this.weight = weight;
        this.color = color;
    }

    public Integer getWeight() {
        return weight;
    }

    public String getColor() {
        return color;
    }

    public String toString() {
        return String.format("Apple{color='%s', weight=%d}", color, weight);
    }
}


