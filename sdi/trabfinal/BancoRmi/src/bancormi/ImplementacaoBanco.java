/*
 * Alexandre Maros & Nadyan S. Pscheidt
 * Implementacao das funcoe do Banco [servidor]
 * 
 * Algumas notas:
 *   - Estamos usando uma simples ArrayList e a busca nao esta otimizada
 *   resolvemos fazer assim, inicialmente por simplicidade, e caso 
 *   sobrasse tempo, colocariamos uma estrutura mais otimizada, como por 
 *   exemplo uma hash table.
 */


package bancormi;
//package sdi.trabfinal;
        
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Random;

public class ImplementacaoBanco implements Banco {
        
    private ArrayList<Conta> contas;
    private String name;

    public ImplementacaoBanco() {
        contas = new ArrayList<Conta>();
        
    }

    // Retorna o ID da conta
    public int abreConta() {
        Random rnd = new Random();
        boolean existe = false;
        int id;
        
        do {
            id = 1000 + rnd.nextInt(9000);
            existe = false;
            for (int i = 0; i < contas.size(); i++) {
                if (contas.get(i).getContaId() == id) {
                    existe = true;
                    break;
                }
            }
        } while (existe);
        
        Conta conta = new Conta(id);
        contas.add(conta);
        return id;
    }
    
    // Retorna novo saldo
    // se -1.0 == nao achou contaid 
    public double depositar(int contaId, double valor) {
        for (int i = 0; i < contas.size(); i++) {
            if (contas.get(i).getContaId() == contaId) {
                return contas.get(i).depositar(valor);
            }
        }
        return -1.0;
    }

    // Retorna o saldo
    // -1.0 se nao achou contaId
    public double verificaSaldo(int contaId) {
        for (int i = 0; i < contas.size(); i++) {
            if (contas.get(i).getContaId() == contaId) {
                return contas.get(i).getSaldo();
            }
        }
        return -1.0;
    }

    // Retorna um inteiro (1- sucesso, 2- saldo insuficiente, 3- id ivalido)
    public int sacar(int contaId, double qtd) {
        for (int i = 0; i < contas.size(); i++) {
            if (contas.get(i).getContaId() == contaId) {
                return contas.get(i).sacar(qtd);
            }
        }
        return 3;
    }

    // Transfere valor
    // 3 - idOrigem invalido
    // 4 - idDestino invalido
    // 2 - saldo insuficiente idOrigem
    // 1 - sucesso
    public int transferir(int idOrigem, int idDestino, double valor) {
        Conta c1, c2;
        c1 = null;
        c2 = null;
        
        for (int i = 0; i < contas.size(); i++) {
            if (c1 != null && contas.get(i).getContaId() == idOrigem) {
                c1 = contas.get(i);
            } else if (c2 != null && contas.get(i).getContaId() == idDestino) {
                c2 = contas.get(i);
            }
            if (c1 != null && c2 != null) {
                break;
            }
        }

        if (c1 == null) {
            return 3;
        }

        if (c2 == null) {
            return 4;
        }

        int saida = c1.sacar(valor);
        // saida == 2 (saldo insuficiente)
        if (saida == 2) {
            return 2;
        }

        c2.depositar(valor);

        return 1;
    }
    
    public boolean isAlive() {
        return true;
    }
    
    public void setServerName(String name) {
        this.name = name;
    }
}
