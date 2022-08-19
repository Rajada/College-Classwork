public interface StackADT<T>
{
	public void push(Integer element);
	
	public Integer pop();
	
	public Integer peek();
	
	public boolean isEmpty();
	
	public int size();
	
	public String toString();
	
}
