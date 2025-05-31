.686     
.model flat, stdcall
 ExitProcess PROTO :DWORD
 includelib  kernel32.lib  ; ExitProcess
 printf		 PROTO C :VARARG
 includelib  legacy_stdio_definitions.lib
 scanf		 PROTO C : dword,:vararg

 ;asm function call
 calcF		PROTO :dword, :dword, :dword
 replicate	PROTO :dword, :dword

 ;c function call
 pdata		PROTO c:dword
 exitop		PROTO c:dword, :dword
 printMID	PROTO C:dword, :dword
 stringcmp	PROTO c:dword, :dword, :dword


.DATA
;username and password
username db 'HUST', 0
password db 'hust', 0
;prompt out
buf1 db 'USERNAME (not more than 10 words):', 0
buf2 db 'Incorrect Username or password.', 0
buf3 db 'PASSWORD (not more than 10 words):', 0
buf4 db 'OK!', 0
buf5 db 'Press "R" to repeat or Press "Q" to exit.', 0
buf6 db 'Please try again later!', 0
buf7 db 'Incorrect input, Please Try Again!', 0


lpFmt	db	"%s",0ah, 0dh, 0	;printf string type
lpFmt1	db	"%d",0ah, 0dh, 0	;printf decimal type
format2 db	'%s',0				;scanf
valueu	db	11 dup(0)			;username
valuep	db	11 dup(0)			;password

sdaprint	db 'SDA:%d', 0ah, 0dh, 0
sdbprint	db 'SDB:%d', 0ah, 0dh, 0
sdcprint	db 'SDC:%d', 0ah, 0dh, 0
sfprint		db 'SF:%d', 0ah, 0dh, 0ah, 0dh, 0
samidprint	db 'SAMID:%s', 0ah, 0dh, 0

include A3_2_struct.asm

INPUT SAMPLES  <'00000001',321,432,10,?>
	SAMPLES  <'00000002',1265,544,300,?>
	SAMPLES  <'00000003',321,432,10,?>
	SAMPLES  <'00000004',2400,1000,300,?>
	SAMPLES  <'00000005',2410,1005,307,?>

LOWF SAMPLES 100 dup(<>)
MIDF SAMPLES 100 dup(<>)
HIGHF SAMPLES 100 dup(<>)

count	dd ?	;count 3 times
flag	dd ?	;boolean
roq		db ?	;r or q
desptr	dd ?
sourptr dd ?
kunci	dd ?


.STACK 200

.CODE

;main
main proc c
	mov count, 0

;login
L1:
	cmp count, 2
	jg Exit
	mov flag, 1
	invoke stringcmp, offset valueu,offset valuep, offset flag
	cmp flag, 1
	je TRUE

FALSE:
	inc count
	invoke printf,offset lpfmt,offset buf2		;Incorrect username or password
	jmp L1

TRUE: 
	invoke printf,offset lpfmt,offset buf4		;OK
	jmp L2_1									;countinue process

Exit:
	invoke printf,offset lpFmt,offset buf6		;Please Try Again Later
	invoke ExitProcess, 0

;calculate
L2_1:
	mov ecx, 0
	mov edx, 0	;LOW
	mov esi, 0	;MID
	mov edi, 0	;HIGH

L2_2:
	invoke calcF, INPUT[ecx].SDA, INPUT[ecx].SDB, INPUT[ecx].SDC
	mov INPUT[ecx].SF, eax
	cmp eax, 100
	je L3_1 ;MID
	jg L3_2	;HIGH
	jl L3_3	;LOW

L2_3:
	add ecx, 25
	cmp ecx, 100
	jle L2_2
	jmp LAST

L3_1:
	lea ebx, MIDF[esi]
	mov desptr, ebx
	lea ebx,INPUT[ecx]
	mov sourptr, ebx
	invoke replicate, desptr, sourptr
	add esi, 25
	jmp L2_3

L3_2:
	lea ebx, HIGHF[esi]
	mov desptr, ebx
	lea ebx,INPUT[ecx]
	mov sourptr, ebx
	invoke replicate, desptr, sourptr
	add edi, 25
	jmp L2_3

L3_3:
	lea ebx, LOWF[esi]
	mov desptr, ebx
	lea ebx,INPUT[ecx]
	mov sourptr, ebx
	invoke replicate, desptr, sourptr
	add edx, 25
	jmp L2_3

LAST:
	sub esi, 25
	invoke printMID, offset MIDF, esi

L_END:
	invoke exitop, offset INPUT, offset kunci
	cmp kunci, 0
	jg L2_1
	jl L_END
	invoke ExitProcess, 0

main endp

END