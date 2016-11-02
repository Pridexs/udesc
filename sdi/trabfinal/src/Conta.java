package bancormi;
//package sdi.trabfinal;

import java.io.Serializable;

        
public class Conta implements Serializable {

    private final static long serialVersionUID = 159624945;
    
    private int contaId;
    private double saldo;
        
    public Conta(int contaId) {
        this.contaId = contaId;
        this.saldo = 0.0;
    }

    public double depositar(double valor) {
        this.saldo += valor;
        return this.saldo;
    }

    // 2 - saldo insuficiente
    // 1 - sucesso
    public int sacar(double valor) {
        if (valor > saldo) {
            return 2;
        } else {
            saldo -= valor;
            return 1;
        }
    }

    public void setContaId(int contaId) {
        this.contaId = contaId;
    }

    public void setSaldo(double saldo) {
        this.saldo = saldo;
    }

    public int getContaId() {
        return this.contaId;
    }

    public double getSaldo() {
        return this.saldo;
    }
}