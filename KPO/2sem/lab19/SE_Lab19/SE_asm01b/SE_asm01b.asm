.586P
.MODEL FLAT, STDCALL

includelib kernel32.lib
includelib "..\Debug\SE_asm01a.lib"

ExitProcess      PROTO: DWORD
SetConsoleTitleA  PROTO: DWORD
GetStdHandle    PROTO: DWORD
WriteConsoleA    PROTO: DWORD, : DWORD, : DWORD, : DWORD, : DWORD
getmin        PROTO: DWORD, : DWORD
getmax        PROTO: DWORD, : DWORD

.STACK 4096

.CONST 
consoletitle  DB 'SE_asm01b', 0
Arr        DD 56, 32, 82, -2, 10, 98, -17, -11, 7, 4

.DATA
result1      BYTE "getmax + getmin = ", 0
result      sdword 0
result2      BYTE 40 dup(0)
consolehandle  DD 0h

.CODE
main PROC

  invoke SetConsoleTitleA, offset consoletitle          ; Устанавливаем заголовок консоли
  push -11                            ; Получаем хэндл консоли для вывода
  call GetStdHandle
  mov consolehandle, eax

  invoke getmin, offset Arr, lengthof Arr            ; Вызываем функцию getmin для массива Arr

  mov result, eax

  invoke getmax, offset Arr, lengthof Arr

  add result, eax                        ; Складываем результаты getmin и getmax
  xor eax, eax							 ; для очистки региста

  push result							 ; закидываем result в стек
  push offset result2                    ; Закидываем в стек ссылку на строку куда будет запсан результат
  call tochar							 ; Преобразуем результат в строку

  invoke WriteConsoleA, consolehandle, offset result1, sizeof result1, 0, 0
  invoke WriteConsoleA, consolehandle, offset result2, sizeof result2, 0, 0

  push 0
  call ExitProcess

main ENDP

tochar PROC uses eax ebx ecx edi esi, pstr : dword, intfield : sdword
  mov edi, pstr
  mov esi, 0
  mov eax, intfield
  cdq
  mov ebx, 10
  idiv ebx
cycle:
  push dx								 ; Добавляем остаток в стек
  inc esi
  test eax, eax                          ; Если результат деления на 10 равен 0, завершаем цикл
  jz fin								 ; расширение до 64 бит
  cdq									 ; Деление числа на 10
  idiv ebx
  jmp cycle
fin:
  mov ecx, esi							 ; Количество цифр в числе
write: 
  pop bx								 ; Извлекаем остаток из стека
  add bl, '0'							 ; Преобразуем в ASCII и записываем в строку
  mov[edi], bl
  inc edi
  loop write							; Переходим к следующей цифре
  ret
tochar ENDP

END main