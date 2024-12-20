.586P                         ; ������� ��������� (��������� Pentium)
.MODEL FLAT, STDCALL          ; ������ ������, ���������� � ������
includelib kernel32.lib       ; ���������� ���������� � �������� ExitProcess
includelib user32.lib         ; ���������� ���������� ��� MessageBoxA

ExitProcess PROTO :DWORD      ; �������� ������� ���������� �������� Windows
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD  ; �������� API-������� MessageBoxA

.STACK 4096                   ; ������� ����� �������� 4096 ����

.DATA                         ; ������� ������
    myBytes     BYTE    10, 20, 0, 30, 40   ; ������ �� 5 ������
    SUM         DWORD   0                        ; ��� �������� �����
    str0        db      "��������� ����, ���� 2, ��", 0            
    str1        db      "������ �������� 0", 0 
    str2        db      "������ �� �������� 0", 0
    strSum      db      "����� �������: %d", 0

.CODE
main PROC
start:  
    ; ������ � �������� myBytes
    mov ESI, OFFSET myBytes    ; ��������� �� ������ myBytes
    xor EAX, EAX               ; �������� ����������� ��� �����
    mov ECX, 5                 ; ���������� ��������� � �������

SUM_LOOP:
    movzx EBX, BYTE PTR [ESI]  ; ��������� ������� ����, �������� ��� �� DWORD
    add EAX, EBX               ; ���������� �������� � �����
    inc ESI                    ; ��������� � ���������� ��������
    loop SUM_LOOP              ; ��������� ����

    mov [SUM], EAX             ; ��������� ����� � ���������� SUM

    ; �������� �� ������� �������� ��������
    mov ESI, OFFSET myBytes    ; ��������� �� ������ myBytes
    mov ECX, 5                 ; ���������� ��������� �������
                  ; ���������� EBX (���� ������� ����)

CHECK_ZERO_LOOP:
    movzx EAX, BYTE PTR [ESI]  ; ��������� ������� ����, �������� ��� �� DWORD
    test EAX, EAX              ; ���������, ����� �� ���� ����
    jz FOUND_ZERO              ; ���� ������ 0, ��������� � ����� FOUND_ZERO
    inc ESI                    ; ��������� � ���������� ��������
    loop CHECK_ZERO_LOOP       ; ��������� ����

NO_ZERO:
    mov EBX, 1                 ; ���� ����� �� �������, ���������� 1 � EBX
    invoke MessageBoxA, 0, OFFSET str2, OFFSET str0, 0
    jmp DISPLAY_SUM            ; ��������� � ������ �����

FOUND_ZERO:
    mov EBX, 0                 ; ���� ������ 0, ���������� 0 � EBX
    invoke MessageBoxA, 0, OFFSET str1, OFFSET str0, 0

DISPLAY_SUM:
    ; ����� ����� �������� ����� ����� ����� MessageBoxA
    ; ������ ������ �������� ���������� SUM ��� ������

    push 0                     ; ��������� ���������
    call ExitProcess

main ENDP
end main
