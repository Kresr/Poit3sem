.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib
ExitProcess PROTO : DWORD
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD
.STACK 4096
.DATA
MB_OK EQU 0
STR1 DB "MessageBox Example", 0
HW DD ?
CHAR_ARRAY DB 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0
BOOLEAN DB 1
STRUCT_ID DD 42
STRUCT_VALUE DD 3.14
INT_ARRAY DD 1, 2, 3, 4, 5
.CODE
main PROC
    INVOKE MessageBoxA, HW, OFFSET CHAR_ARRAY, OFFSET STR1, MB_OK
    push 0
    call ExitProcess
main ENDP
end main
