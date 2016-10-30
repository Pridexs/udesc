package bancormi;
//package sdi.trabfinal;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Banco extends Remote {
    // Retorna o ID da conta
    int abreConta() throws RemoteException;
    
    // Retorna novo saldo
    double depositar(int contaId, double valor) throws RemoteException;

    // Retorna o saldo
    double verificaSaldo(int contaId) throws RemoteException;

    // Retorna um inteiro (1- sucesso, 2- saldo insuficiente)
    int sacar(int contaId, double qtd) throws RemoteException;

    // Transfere valor
    int transferir(int idOrigem, int idDestino, double valor) throws RemoteException;
}
