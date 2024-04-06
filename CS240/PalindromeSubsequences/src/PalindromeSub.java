public class PalindromeSub {

    public static void main(String args[]) {

        String given = args[0];

        System.out.println(getPalindromesCount(given));


    }


    public static int getPalindromesCount(String s) {
        // Write your code here

//        int nop = 0;
//        for (int i = 0; i < s.length() - 4; i++) {
//            int j = i + 1;
////            111000111
//            StringBuilder fakep = new StringBuilder();
//            fakep.append(s.charAt(i));
//            fakep.append(s.charAt(j));
//            for(int m = s.length() - 1; m > i + 4; m--) {
//                int l = m - 1;
//                StringBuilder fakep2 = new StringBuilder();
//                fakep2.append(s.charAt(m));
//                fakep2.append(s.charAt(l));
//                if(fakep.compareTo(fakep2) == 0) {
//                    nop += (l - j);
//                }
//                System.out.println(fakep.toString() + fakep2.toString());
//
//            }
//        }

        int nop = 1;
        for (int i = 0; i < s.length() - 4; i++) {
            for(int m = s.length() - 1; m > i + 4; m--) {
                if(s.charAt(i) == s.charAt(m)){
                    for(int j = i + 1; j < m - 2; j++) {
                        for(int l = m - 1; l > j + 1; l--) {
                            if(s.charAt(j) == s.charAt(l)) {
                                nop += l - j - 1;
                            }
                        }
                    }
                }
            }
        }

        int numberOfPalindromes = 0;
        for(int i = 0; i < s.length() - 4; i++) {
            for(int j = 1; j < s.length() - 3; j++) {
                if (j <= i) continue;
                for(int k = 2; k < s.length() - 2; k++) {
                    if(k <= j) continue;
                    for(int l = 3; l < s.length() - 1; l ++) {
                        if(l <= k) continue;
                        for(int m = 4; m <s.length(); m++) {
                            if(m <= l) continue;


//                            if(i != j && i != k && i != l && i != m &&
//                                j != k && j != l && j != m &&
//                                k != l && k != m &&
//                                l != m) {
//                            if(i < j && j < k && k < l && l < m) {

//                            0110110101

                            StringBuilder newPalindrome = new StringBuilder();
                            newPalindrome.append(s.charAt(i));
                            newPalindrome.append(s.charAt(j));
                            newPalindrome.append(s.charAt(k));
                            newPalindrome.append(s.charAt(l));
                            newPalindrome.append(s.charAt(m));
                            if (isPalindrome(newPalindrome.toString())) {
                                numberOfPalindromes++;
                            }
//                            System.out.println(newPalindrome.toString());
//                            }
                        }
                    }
                }
            }
        }

        numberOfPalindromes = (int) (numberOfPalindromes % (Math.pow(10 , 9) + 7));

        return numberOfPalindromes;

    }

    public static boolean isPalindrome(String s) {
        for(int i = 0, j = (s.length() - 1); i < (s.length() / 2); i++, j--) {
            if(s.charAt(i) != s.charAt(j)) return false;
        }
        return true;
    }
}
