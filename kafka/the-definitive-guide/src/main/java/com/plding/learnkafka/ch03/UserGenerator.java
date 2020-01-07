package com.plding.learnkafka.ch03;

public class UserGenerator {
    public static User getNext() {
        User user = new User();
        user.setName("hello");
        user.setFavoriteColor("green");
        user.setFavoriteNumber(1);
        return user;
    }

    public static void main(String[] args) {
        System.out.println("user: " + UserGenerator.getNext());
    }
}
