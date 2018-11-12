/**
 * 
 */
package test;

/**
 * @author ivooesch
 *
 */
public abstract class Tier {
	
	
	String Name;
	
	public Tier(String NewName) {
		Name = NewName;
	}

	public void PrintName() {
		System.out.println("Mein Name ist " + Name);
	}
	
	abstract public void BewegeDich();
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
