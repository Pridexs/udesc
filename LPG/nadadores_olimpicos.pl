touca(amarela).
touca(azul).
pais(russia).
especialidade(borboleta).
especialidade(crawl).
medalhas(dois).
suco(abacaxi).
suco(limao).
suco(maracuja).
idade(dezenove).
idade(vinte).
idade(vinte_e_um).

solucao :- deduz(X, Y, Z, G), write(X), nl, write(Y), nl, write(Z), nl, write(G), nl.

deduz( (verde,eua,E1,cinco,S1,I1), (T2,china,peito,tres,laranja,I2), (T3,brasil,costas,oito,S3,vinte_e_quatro), (branca,P4,E4,M4,S4,I4) ) :-
	touca(T3),touca(T2),
	T3 \== T2,
	pais(P4),
	especialidade(E1),especialidade(E4),
	E1 \== E4, E1 \== crawl,
	medalhas(M4),
	suco(S1),suco(S3),suco(S4),
	S1 \== S3, S1 \== S4, S3 \== S4,
	idade(I1),idade(I2),idade(I4),
	I1 \== I2, I1 \== I4, I2 \== I4,
	(T2 == azul,E1 == borboleta),
	(E4 == crawl, S3 == limao),
	((I4 == dezenove,(T3 == azul;T2 == azul;T1 == azul))),
	(I1 == vinte ; I4 == vinte),
	((T1 == azul,(S3 == maracuja;S4 == maracuja));(T2 == azul,(S3 == maracuja; S4 == maracuja));(T3 == azul,S4 == maracuja)).


	
	
	
	
	