.586P
.MODEL FLAT, STDCALL

includelib kernel32.lib
includelib libucrt.lib
includelib "..\Debug\SE_asm01d.lib"
ExitProcess      PROTO: DWORD
SetConsoleTitleA  PROTO: DWORD
GetStdHandle    PROTO: DWORD
WriteConsoleA    PROTO: DWORD, : DWORD, : DWORD, : DWORD, : DWORD
EXTRN getmax: proc
EXTRN getmin: proc

.STACK 4096

.CONST 

Arr        DD 56, 32, 82, -2, 10, -98, 17, -11, 7, 4

.DATA
result1      BYTE "getmax + getmin = ", 0
result      sdword 0
result2      BYTE 40 dup(0)
consolehandle  DD 0h

.CODE
main PROC

  

  push -11
  call GetStdHandle
  mov consolehandle, eax

  push lengthof Arr
  push offset Arr
  call getmin

  mov result, eax

  push lengthof Arr
  push offset Arr
  call getmax

  add result, eax
  xor eax, eax

  push result
  push offset result2
  call tochar

  invoke WriteConsoleA, consolehandle, offset result1, sizeof result1, 0, 0
  invoke WriteConsoleA, consolehandle, offset result2, sizeof result2, 0, 0

  push 0
  call ExitProcess

main ENDP

tochar PROC uses eax ebx ecx edx edi esi, pstr : dword, intfield : sdword
    mov edi, pstr       ; ��������� �� ������
    mov eax, intfield   ; ��������� ����� ��� ��������������
    xor esi, esi        ; �������� ������� ��������
    mov ebx, 10        

    ; ���������, ������������� �� �����
    cmp eax, 0
    jge CONVERT         ; ���� ����� >= 0, ��������� � �����������

    ; ��������� �������������� �����
    mov byte ptr [edi], '-' ; ��������� ���� ����� � ������ ������
    inc edi             ; �������� ��������� ������
    neg eax             ; ����������� ����� � �������������

CONVERT:
    
    cdq                 ; ��������� EAX � EDX ��� �������
    idiv ebx            ; ����� EAX �� 10, ������� � EDX (������� �����)
PUSH_DIGIT:
    push dx             ; ��������� ������� (�����) � �����
    inc esi             ; ����������� ������� ����
    test eax, eax       ; ���������, ���� �� ��� �����
    jnz CONVERT         ; ���� ����, ���������� �������

    ; ��������� ����� �� ����� � ���������� �� � ������
    mov ecx, esi        ; ���������� ���� � �����
WRITE_DIGITS:
    pop dx              ; �������� ����� �� �����
    add dl, '0'         ; ����������� � 
    mov [edi], dl       ; ���������� ������ � ������
    inc edi             ; �������� ��������� ������
    loop WRITE_DIGITS   ; ��������� ��� ���� � dd���

    ; ��������� ������ ������� ��������
    mov byte ptr [edi], 0

    ; ���������� ����� ������ (������� ����, ���� ����)
    mov eax, edi
    sub eax, pstr       ; ��������� ����� ������
    ret
tochar ENDP


END main
