package rsa;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author pridexs
 */
public class RSA {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int option;
        
        GeradorRSA grsa = new GeradorRSA(128);
        
        do {
            System.out.println("1. Gerar novas chaves publicas e privadas");
            System.out.println("2. Mostrar chaves publicas e privadas");
            System.out.println("3. Criptografar/ Descriptografar mensagem");
            System.out.println("4. Brute force attack");
            System.out.println("0. Sair");
            
            option = in.nextInt();
            in.nextLine();
            
            if (option == 1) {
                System.out.print("Digite quantos bytes a chave privada terá: ");
                int nBytes = in.nextInt();
                in.nextLine();
                grsa = new GeradorRSA(nBytes);
            } else if (option == 2) {
                grsa.imprimirChaves();
            } else if (option == 3) {
                System.out.println("\nDigite a string para criptografar:");
                String s = in.nextLine();
                System.out.println("");
                
                long tStart = System.nanoTime();
                ArrayList<BigInteger> c = grsa.criptografarString(s, 8);
                long tEnd = System.nanoTime();
                System.out.println("Demorou " + ( ((tEnd - tStart) / 1000000)) + " milisegundos para criptografar" );
                
                System.out.println("A array de bytes criptografada: ");
                System.out.println(c.toString());
                System.out.println("");
                
                System.out.println("Descriptografando: ");
                System.out.println(grsa.descriptografarString(c));
                System.out.println("");
            } else if (option == 4) {
                long tStart = System.nanoTime();
                
                grsa.ataqueForcaBruta();
                
                long tEnd = System.nanoTime();
                System.out.println("\nDemorou " + ( ((tEnd - tStart) / 1000000)) + " milisegundos para completar o ataque" );
            }
            
        } while(option != 0);
    }
   
    
}
