! Exercicios -  Fundamentos de SO 
!16. Escreva uma subrotina em Assembly que calcule a media aritmetica de uma quantidade arbitraria
!de numeros passados como parametro na pilha. O primeiro parametro deve ser a quantidade de
!numeros a processar. Por exemplo, para calcular a media de 4, 9 e 5, a chamada em C equivalente
!seria media(3, 4, 9, 5). A media calculada deve ser retornada em AX.
! 
!
! Alexandre Maros
! UDESC - SOP - 2015/1

.SECT   .TEXT
media:
    PUSH    BP              ! salva BP
    MOV     BP,SP           ! salva SP em BP
    ADD     BP,4            ! Coloca o ponteiro no primeiro argumento da pilha
    MOV     CX,(BP)         ! Coloca o valor do primiero argumento em CX (numero de elementos)
    MOV     (_nNum),CX      ! Coloca a quantidade de numeros em nNum
    XOR     AX,AX           ! Zera AX
    MOV     (_num),AX       ! Zera Num
    JMP     _loop           ! Vai para loop

_loop:
    ADD     BP,2            ! Passa por todos os argumentos restantes
    MOV     AX,(BP)         ! Tira numero digitado
    ADD     (_num),AX       ! Adiciona em _num 
    DEC     CX              ! Decrementa CX
    JNZ     _loop           ! Volta

_encerra:
    MOV     AX,(_num)       ! Adiciona a soa de todos os numeros em AX
    MOV     CX,(_nNum)      ! Adiciona a quantidade de numeros em CX
    DIV     CX              ! Divide AX por CX
    MOV     (_num),AX       !
    MOV     AX,(_num)
    POP     BP              ! restaura BP
    RET                     ! encerra funcao
                            ! retorno fica salvo em AX

.SECT   .DATA
_num:   .SPACE 16
_nNum:  .SPACE 16

.SECT   .BSS
