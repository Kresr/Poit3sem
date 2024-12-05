.586P                         ; система подкоманд (процессор Pentium)
.MODEL FLAT, STDCALL          ; модель памяти, соглашение о вызове
includelib kernel32.lib       ; подключаем библиотеку с функцией ExitProcess
includelib user32.lib         ; подключаем библиотеку для MessageBoxA

ExitProcess PROTO :DWORD      ; прототип функции завершения процесса Windows
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD  ; прототип API-функции MessageBoxA

.STACK 4096                   ; сегмент стека размером 4096 Мбайт

.DATA                         ; сегмент данных
    myBytes     BYTE    10h, 20h, 30h, 40h, 0h   ; Массив из 4 байтов
    SUM         DWORD   0                        ; Для хранения суммы
    str0        db      "Ермоленко СТас, курс 2, ПИ", 0            
    str1        db      "Массив содержит 0", 0 
    str2        db      "Массив не содержит 0", 0

.CODE
main PROC
start:  
    ; Работа с массивом myBytes
    mov ESI, OFFSET myBytes    ; Указатель на массив myBytes
    mov AH, [ESI]              ; Загружаем первый байт в старший регистр AH
    mov AL, [ESI + 2]          ; Загружаем третий байт в младший регистр AL

    ; Суммирование элементов массива myBytes
    mov ESI, OFFSET myBytes    ; Указатель на массив myBytes
    mov ECX, 5               ; Количество элементов в массиве (4 байта)
    xor EAX, EAX               ; Обнуляем аккумулятор для суммы

SUM_LOOP:
    movzx EBX, BYTE PTR [ESI]  ; Загружаем текущий байт, расширяя его до DWORD
    add EAX, EBX               ; Прибавляем значение к сумме
    inc ESI                    ; Переходим к следующему элементу (BYTE = 1 байт)
    loop SUM_LOOP              ; Повторяем цикл

    mov [SUM], EAX             ; Сохраняем сумму в переменной SUM

    ; Проверка на наличие нулевого элемента
    mov ESI, OFFSET myBytes    ; Указатель на массив myBytes
    mov ECX, 5                 ; Количество элементов массива
    xor EBX, EBX               ; Сбрасываем EBX (флаг наличия нуля)

CHECK_ZERO_LOOP:
    movzx EAX, BYTE PTR [ESI]  ; Загружаем текущий байт, расширяя его до DWORD
    test EAX, EAX              ; Проверяем, равен ли байт нулю
    jz FOUND_ZERO              ; Если найден 0, переходим к метке FOUND_ZERO
    inc ESI                    ; Переходим к следующему элементу
    loop CHECK_ZERO_LOOP       ; Повторяем цикл

NO_ZERO:
    mov EBX, 1                 ; Если нулей не найдено, записываем 1 в EBX
    invoke MessageBoxA, 0, OFFSET str2, OFFSET str0, 0
    jmp END_PROGRAM            ; Завершаем программу

FOUND_ZERO:
    mov EBX, 0                 ; Если найден 0, записываем 0 в EBX
    invoke MessageBoxA, 0, OFFSET str1, OFFSET str0, 0

END_PROGRAM:
    push 0                     ; Завершаем программу
    call ExitProcess

main ENDP
end main
