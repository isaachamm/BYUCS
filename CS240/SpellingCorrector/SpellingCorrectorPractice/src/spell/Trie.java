package spell;

import java.util.Objects;

public class Trie implements ITrie{

    Node root = new Node();
    private int wordCount = 0;
    private int nodeCount = 1;

    @Override
    public int getWordCount() {
        return wordCount;
    }
    @Override
    public int getNodeCount() {
        return nodeCount;
    }
    public void incrementNodeCount() {
        nodeCount++;
    }
    public void incrementWordCount() {
        wordCount++;
    }

    @Override
    public void add(String word) {

        Node currNode = root;

        for(int i = 0; i < word.length(); i++) {
            int index = (int) (word.charAt(i) - 'a');
            if(currNode.getChildren()[index] == null) {
                Node newNode = new Node();
                nodeCount++;
                currNode.getChildren()[index] = newNode;
            }
                currNode = currNode.getChildren()[index];
        }
        if(currNode.getValue() == 0) {
            incrementWordCount();
        }
        currNode.incrementValue();

    }

    @Override
    public Node find(String word) {
        Node currNode = root;
        for(int i = 0; i < word.length(); i++) {
            int index = (int) (word.charAt(i) - 'a');
            if(currNode.getChildren()[index] == null) {
                return null;
            }
            else {
                    currNode = currNode.getChildren()[index];
            }
        }
        if(currNode.getValue() > 0 ) return currNode;
        else return null;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Trie trie = (Trie) o;

        if(trie.getWordCount() != this.getWordCount() ||
            trie.getNodeCount() != this.getNodeCount()) {
            return false;
        }

        return equalsHelper(this.root, trie.root);
    }

    public boolean equalsHelper(Node thisNode, Node oNode) {
        if(thisNode.getValue() != oNode.getValue()) return false;

        for(int i = 0; i < 26; i++) {
            if(thisNode.getChildren()[i] != null && oNode.getChildren()[i] != null){
                if(!equalsHelper(thisNode.getChildren()[i], oNode.getChildren()[i])) return false;
            }
            else if (thisNode.getChildren()[i] != null) return false;
            else if (thisNode.getChildren()[i] != null) return false;
        }
        return true;
    }

    @Override
    public int hashCode() {
        int index = 0;
        Node[] rootChildren = root.getChildren();
        for (int i = 0; i < 26; i++) {
            if (rootChildren[i] != null) {
                index = i;
            }
        }
        return (wordCount * nodeCount * index);
    }

    @Override
    public String toString() {

        StringBuilder trieString = new StringBuilder();
        StringBuilder currWord = new StringBuilder();
        toStringHelper(trieString, currWord, root);

        return trieString.toString();
    }

    public void toStringHelper(StringBuilder trieString, StringBuilder currWord, Node node) {

        if(node.getValue() > 0) {
            trieString.append(currWord).append("\n");
        }


        for(int i = 0; i < 26; i++) {
            if(node.getChildren()[i] != null) {
                char c = (char) (i + 'a');
                currWord.append(c);
                toStringHelper(trieString, currWord, node.getChildren()[i]);
                currWord.deleteCharAt(currWord.length() - 1);
            }
        }


    }
}
