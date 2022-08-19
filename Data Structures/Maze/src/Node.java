public class Node
{
    private int x;
    private int y;

    Node(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    int getX()
    {
        return this.x;
    }

    int getY()
    {
        return this.y;
    }

    @Override
    public String toString()
    {
        return "(" + this.x + "," + this.y + ")";
    }
}
