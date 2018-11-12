/**
 * 
 */
package test;

import java.util.Vector;

/**
 * @author ivooesch
 *
 */
public class KrachmacherSammlung {
	
	Vector<Krachmacher> Plagegeister;

	/**
	 * 
	 */
	public KrachmacherSammlung() {
		// TODO Auto-generated constructor stub
		Plagegeister = new Vector<Krachmacher>();
	}
	
	public void AddLaermvieh(Krachmacher km) {
		Plagegeister.add(km);
	}

	public void LassHoeren() {
		for (Krachmacher k: Plagegeister) {
			k.KrachMachen();
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		KrachmacherSammlung l = new KrachmacherSammlung();
		
		l.AddLaermvieh(new Krachmacher() {
			public void KrachMachen() {
              System.out.println("Test 1");				
			}});

		l.AddLaermvieh(new Krachmacher() {
			public void KrachMachen() {
              System.out.println("Test 2");				
			}});
		l.AddLaermvieh(new Krachmacher() {
			public void KrachMachen() {
              System.out.println("Test 3");				
			}});
		l.LassHoeren();
	}

}
