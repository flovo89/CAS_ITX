/**
 * 
 */
package test;

/**
 * @author ivooesch
 *
 */
public abstract class Vogel extends Tier{
	
	
	public Vogel(String NewName) {
		super(NewName);
	}
	
	abstract public void NistplatzVorbereiten(); 
	
	
	@Override
	public void BewegeDich() {
		System.out.println("Vogel: Ich fliege");
	
	}
	


}
