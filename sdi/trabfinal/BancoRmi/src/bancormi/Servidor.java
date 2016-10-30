package bancormi;
//package sdi.trabfinal;
        
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;
        
public class Servidor {
        
    public Servidor() {}
        
    public static void main(String args[]) {

        String host;
        boolean bRetorno;
        
        if (args.length < 1) {
            // Em um programa real eu teria um dominio especifico para
            // hostear o servideo de nameservice para abstrair essa
            // parte do cliente.
            System.out.println("Execute passando o ip do servidor de nameservice!");
            return;
        } else { 
            host = args[0];
        }
        
        Registry registry;
        
        
        try {
            ImplementacaoBanco obj = new ImplementacaoBanco();
            Banco stub = (Banco) UnicastRemoteObject.exportObject(obj, 0);
            registry = LocateRegistry.getRegistry(host);
            NameService sns = (NameService) registry.lookup("NameService");
            
            bRetorno = sns.bindService("MasterServer", stub);
            
            if (bRetorno) {
                System.out.println("Servidor Banco ativo");
            } else {
                System.out.println("Erro");
            }
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
