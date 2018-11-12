/**
 * 
 */
package test;

/**
 * @author ivooesch
 *
 */
public class Amsel extends Vogel  {

	/**
	 * @param NewName
	 */
	public Amsel(String NewName) {
		super(NewName);
		// TODO Auto-generated constructor stub
	}

	
	/* (non-Javadoc)
	 * @see test.Vogel#NistplatzVorbereiten()
	 */
	@Override
	public void NistplatzVorbereiten() {
		// TODO Auto-generated method stub
		System.out.println("Amsel: Ich trage Lehm, Moos und Haare in ein Gebuesch");
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Amsel a = new Amsel("Anna");
		Vogel v = a;
		//Krachmacher km = (Krachmacher)a; // v
		v.PrintName();
		v.NistplatzVorbereiten();
      //  km.KrachMachen();
     //   km = (Krachmacher) v;
     //   km.KrachMachen();

	}

}
