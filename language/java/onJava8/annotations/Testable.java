// annotations/Testable.java
package annotations;

import onjava.atunit.*;

public class Testable {
    public void execute() {
        System.out.println("Executing..");
    }

    @Test
    void testExecute() { execute(); }
}
