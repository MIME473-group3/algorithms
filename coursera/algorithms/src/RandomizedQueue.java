import java.util.Iterator;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item> implements Iterable<Item> {
	
	private Item[] container;
	private int i;
	private int capacity;
	
	// construct an empty randomized queue
   @SuppressWarnings("unchecked")
public RandomizedQueue() {   
   
	   container = (Item[]) new Object[1];
	   i = 0;
	   capacity = 1;
   }
   
// is the queue empty?
   public boolean isEmpty()  {   
	   return i == 0;
   } 
   
// return the number of items on the queue
   public int size()       {   
	   return i;
   }            
   
// add the item
   public void enqueue(Item item) {   
	   if(item == null) throw new NullPointerException("RandomizedQueue.enqueue");
	   if(i == capacity || i < 0)
		   this.enlarge();
	   
	   container[i] = item;
	   ++i;	   
   }
   
// delete and return a random item
   public Item dequeue()           {   
	   if(isEmpty()) throw new NoSuchElementException("RandomizedQueue.dequeue");	   
	   
	   int random = StdRandom.uniform(i);
	   Item it = container[random];
	   container[random] = null;
	   --i;
	   swap(random, i);
	   
	   if(i < capacity / 2)
		   this.shrink();  
	   
	   return it;
   }
   
// return (but do not delete) a random item
   public Item sample()    {   
	   if(isEmpty()) throw new NoSuchElementException("RandomizedQueue.sample");
	   return container[StdRandom.uniform(i)];
   }                  
   
// return an independent iterator over items in random order
   public Iterator<Item> iterator() {   
	   
	   return new RandomizedQueueIterator<Item>(container, i);
   }  
	@SuppressWarnings("unchecked")
	private void enlarge() {
		
		if(capacity == 0) {
			
			capacity = 1;
			i = 0;
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
			i = -1;
			capacity = 0;
		} else {
			resize(newCapacity);
		}
	}
	
	private void resize(int capacity) {
		
		@SuppressWarnings("unchecked")
		Item[] tmpContainer = (Item[]) new Object[capacity];
		for(int j = 0; j < i; ++j)
			tmpContainer[j] = container[j];
		
		this.container = tmpContainer;
		this.capacity = capacity;
	}
   
   private void swap(int a, int b) {
	   
	   Item it = container[a];
	   container[a] = container[b];
	   container[b] = it;
   }
   
   /*
    * The order of two or more iterators to the same randomized queue should 
    * be mutually independent; each iterator must maintain its own random order.
    */
   @SuppressWarnings("hiding")
private class RandomizedQueueIterator<Item> implements Iterator<Item> {
	   
	private Item[] container;
	private int[] indices;
	private int i;
	
	public RandomizedQueueIterator(final Item[] container, int i) {
		
		this.container = container;
		this.i = i;
		
		if(hasNext()) {
			indices = new int[i];
			for(int j = 0; j < i; ++j)
				indices[j] = j;
		}		
	}
	   
	@Override
	public boolean hasNext() {
		return i > 0;
	}
	
	@Override
	public Item next() {
		if(i <= 0) throw new NoSuchElementException("RandomizedQueueIterator.next");
		
		int random = StdRandom.uniform(i);
		int index = indices[random];
		Item it = container[index];
		--i;
		swapInds(random, i);
		return it;
	}
	
	@Override
	public void remove() {
		throw new UnsupportedOperationException("RandomizedQueueIterator.remove");		
	}
	
	private void swapInds(int a, int b) {
		int ind = indices[a];
		indices[a] = indices[b];
		indices[b] = ind;
	}
   }
   
// unit testing   
   public static void main(String[] args)  {   
	   int N = 1;//33554432;
	   int kmax = 100;
	   boolean quiet = true;
	   
	   for(int k = 0; k < kmax; ++k) {
		   N *= 2;	   
		   
		   Stopwatch watch = new Stopwatch();
		   
		   RandomizedQueue<Integer> queue = new RandomizedQueue<Integer>();
		   
		   if(!quiet) System.out.println("Enqueing " + N + " consecutive elements starting from 0");
		   for(int i = 0; i < N; ++i)
			   queue.enqueue(i);		  
		   
		   if(!quiet) System.out.println("Iterating over all " + N + " elements");
		   int counter = 0;
		   Iterator<Integer> it = queue.iterator();
		   while(it.hasNext()) {
			   int a = it.next();
			   if(!quiet) System.out.print(Integer.toString(a));
			   if(!quiet) System.out.print(" ");
			   counter++;
		   }
		   if(!quiet) System.out.println();
		   if(!quiet) System.out.println("Size = " + Integer.toString(queue.size()));
		   if(!quiet) System.out.println("Printed " + Integer.toString(counter) + " elements");
		   
		   counter = 0;
		   if(!quiet) System.out.println("Sampling " + N + " elements");
		   for(int i = 0; i < N; ++i) {
			   int a = queue.sample();
			   if(!quiet) System.out.print(Integer.toString(a));
			   if(!quiet) System.out.print(" ");
			   counter++;
		   }
		   if(!quiet) System.out.println();
		   if(!quiet) System.out.println("Size = " + Integer.toString(queue.size()));
		   if(!quiet) System.out.println("Printed " + Integer.toString(counter) + " elements");
		   
		   counter = 0;
		   if(!quiet) System.out.println("Dequeing " + N + " elements");
		   for(int i = 0; i < N; ++i) {
			   int a = queue.dequeue();
			   if(!quiet)System.out.print(Integer.toString(a));
			   if(!quiet)System.out.print(" ");
			   counter++;
		   }
		   if(!quiet) System.out.println();
		   if(!quiet) System.out.println("Size = " + Integer.toString(queue.size()));
		   if(!quiet) System.out.println("Printed " + Integer.toString(counter) + " elements");
		   
		   
		   if(!quiet) System.out.println("Enqueing " + N + " consecutive elements starting from 0");
		   for(int i = 0; i < N; ++i)
			   queue.enqueue(i);		  
		   
		   if(!quiet) System.out.println("Iterating with two different iterators over all " + N + " elements");
		   counter = 0;
		   Iterator<Integer> itA = queue.iterator();
		   Iterator<Integer> itB = queue.iterator();
		   StringBuilder builderA = new StringBuilder();
		   StringBuilder builderB = new StringBuilder();
		   while(itB.hasNext() && itB.hasNext()) {
			   int A = itA.next();
			   int B = itB.next();
			   if(!quiet) builderA.append(A + " ");
			   if(!quiet) builderB.append(B + " ");
			   counter++;
		   }
		   if(!quiet) System.out.println();
		   if(!quiet) System.out.println("Size = " + Integer.toString(queue.size()));
		   if(!quiet) System.out.println("Iterated over " + Integer.toString(counter) + " elements");
		   if(!quiet) System.out.println("Iterator A = ");
		   if(!quiet) System.out.println(builderA.toString());
		   if(!quiet) System.out.println("Iterator B = ");
		   if(!quiet) System.out.println(builderB.toString());
		   
		   System.out.println("N = " + N + "\t Took = " + watch.elapsedTime());
	   }	
   }
}