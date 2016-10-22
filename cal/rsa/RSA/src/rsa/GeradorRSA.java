package rsa;

import java.math.BigInteger;
import java.util.ArrayList;
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
        
        mN = mP.multiply(mQ);
        
        mE = new BigInteger(Integer.toString(geraPrimoPequeno()));
        BigInteger x = mP.subtract(BigInteger.ONE).multiply(mQ.subtract(BigInteger.ONE));
        while (mE.gcd(x).compareTo(BigInteger.ONE) != 0) {
            mE = new BigInteger(Integer.toString(geraPrimoPequeno()));
        }
        
        mD = inversoModular(mE, x);
        
        imprimirChaves();
    }
    
    int geraPrimoPequeno() {
        // Pega um dos ultimos 20% primos gerados no cravo erastotenes
        ArrayList<Integer> primos = crivoErastotenes(1000000);
        Random rnd = new Random();
        int index = rnd.nextInt( (int) (0.2 * primos.size()) ) + 1;

        return primos.get(primos.size() - index);
    }
    
    ArrayList<Integer> crivoErastotenes(int limite) {
        ArrayList<Integer> primos = new ArrayList<Integer>();
        boolean[] ehComposto = new boolean[limite];
        int sqrtLimite = (int) Math.sqrt(limite);
        
        for (int i = 2; i <= sqrtLimite; i++) {
            if (!ehComposto[i]) {
                primos.add(i);
                for (int j = i*i; j < limite; j += i) {
                    ehComposto[j] = true;
                }
            }
        }
        
        for (int i = sqrtLimite + 1; i < limite; i++) {
            if (!ehComposto[i]) {
                primos.add(i);
            }
        }
        
        return primos;
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
    
    ArrayList<BigInteger> criptografarString(String m, int nBytes) {
        // Quebra a string em blocos de nBytes
        ArrayList<byte[]> bytes = new ArrayList<byte[]>();
        ArrayList<BigInteger> crip = new ArrayList<BigInteger>();
        byte[] mbytes = m.getBytes();
        int count = 0;
        
        int nBlocks = (int) Math.ceil( ((double) mbytes.length) / ((double) nBytes));
        
        for (int i = 0; i < nBlocks; i++) {
            int tamanhoBloco;
            if (nBlocks == 1) {
                tamanhoBloco = mbytes.length;
            } else {
                tamanhoBloco = nBytes - (((nBytes*(i+1)) % mbytes.length) % nBytes);
            }
            byte[] bloco = new byte[tamanhoBloco];
            count = 0;
            for (int j = nBytes*i; j < nBytes*i + tamanhoBloco; j++ ) {
                bloco[count++] = mbytes[j];
            }
            bytes.add(bloco);
        }
        
        for (int i = 0; i < nBlocks; i++) {
            crip.add(expModular(new BigInteger(bytes.get(i)), mE, mN));
        }

        return crip;
    }
    
    String descriptografarString(ArrayList<BigInteger> crip) {
        String mensagem = "";
        
        for (int i = 0; i < crip.size(); i++) {
            mensagem += new String(expModular(crip.get(i), mD, mN).toByteArray());
        }
       
        return  mensagem;
    }
    
    String ataqueForcaBruta() {
        
        long tStart = System.nanoTime();
        
        BigInteger publicN = mN;
        
        BigInteger bruteforceP = new BigInteger("1");
        BigInteger bruteforceQ;
        BigInteger bruteforceD;
                
        BigInteger nbytwo = publicN.divide(new BigInteger("2"));
        
        if (nbytwo.mod(new BigInteger("2")).compareTo(BigInteger.ZERO) == 0) {
            nbytwo = nbytwo.subtract(BigInteger.ONE);
        }
        
        for (BigInteger i = nbytwo; i.compareTo(BigInteger.ZERO) > 0; i = i.subtract(new BigInteger("2"))) {
            if (publicN.mod(i).compareTo(BigInteger.ZERO) == 0) {
                bruteforceP = i;
                break;
            }
        }
        
        bruteforceQ = publicN.divide(bruteforceP);
        
        System.out.println(publicN);
        System.out.println(mE);
        System.out.println(bruteforceP);
        System.out.println(bruteforceQ);
        bruteforceD = inversoModular(mE, bruteforceP.subtract(BigInteger.ONE)
            .multiply(bruteforceQ.subtract(BigInteger.ONE)));
        
        long tEnd = System.nanoTime();
        System.out.println("\nDemorou " + ( ((tEnd - tStart) / 1000000)) + " milisegundos para completar" );
        
        if (bruteforceD.compareTo(mD) == 0) {
            
            System.out.println("Ataque forca bruta: ");
            System.out.println("p: " + bruteforceP);
            System.out.println("q: " + bruteforceQ);
            System.out.println("d: " + bruteforceD);
            System.out.println("");
        } else {
            System.out.println("Ataque de forca bruta não sucedidio.\n");
        }
        
        
        return "a";
    }
    
    void imprimirChaves() {
        System.out.println("============= RSA =============");
        System.out.println("Chave publica:");
        System.out.println("e: " + mE.toString());
        System.out.println("n: " + mN.toString());
        System.out.println("Chave privada:");
        System.out.println("d: " + mD.toString());
        System.out.println("============= RSA =============\n");
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
