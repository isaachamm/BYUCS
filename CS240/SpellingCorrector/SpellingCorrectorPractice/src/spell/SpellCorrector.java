package spell;

import java.io.File;
import java.io.IOException;
import java.util.*;

public class SpellCorrector implements ISpellCorrector{
    Trie dictionary = new Trie();
    Set<String> editDistance = new HashSet();
    Set<String> foundWords = new HashSet();

    @Override
    public void useDictionary(String dictionaryFileName) throws IOException {

        File file = new File(dictionaryFileName);

        Scanner scanner = new Scanner(file);
        while(scanner.hasNext()){
            String str = scanner.next();
            str = str.toLowerCase();
            dictionary.add(str);
        }


    }

    @Override
    public String suggestSimilarWord(String inputWord) {
        inputWord = inputWord.toLowerCase();

        editDistance.clear();
        foundWords.clear();

        if(dictionary.find(inputWord) != null) return inputWord;

        insertionDistance(inputWord);
        deletionDistance(inputWord);
        alterationDistance(inputWord);
        transpositionDistance(inputWord);

        String[] holder = editDistance.toArray(new String[0]);
        if (foundWords.isEmpty()) {
            for (String s : holder) {
                insertionDistance(s);
                deletionDistance(s);
                alterationDistance(s);
                transpositionDistance(s);
            }
        }

        if (foundWords.isEmpty()) return null;

        int frequency = 0;
        String suggestion = new String();
        for (String s : foundWords) {
            if (frequency < dictionary.find(s).getValue()) {
                suggestion = s;
                frequency = dictionary.find(s).getValue();
            }
            else if (frequency == dictionary.find(s).getValue()) {
                if (suggestion.compareTo(s) > 0) {
                    suggestion = s;
                }
            }
        }

        return suggestion;
    }

    public void insertionDistance(String inputWord) {
        for(int i = 0; i < inputWord.length() + 1; i++) {
            for(int j = 0; j < 26; j++) {
                StringBuilder sb = new StringBuilder(inputWord);
                char newChar = (char) (j + 'a');
                sb.insert(i, newChar);
                String newWord = sb.toString();
                if (dictionary.find(newWord) != null) {
                    foundWords.add(newWord);
                }
                editDistance.add(newWord);
            }
        }
    }

    public void deletionDistance(String inputWord) {
        for(int i = 0; i < inputWord.length(); i++) {
            StringBuilder sb = new StringBuilder(inputWord);
            sb.deleteCharAt(i);
            String newWord = sb.toString();
            if(dictionary.find(newWord) != null) {
                foundWords.add(newWord);
            }
            editDistance.add(newWord);
        }

    }
    public void transpositionDistance(String inputWord) {

        for(int i = 1; i < inputWord.length(); i++) {
                StringBuilder sb = new StringBuilder(inputWord);
                char holder = sb.charAt(i);
                sb.deleteCharAt(i);
                sb.insert(i - 1, holder);
            String newWord = sb.toString();
            if (dictionary.find(newWord) != null) {
                    foundWords.add(newWord);
                }
                editDistance.add(newWord);
        }
    }
    public void alterationDistance(String inputWord) {

        for(int i = 0; i < inputWord.length(); i++) {
            for(int j = 0; j < 26; j++) {
                StringBuilder sb = new StringBuilder(inputWord);
                char newChar = (char) (j + 'a');
                sb.setCharAt(i, newChar);
                String newWord = sb.toString();
                if (dictionary.find(newWord) != null) {
                    foundWords.add(newWord);
                }
                editDistance.add(newWord);
            }
        }
    }
}
