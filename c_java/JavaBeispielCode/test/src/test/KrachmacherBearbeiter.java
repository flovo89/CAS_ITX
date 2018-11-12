/**
 * 
 */
package test;

/**
 * @author ivooesch
 *
 */
public class KrachmacherBearbeiter {
	
	Krachmacher MeinKrach;
	
	public KrachmacherBearbeiter(Krachmacher km) 
	{
		MeinKrach = km;
	}
	
	public void Bearbeite()
	{
		MeinKrach.KrachMachen();
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		class Testclass implements Krachmacher {

			@Override
			public void KrachMachen() {
				// TODO Auto-generated method stub
                System.out.println("Test Sucessfull");				
			}
			
		}
		System.out.println("Testing KrachmacherBearbeiter...");
		
		KrachmacherBearbeiter kmb = new KrachmacherBearbeiter(new Testclass());
		
		KrachmacherBearbeiter kmb2 = new KrachmacherBearbeiter(new Krachmacher() {

			   @Override
			   public void KrachMachen() {
                  System.out.println("Test Sucessfull");				
			   }
			});
		kmb.Bearbeite();
		kmb2.Bearbeite();

		System.out.println("the 2 Lines above should read 'Test Sucessfull', Testing done...");
	}

}
