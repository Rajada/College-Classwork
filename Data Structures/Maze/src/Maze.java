import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Maze
{
    private final int TRIED = 3;

    private int [][] grid = {{1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1}};

    Maze(File mazeFile) throws FileNotFoundException
    {
        if(mazeFile.exists())
        {
            Scanner sc = new Scanner(mazeFile);
            sc.useDelimiter(",");

            while(sc.hasNextInt())
            {
                for(int row = 0; row < grid.length; row ++)
                    for(int col = 0; col < grid[0].length; col ++)
                    {
                        System.out.println(row + " " + col);
                        grid[row][col] = sc.nextInt();

                    }
            }

            sc.close();
        }
    }

    public boolean NavigateMaze()
    {
        boolean done = false;
        Node currentNode = new Node(0,0);
        StackADT<Node> stack = new ArrayStack<> ();
        stack.push(currentNode);
        while (!(done))
        {
            currentNode = stack.pop();
            grid[currentNode.getX()][currentNode.getY()] = TRIED;
            if (currentNode.getX() == grid.length-1 && currentNode.getY() == grid[0].length-1)
                done = true;
            else
            {
                stack = addNode(currentNode.getX(),currentNode.getY() - 1, stack);
                stack = addNode(currentNode.getX(),currentNode.getY() + 1, stack);
                stack = addNode(currentNode.getX() - 1,currentNode.getY(), stack);
                stack = addNode(currentNode.getX() + 1,currentNode.getY(), stack);
            }
        }

        return done;
    }

    private boolean isValid (int row, int column)
    {
        boolean result = false;

        if ((row >= 0 && row < grid.length) && (column >= 0 && column < grid[row].length))
            if (grid[row][column] == 1)
                result = true;
        return result;
    }

    private StackADT<Node> addNode(int x, int y, StackADT<Node> stack)
    {
        Node npos = new Node(x, y);

        if (isValid(npos.getX(),npos.getY()))
            stack.push(npos);
        return stack;
    }

    @Override
    public String toString()
    {
        StringBuilder output = new StringBuilder();

        for (int[] ints : grid)
        {
            for (int col = 0; col < grid[0].length; col++)
                output.append(ints[col]);
            output.append("\n");
        }

        return output.toString();
    }
}
