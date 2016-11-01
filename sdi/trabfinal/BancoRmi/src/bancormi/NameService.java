package bancormi;
//package sdi.trabfinal;
        
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface NameService extends Remote {
    // Da bind em um novo servidor
    String bindService(String name, Remote object) throws RemoteException;
    
    // Tira um servidor
    boolean unbindService(String name) throws RemoteException;
    
    // Elege um novo mestre
    int eleicao() throws RemoteException;
}

