/**
 * 
 */
package test;

/**
 * @author ivooesch
 *
 */
public class Loewe extends Tier implements Krachmacher {

	/**
	 * @param NewName 
	 * 
	 */
	public Loewe(String NewName) {
		// TODO Auto-generated constructor stub	System.out.println("Kroak ich heisse " + Name + " Kroak");
		super(NewName);
	}

	/* (non-Javadoc)
	 * @see test.Krachmacher#KrachMachen()
	 */
	@Override
	public void KrachMachen() {
		// TODO Auto-generated method stub
		System.out.println("Loewe: Roaaar!!");

	}

	/* (non-Javadoc)
	 * @see test.Tier#BewegeDich()
	 */
	@Override
	public void BewegeDich() {
		// TODO Auto-generated method stub
		System.out.println("Loewe: Ich schleiche mich an");

	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Loewe l = new Loewe("Boss");
		Tier t = l;
		Krachmacher km = l; // v
		t.BewegeDich();
	    km.KrachMachen();
	    km = (Krachmacher) t;
	    km.KrachMachen();
	}

}


