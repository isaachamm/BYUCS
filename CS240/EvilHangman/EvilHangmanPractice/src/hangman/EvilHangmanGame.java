package hangman;

import java.io.File;
import java.io.IOException;
import java.util.*;

public class EvilHangmanGame implements IEvilHangmanGame{
    private int guesses = 0;
    private Object TreeSet;
    private String wordGuess = new String();
    private int guessCount = 0;
    private SortedSet<Character> guessedCharacters = new TreeSet <Character>();
    private Set<String> dictionary = new HashSet<String>();
    private Map<String, Set<String>> partitions = new HashMap<>();

    public EvilHangmanGame() {};

    public int getGuesses() {
        return guesses;
    }
    public void setGuesses(int guesses) {
        this.guesses = guesses;
    }
    public String getWordGuess() {
        return wordGuess;
    }
    public int getGuessCount() {
        return guessCount;
    }
    public void setGuessCount(int guessCount) {
        this.guessCount = guessCount;
    }
    public Set<String> getDictionary() {
        return dictionary;
    }
    public void decrementGuesses() {guesses--;}


    @Override
    public void startGame(File dictionary, int wordLength) throws IOException, EmptyDictionaryException {
        this.dictionary.clear();

        if(guesses == 0) {
            guesses = wordLength;
        }

        StringBuilder wg = new StringBuilder(); // wg for wordguess
        for(int i = 0; i < wordLength; i++) {
            wg.append('_');
        }
        wordGuess = wg.toString();

        Scanner scanner = new Scanner(dictionary);
        while(scanner.hasNext()) {
            String str = scanner.next();
            str = str.toLowerCase();
            if(str.length() == wordLength) {
                this.dictionary.add(str);
            }
        }
        if(this.dictionary.isEmpty()) throw new EmptyDictionaryException();
    }

    @Override
    public Set<String> makeGuess(char guess) throws GuessAlreadyMadeException {

        guess = Character.toLowerCase(guess);
        if(guessedCharacters.contains(guess)) throw new GuessAlreadyMadeException();
        guessedCharacters.add(guess);

        partitions.clear();

        for(String s : dictionary) {
            String subsetKey = getSubsetKey(guess, s);
            if ((partitions.get(subsetKey) != null)) {
                Set<String> newPartition = partitions.get(subsetKey);
                newPartition.add(s);
                partitions.put(subsetKey, newPartition);
            }
            else {
                Set<String> newPartition = new HashSet<>();
                newPartition.add(s);
                partitions.put(subsetKey, newPartition);
            }
        }

        int partitionSize = 0;
        String partitionKey = null;
        for(Map.Entry<String, Set<String>> partition: partitions.entrySet()) {
            if(partition.getValue().size() > partitionSize) {
                partitionSize = partition.getValue().size();
                partitionKey = partition.getKey();
            }
            else if (partition.getValue().size() == partitionSize) {
                if (partitionKey.compareTo(partition.getKey()) > 0) {
                    partitionKey = partition.getKey();
                }
            }
        }

        int guessCount = 0;
        StringBuilder wg = new StringBuilder();
        for (int i = 0; i < partitionKey.length(); i++) {
            if(wordGuess.charAt(i) != '_') {
                wg.append(wordGuess.charAt(i));
            }
            else if (partitionKey.charAt(i) != '_') {
                wg.append(partitionKey.charAt(i));
                guessCount++;
            }
            else {
                wg.append('_');
            }
        }
        this.wordGuess = wg.toString();
        this.guessCount = guessCount;

        this.dictionary = partitions.get(partitionKey);

        return partitions.get(partitionKey);
    }

    public String getSubsetKey(char guess, String word) {
        StringBuilder sb = new StringBuilder();
        for (char c : word.toCharArray()) {
            if (c == guess) {
                sb.append(c);
            }
            else {
                sb.append('_');
            }
        }

        return sb.toString();
    }

    @Override
    public SortedSet<Character> getGuessedLetters() {
        return guessedCharacters;
    }
}
