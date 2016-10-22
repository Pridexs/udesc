package rsa;

import java.math.BigInteger;
import java.util.Random;
import java.util.Vector;


public class GeradorRSA {
    private BigInteger mP, mQ;
    private BigInteger mN, mE, mD;
    private int nBits;
    private Random random;
    
    GeradorRSA(int nBits) {
        random = new Random();
        this.nBits = nBits;
        
        mP = primoProvavel();
        mQ = primoProvavel();
        
        System.out.println("p: " + mP.toString());
        System.out.println("q: " + mQ.toString());
    }
    
    int geraPrimoPequeno() {
        return 65537;
    }
    
    void crivoErastotenes() {
        
    }
    
    BigInteger primoProvavel() {
        BigInteger n = new BigInteger(nBits-1, random);
        n = n.add(new BigInteger("1").shiftLeft(nBits-1));
        
        if ( n.mod(new BigInteger("2")).compareTo(BigInteger.ZERO) == 0) {
            n = n.add(BigInteger.ONE);
        }
        
        while ( ! testePrimalidade(n) ) {
            n = new BigInteger(nBits-1, random);
            n = n.add(new BigInteger("1").shiftLeft(nBits-1));
            
            if ( n.mod(new BigInteger("2")).compareTo(BigInteger.ZERO) == 0) {
                n = n.add(BigInteger.ONE);
            }
        }
        
        return n;
    }


    // Miller-Rabin test
    // Esse é um metodo que usei quando fiz o algoritmo pela primeira vez
    // Não é muito igual ao que o professor fez mas funcionou pra varios casos
    // de teste. Ver se precisa refazer depois.
    boolean testePrimalidade(BigInteger n) {
        
        BigInteger s = n.subtract(new BigInteger("1"));
        int t = 0;
        BigInteger a, v;
        
        while ( s.mod(new BigInteger("2")).equals(BigInteger.ZERO) ) {
            s = s.shiftRight(1);
            t++;
        }
        
        for (int j = 0; j < 64; j++) {
            do {
                a = new BigInteger(nBits, random);
            } while (a.compareTo(n) < 0);
            
            v = expModular(a, s, n);
            
            if ( v.compareTo(BigInteger.ONE) != 0 ) {
                int i = 0;
                while ( v.compareTo(n.subtract(BigInteger.ONE)) != 0 ) {
                    if (i == t-1) {
                        return false;
                    } else {
                        i++;
                        
                        v = expModular(v, new BigInteger("2"), n);
                    }
                }
            }
        }
        
        return true;

    }
    
    BigInteger inversoModular(BigInteger a, BigInteger n) {
        Tripla_egcd egcd = gcdExt(a, n);
        return egcd.x.mod(n);
    }
    
    BigInteger expModular(BigInteger num, BigInteger exp, BigInteger n) {
        BigInteger z = new BigInteger("1");
        num = num.mod(n);
        while (exp.compareTo(BigInteger.ZERO) > 0) {
            if (exp.mod(new BigInteger("2")).compareTo(BigInteger.ONE) == 0) {
                z = z.multiply(num);
                z = z.mod(n);
            }
            exp = exp.shiftRight(1);
            num = num.multiply(num);
            num = num.mod(n);
        }
        return z;
    }
    
    Tripla_egcd gcdExt(BigInteger a, BigInteger b) {
        if (b.compareTo(BigInteger.ZERO) == 0)
            return new Tripla_egcd(a, new BigInteger("1"), new BigInteger("0"));
        
        Tripla_egcd rlinha = gcdExt(b, a.mod(b));
        Tripla_egcd r = new Tripla_egcd(rlinha.gcd, rlinha.y,
            rlinha.x.subtract( a.divide(b).multiply(rlinha.y) ));
        
        return r;
    }
    
    String ataqueForcaBruta(String msg, int e, BigInteger n) {
        return "a";
    }

    /*
     *====== SETTERS & GETTERS ======
     */
    
    public BigInteger getmP() {
        return mP;
    }

    public void setmP(BigInteger mP) {
        this.mP = mP;
    }

    public BigInteger getmQ() {
        return mQ;
    }

    public void setmQ(BigInteger mQ) {
        this.mQ = mQ;
    }

    public BigInteger getmN() {
        return mN;
    }

    public void setmN(BigInteger mN) {
        this.mN = mN;
    }

    public BigInteger getmE() {
        return mE;
    }

    public void setmE(BigInteger mE) {
        this.mE = mE;
    }

    public BigInteger getmD() {
        return mD;
    }

    public void setmD(BigInteger mD) {
        this.mD = mD;
    }
    
}
