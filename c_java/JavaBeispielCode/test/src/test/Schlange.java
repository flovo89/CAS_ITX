/**
 * 
 */
package test;

/**
 * @author ivooesch
 *
 */
public class Schlange extends Tier {

	/**
	 * @param NewName 
	 * 
	 */
	public Schlange(String NewName) {
		// TODO Auto-generated constructor stub
		super(NewName);
	}

	/* (non-Javadoc)
	 * @see test.Tier#BewegeDich()
	 */
	@Override
	public void BewegeDich() {
		// TODO Auto-generated method stub
		System.out.println("Schlange: Ich schlaengle mich von dannen");

	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Schlange s = new Schlange("Martha");
		Tier t = s;
//		Krachmacher km = s; // v
		t.BewegeDich();
//	    km.KrachMachen();
//	    km = (Krachmacher) t;
//	    km.KrachMachen();

	}

}


