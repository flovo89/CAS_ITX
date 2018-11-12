/**
 * 
 */
package test;

/**
 * @author ivooesch
 *
 */
public class Presslufthammer implements Krachmacher {

	/**
	 * 
	 */
	public Presslufthammer() {
		// TODO Auto-generated constructor stub
	}

	/* (non-Javadoc)
	 * @see test.Krachmacher#KrachMachen()
	 */
	@Override
	public void KrachMachen() {
		// TODO Auto-generated method stub
		System.out.println("Presslufthammer: Rattattatatttat!");

	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Presslufthammer p = new Presslufthammer();
		Krachmacher km = p; // v
	    km.KrachMachen();
	}

}
