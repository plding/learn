// annotations/database/Uniqueness.java
package annotations.database;

import java.lang.annotation.*;

@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
public @interface Uniqueness {
    Constraints constraints() default @Constraints(unique = true);
}
