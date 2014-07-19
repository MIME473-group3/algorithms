import java.util.Iterator;


public class Subset {

	public static void main(String[] args) {
		
		assert(args.length > 0);
		int K = Integer.parseInt(args[0]);

		RandomizedQueue<String> rQue = new RandomizedQueue<String>();
		while(!StdIn.isEmpty()) {
			
			rQue.enqueue(StdIn.readString());
		}
		
		Iterator<String> it = rQue.iterator();
		for(int i = 0; i < K; ++i)
			System.out.println(it.next());
	}
}
