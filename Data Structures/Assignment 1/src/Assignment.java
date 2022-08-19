public class Assignment
{
    private int [] A;
    private int [] B;

    Assignment(int [] InitialA, int [] InitialB)
    {
        A = InitialA;
        B = InitialB;
    }

    public String FindRankedNumber(int Rank)
    {
        int result = -1, AInt = A.length - 1, BInt = B.length - 1;
        String output= "";

        if(Rank == 1)
            output = Rank + "st largest number in the two arrays is ";
        else if(Rank == 2)
            output = Rank + "nd largest number in the two arrays is ";
        else if(Rank == 3)
            output = Rank + "rd largest number in the two arrays is ";
       else
            output = Rank + "th largest number in the two arrays is ";

        if((Rank < 1) || (Rank > (AInt + BInt + 2))) // Don't accept bad inputs
            return "Rank must be between 1 and " + (AInt + BInt + 2);

        for(int i = 0; i < Rank; i++)
        {
            if (AInt <= -1)
            {
                result = B[BInt];
                BInt--;
            }
            else if(BInt <= -1)
            {
                result = A[AInt];
                AInt--;
            }
            else
                {
                if (A[AInt] > B[BInt])
                {
                    result = A[AInt];
                    AInt--;
                }
                else
                    {
                    result = B[BInt];
                    BInt--;
                }
            }
        }

        output += result;
        return output;
    }
}
