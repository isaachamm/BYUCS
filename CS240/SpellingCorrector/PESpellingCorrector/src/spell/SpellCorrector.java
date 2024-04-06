package spell;

import java.io.File;
import java.io.IOException;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class SpellCorrector implements ISpellCorrector{

    private Trie dictionary = new Trie();
    private Set<String> editDistance = new HashSet<>();
    private Set<String> foundWords = new HashSet<>();


    @Override
    public void useDictionary(String dictionaryFileName) throws IOException {

        File file = new File(dictionaryFileName);

        Scanner scanner = new Scanner(file);
        while(scanner.hasNext()) {
            String str = scanner.next();
            dictionary.add(str);
        }
        int i = 0;
    }

    @Override
    public String suggestSimilarWord(String inputWord) {

        inputWord = inputWord.toLowerCase();

        editDistance.clear();
        foundWords.clear();

        if(dictionary.find(inputWord) != null) return inputWord;

        deletionDistance(inputWord);
        transpositionDistance(inputWord);
        alterationDistance(inputWord);
        insertionDistance(inputWord);

        String[] editArray = new String[editDistance.size()];
        editDistance.toArray(editArray);
        if(foundWords.isEmpty()) {
            for(String s : editArray) {
                deletionDistance(s);
                transpositionDistance(s);
                alterationDistance(s);
                insertionDistance(s);
            }
        }

        if(foundWords.isEmpty()) return null;

        int frequency = 0;
        String suggestion = null;
        for(String s : foundWords) {
            if(frequency < dictionary.find(s).getValue()) {
                frequency = dictionary.find(s).getValue();
                suggestion = s;
            }
            else if (frequency == dictionary.find(s).getValue()) {
                assert suggestion != null;
                if (suggestion.compareTo(s) > 0) {
                    suggestion = s;
                }
            }
        }


        return suggestion;
    }

    public void deletionDistance(String word) {
        for(int i = 0; i < word.length(); i++) {
            StringBuilder sb = new StringBuilder(word);
            sb.deleteCharAt(i);
            String newWord = sb.toString();
            if(dictionary.find(newWord) != null) {
                foundWords.add(newWord);
            }
            editDistance.add(newWord);
        }
    }
    public void transpositionDistance(String word) {
        for(int i = 1; i < word.length(); i++) {
            StringBuilder sb = new StringBuilder(word);
            char c = sb.charAt(i);
            sb.deleteCharAt(i);
            sb.insert(i - 1, c);
            String newWord = sb.toString();
            if(dictionary.find(newWord) != null) {
                foundWords.add(newWord);
            }
            editDistance.add(newWord);
        }
    }
    public void alterationDistance(String word) {
        for(int i = 0; i < word.length(); i++) {
            for(int j = 0; j < 26; j++) {
                StringBuilder sb = new StringBuilder(word);
                char c = (char) (j + 'a');
                sb.setCharAt(i, c);
                String newWord = sb.toString();
                if (dictionary.find(newWord) != null) {
                    foundWords.add(newWord);
                }
                editDistance.add(newWord);
            }
        }
    }
    public void insertionDistance(String word) {
        for(int i = 0; i <= word.length(); i++) {
            for(int j = 0; j < 26; j++) {
                StringBuilder sb = new StringBuilder(word);
                char c = (char) (j + 'a');
                sb.insert(i, c);
                String newWord = sb.toString();
                if (dictionary.find(newWord) != null) {
                    foundWords.add(newWord);
                }
                editDistance.add(newWord);
            }
        }
    }

}
