package hangman;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.Scanner;
import java.util.Set;

public class EvilHangman {

    public static void main(String[] args) throws IOException, EmptyDictionaryException, GuessAlreadyMadeException {

        File file = new File(args[0]);
        int wordLength = Integer.parseInt(args[1]);

        EvilHangmanGame game = new EvilHangmanGame();
        game.startGame(file, wordLength);
        game.setGuesses(Integer.parseInt(args[2]));

        Scanner in = new Scanner(System.in);

        String wordGuess = game.getWordGuess();

        while(game.getGuesses() > 0) {
            System.out.println("You have " + game.getGuesses() + " left");
            System.out.println("Used letters: " + game.getGuessedLetters().toString());
            System.out.println("Word: " + game.getWordGuess());

            while(true) {
            System.out.print("Enter guess: ");
            String nextGuess = in.next().toLowerCase();
                if(nextGuess.length() > 1) {
                    System.out.println("Invalid input! ");
                    continue;
                }
                char guess = nextGuess.charAt(0);
                if(!Character.isAlphabetic(guess)) {
                    System.out.println("Invalid input! ");
                    continue;
                }
                if (game.getGuessedLetters().contains(guess)) {
                    System.out.println("Guess already made! ");
                    continue;
                }

                game.makeGuess(guess);
                if (wordGuess.compareTo(game.getWordGuess()) == 0){
                    System.out.println("Sorry, there are no " + guess);
                    game.decrementGuesses();
                    if(game.getGuesses() == 0) {
                        System.out.println("Sorry, you lost!");
                        String[] dictionary = new String[game.getDictionary().size()];
                        game.getDictionary().toArray(dictionary);
                        System.out.println("The word was: " + dictionary[0]);
                    }
                    break;
                }
                else {
                    wordGuess = game.getWordGuess();
                    System.out.println("Yes, there is " + game.getGuessCount() + " " + guess);
                    if(game.getDictionary().size() == 1) {
                        System.out.println("You win! You guessed the word " + game.getWordGuess());
                        game.setGuesses(0);
                    }
                    else break;
                }
            }
        }
    }
}
