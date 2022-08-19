public class CircularArrayQueue<T> implements QueueADT<T>
{
    private T[] queue;
    private int head, tail, size;
    private final static int LIMIT_SIZE = 50;

    public CircularArrayQueue()
    {
        this.queue = (T[]) new Object[LIMIT_SIZE];
        this.head = tail = size = 0;
    }

    public CircularArrayQueue(int initSize)
    {
        this.queue = (T[]) new Object[initSize];
        this.head = tail = size = initSize;
    }

    private void expandCapacity()
    {
        T[] larger = (T[])(new Object[queue.length *2]);
        for(int scan=0; scan < size; scan++)
        {
            larger[scan] = queue[head];
            head = (head + 1) % queue.length;
        }
        head = 0;
        tail = size;
        queue = larger;
    }

    @Override
    public void enqueue (T element)
    {
        if (size() == queue.length)
            expandCapacity();
        queue[tail] = element;
        tail = (tail + 1) % queue.length;
        size++;
    }

    @Override
    public T dequeue()
    {
        if (isEmpty())
            throw new RuntimeException("Cannot dequeue from empty queue");

        T result = queue[head];
        queue[head] = null;
        head = (head+1) % queue.length;
        size--;
        return result;
    }

    @Override
    public T first()
    {
        if (isEmpty())
        {
            throw new RuntimeException("Queue is empty");
        }
        return this.queue[this.head - 1];
    }

    @Override
    public boolean isEmpty()
    {
        return size == 0;
    }

    @Override
    public int size()
    {
        return size;
    }

    @Override
    public String toString()
    {
        StringBuilder result = new StringBuilder();
        int count = size;
        int i = head;

        while(count > 0)
        {
            result.append(queue[i]);
            i--;
            count--;

            if(i < 0)
                i = size - 1;
        }

        return result.toString();
    }
}
