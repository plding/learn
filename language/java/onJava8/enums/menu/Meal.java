// enums/menu/Meal.java
// {java enums.menu.Meal}
package enums.menu;

public class Meal {
    public static void main(String[] args) {
        for (int i = 0; i < 5; ++i) {
            for (Course course : Course.values()) {
                Food food = course.randomSelection();
                System.out.println(food);
            }
            System.out.println("***");
        }
    }
}
