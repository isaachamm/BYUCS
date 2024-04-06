package hangman;

import java.io.File;
import java.io.IOException;
import java.util.*;

public class EvilHangmanGame implements IEvilHangmanGame{

    private SortedSet<Character> guessedLetters = new TreeSet<>() {};
    private HashSet<String> dictionary = null;         //The dictionary that initializes with all words
    private int wordLength;
    private int charNumber; // holds the number of chars on correct guesses to print in main
    private String word;
    private int guesses;
    private HashMap<String, HashSet<String>> partitionSubsets = new HashMap<>(); //String is the subset key, set of strings are the corresponding words

    public void setGuesses(int guesses) {
        this.guesses = guesses;
    }
    public int getGuesses() {
        return guesses;
    }
    public String getWord() {
        return word;
    }
    public int getCharNumber() {
        return charNumber;
    }
    public Set<String> getDictionary() {
        return dictionary;
    }
    public void decrementGuesses() { guesses--; }

    @Override
    public void startGame(File dictionary, int wordLength) throws IOException, EmptyDictionaryException {

        this.dictionary = new HashSet<>();
        if (this.guesses == 0 ) {
            this.guesses = wordLength;
        }

        try(Scanner scanner = new Scanner(dictionary)) {

            while (scanner.hasNext()) {
                String str = scanner.next();
                if(str.length() == wordLength) {
                    this.dictionary.add(str);
                }
            }
        }
        catch (IOException ex) {
            System.out.println("File not found: " + dictionary);
            throw new IOException();
        }
        if(this.dictionary.isEmpty()) throw new EmptyDictionaryException();

        //initialize this.word here to be able to compare it in main
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < wordLength; i++) {
            sb.append('_');
        }
        this.word = sb.toString();
    }

    @Override
    public Set<String> makeGuess(char guess) throws GuessAlreadyMadeException {
        guess = Character.toLowerCase(guess);

        partitionSubsets.clear();

        if(guessedLetters.contains(guess)) throw new GuessAlreadyMadeException();
        guessedLetters.add(guess);

        for(String s : dictionary) {
            String subKey = getSubsetKey(s, guess);
            HashSet<String> partition = new HashSet<>();
            if (partitionSubsets.get(subKey) != null) {
                partition = partitionSubsets.get(subKey);
            }
            partition.add(s);
            this.partitionSubsets.put(subKey, partition);
        }

        String partitionToUse = new String();
        int partitionSize = 0;
        for(Map.Entry<String, HashSet<String>> partitions : partitionSubsets.entrySet()) {
            if (partitionSize < partitions.getValue().size()) {
                partitionSize = partitions.getValue().size();
                partitionToUse = partitions.getKey();
            }
            else if (partitionSize == partitions.getValue().size()) {
                if (partitionToUse.compareTo(partitions.getKey()) > 0) {
                    partitionToUse = partitions.getKey();
                }
            }
        }

        StringBuilder wordHolder = new StringBuilder();
        charNumber = 0;
        for(int i = 0; i < this.word.length(); i++) {
            if(partitionToUse.charAt(i) == '_' &&
                    this.word.charAt(i) == '_') {
                wordHolder.append('_');
            } else if (partitionToUse.charAt(i) != '_') {
                wordHolder.append(partitionToUse.charAt(i));
                charNumber++;
            }
            else if (this.word.charAt(i) != '_') {
                wordHolder.append(this.word.charAt(i));
            }
        }
        this.word = wordHolder.toString();
        this.dictionary = partitionSubsets.get(partitionToUse);

        return this.dictionary;
    }

    @Override
    public SortedSet<Character> getGuessedLetters() {
        return guessedLetters;
    }

    public String getSubsetKey(String word, char guessedLetter) {
        StringBuilder subKey = new StringBuilder();

        for(char c : word.toCharArray()) {
            if(c == guessedLetter) subKey.append(c);
            else subKey.append('_');
        }

        return subKey.toString();
    }
}
