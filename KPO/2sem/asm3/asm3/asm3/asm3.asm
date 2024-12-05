.586P                         ; ������� ��������� (��������� Pentium)
.MODEL FLAT, STDCALL          ; ������ ������, ���������� � ������
includelib kernel32.lib       ; ���������� ���������� � �������� ExitProcess
includelib user32.lib         ; ���������� ���������� ��� MessageBoxA

ExitProcess PROTO :DWORD      ; �������� ������� ���������� �������� Windows
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD  ; �������� API-������� MessageBoxA

.STACK 4096                   ; ������� ����� �������� 4096 �����

.DATA                         ; ������� ������
    myBytes     BYTE    10h, 20h, 30h, 40h, 0h   ; ������ �� 4 ������
    SUM         DWORD   0                        ; ��� �������� �����
    str0        db      "��������� ����, ���� 2, ��", 0            
    str1        db      "������ �������� 0", 0 
    str2        db      "������ �� �������� 0", 0

.CODE
main PROC
start:  
    ; ������ � �������� myBytes
    mov ESI, OFFSET myBytes    ; ��������� �� ������ myBytes
    mov AH, [ESI]              ; ��������� ������ ���� � ������� ������� AH
    mov AL, [ESI + 2]          ; ��������� ������ ���� � ������� ������� AL

    ; ������������ ��������� ������� myBytes
    mov ESI, OFFSET myBytes    ; ��������� �� ������ myBytes
    mov ECX, 5               ; ���������� ��������� � ������� (4 �����)
    xor EAX, EAX               ; �������� ����������� ��� �����

SUM_LOOP:
    movzx EBX, BYTE PTR [ESI]  ; ��������� ������� ����, �������� ��� �� DWORD
    add EAX, EBX               ; ���������� �������� � �����
    inc ESI                    ; ��������� � ���������� �������� (BYTE = 1 ����)
    loop SUM_LOOP              ; ��������� ����

    mov [SUM], EAX             ; ��������� ����� � ���������� SUM

    ; �������� �� ������� �������� ��������
    mov ESI, OFFSET myBytes    ; ��������� �� ������ myBytes
    mov ECX, 5                 ; ���������� ��������� �������
    xor EBX, EBX               ; ���������� EBX (���� ������� ����)

CHECK_ZERO_LOOP:
    movzx EAX, BYTE PTR [ESI]  ; ��������� ������� ����, �������� ��� �� DWORD
    test EAX, EAX              ; ���������, ����� �� ���� ����
    jz FOUND_ZERO              ; ���� ������ 0, ��������� � ����� FOUND_ZERO
    inc ESI                    ; ��������� � ���������� ��������
    loop CHECK_ZERO_LOOP       ; ��������� ����

NO_ZERO:
    mov EBX, 1                 ; ���� ����� �� �������, ���������� 1 � EBX
    invoke MessageBoxA, 0, OFFSET str2, OFFSET str0, 0
    jmp END_PROGRAM            ; ��������� ���������

FOUND_ZERO:
    mov EBX, 0                 ; ���� ������ 0, ���������� 0 � EBX
    invoke MessageBoxA, 0, OFFSET str1, OFFSET str0, 0

END_PROGRAM:
    push 0                     ; ��������� ���������
    call ExitProcess

main ENDP
end main
