.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib

ExitProcess PROTO: DWORD

.STACK 4096

.CONST 
Arr sdword 56, 32, 82, -2, 10, -98, 17, -11, 7, 4

.DATA
min sdword ?
max sdword ?

.CODE

main PROC
START:

push lengthof Arr
push offset Arr
call getmin
mov min, eax

push lengthof Arr
push offset Arr
call getmax
mov max, eax

push 0
call ExitProcess
main ENDP


getmin PROC uses ecx esi ebx, parr: dword, elem: dword
      mov   ecx, elem       ; Загрузка количества элементов массива в регистр ecx
      mov   esi, parr       ; Загрузка адреса начала массива в регистр esi
      mov   ebx, [esi]      ; Загрузка первого элемента массива в регистр ebx

CYCLE: 
      lodsd                 ; Загрузка следующего элемента массива в eax и инкремент адреса esi
      cmp   eax, ebx        ; Сравнение текущего элемента с текущим минимальным значением в ebx
      jge   FALSE           ; Переход к метке FALSE, если текущий элемент больше или равен текущему минимальному
      xchg  ebx, eax        ; Обмен значениями текущего элемента и текущего минимального
FALSE: 
      loop  CYCLE           ; Повторение цикла, если не достигнуто количество элементов
      xchg eax, ebx         ; Загрузка минимального значения в eax перед возвратом
      ret                   ; Возврат из процедуры
getmin ENDP

getmax PROC uses ecx esi ebx, parr: dword, elem: dword

      mov   ecx, elem
      mov   esi, parr
      mov   ebx, [esi]
CYCLE: 
      lodsd
      cmp   eax, ebx
      jle   FALSE
      xchg  ebx, eax 
FALSE: 
      loop  CYCLE
      xchg ebx, eax
	ret
getmax ENDP

END main