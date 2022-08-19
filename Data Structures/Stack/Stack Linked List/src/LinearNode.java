public class LinearNode<T>
{
	private LinearNode next;
	private Integer elem;
	
	public LinearNode()
	{
		this.next = null;
		this.elem = null;
	}
	
	public LinearNode(Integer elem)
	{
		this.next = null;
		this.elem = elem;
	}

	public LinearNode getNext() {
		return this.next;
	}
	
	public void setNext(LinearNode node) {
		this.next = node;
	}
	
	public Integer getElem() {
		return this.elem;
	}
	
	public void setElem(Integer elem) {
		this.elem = elem;
	}
}
