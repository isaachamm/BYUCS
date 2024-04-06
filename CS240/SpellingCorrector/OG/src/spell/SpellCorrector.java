package spell;

import java.io.IOException;
import java.io.File;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public class SpellCorrector implements ISpellCorrector{

    private final Trie dictionary = new Trie();
    private final HashSet<String> editDistanceSet = new HashSet<>(); // used to store all edit distance words
    private final HashSet<String> foundWords = new HashSet<>(); // used to store words that are found in the dictionary from edit distance set

    @Override
    public void useDictionary(String dictionaryFileName) throws IOException {

        File file = new File(dictionaryFileName);
        Scanner scanner = new Scanner(file);
        while(scanner.hasNext()) {
            String str = scanner.next();
            str = str.toLowerCase();
            dictionary.add(str);
        }
    }

    @Override
    public String suggestSimilarWord(String inputWord) {
        inputWord = inputWord.toLowerCase();
        if (dictionary.find(inputWord) != null) { return inputWord; } // the word's not misspelled
        else {
            editDistanceSet.clear();
            foundWords.clear();

            calculateEditDistance(inputWord, editDistanceSet);


            //this is necessary to do so that the edit set isn't edited as it's passed
            String[] editOneHolder = editDistanceSet.toArray(new String[0]);
            if (foundWords.isEmpty()) {
                for(String word : editOneHolder) {
                    calculateEditDistance(word, editDistanceSet);
                }
            }

            if (editDistanceSet.isEmpty()) return null;


            String suggestion = new String("");
            Integer frequency = 0;

            for (String word : foundWords) {
                if(frequency < dictionary.find(word).getValue()) {
                    frequency = dictionary.find(word).getValue();
                    suggestion = word;
                }
                else if(frequency.equals(dictionary.find(word).getValue())) {
                    if(word.compareTo(suggestion) < 0) {
                        suggestion = word;
                    }
                }
            }

            if(!suggestion.equals("")) return suggestion;
            else return null;


        }
    }
    public void deletionDistance(String inputWord, HashSet<String> setToAddTo) {
        //deletion distance
        for (int i = 0; i < inputWord.length(); i++) {
            StringBuilder sb = new StringBuilder(inputWord);
            sb.deleteCharAt(i);
            String newWord = sb.toString();
            if(dictionary.find(newWord) != null){
                foundWords.add(newWord);
            }
            setToAddTo.add(newWord);
        }
    }
    public void transpositionDistance(String inputWord, HashSet<String> setToAddTo) {
        for (int i = 1; i < inputWord.length(); i++) { // has to be one instead of 0 becuase it's n-1 transpositions
            StringBuilder sb = new StringBuilder(inputWord);
            char transpositionChar = sb.charAt(i);
            sb.deleteCharAt(i);
            sb.insert(i - 1, transpositionChar);
            String newWord = sb.toString();
            if(dictionary.find(newWord) != null){
                foundWords.add(newWord);
            }
            setToAddTo.add(newWord);
        }
    }
    public void alterationDistance(String inputWord, HashSet<String> setToAddTo) {
        for (int i = 0; i < inputWord.length(); i++) {
            for (int j = 0; j < 26; j++) {
                StringBuilder sb = new StringBuilder(inputWord);
                sb.deleteCharAt(i);
                char alterationChar = (char) (j + 'a');
                sb.insert(i, alterationChar);
                String newWord = sb.toString();
                if(dictionary.find(newWord) != null){
                    foundWords.add(newWord);
                }
                setToAddTo.add(newWord);
            }
        }
    }
    public void insertionDistance(String inputWord, HashSet<String> setToAddTo) {
        for (int i = 0; i <= inputWord.length(); i++) {
            for (int j = 0; j < 26; j++) {
                StringBuilder sb = new StringBuilder(inputWord);
                char alterationChar = (char) (j + 'a');
                sb.insert(i, alterationChar);
                String newWord = sb.toString();
                if(dictionary.find(newWord) != null){
                    foundWords.add(newWord);
                }
                setToAddTo.add(newWord);
            }
        }
    }
    public void calculateEditDistance(String inputWord, HashSet<String> setToAddTo) {
        deletionDistance(inputWord, setToAddTo);
        transpositionDistance(inputWord, setToAddTo);
        alterationDistance(inputWord, setToAddTo);
        insertionDistance(inputWord, setToAddTo);
    }


}
