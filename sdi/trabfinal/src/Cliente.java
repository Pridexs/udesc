package bancormi;
//package sdi.trabfinal;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class Cliente {

    private Cliente() {}

    // falta adicionar
    // pra ele pedir de novo caso de erro
    public static void main(String[] args) {
        
        Scanner in = new Scanner(System.in);
        int option;
        int retorno_int, conta, contaDest;
        double valor, retorno_double;

        String host;
        
        if (args.length < 1) {
            // Em um programa real eu teria um dominio especifico para
            // hostear o servideo de nameservice para abstrair essa
            // parte do cliente.
            System.out.println("Execute passando o ip do servidor de nameservice!");
            return;
        } else { 
            host = args[0];
        }
        
        try {
            Registry registry = LocateRegistry.getRegistry(host);
            Banco stub = (Banco) registry.lookup("MasterServer");
            
            do {
                System.out.println("1. Criar nova conta");
                System.out.println("2. Depositar");
                System.out.println("3. Verificar saldo");
                System.out.println("4. Sacar");
                System.out.println("5. Transferir");
                System.out.println("0. Sair");
                System.out.print("\n> ");

                option = in.nextInt();
                in.nextLine();

                if (option == 1) {
                    System.out.println("Sua nova conta tem numero: " + stub.abreConta());
                } else if (option == 2) {
                    System.out.println("Digite o numero da conta em que ira depositar: ");
                    conta = in.nextInt();
                    System.out.println("Digite o valor a ser depositado: ");
                    valor = in.nextDouble();
                    
                    retorno_double = stub.depositar(conta, valor);
                    if (retorno_double == -1.0) {
                        System.out.println("Conta invalida!");
                    } else {
                        System.out.println("O novo saldo e: " + retorno_double);
                    }
                    
                } else if (option == 3) {
                    System.out.println("Digite o numero da conta: ");
                    conta = in.nextInt();
                    
                    retorno_double = stub.verificaSaldo(conta);
                    if (retorno_double == -1.0) {
                        System.out.println("Conta invalida!");
                    } else {
                        System.out.println("Saldo da conta: " + retorno_double);
                    }

                } else if (option == 4) {
                    System.out.println("Digite o numero da conta: ");
                    conta = in.nextInt();
                    System.out.println("Digite o valor a ser sacado: ");
                    valor = in.nextDouble();
                    
                    retorno_int = stub.sacar(conta, valor);
                    if (retorno_int == 3) {
                        System.out.println("Conta invalida!");
                    } else if (retorno_int == 2) {
                        System.out.println("Saldo insuficiente!");
                    } else if (retorno_int == 1) {
                        System.out.println("Saque efetuado com sucesso!");
                    } else {
                        System.out.println("ERRO INESPERADO AO SACAR! " + retorno_int);
                    }
                    
                } else if (option == 5) {
                    System.out.println("Digite o numero da conta de origem: ");
                    conta = in.nextInt();
                    System.out.println("Digite o nnumero da conta de destino: ");
                    contaDest = in.nextInt();
                    System.out.println("Digite o valor a ser transferido: ");
                    valor = in.nextDouble();
                    
                    retorno_int = stub.transferir(conta, contaDest, valor);
                    if (retorno_int == 4) {
                        System.out.println("Conta de destino invalida!");
                    } else if (retorno_int == 3) {
                        System.out.println("Conta de origem invalida!");
                    } else if (retorno_int == 2) {
                        System.out.println("Saldo insuficiente para transferir!");
                    } else if (retorno_int == 1) {
                        System.out.println("Transferencia efetuada com sucesso!");
                    } else {
                        System.out.println("ERRO INESPERADO AO SACAR! " + retorno_int);
                    }
                }
            } while(option != 0);

            //String response = stub.sayHello();
            //System.out.println("response: " + response);
        } catch (RemoteException re) {
            System.out.println("PRECISO ACHAR OUTROS SERVIDOR!");
        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
