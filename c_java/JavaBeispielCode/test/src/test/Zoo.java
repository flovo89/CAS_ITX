/**
 * 
 */
package test;

import java.util.Vector;

/**
 * @author ivooesch
 *
 */
public class Zoo {
	
	Vector<Vogel> Voliere;
	Vector<Schlange> Terarium;
	Vector<Loewe> Kaefig;
	KrachmacherSammlung Laermviecher;
	Vector<Tier> Katalog;
	
	
	/**
	 * 
	 */
	public Zoo() {
		// TODO Auto-generated constructor stub
		Voliere = new Vector<Vogel>();
		Terarium= new Vector<Schlange>();
		Kaefig= new Vector<Loewe>();
	    Laermviecher= new KrachmacherSammlung();
	    Katalog= new Vector<Tier>();
	}

	public void TierHinzufuegen(Tier Neuzugang) {
		// TODO Auto-generated constructor stub
		Katalog.add(Neuzugang);
		
        if (Neuzugang instanceof Vogel) {
		   Voliere.add((Vogel) Neuzugang);
        }

        if (Neuzugang instanceof Schlange) {
        	Terarium.add((Schlange) Neuzugang);
        }

        if (Neuzugang instanceof Krachmacher) {
        	Laermviecher.AddLaermvieh((Krachmacher) Neuzugang);
        }

        if (Neuzugang instanceof Loewe) {
        	Kaefig.add((Loewe) Neuzugang);
        }
	}
	
	public void LaermmacherDazuschmuggeln(Presslufthammer Neuzugang) {
		// TODO Auto-generated constructor stub
        Laermviecher.AddLaermvieh(Neuzugang);
	}
	
	public void AlleTiereZeigen() {
		System.out.println("\nAlle Tiere:");
		for (Tier t: Katalog) {
			t.PrintName();
			t.BewegeDich();
			System.out.println();
		}
	}

	public void TerariumInhaltZeigen() {
		System.out.println("\nTerariumbewohner:");
		for (Schlange s: Terarium) {
			s.PrintName(); 
		}
	}

	public void KaefigInhaltZeigen() {
		System.out.println("\nKaefigbewohner:");
		for (Loewe l: Kaefig) {
			l.PrintName(); 
		}
	}

	public void VolierenInhaltZeigen() {
		System.out.println("\nVolierenbewohner:");
		for (Vogel v: Voliere) {
			v.PrintName();
			v.NistplatzVorbereiten();
			System.out.println();
		}
	}

	public void LauteTiereZeigen() {
		System.out.println("Laute Tiere:");
		Laermviecher.LassHoeren();
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Zoo MeinZoo = new Zoo();
		
		MeinZoo.TierHinzufuegen(new Loewe("Simba"));
		MeinZoo.TierHinzufuegen(new Amsel("Anna"));
		MeinZoo.TierHinzufuegen(new Schlange("Kaa"));
		MeinZoo.TierHinzufuegen(new Papagei("Rio"));
		MeinZoo.TierHinzufuegen(new Loewe("Schnurrli"));
		MeinZoo.TierHinzufuegen(new Schlange("Boa"));
		MeinZoo.TierHinzufuegen(new Kraehe("Abraxas"));
		MeinZoo.TierHinzufuegen(new Amsel("Arnold"));
		MeinZoo.TierHinzufuegen(new Papagei("Beo"));
		//MeinZoo.TierHinzufuegen(new Presslufthammer());
		MeinZoo.LaermmacherDazuschmuggeln(new Presslufthammer());
		
		
		
		
		MeinZoo.AlleTiereZeigen();
		MeinZoo.KaefigInhaltZeigen();
		MeinZoo.TerariumInhaltZeigen();
		MeinZoo.VolierenInhaltZeigen();
		MeinZoo.LauteTiereZeigen();

	}

}
