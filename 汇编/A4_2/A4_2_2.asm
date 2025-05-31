.686     
.model flat, stdcall
  ExitProcess proto stdcall :dword
  includelib  kernel32.lib
  printf      proto c :vararg
  scanf      proto c :vararg
  includelib  libcmt.lib
public exit_opt_sub

.data
 command_error db 'Command not found, please input again.',10,0
 exit_tip db 'Click Q to quit, click R to redo: ',0
 tmp_opt db 100 dup(0),0
 lpSmt db "%s",0

.code

exit_opt_sub proc 
LOCAL local_tmp_char[100]:dword,tmp_ans:dword
PUSHAD
	MOV		EBX,1
	JMP		SECOND
WC:
	invoke printf, offset command_error,EAX
SECOND:
	invoke printf, offset exit_tip,EAX
	LEA		EAX,local_tmp_char
	invoke scanf,offset lpSmt,offset tmp_opt
	MOV		EAX,1
	CMP		tmp_opt[EAX],0
	JNZ		WC
	MOV		EAX,0
	MOV		EBX,'Q'
	CMP		tmp_opt[EAX],'Q'
	JZ		EXIT
	MOV		EBX,'R'
	CMP		tmp_opt[EAX],'R'
	JZ		STAY
	JMP		WC
EXIT:
	invoke ExitProcess,0
STAY:
	RET
	POPAD
exit_opt_sub endp


exit_opt proc 
LOCAL local_tmp_char[100]:dword,tmp_ans:dword
PUSHAD
	MOV		EBX,1
	JMP		SECOND
WC:
	invoke printf, offset command_error,EAX
SECOND:
	invoke printf, offset exit_tip,EAX
	LEA		EAX,local_tmp_char
	invoke scanf,offset lpSmt,offset tmp_opt
	MOV		EAX,1
	CMP		tmp_opt[EAX],0
	JNZ		WC
	MOV		EAX,0
	MOV		EBX,'Q'
	CMP		tmp_opt[EAX],'Q'
	JZ		EXIT
	MOV		EBX,'R'
	CMP		tmp_opt[EAX],'R'
	JZ		STAY
	JMP		WC
EXIT:
	invoke ExitProcess,0
STAY:
	RET
	POPAD
exit_opt endp
end