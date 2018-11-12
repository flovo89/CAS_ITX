/**
 * 
 */
package test;

/**
 * @author ivooesch
 *
 */
public class Papagei extends Vogel implements Krachmacher {

	/**
	 * @param NewName
	 */
	public Papagei(String NewName) {
		super(NewName);
		// TODO Auto-generated constructor stub
	}

	/* (non-Javadoc)
	 * @see test.Krachmacher#KrachMachen()
	 */
	@Override
	public void KrachMachen() {
		// TODO Auto-generated method stub
		System.out.println("Papagei: Kroak ich heisse " + Name + " Kroak");

	}

	/* (non-Javadoc)
	 * @see test.Vogel#NistplatzVorbereiten()
	 */
	@Override
	public void NistplatzVorbereiten() {
		// TODO Auto-generated method stub
		System.out.println("Papagei: Ich suche eine Hoehle");

	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Papagei p = new Papagei("Polly");
		Vogel v = p;
		Krachmacher km = p; // v
		v.PrintName();
		v.NistplatzVorbereiten();
	    km.KrachMachen();
	    km = (Krachmacher) v;
	    km.KrachMachen();

	}

}
