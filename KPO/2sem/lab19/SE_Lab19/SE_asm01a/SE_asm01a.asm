.586P
.MODEL FLAT, STDCALL
.CODE
getmin PROC uses ecx esi ebx, parr: dword, elem: dword
      mov   ecx, elem       ; Загрузка количества элементов массива
      mov   esi, parr       ; Загрузка адреса начала массива
      mov   ebx, [esi]      ; Загрузка первого элемента массива

CYCLE: 
      lodsd                 ; Загрузка следующего элемента массива в eax
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
      xchg eax, ebx
	ret
getmax ENDP

end