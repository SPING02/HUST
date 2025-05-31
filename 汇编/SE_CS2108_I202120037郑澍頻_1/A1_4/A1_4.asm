.686P 
.model flat, c
  ExitProcess	proto stdcall :dword
  includelib	kernel32.lib
  printf		proto c :vararg
  scanf			proto c :vararg
  includelib	libcmt.lib
  includelib	legacy_stdio_definitions.lib

.data
	SAMID	DB	'000001'	;The serial number of each set of data
	SDA		DD	256809		;Status of info A
	SDB		DD	-1023		;Status of info B
	SDC		DD	1265		;Status of info C
	SF		DD	0			;Result of process
	LOWF	DD	0
	MIDF	DD	0
	HIGHF	DD	0
	divn	DD	128

.stack   200

.code
	main proc  
	mov eax,SDA
	mov edx,0
	imul eax,5
	add eax,SDB
	sub eax,SDC
	add eax,100
	idiv divn
 
	mov SF,eax
	cmp SF,100
	jz L1
	sub SF,100
	js L2
	jns L3

L2:
	mov LOWF,eax
	invoke printf, offset LOWF,ebx
	invoke ExitProcess,0
 
L1:
	mov MIDF,eax
	invoke printf, offset HIGHF,ebx
	invoke ExitProcess,0
 
L3:
	mov HIGHF,eax
	invoke printf, offset MIDF,ebx
	invoke ExitProcess,0

	main  endp
END