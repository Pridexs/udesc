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
        
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.rmi.AccessException;
import java.rmi.NotBoundException;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ImplementacaoBanco implements Banco {
        
    private ArrayList<Conta> contas;
    private String name;
    private String host;
    
    Object mutex = new Object();

    public ImplementacaoBanco() {
        contas = new ArrayList<Conta>();
        
    }

    // Retorna o ID da conta
    @Override
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
        
        synchronized(mutex) {
            Conta conta = new Conta(id);
            contas.add(conta);

            // Replica os dados
            if ("MasterServer".equals(name)) {
                ArrayList<String> hostSlaves = getRegistryList();
                try {
                    Registry registry = LocateRegistry.getRegistry(host);
                    for (String h : hostSlaves) {
                        Banco stub = (Banco) registry.lookup(h);
                        stub.abreConta(id);
                    }
                } catch (RemoteException ex) {
                    Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
                } catch (NotBoundException ex) {
                    System.out.println("ISSO NAO DEVERIA ACONTECER!");
                    Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
        
        
        System.out.println("[" + name + "]: Criei conta " + id);
        
        return id;
    }
    
    // Cria uma conta com um ID especifico
    @Override
    public void abreConta(int idConta) {     
        synchronized(mutex) {
            Conta conta = new Conta(idConta);
            contas.add(conta);
        }
        System.out.println("[" + name + "]: Criei conta " + idConta);
    }
    
    // Retorna novo saldo
    // se -1.0 == nao achou contaid 
    @Override
    public double depositar(int contaId, double valor) {
        for (Conta c : contas) {
            if (c.getContaId() == contaId) {
                double novoValor = -1.0;
                synchronized(mutex) {
                    novoValor = c.depositar(valor);

                    System.out.println("[" + name + "]: Depositei " + contaId + "," + valor);

                    // Replica os dados
                    if ("MasterServer".equals(name)) {
                        ArrayList<String> hostSlaves = getRegistryList();
                        int hSize = hostSlaves.size();
                        try {
                            Registry registry = LocateRegistry.getRegistry(host);
                            for (String h : hostSlaves) {
                                Banco stub = (Banco) registry.lookup(h);
                                stub.depositar(contaId, valor);
                            }
                        } catch (RemoteException ex) {
                            Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (NotBoundException ex) {
                            System.out.println("ISSO NAO DEVERIA ACONTECER!");
                            Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                }

                return novoValor;
            }
        }
        return -1.0;
    }

    // Retorna o saldo
    // -1.0 se nao achou contaId
    @Override
    public double verificaSaldo(int contaId) {
        for (Conta c : contas) {
            if (c.getContaId() == contaId) {
                return c.getSaldo();
            }
        }
        return -1.0;
    }

    // Retorna um inteiro (1- sucesso, 2- saldo insuficiente, 3- id ivalido)
    @Override
    public int sacar(int contaId, double qtd) {
        for (Conta c : contas) {
            if (c.getContaId() == contaId) {
                int retorno = 0;
                synchronized(mutex) {
                    retorno = c.sacar(qtd);
                    if (retorno == 2) {
                        return 2;
                    }

                    System.out.println("[" + name + "]: Saquei " + contaId + "," + qtd);

                    // Replica os dados
                    if ("MasterServer".equals(name)) {
                        ArrayList<String> hostSlaves = getRegistryList();
                        int hSize = hostSlaves.size();
                        try {
                            Registry registry = LocateRegistry.getRegistry(host);
                            for (String h : hostSlaves) {
                                Banco stub = (Banco) registry.lookup(h);
                                stub.sacar(contaId, qtd);
                            }
                        } catch (RemoteException ex) {
                            Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (NotBoundException ex) {
                            System.out.println("ISSO NAO DEVERIA ACONTECER!");
                            Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                }
                
                return retorno;
            }
        }
        return 3;
    }

    // Transfere valor
    // 3 - idOrigem invalido
    // 4 - idDestino invalido
    // 2 - saldo insuficiente idOrigem
    // 1 - sucesso
    @Override
    public int transferir(int idOrigem, int idDestino, double valor) {
        Conta c1, c2;
        c1 = null;
        c2 = null;
        
        for (Conta c : contas) {
            if (c1 == null && c.getContaId() == idOrigem) {
                c1 = c;
            } else if (c2 == null && c.getContaId() == idDestino) {
                c2 = c;
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

        synchronized(mutex) {
            int saida = c1.sacar(valor);
            // saida == 2 (saldo insuficiente)
            if (saida == 2) {
                return 2;
            }

            c2.depositar(valor);

            System.out.println("[" + name + "]: Transferi " + idOrigem + "," + idDestino + "," + valor);

            // Replica os dados
            if ("MasterServer".equals(name)) {
                ArrayList<String> hostSlaves = getRegistryList();
                int hSize = hostSlaves.size();
                try {
                    Registry registry = LocateRegistry.getRegistry(host);
                    for (String h : hostSlaves) {
                        Banco stub = (Banco) registry.lookup(h);
                        stub.transferir(idOrigem, idDestino, valor);
                    }
                } catch (RemoteException ex) {
                    Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
                } catch (NotBoundException ex) {
                    System.out.println("ISSO NAO DEVERIA ACONTECER!");
                    Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }

        return 1;
    }
    
    @Override
    public boolean isAlive() {
        return true;
    }
    
    @Override
    public void setServerName(String name) {
        System.out.println("[" + this.name + "]: Novo nome " + name);
        this.name = name;
    }
    
    @Override
    public ArrayList<String> getRegistryList() {
        ArrayList<String> nomesLista = new ArrayList<String>();
        
        Registry registry;
        try {
            registry = LocateRegistry.getRegistry(host);
            String[] list = registry.list();
 
            for (String l : list) {

                if (!"MasterServer".equals(l) && !"NameService".equals(l)) {
                    nomesLista.add(l);
                }
            }
        } catch (RemoteException ex) {
            // Should not happen
            System.out.println("Nao encontrei o servidor de NameService, isso nao deveria acontecer.");
            Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return nomesLista;
    }
    
    public void setHost(String host) {
        this.host = host;
    }
    
    @Override
    public byte[] copiarContas() throws IOException {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ObjectOutputStream oos = new ObjectOutputStream(baos);
        oos.writeObject(contas);
        oos.close();
        return baos.toByteArray();
    }
    
    @Override
    public boolean clonarContasMestre() {
        synchronized(mutex) {
            try {
                Registry registry = LocateRegistry.getRegistry(host);
                Banco stub;
                stub = (Banco) registry.lookup("MasterServer");
                ObjectInputStream ois = new ObjectInputStream(new ByteArrayInputStream(stub.copiarContas()));

                // Eu tenho certeza que uma ArrayList<Conta> vai checar aqui.
                @SuppressWarnings("unchecked")
                ArrayList<Conta> ccopy = (ArrayList<Conta>)ois.readObject();

                contas = ccopy;

                return true;
            } catch (RemoteException ex) {
                Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
            } catch (NotBoundException | ClassNotFoundException | IOException ex) {
                Logger.getLogger(ImplementacaoBanco.class.getName()).log(Level.SEVERE, null, ex);
            }
            return false;
        }
    }
    
}
