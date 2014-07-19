import java.util.Iterator;
import java.util.NoSuchElementException;


/*
 * Your deque implementation must support each deque operation in constant worst-case time and use space proportional
 * to the number of items currently in the deque. Additionally, your iterator implementation must support the operations
 *  next() and hasNext() (plus construction) in constant worst-case time and use a constant amount of extra space per iterator.
 */
public class Deque<Item> implements Iterable<Item> {
	
	private Item[] container;
	private int begin;
	private int end;
	private int capacity;
	
// construct an empty deque
   @SuppressWarnings("unchecked")
public Deque() {	   
		capacity = 1;
		begin = 0;
		end = 0;
		container = (Item[]) new Object[1];
   }
   
 // is the deque empty?
   public boolean isEmpty() {
	   return begin == end;
   }
   
// return the number of items on the deque
   public int size() {
	   return end - begin;
   }
   
// insert the item at the front
   public void addFirst(Item item) {
	   if(item == null) throw new NullPointerException("Deque.addFirst");
	   
	   if(isEmpty()) {
		   container[begin] = item;
		   end++;
	   } else {
		   while(begin <= 0) 
			   this.enlarge();
		   
		   if(!isEmpty()) begin--;
		   container[begin] = item;
	   }	   
   }
   
// insert the item at the end
   public void addLast(Item item) {	   
	   if(item == null) throw new NullPointerException("Deque.addLast");
	   
	   if(end >= capacity)
		   this.enlarge();   

	   container[end] = item;
	   end++;	
   }
   
// delete and return the item at the front
   //throw a java.util.NoSuchElementException if the client attempts to remove an item from an empty deque
   public Item removeFirst() {	   
	   if(isEmpty()) throw new NoSuchElementException("Deque.removeFirst");
	   
	   Item tmp = container[begin];
	   container[begin] = null;
	   begin++;	   
	   
	   if(begin == end) {
		   begin = 0;
		   end = 0;
	   }
	   
	   if(size() < capacity / 2)
		   this.shrink();
	   
	   return tmp;
   }
   
// delete and return the item at the end
   public Item removeLast() {
	   if(isEmpty()) throw new NoSuchElementException("Deque.removeLast");
	   
	   end--;
	   Item tmp = container[end];
	   container[end] = null;
	   
	   if(size() < capacity / 2)
		   this.shrink();
	   
	   return tmp;
   }
   
// return an iterator over items in order from front to end
   public Iterator<Item> iterator() {	   
	   return new DequeIterator<Item>(container, begin, end);
   }
   
	@SuppressWarnings("unchecked")
	private void enlarge() {
		
		if(capacity == 0) {
			
			capacity = 1;
			begin = 0;
			end = 0;
			container = (Item[]) new Object[1];
		} else {
		
			resize(capacity * 2);
		}
	}
	
	private void shrink() {
		
		if(capacity == 0) return;
		int newCapacity = capacity / 2;
		if(newCapacity == 0) {
			
			container = null;
			begin = -1;
			end = -1;
			capacity = 0;
		} else {
			resize(newCapacity);
		}
	}
	
	private void resize(int capacity) {
		
		@SuppressWarnings("unchecked")
		Item[] tmpContainer = (Item[]) new Object[capacity];
		int newBegin = (capacity - size()) / 2;
		for(int i = begin; i < end; ++i)
			tmpContainer[newBegin++] = container[i];
		
		this.begin = (capacity - size()) / 2;
		this.end = newBegin;		
		this.container = tmpContainer;
		this.capacity = capacity;
	}
   
   @SuppressWarnings("hiding")
private class DequeIterator<Item> implements Iterator<Item> {
	   
	   private Item[] container;
	   private int begin;
	   private int end;
	   
	   public DequeIterator(Item[] container, int begin, int end){
		   
		   this.container = container;
		   this.begin = begin;
		   this.end = end;		   
	   }
	   
		@Override
		public boolean hasNext() {
			return end != begin;
		}
		
		@Override
		//throw a java.util.NoSuchElementException if the client calls the next() method in the iterator and there are no more items to return.
		public Item next() {
			if(begin == end) throw new NoSuchElementException("DequeIterator.next");
			
			begin++;			
			return container[begin - 1];
		}
		
		@Override
		public void remove() {
			throw new UnsupportedOperationException("DequeIterator.remove");
		}
   }
    
// unit testing
   public static void main(String[] args) {	   
	    
	   int N = 33554432;
	   int kmax = 1;
	   boolean quiet = true;
	   
	   for(int k = 0; k < kmax; ++k) {
//		   N *= 2;	   
		   
		   Stopwatch watch = new Stopwatch();
		   
		   Deque<Integer> deque = new Deque<Integer>();
		   
		   for(int i = 0; i < 5; i++) {
			   deque.addFirst(1);
			   deque.removeFirst();
		   }
		   
		   
		   for(int i = 0; i < 5; i++) {
			   deque.addFirst(1);
			   deque.removeLast();
		   }
		   
		   if(!quiet) System.out.println("Adding " + N + " first and " + N + " last elements\nfor a total of " + 2 * N + " elements");
		   for(int i = 0; i < N; ++i) {
			   deque.addFirst(StdRandom.uniform(100));
			   deque.addLast(StdRandom.uniform(100));
		   }
		   
		   int counter = 0;
		   Iterator<Integer> it = deque.iterator();
		   while(it.hasNext()) {
			   int a = it.next();
//			   System.out.print(Integer.toString(a));
//			   System.out.print(" ");
			   counter++;
		   }
		   if(!quiet) System.out.println();
		   if(!quiet) System.out.println("Size = " + Integer.toString(deque.size()));
		   if(!quiet) System.out.println("Printed " + Integer.toString(counter) + " elements");
		   
		   if(!quiet) System.out.println("Removing " + N + " first elements");
		   for(int i = 0; i < N; ++i) {
				   deque.removeFirst();
		   }
		   
		   if(!quiet) System.out.println("Size = " + Integer.toString(deque.size()));
		   
		   if(!quiet) System.out.println("Removing " + N + " first elements");
		   for(int i = 0; i < N; ++i) {
			   deque.removeLast();
		   }
		   
		   if(!quiet) System.out.println("Size = " + Integer.toString(deque.size()));
		   
		   if(!quiet) System.out.println("Adding " + N + " random elements");
		   for(int i = 0; i < N; ++i) {
			   if(StdRandom.uniform(2) == 0)
				   deque.addFirst(StdRandom.uniform(100));
			   else 
				   deque.addLast(StdRandom.uniform(100));
				   
	   }
		   if(!quiet) System.out.println("Size = " + Integer.toString(deque.size()));
		   
		   if(!quiet) System.out.println("Removing " + N + " random elements");
		   for(int i = 0; i < N; ++i) {
			   if(StdRandom.uniform(2) == 0)
				   deque.removeFirst();
			   else
				   deque.removeLast();
	   }
		   if(!quiet) System.out.println("Size = " + Integer.toString(deque.size()));
		   
		   
		   if(!quiet) System.out.println("N = " + N + "\t Took = " + watch.elapsedTime());
	   }	
   }
}