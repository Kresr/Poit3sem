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
    mov edi, pstr       ; Указатель на строку
    mov eax, intfield   ; Загружаем число для преобразования
    xor esi, esi        ; Обнуляем счетчик символов
    mov ebx, 10        

    ; Проверяем, отрицательное ли число
    cmp eax, 0
    jge CONVERT         ; Если число >= 0, переходим к конвертации

    ; Обработка отрицательного числа
    mov byte ptr [edi], '-' ; Добавляем знак минус в начало строки
    inc edi             ; Сдвигаем указатель строки
    neg eax             ; Преобразуем число в положительное

CONVERT:
    
    cdq                 ; Расширяем EAX в EDX для деления
    idiv ebx            ; Делим EAX на 10, остаток в EDX (младшая цифра)
PUSH_DIGIT:
    push dx             ; Сохраняем остаток (цифру) в стеке
    inc esi             ; Увеличиваем счетчик цифр
    test eax, eax       ; Проверяем, есть ли еще цифры
    jnz CONVERT         ; Если есть, продолжаем деление

    ; Извлекаем цифры из стека и записываем их в строку
    mov ecx, esi        ; Количество цифр в числе
WRITE_DIGITS:
    pop dx              ; Получаем цифру из стека
    add dl, '0'         ; Преобразуем в 
    mov [edi], dl       ; Записываем символ в строку
    inc edi             ; Сдвигаем указатель строки
    loop WRITE_DIGITS   ; Повторяем для всех ц ddифр

    ; Завершаем строку нулевым символом
    mov byte ptr [edi], 0

    ; Возвращаем длину строки (включая знак, если есть)
    mov eax, edi
    sub eax, pstr       ; Вычисляем длину строки
    ret
tochar ENDP


END main
