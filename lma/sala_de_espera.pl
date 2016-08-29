camisa(amarela).
camisa(azul).
camisa(branca).
camisa(verde).
camisa(vermelha).
paciente(alvaro).
paciente(celso).
paciente(eduardo).
paciente(marcos).
paciente(rodrigo).
revista(caras).
revista(epoca).
revista(galileu).
revista(istoe).
revista(veja).
dentista(adriana).
dentista(danielle).
dentista(priscila).
dentista(silvia).
dentista(raquel).
horario(dez).
horario(dez_e_quinze).
horario(dez_e_trinta).
horario(dez_e_quarenta_e_cinco).
horario(onze).
motivo(aparelho).
motivo(canal).
motivo(clareamento).
motivo(obturacao).
motivo(restauracao).

solucao :- deduz(X, Y, Z, G, H), write(X), nl, write(Y), nl, write(Z), nl, write(G), nl, write(H), nl.

deduz( (C1,P1,R1,D1,H1,M1) , (C2,P2,R2,D2,H2,M2), (C3,P3,R3,D3,H3,M3), (C4,P4,R4,D4,H4,M4), (C5,P5,R5,D5,H5,M5) ) :-
		camisa(C1), camisa(C2), camisa(C3), camisa(C4), camisa(C5),
		C4 \== amarela,C1 \== amarela, C5 \== amarela,C1 \== verde, C5 \== verde, C4 \== vermelha, C5 \== vermelha, C1 \== azul, C2 \== azul,C1 \== branca, C2 \== branca,
		C1 \== C2, C1 \== C3, C1 \== C4, C1 \== C5, C2 \== C3, C2 \== C4, C2 \== C5, C3 \== C4, C3 \== C4, C4 \== C5,
		((C1 == vermelha,C5 == azul,(C2 == verde;C3 == verde;C4 == verde));(C1 == vermelha,C4 == azul,(C2 == verde;C3 == verde));(C1 == vermelha,C3 == azul,C2 == verde);
         (C2 == vermlha,C5 == azul,(C3 == verde;C4 == verde));(C3 == vermeleha,C5 == azul,C4 == verde);(C2 == vermelha,C4 == azul,C3 == verde)),	     
		paciente(P1), paciente(P2), paciente(P3), paciente(P4), paciente(P5),
		P4 \== eduardo, P5 \== eduardo, P1 \== marcos, P5 \== marcos, P1 \== rodrigo, P2 \== rodrigo,
		P1 \== P2, P1 \== P3, P1 \== P4, P1 \== P5, P2 \== P3, P2 \== P4, P2 \== P5, P3 \== P4, P3 \== P4, P4 \== P5,
		revista(R1), revista(R2), revista(R3), revista(R4), revista(R5),
	    R1 \== veja, R5 \== veja, R4 \== istoe, R5 \== istoe,
		R3 == galileu, R1 \== R2, R1 \== R3, R1 \== R4, R1 \== R5, R2 \== R3, R2 \== R4, R2 \== R5, R3 \== R4, R3 \== R5, R4 \== R5,
		motivo(M1), motivo(M2), motivo(M3), motivo(M4), motivo(M5),
		M1 \== aparelho, M5 \== aparelho, M1 \== restauracao, M2 \== restauracao, M5 \== restauracao,C4 \== canal, C5 \== canal,C1 \== obturacao, C2 \== obturacao,
		M1 \== M2, M1 \== M3, M1 \== M4, M1 \== M5, M2 \== M3, M2 \== M4, M2 \== M5, M3 \== M4, M3 \== M5, M4 \== M5,
		dentista(D1), dentista(D2), dentista(D3), dentista(D4), dentista(D5),
		D1 \== adriana, D5 \== adriana, D1 \== priscila, D2 \== priscila, 
		D3 == raquel, D1 == silvia, D1 \== D2, D1 \== D3, D1 \== D4, D1 \== D5, D2 \== D3, D2 \== D4, D2 \== D5, D3 \== D4, D3 \== D5, D4 \== D5,
		horario(H1), horario(H2), horario(H3), horario(H4), horario(H5),
		(H1 == dez_e_quinze ; H5 == dez_e_quinze),
		H4 == dez, H1 \== H2, H1 \== H3, H1 \== H4, H1 \== H5, H2 \== H3, H2 \== H4, H2 \== H5, H3 \== H4, H3 \== H5, H4 \== H5,
		((P3 == alvaro,D3 == priscila);(P4 == alvaro,D4 == priscila);(P5 == alvaro, D5 == priscila)),
		((M3 == obturacao, R3 == caras);(M4 == obturacao,R4 == caras);(M5 == obturacao,R5 == caras)),
		((P1 == eduardo,R5 == galileu,(R2 == veja;R3 == veja; R4 == veja));(P1 == eduardo,R4 == galileu,(R2 == veja;R3 == veja));(P1 == eduardo,R3 == galileu,R2 == veja);
		 (P2 == eduardo,R5 == galileu,(R3 == veja;R4 == veja));(P3 == eduardo,R5 == galileu,R4 == veja);(P2 == eduardo,R4 == galileu,R3 == veja)),
		((R1 == istoe,M5 == restauracao,(M2 == aparelho;M3 == aparelho;M4 == aparelho));(R1 == istoe,M4 == restauracao,(M2 == aparelho;M3 == aparelho));(R1 == istoe,M3 == restauracao,M2 == aparelho); % Regra 3
		 (R2 == istoe,M5 == restauracao,(M3 == aparelho;M4 == aparelho));(R3 == istoe,M5 == restauracao,M3 == aparelho);(R2 == istoe,M4 == restauracao,M3 == aparelho)), 
	    ((C1 == amarela,P5 == rodrigo,(P2 == marcos;P3 == marcos;P4 == marcos));(C1 == amarela,P4 == rodrigo,(P2 == marcos;P3 == marcos));(C1 == amarela,P3 == rodrigo,P2 == marcos);
	     (C2 == amarela,P5 == rodrigo,(P3 == marcos;P4 == marcos));(C3 == amarela,P5 == rodrigo,P4 == marcos);(C2 == amarela,P4 == rodrigo,P3 == marcos)),
		((M1 == canal,M5 == obturacao,(M2 == restauracao;M3 == restauracao;M4 == restauracao));(M1 == canal,M4 == obturacao,(M2 == restauracao;M3 == restauracao));(M1 == canal,M3 == obturacao,M2 == restauracao); % Regra 7
         (M2 == canal,M5 == obturacao,(M3 == restauracao;M4 == restauracao));(M3 == canal,M5 == obturacao,M4 == restauracao);(M2 == canal,M4 == obturacao,M3 == restauracao)),	
		((H4 == dez_e_trinta,(C3 == amarela;C2 == amarela;C1 == amarela));(H3 == dez_e_trinta,(C2 == amarela;C1== amarela));(H2 == dez_e_trinta,C1 == amarela)),
		((H5 == onze,(C4 == azul;C3 == azul;C2 == azul;C1 == azul));(H4 == onze,(C3 == azul;C2 == azul;C1 == azul));(H3 == onze,(C2 == azul;C1 == azul));(H2 == onze,C1 == azul)),
		(D3 == raquel,D5 == priscila,D4 == adriana),
		((R1 == caras,D2 == priscila);(R2 == caras,D3 == priscila);(R3 == caras,D4 == priscila);(R4 == caras,D5 == priscila)),
		((R1 == istoe,C5 == branca,(C2 == amarela;C3 == amarela;C4 == amarela));(R1 == istoe, C4 == branca,(C2 == amarela;C3 == amarela));(R1 == istoe,C3 == branca,C2 == amarela);
		 (R2 == istoe,C5 == branca,(C3 == amarela;C4 == amarela));(R3 == istoe,C5 == branca,(C4 == amarela));(R2 == istoe,C4 == branca,C3 == amarela)).