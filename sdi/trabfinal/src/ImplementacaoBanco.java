package sdi.trabfinal;
        
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

public class ImplementacaoBanco implements Banco {
        
    private ArrayList<Conta> contas;
    private int counterContas;

    public ImplementacaoBanco() {
        contas = new ArrayList<Conta>();
        counterContas = 0;
    }

    // Retorna o ID da conta
    public int abreConta() {
        int id = counterContas;
        counterContas++;
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
}
