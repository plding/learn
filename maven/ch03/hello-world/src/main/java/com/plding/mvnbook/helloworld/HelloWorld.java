package com.plding.mvnbook.helloworld;

public class HelloWorld
{
    public String sayHello()
    {
        return "Hello Maven";
    }

    public static void main(String[] args)
    {
        System.out.println(new HelloWorld().sayHello());
    }
}
