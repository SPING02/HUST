.686P 
.model flat, stdcall
  ExitProcess proto stdcall :dword
  includelib  kernel32.lib
  printf      proto c :vararg
  scanf       proto c :vararg
  VirtualProtect proto : dword, :dword, :dword, :dword
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib

timeGetTime proto stdcall
includelib  Winmm.lib

.DATA
__t1		dd ?
__t2		dd ?
__fmtTime	db	0ah, 0dh, "Time cunsumed is %ld ms", 2 dup(0ah, 0dh), 0

.CODE
winTimer	proc stdcall, flag : DWORD
    jmp	__L1
__L1: 
    call timeGetTime
    cmp	flag, 0
    jnz	__L2
    mov	__t1, eax
    ret	4
__L2: 
    mov	__t2, eax
    sub	eax, __t1
    invoke	printf, offset __fmtTime, eax
    ret	4
winTimer	endp

samples struct
    ;SAMID  DB 9 DUP(0)   
    SDA   DD  256809   
    SDB   DD  -1023     
    SDC   DD   1265   
    SF    DD   0      
samples ends

calc        proto demo_tmp:samples
save_data   proto pos:dword,demo_tmp:samples
print_data  proto pos:dword
exit_opt    proto
extern exit_opt_sub:proto

.data

demo SAMPLES 10 dup(<2400,1000,300,>)

LOWF DD 100 dup(4)
MIDF DD 100 dup(4)
HIGHF DD 100 dup(4)

    
lpSmt           db "%s",0
outfmt          db "%ld",10,0
numfmt          db "%ld",0
key             db 'h' xor 'X','u' xor 'X','s' xor 'X','t' xor 'X',0
key_username    db 'H' xor 'X','U' xor 'X','S' xor 'X','T' xor 'X',0
flag            db 'flag',0
qcomm           db 'Q',0
rcomm           db 'R',0
error           db 'Incorrect Username or password. ',10,0
exit_tip        db 'Press "R" to repeat or Press "Q" to exit. ',0
interference    db 'You will never break this',0
command_error   db 'Incorrect input, Please Try Again!',10,0

 data_a         db 'SDA:' ,0
 data_b         db 'SDB:' ,0
 data_c         db 'SDC:' ,0
 data_f         db 'SF:' ,0
 mid_data       db 'MIDF:',10,0

 shift          db ' ',10,0
 correct        db 'Ok!',10,0
 user_message   db 'USERNAME (not more than 10 words):',0
 message        db 'PASSWORD (not more than 10 words):',0

 len_key        dd 0
 len_tmp        dd 0
 keyword       db 100 dup(0),0
 username       db 100 dup(0),0
 tmp_opt        db 100 dup(0),0
 ans            dd 0

 machine_code   db 0E8H,051H,0,0,0
 lenTH EQU $-machine_code 
 oldprotect     dd ?

.stack   200
.code

print_myself MACRO A, B
    PUSHAD
    invoke printf, A, B
    POPAD
ENDM

STRINGCMP MACRO key_com,keyword_com,output
LOCAL S, N, K, M, NEXT, L, D, ENDMACRO
    PUSHAD
    MOV     EAX, 0
S:
    CMP     key_com[EAX], 0
    JZ      N
    INC     EAX
    JMP     S
N:
    MOV     len_key, EAX
    MOV     EAX, 0
K:
    CMP     keyword_com[EAX],0
    JZ      M
    INC     EAX
    JMP     K
M:
    CMP     EAX, len_key
    JZ      NEXT
    MOV     EAX, 0
    MOV     output,EAX
    JMP     ENDMACRO
NEXT:
    MOV     EAX, 10
L: 
    DEC     EAX
    CMP     EAX, -1
    JZ      D
    MOV     BL, keyword_com[EAX]
    MOV     BH, key_com[EAX] 
    MOV     DL, 0
    CMP     BL, DL
    JZ      L
    CMP     BH,DL
    JZ      L
    XOR     BL, 'X'
    CMP     BL,BH 
    JZ      L
    MOV     EAX, 0
    MOV     output, EAX
    JMP     ENDMACRO
D:
    MOV     EAX, 1
    MOV     output,EAX
    JMP     ENDMACRO
ENDMACRO:

POPAD
ENDM


main PROC C
    invoke winTimer, 0
    MOV     EBX, 64
LOOPM:
    MOV     demo[EBX].SDA, EBX
    SUB     EBX, 16
    JNE     LOOPM

;call login
    MOV     EAX, lenTH 
    MOV     EBX, 40h
    lea     ECX, CopyHere
    invoke VirtualProtect,ECX,EAX,EBX,offset oldprotect 
    MOV     ECX, lenTH
    MOV     EDI, offset CopyHere
    MOV     ESI, offset machine_code 
CopyCode:
    MOV     AL, [ESI] 
    MOV     [EDI], AL 
    INC     ESI 
    INC     EDI
    LOOP    CopyCode 
CopyHere:
    db lenTH dup(0)


BEGIN:
    MOV     EBX, offset demo
    MOV     ECX, 160
LOOPB:
    invoke calc,demo[ecx]
    SUB     ECX, 16
    JNE     LOOPB      
    invoke print_data, offset MIDF
    invoke exit_opt_sub
    JMP     BEGIN
    invoke winTimer, 1
    invoke ExitProcess,0
main  ENDP

login PROC
    LOCAL   sum:dword
    MOV     ecx,3
    MOV     sum,ecx
    invoke printf, offset user_message,eax
    invoke scanf,offset lpSmt, offset username
    invoke printf, offset message,eax
    invoke scanf,offset lpSmt, offset keyword
    JMP     FIRST
TRY:
    print_myself offset shift,eax
    invoke printf, offset error,eax
    invoke printf, offset user_message,eax
    invoke scanf,offset lpSmt, offset username
    invoke printf, offset message,eax
    invoke scanf,offset lpSmt, offset keyword
FIRST:
    MOV     EAX, 1
    STRINGCMP key_username,username,ans
    CMP     ans, EAX
    JNZ     WRONG_TRY
    JZ      CONTINUE
    CONTINUE:
    MOV     EAX, 1
    STRINGCMP key,keyword,ans
    CMP     ans, EAX
    JZ      ENDLOGIN
WRONG_TRY:
    DEC     sum
    JNZ     TRY
invoke ExitProcess,0
ENDLOGIN:
    invoke printf, offset correct,EAX
    MOV     EAX,0
    MOV     EAX,0
login  ENDP

calc proc demo_tmp:samples
    PUSHAD
    MOV     EAX,demo_tmp.SDA
    IMUL    EAX,5
    ADD     EAX,demo_tmp.SDB
    SUB     EAX,demo_tmp.SDC
    ADD     EAX,100
    SHR     EAX,7
    MOV     demo_tmp.SF,EAX
    SUB     EAX,100
    JZ      MIDN
    JS      LOWN
    JNS     HIGHN
    MOV     EAX,3
    MOV     EBX,9
    MOV     ECX,6
    MOV     EDX,0
LOWN:
    MOV     EBX,0
    invoke save_data,offset LOWF,demo_tmp
    JMP     ENDCAL
MIDN:
    MOV     EBX,0
    invoke save_data,offset MIDF,demo_tmp
    JMP     ENDCAL
HIGHN:
    MOV     EBX,0
    invoke save_data,offset HIGHF,demo_tmp
    JMP     ENDCAL
ENDCAL:
    POPAD
    RET
calc endp


save_data proc pos:dword,demo_save:samples
    PUSHAD
    MOV     EBX,pos
    MOV     ECX,demo_save.SDA
    MOV     EDX,[EBX]
    MOV     [EBX+EDX],ECX
    MOV     ECX,demo_save.SDB
    MOV     [EBX+EDX+4],ECX
    MOV     ECX,demo_save.SDC
    MOV     [EBX+EDX+8],ECX
    MOV     ecx,demo_save.SF
    MOV     [EBX+EDX+12],ECX
    MOV     ECX,16
    MOV     EBX,pos
    ADD     [EBX],ECX
    POPAD
    RET
save_data endp


print_data proc pos:dword
    LOCAL sum_print:dword
    PUSHAD
    MOV     EAX,1
    MOV     EBX,pos
    MOV     EDX,[EBX]
    MOV     ECX,4
    print_myself offset shift,EAX
    print_myself offset mid_data,EAX
    CMP     EDX,4
    JZ      END_PRINT
LOOPP:
    MOV     EAX,[EBX+ECX]
    print_myself offset data_a,EAX
    print_myself offset outfmt,EAX
    MOV     EAX,[EBX+ECX+4]
    print_myself offset data_b,EAX
    print_myself offset outfmt,EAX
    MOV     EAX,[EBX+ECX+8]
    print_myself offset data_c,EAX
    print_myself offset outfmt,EAX
    MOV     EAX,[EBX+ECX+12]
    print_myself offset data_f,EAX
    print_myself offset outfmt,EAX
    ADD     ECX,16
    MOV     EAX,0
    print_myself offset shift,EAX
    MOV     EAX,1
    ADD     sum_print,EAX
    CMP     ECX,edx
    JNZ     LOOPP

END_PRINT:
    POPAD
    RET
print_data endp
end