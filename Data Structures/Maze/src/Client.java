import java.io.File;
import java.io.FileNotFoundException;

public class Client
{
	public static void main(String[] args) throws FileNotFoundException
	{
		File mazeFile = new File("src/Maze.txt");
		Maze Maze = new Maze(mazeFile);

		System.out.println(Maze);

		if(Maze.NavigateMaze())
			System.out.println("The maze is solved.");
		else
			System.out.println("The maze is unsolvable.");

		System.out.println(Maze);
	}
}
