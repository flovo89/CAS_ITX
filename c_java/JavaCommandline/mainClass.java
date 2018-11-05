public class mainClass
{
	public static void main(String args[])
 	{
 		int nbrStudents;

 		System.out.println("Hello"); // Ausgabe "Hello"

 		if(args.length > 0) // Argument vorhanden?
 		{ // ja --> Anzahl Studierende bestimmen
 			nbrStudents = Integer.parseInt(args[0]);
 			System.out.println("Die Klasse hat " + nbrStudents + " Studierende");
 		}

 		System.exit(0); // Programm beenden
	} 
}

