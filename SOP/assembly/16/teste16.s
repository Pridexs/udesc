! Programa teste para ler numeros e utilizar a funcao media, imprimindo (sem os restos) o resultado no final.
! O arquivo 16.s contem a implementacao da sub rotina
! Alexandre Maros
! UDESC - 2015/1
!

#include "../syscalnr.h"  

.SECT .TEXT
start:
    MOV     BP,SP       ! salva SP
    
    PUSH    entreQtd    ! endereco da string
    PUSH    _PRINTF     ! no. da syscall
    SYS                 ! executa syscall 

    CALL    readnum     ! le string e converte para numero
    
    MOV     (_nNum),AX  ! guarda quantidade de numeros
    MOV     CX,AX       ! coloca quantidade de numeros em CX
    JMP     loop1

loop1:
    
    MOV     BP,SP       ! guarda posicao da pilha
    PUSH    entreN
    PUSH    _PRINTF
    SYS
    MOV     SP,BP       ! limpa pilha

    CALL    readnum     ! le numero
    PUSH    AX          ! coloca na pilha
    DEC     CX          ! Decrementa CX
    JNZ     loop1       ! volta se nao chegou em zero
    JMP     imprime     ! imprime Media

imprime:
    PUSH    (_nNum)     ! empilha qtd numeros
    CALL    media       ! chama funcao media
    PUSH    AX          ! empilha AX (resultado de media)
    PUSH    resultado   ! empilha string
    PUSH    _PRINTF     ! imprime
    SYS

encerra:    
    MOV     SP,BP   ! limpa pilha
    PUSH    0       ! codigo de retorno=0
    PUSH    _EXIT       
    SYS             ! encerra o programa

.SECT   .DATA
entreQtd:       .ASCIZ  '\nEntre quantidade de numeros: '
entreN:   .ASCIZ  'Digite numero: '
resultado:  .ASCIZ  'Media: %d\n'

.SECT   .BSS
nNum:   .SPACE 16
x:      .SPACE 16
