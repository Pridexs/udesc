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
    public boolean bindService(String name, Remote object) {
        try {
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind(name, object);
            System.out.println("Service " + name + " bounded.");
            return true;
        } catch (RemoteException ex) {
            Logger.getLogger(ImplementacaoNameService.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return false;
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
