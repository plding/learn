// onjava/atunit/Test.java
// Test @Test tag
package onjava.atunit;

import java.lang.annotation.*;

@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface Test {}
