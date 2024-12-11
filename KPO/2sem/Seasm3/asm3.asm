.MODEL FLAT, STDCALL          ; модель памяти, соглашение о вызове
includelib kernel32.lib       ; подключаем библиотеку с функцией ExitProcess
includelib user32.lib         ; подключаем библиотеку для MessageBoxA
ExitProcess PROTO :DWORD      ; прототип функции завершения процесса Windows
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD  ; прототип API-функции MessageBoxA
wsprintfA PROTO C :DWORD, :DWORD, :VARARG  ; Объявляем с соглашением C

.STACK 4096                   ; сегмент стека размером 4096 байт

.DATA                         ; сегмент данных
    myBytes     BYTE    10, 20, 0, 30, 40       ; Массив из 5 байтов
    SUM         DWORD   0                        ; Для хранения суммы
    str0        db      "Ермоленко СТас, курс 2, ПИ", 0            
    str1        db      "Массив содержит 0", 0 
    str2        db      "Массив не содержит 0", 0
    strSum      db      "Сумма массива: %d", 0
    buffer      db      64 DUP (?)               ; Буфер для строки

.CODE
main PROC
start:  
    ; Работа с массивом myBytes
    mov ESI, OFFSET myBytes    ; Указатель на массив myBytes
    xor EAX, EAX               ; Обнуляем аккумулятор для суммы
    mov ECX, 5                 ; Количество элементов в массиве

SUM_LOOP:
    movzx EBX, BYTE PTR [ESI]  ; Загружаем текущий байт, расширяя его до DWORD
    add EAX, EBX               ; Прибавляем значение к сумме
    inc ESI                    ; Переходим к следующему элементу
    loop SUM_LOOP              ; Повторяем цикл

    mov [SUM], EAX             ; Сохраняем сумму в переменной SUM

    ; Проверка на наличие нулевого элемента
    mov ESI, OFFSET myBytes    ; Указатель на массив myBytes
    mov ECX, 5                 ; Количество элементов массива

CHECK_ZERO_LOOP:
    movzx EAX, BYTE PTR [ESI]  ; Загружаем текущий байт, расширяя его до DWORD
    test EAX, EAX              ; Проверяем, равен ли байт нулю
    jz FOUND_ZERO              ; Если найден 0, переходим к метке FOUND_ZERO
    inc ESI                    ; Переходим к следующему элементу
    loop CHECK_ZERO_LOOP       ; Повторяем цикл

NO_ZERO:
    invoke MessageBoxA, 0, OFFSET str2, OFFSET str0, 0
    jmp DISPLAY_SUM            ; Переходим к выводу суммы

FOUND_ZERO:
    invoke MessageBoxA, 0, OFFSET str1, OFFSET str0, 0

DISPLAY_SUM:
    ; Формируем строку с суммой
    invoke wsprintfA, OFFSET buffer, OFFSET strSum, [SUM]
    invoke MessageBoxA, 0, OFFSET buffer, OFFSET str0, 0

    push 0                     ; Завершаем программу
    call ExitProcess

main ENDP
end main
