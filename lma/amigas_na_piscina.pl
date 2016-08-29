menina(ana).
menina(raquel).
menina(vivian).
menina(bruna).
maio(amarelo).
maio(azul).
maio(branco).
maio(verde).
idade(oito).
idade(nove).
idade(dez).
idade(onze).
suco(laranja).
suco(limao).
suco(maracuja).
suco(morango).
protetor(fps40).
protetor(fps45).
protetor(fps50).
protetor(fps55).
animal(cachorros).
animal(gatos).
animal(passaros).
animal(peixes).

solucao :- deduz(X, Y, Z, A), write(X), nl, write(Y), nl, write(Z), nl, write(A), nl.
deduz((branco,raquel,onze,laranja,P1,gatos), (M2,N2,I2,S2,fps55,A2), (M3,N3,I3,S3,P3,cachorros), (verde,N4,oito,morango,P4,peixes)) :-
		maio(M2),
		maio(M3),
		menina(N2),
		menina(N3),
		menina(N4),
		idade(I2),
		idade(I3),
		suco(S2),
		suco(S3),
		protetor(P1),
		protetor(P3),
		protetor(P4),
		animal(A2),
		M2 \== M3,
		M2 \== branco,
		M2 \== verde,
		M3 \== branco,
		M3 \== verde,
		N2 \== N3,
		N2 \== N4,
		N3 \== N4,
		N2 \== raquel,
		N3 \== raquel,
		N4 \== raquel,
		N2 \== ana,
		I2 \== I3,
		I2 \== onze,
		I2 \== oito,
		I3 \== onze,
		I3 \== oito,
		S2 \== laranja,
		S2 \== morango,
		S3 \== laranja,
		S3 \== morango,
		P1 \== P3,
		P1 \== P4,
		P3 \== P4,
		P1 \== fps55,
		P3 \== fps55,
		P4 \== fps55,
		((N3 == ana,P3 == fps50);(N4 == ana,P4 == fps50)),
		P3 == fps40,
		S2 == limao,
		((S3 == maracuja, A2 == passaros);(S4 == maracuja, A3 == passaros)),
		((A2 == passaros,N2 == vivian);(A3 == passaros,N3 == vivian)),
		(I3 == nove, M2 == azul).