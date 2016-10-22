/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rsa;

import java.math.BigInteger;

/**
 *
 * @author pridexs
 */
public class Tripla_egcd {
    public BigInteger gcd, x, y;
    
    Tripla_egcd(BigInteger a, BigInteger b, BigInteger c) {
        gcd = a;
        x = b;
        y = c;
    }
}
