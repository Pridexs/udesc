package bancormi;
//package sdi.trabfinal;
        
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Random;

public class ServidorNameService {
    public static void main(String args[]) {
        
        try {
            ImplementacaoNameService obj = new ImplementacaoNameService();
            NameService stub = (NameService) UnicastRemoteObject.exportObject(obj, 0);

            // Bind the remote object's stub in the registry
            Registry registry = LocateRegistry.getRegistry();
            registry.bind("NameService", stub);

            System.err.println("Servidor de Nomes executando");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
