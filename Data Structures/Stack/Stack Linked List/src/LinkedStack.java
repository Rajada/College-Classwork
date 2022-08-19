public class LinkedStack<T> implements StackADT<T>
{
	private int count; 
	private LinearNode<T> top;

	/**
	 * Constructor
	 */
	public LinkedStack()
	{
		this.count = 0;
		this.top = null;
	}

	
	/* (non-Javadoc)
	 * @see itu.data.structure.stack.StackADT#push(java.lang.Object)
	 */
	public void push(Integer element)
	{
		LinearNode<T> temp = new LinearNode<T>(element);

		temp.setNext(this.top);
		this.top = temp;
		this.count++;
	}

	
	/* (non-Javadoc)
	 * @see itu.data.structure.stack.StackADT#pop()
	 */
	public Integer pop()
	{
		if (isEmpty())
		{
			throw new RuntimeException("Impossible to pop an element from the Stack when is empty");
		}
		Integer result = this.top.getElem();
		this.top = this.top.getNext();
		this.count--;

		return result;
	}

	
	/* (non-Javadoc)
	 * @see itu.data.structure.stack.StackADT#peek()
	 */
	public Integer peek()
	{
		if (isEmpty())
		{
			throw new RuntimeException("Impossible to peek an element from the Stack when is empty");
		}
		return this.top.getElem();
	}

	/* (non-Javadoc)
	 * @see itu.data.structure.stack.StackADT#isEmpty()
	 */
	public boolean isEmpty() {
		return (this.count == 0);
	}

	/* (non-Javadoc)
	 * @see itu.data.structure.stack.StackADT#size()
	 */
	public int size() {
		return this.count;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString()
	{
		String result = "";
		LinearNode<T> current = this.top;

		while (current != null)
		{
			result = result + (current.getElem()).toString() + "\n";
			current = current.getNext();
		}

		return result;
	}
}