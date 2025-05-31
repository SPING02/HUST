.686P 
.model flat, c
  ExitProcess proto stdcall :dword
  includelib  kernel32.lib
  printf      proto c :vararg
  scanf       proto c :vararg
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib

  timeGetTime proto stdcall
  includelib  Winmm.lib

.DATA
__t1		dd ?
__t2		dd ?
__fmtTime	db	0ah, 0dh, "Time consumed is %ld ms", 2 dup(0ah, 0dh), 0

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


.data
SAMPLES STRUCT
    SAMID   DB  9 DUP(0)
    SDA     DD  256809    
    SDB     DD  -1023      
    SDC     DD  1265   
    SF      DD  0      
SAMPLES ENDS

INPUT  SAMPLES  <'1',321,432,10,?>
    SAMPLES  <'2',12654,544,342,?>
    SAMPLES  <'3',32100654,432,10,?>
    SAMPLES  <'00000004',2400,1000,300,?>
	SAMPLES  <'00000005',2410,1005,307,?>

LOWF SAMPLES 5 dup(<>)
MIDF SAMPLES 5 dup(<>)
HIGHF SAMPLES 5 dup(<>)

.stack   200

.code
    main proc  
    invoke winTimer, 0
    mov ecx,1000000000

L0:
    mov eax,INPUT.SDA
    mov edx,0
    imul eax,5
    add eax,INPUT.SDB
    sub eax,INPUT.SDC
    add eax,100
    ;idiv divn
    shr eax,7

    mov INPUT.SF,eax


    DEC   ecx
    JNE   L0
    invoke winTimer, 1
    invoke ExitProcess,0

main endp
END