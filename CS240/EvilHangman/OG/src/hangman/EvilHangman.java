package hangman;

import javax.management.relation.RelationNotFoundException;
import java.io.File;
import java.io.IOException;
import java.util.HashSet;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;

public class EvilHangman {

    public static void main(String[] args) throws EmptyDictionaryException, IOException, GuessAlreadyMadeException {
        EvilHangmanGame game = new EvilHangmanGame();
        File file = new File(args[0]);

        game.startGame(file, Integer.parseInt(args[1]));
        game.setGuesses(Integer.parseInt(args[2]));
        Scanner in = new Scanner(System.in);
        Set<String> dictionary = game.getDictionary();
        String compareWord = new String(game.getWord());

        while(game.getGuesses() > 0) {
            System.out.println("You have " + game.getGuesses() + " left");
            System.out.println("Used letters: " + game.getGuessedLetters().toString());
            System.out.println("Word: " + game.getWord());
            while(true) {
                System.out.println("Enter guess: ");
                String nextGuess = in.next();
                nextGuess = nextGuess.toLowerCase();
                if (nextGuess.length() > 1) {
                    System.out.println("Invalid Input! ");
                }
                else if (!Character.isLetter(nextGuess.charAt(0))){
                    System.out.println("Invalid Input! ");
                }
                else if (game.getGuessedLetters().contains(nextGuess.charAt(0))){
                    System.out.println("Guess already made! ");
                }
                else {
                    dictionary = game.makeGuess(nextGuess.charAt(0));
                    if(compareWord.compareTo(game.getWord()) == 0) {
                        System.out.println("Sorry, there are no " + nextGuess.charAt(0) + '\n');
                        game.decrementGuesses();
                        if(game.getGuesses() == 0) {
                            String[] dictionaryArray = new String[dictionary.size()];
                            dictionary.toArray(dictionaryArray);
                            Random rand = new Random();
                            int randNum = rand.nextInt(dictionary.size());
                            System.out.println("Sorry, you lost! " +
                                    "The word was: " + dictionaryArray[randNum]);
                        }
                    }
                    else {
                        compareWord = game.getWord();
                        System.out.println("Yes, there is " + game.getCharNumber()
                                + " " + nextGuess.charAt(0) + "\n");
                        if(dictionary.size() == 1) {
                            System.out.println("You win! " +
                                    "You guessed the word: " +
                                    dictionary.toString());
                            game.setGuesses(0);
                        }
                    }
                    break;
                }
            }
        }



    }

}
