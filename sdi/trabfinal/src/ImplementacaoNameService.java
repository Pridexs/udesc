package bancormi;
//package sdi.trabfinal;
        
import java.rmi.AccessException;
import java.rmi.AlreadyBoundException;
import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ImplementacaoNameService implements NameService {
    // Da bind em um novo servidor
    public String bindService(String name, Remote object) throws AccessException {
        Registry registry;
        ArrayList<String> registros = new ArrayList<String>();
        try {
            registry = LocateRegistry.getRegistry();
            String[] boundedNames = registry.list();
            for (int i = 0; i < boundedNames.length; i++) {
                registros.add(boundedNames[i]);
            }
        } catch (RemoteException ex) {
            Logger.getLogger(ImplementacaoNameService.class.getName()).log(Level.SEVERE, null, ex);
            return "ERROR";
        }

        String newName = name;
        boolean nomeEmUso = false;

        // Se for 1 nao tem ServidorMestre entao seja o mestre.
        if (registros.size() == 1) {
            try {
                registry.bind(newName, object);
            } catch (RemoteException ex) {
                Logger.getLogger(ImplementacaoNameService.class.getName()).log(Level.SEVERE, null, ex);
            } catch (AlreadyBoundException ex) {
                Logger.getLogger(ImplementacaoNameService.class.getName()).log(Level.SEVERE, null, ex);
            }
        } else { 
            // Se nao, seja um escravo.
            name = "Slave";

            boolean encontrou = false;
            int numeroSlave = 1;
            while (!encontrou) {
                newName = name + numeroSlave;
                try {
                    Banco stub = (Banco) registry.lookup(newName);
                    encontrou = ! stub.isAlive();
                } catch (RemoteException ex) {
                    System.out.println("Encontrei um possivel lugar. Nome: " + newName);
                    try {
                        registry.rebind(newName, object);
                        break;
                        //Logger.getLogger(ImplementacaoNameService.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (RemoteException ex1) {
                        // Nao deve ocorrer
                        Logger.getLogger(ImplementacaoNameService.class.getName()).log(Level.SEVERE, null, ex1);
                        return "ERROR";
                    }
                } catch (NotBoundException ex) {
                    try {
                        // se nao tem, adicione como newName
                        registry.rebind(newName, object);
                        break;
                    } catch (RemoteException ex1) {
                        Logger.getLogger(ImplementacaoNameService.class.getName()).log(Level.SEVERE, null, ex1);
                        return "ERROR";
                    }
                }
                numeroSlave++;
            }
        }
        System.out.println("Service " + newName + " bounded.");
        return newName;
 
    }
    
    // Tira um servidor
    public boolean unbindService(String name) {
        try {
            Registry registry = LocateRegistry.getRegistry();
            registry.unbind(name);
            return true;
        } catch (RemoteException ex) {
            Logger.getLogger(ImplementacaoNameService.class.getName()).log(Level.SEVERE, null, ex);
        } catch (NotBoundException ex) {
            Logger.getLogger(ImplementacaoNameService.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return false;
    }
    
    // Elege um novo mestre
    public int eleicao() {
        return 0;
    }
}
