/**
 * 
 */
package test;

/**
 * @author ivooesch
 *
 */
public class Kraehe extends Vogel implements Krachmacher {

	/**
	 * @param NewName
	 */
	public Kraehe(String NewName) {
		super(NewName);
		// TODO Auto-generated constructor stub
	}

	/* (non-Javadoc)
	 * @see test.Krachmacher#KrachMachen()
	 */
	@Override
	public void KrachMachen() {
		// TODO Auto-generated method stub
		System.out.println("Kraehe: Krah! Krah!");

	}

	/* (non-Javadoc)
	 * @see test.Vogel#NistplatzVorbereiten()
	 */
	@Override
	public void NistplatzVorbereiten() {
		// TODO Auto-generated method stub
		System.out.println("Kraehe: Ich trage Zweige in Baumkronen");

	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Kraehe k = new Kraehe("Max");
		Vogel v = k;
		Krachmacher km = k; // v
		v.PrintName();
		v.NistplatzVorbereiten();
        km.KrachMachen();
        km = (Krachmacher) v;
        km.KrachMachen();
	}

}
