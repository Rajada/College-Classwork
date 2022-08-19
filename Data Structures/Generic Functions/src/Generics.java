public class Generics
{
    public static <T extends Number> double AddNumbers(T num1, T num2)
    {
        double sum = num1.doubleValue() + num2.doubleValue();
        return sum;
    }
}
