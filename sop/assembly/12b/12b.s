! Exercicios -  Fundamentos de SO 
! Exercicio: 12 - b)
!
! 12. Escreva um programa em Assembly que leia dois numeros inteiros x e y calcule x^y usando
! (b) apenas somas
!
! Alexandre Maros
! UDESC - 2015/1

#include "../syscalnr.h"  

.SECT .TEXT
start:
    MOV     BP,SP       ! salva SP
    PUSH    entre_x     ! endereco da string
    PUSH    _PRINTF     ! no. da syscall
    SYS                 ! executa syscall 

    CALL    readnum     ! le string e converte para numero
    MOV     (x),AX      ! armazena o numero lido em 'x'
    
    DEC     AX          ! Decrementa AX para colocar no cont2 para controlar as somas
    MOV     (cont2),AX  

    PUSH    entre_y     ! endereco da string
    PUSH    _PRINTF     ! no. da syscall
    SYS                 ! executa syscall

    CALL    readnum     ! le string e converte para numero
    MOV     (y),AX      ! armazena o numero lido em 'y'
    
    MOV     (cont),AX   ! Coloca AX na variavel cont para controlar as somas
    MOV     AX,(x)      
    JMP     loopSoma1

!   4 * 4 * 4    
!   (4 * 4) * 4
! = (4+4+4+4) * 4
! = (16) * 4
! = 16 + 16 + 16 + 16

loopSoma1:
    MOV     CX,(cont)   ! Coloca contador principal em CX
    MOV     (x),AX      ! Move AX para x
    DEC     CX          ! Decremente CX
    JE      imprime     ! Caso CX for 0, imprima x^y
    MOV     (cont),CX   ! Se nao for, guarde contador principal
    MOV     CX,(cont2)  ! coloque contador secundario em CX
    JMP     loopSoma2   ! Va para a segundo loop
        
loopSoma2:
    ADD     AX,(x)      ! Some x em AX
    DEC     CX          ! Decremente CX
    JE      loopSoma1   ! Caso CX seja 0, volte para loop1
    JMP     loopSoma2   ! Se nao, continue somando

imprime:
    PUSH    (x)         ! Coloque x^y na pilha
    PUSH    resultado   ! Coloque string na pilha
    PUSH    _PRINTF
    SYS

encerra:    
    MOV     SP,BP       ! limpa pilha
    PUSH    0           ! codigo de retorno=0
    PUSH    _EXIT       
    SYS                 ! encerra o programa

.SECT   .DATA
entre_x:        .ASCIZ  '\nEntre x: '
entre_y:        .ASCIZ  '\nEntre y: '
resultado:      .ASCIZ  'x^y: %d\n'

.SECT   .BSS
x:      .SPACE 16
y:      .SPACE 16
cont:   .SPACE 16
cont2:  .SPACE 16
