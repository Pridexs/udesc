package sdi.trabfinal;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Cliente {

    private Cliente() {}

    public static void main(String[] args) {

        String host = (args.length < 1) ? null : args[0];
        try {
            Registry registry = LocateRegistry.getRegistry(host);
            Banco stub = (Banco) registry.lookup("Hello");
            
            System.out.println(stub.abreConta());
            System.out.println(stub.abreConta());
            System.out.println(stub.depositar(0, 20));
            System.out.println(stub.depositar(0, 30));

            //String response = stub.sayHello();
            //System.out.println("response: " + response);
        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
