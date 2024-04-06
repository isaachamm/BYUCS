package spell;

public class Node implements INode{

    public int count = 0;
    Node[] children = new Node[26];

    @Override
    public int getValue() {
        return count;
    }

    @Override
    public void incrementValue() {
        count++;
    }

    @Override
    public Node[] getChildren() {
        return children;
    }
}
