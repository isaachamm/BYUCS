import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;


        class Solution {
            public static void main(String[] args) throws IOException {
                String palindrome = args[0];

                System.out.println(breakPalindrome(palindrome));

            }

            public static String breakPalindrome(String palindromeStr) {

                int counter = 0;
                int highestCharIndex = 0;
                char highestChar = 'a';
                for(char c : palindromeStr.toCharArray()) {
                    if (c > highestChar) {
                        highestChar = c;
                        if(counter != palindromeStr.length() / 2) {
                            highestCharIndex = counter;
                        }
                    }
                    counter++;
                }

                if(highestChar == 'a') {
                    return "IMPOSSIBLE";
                }
                else {
                    StringBuilder sb = new StringBuilder(palindromeStr);
                    sb.setCharAt(highestCharIndex, 'a');
                    return sb.toString();
                }
            }
        }
