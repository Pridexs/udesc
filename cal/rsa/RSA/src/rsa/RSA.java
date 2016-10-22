package rsa;

import java.math.BigInteger;
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
            System.out.println("3. Criptografar mensagem");
            System.out.println("4. Descriptografar mensagem");
            System.out.println("5. Brute force attack");
            System.out.println("0. Sair");
            
            
            option = in.nextInt();
            
            switch (option) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    BigInteger c = grsa.criptografarString("alexandre maros uhuhudsug");
                    System.out.println(c.toString());
                    System.out.println(grsa.descriptografarString(c));
                    break;
                case 4:
                    break;
                case 5:
                    break;
            }
            
        } while(option != 0);
    }
    
}
