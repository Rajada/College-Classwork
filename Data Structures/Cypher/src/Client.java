public class Client
{
    public static void main (String[] args)
    {
        int[] key = {2, 5, 12, 1, 10, 16, 6};
        Integer keyValue;
        StringBuilder encoded = new StringBuilder();
        StringBuilder decoded = new StringBuilder();
        String message = "This is a secret message.";

        CircularArrayQueue<Integer> keyQueue1 = new CircularArrayQueue<>();
        CircularArrayQueue<Integer> keyQueue2 = new CircularArrayQueue<>();

        for (int i : key)
        {
            keyQueue1.enqueue(i);
            keyQueue2.enqueue(i);
        }

        for (int scan = 0; scan < message.length(); scan++)
        {
            keyValue = keyQueue1.dequeue();
            encoded.append((char) ((int) message.charAt(scan) + keyValue));
            keyQueue1.enqueue (keyValue);
        }
        System.out.println ("Encoded:\n" + encoded + "\n");

        for (int scan = 0; scan < encoded.length(); scan++)
        {
            keyValue = keyQueue2.dequeue();
            decoded.append((char) ((int) encoded.charAt(scan) - keyValue));
            keyQueue2.enqueue (keyValue);
        }

        System.out.println ("Decoded:\n" + decoded);
    }
}
