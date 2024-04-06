package spell;

import java.util.Objects;

public class Trie implements ITrie{

    private Node root = new Node();
    private int wordCount = 0;
    private int nodeCount = 1;

    @Override
    public void add(String word) {

        word = word.toLowerCase();
        Node currNode = root;

        for(char c : word.toCharArray()) {
            int index = (int) (c - 'a');
            if(currNode.getChildren()[index] == null) {
                Node newNode = new Node();
                currNode.getChildren()[index] = newNode;
                currNode = currNode.getChildren()[index];
                nodeCount++;
            }
            else {
                currNode = currNode.getChildren()[index];
            }
        }

        if(currNode.getValue() == 0) wordCount++;
        currNode.incrementValue();

    }

    @Override
    public Node find(String word) {

        word = word.toLowerCase();
        Node currNode = root;

        for(char c : word.toCharArray()) {
            int index = (int) (c - 'a');
            if(currNode.getChildren()[index] == null) {
                return null;
            }
            else {
                currNode = currNode.getChildren()[index];
            }
        }

        if(currNode.getValue() == 0) return null;
        return currNode;
    }

    @Override
    public int getWordCount() {
        return wordCount;
    }

    @Override
    public int getNodeCount() {
        return nodeCount;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Trie trie = (Trie) o;

        if(trie.wordCount != this.wordCount ||
                trie.nodeCount != this.nodeCount) return false;

        return equalsHelper(this.root, trie.root);
    }

    public boolean equalsHelper(Node thisNode, Node oNode) {

        if(thisNode.getValue() != oNode.getValue()) return false;

        for(int i = 0; i < 26; i++) {
            if(thisNode.getChildren()[i] != null && oNode.getChildren()[i] != null) {
                if(!equalsHelper(thisNode.getChildren()[i], oNode.getChildren()[i])) return false;
            }
            else if (thisNode.getChildren()[i] != null)
                return false;
            else if (oNode.getChildren()[i] != null)
                return false;
        }

        return true;

    }

    @Override
    public int hashCode() {
        Node[] rootChildren = root.getChildren();
        int index = 0;
        for(int i = 0; i < 26; i++) {
            if(rootChildren[i] != null) {
                index += i;
            }
        }
        return (wordCount * nodeCount * index);
    }

    @Override
    public String toString() {

        StringBuilder trieString = new StringBuilder();
        StringBuilder currWord = new StringBuilder();
        toStringHelper(trieString, currWord, this.root);

        return trieString.toString();
    }

    public void toStringHelper(StringBuilder trieString, StringBuilder currWord, Node currNode) {

        if(currNode.getValue() > 0) {
            trieString.append(currWord.toString()).append('\n');
        }

        for(int i = 0; i < 26; i++) {
            if(currNode.getChildren()[i] != null) {
                char c = (char) (i + 'a');
                currWord.append(c);
                toStringHelper(trieString, currWord, currNode.getChildren()[i]);
                currWord.deleteCharAt(currWord.length() - 1);
            }
        }


    }
}
