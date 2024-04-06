import java.util.*;

public class RandomID {
    public static void main(String args[]) {
        RandomID test = new RandomID();

        test.run();
    }

    public void run() {
        String one = java.util.UUID.randomUUID().toString();
        String two = java.util.UUID.randomUUID().toString();
        String three = java.util.UUID.randomUUID().toString();
        String four = java.util.UUID.randomUUID().toString();
        String five = java.util.UUID.randomUUID().toString();

        System.out.println(one + '\n' + two + '\n' + three + '\n' + four + '\n' + five);
    }
}
