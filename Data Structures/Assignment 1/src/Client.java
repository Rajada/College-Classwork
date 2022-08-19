
public class Client
{
    public static void main(String[] args)
    {
        int [] InitialA = {2,3,5,7,34};
        int [] InitialB = {7,13,20};

        Assignment Assignment = new Assignment(InitialA, InitialB);
        System.out.println(Assignment.FindRankedNumber(1));
        System.out.println(Assignment.FindRankedNumber(2));
        System.out.println(Assignment.FindRankedNumber(3));
        System.out.println(Assignment.FindRankedNumber(4));
        System.out.println(Assignment.FindRankedNumber(5));
        System.out.println(Assignment.FindRankedNumber(6));
        System.out.println(Assignment.FindRankedNumber(7));
        System.out.println(Assignment.FindRankedNumber(8));
    }
}
