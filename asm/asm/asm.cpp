//#include <iostream>
//int main() {
//    int var1 = 42;
//    int var2 = 0;
//    int var3 = 0;
//
//    __asm {
//        mov eax, var1; загрузить var1 в регистр eax
//        mov var2, eax; сохранить eax в var2
//        mov eax, var2; загрузить var2 в регистр eax
//        mov var3, eax; сохранить eax в var3
//    }
//}

//#include <iostream>
// lab 2
//int main() {
//    int x = 5, a = 3, y1 = 0, y2 = 0, y = 0;
//
//    __asm {
//        mov eax, x
//        cmp eax, a
//        jg x_greater_than_a
//
//        // x <= a branch
//        sub eax, a
//        neg eax
//        add eax, a
//        add eax, a
//        mov y1, eax
//        jmp calculations_end
//
//        // x > a branch
//        x_greater_than_a :
//        add eax, a
//            mov y1, eax
//
//            calculations_end :
//    }
//
//    __asm {
//        mov eax, x
//        cmp eax, 10
//        jg x_greater_than_10
//
//        x_less_or_equal_than_10 :
//        mov y2, eax
//            jmp y2_calc_end
//
//            x_greater_than_10 :
//        imul eax, a
//            mov y2, eax
//
//            y2_calc_end :
//    }
//
//    y = y1 + y2;
//
//    std::cout << "y1 = " << y1 << ", y2 = " << y2 << ", y = " << y << std::endl;
//    return 0;
//}

//#include <iostream>
//
//using namespace std;
//
//int main() {
//    int sum;
//    __asm{
//      mov ecx, 1
//      mov eax, 0
//
//      loop_start:
//      mov ebx, ecx
//      imul ebx, ecx
//      add eax, ebx
//      add eax, ebx
//      add eax, ecx
//      sub eax, 3
//      add edx, eax
//
//      inc ecx
//      cmp ecx, 11
//      jl loop_start
//    }
//    cout << "Сумма значений функции y = 2x^2 + 5x - 3 в диапазоне от 1 до 10 с шагом 1: " << edx << endl;
//    return 0;
//}



// lab 3
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    int sum = 0;
//    int x = 1;
//    int y = 0;
//
//    __asm
//    {
//    loop_start:
//            mov eax, x //загрузить x в регистр eax
//            mov ebx, 2 //загрузить 2 в регистр ebx
//            imul eax, eax //умножить x на x
//            imul eax, ebx //умножить результат на 2
//            mov ebx, 5
//            imul ebx, x
//            add eax, ebx
//            sub eax, 3 //вычесть 3 из результата
//            add sum, eax //добавить результат к общей сумме
//            add x, 1 //увеличить x на 1
//            cmp x, 11 //сравнить x с 11
//            jl loop_start //если x < 11, то перейти на loop_start
//    }
//    //for (int i = 1; i <= 10; i++)
//    //{
//    //    sum += 2 * i * i + 5 * i - 3;
//    //}
//    cout << "Sum of function y=2x^2+5x-3 in range [1,10]: " << sum << endl;
//    return 0;
//}

#include <iostream>
#include <array>

using namespace std;

int main() {
    array<int, 10> nums = { 12, 53, -5, 10, 11, -7, 20, 32, -12, 15 };
    array<int, 10> quotients;
    array<int, 10> remainders;

    __asm {
            mov ecx, 0
            for_loop:
            mov eax, dword ptr nums[ecx * 4]
            cdq
            mov ebx, 3
            idiv ebx
            mov dword ptr quotients[ecx * 4], eax
            mov dword ptr remainders[ecx * 4], edx

            ; Check if remainder is negative
            cmp edx, 0
            jge remainder_end

            ; If remainder is negative, add divisor to make it positive
            add edx, ebx
            dec eax
            mov dword ptr quotients[ecx * 4], eax
            mov dword ptr remainders[ecx * 4], edx

            remainder_end :
            inc ecx
            cmp ecx, 10
            jnge for_loop
    }


    cout << "Quotients: ";
    for (int q : quotients) {
        cout << q << " ";
    }
    cout << endl;

    cout << "Remainders: ";
    for (int r : remainders) {
        cout << r << " ";
    }
    cout << endl;

    return 0;
}

org 7C00h

start:
cli ; Отключаем прерывания (чтобы избежать внешних вмешательств)
xor ax, ax ; Обнуляем регистр ax
mov ds, ax ; Инициализируем dataSegment в ноль
mov es, ax ; Инициализируем es в ноль
mov ss, ax ; Инициализируем StackSegment в ноль
mov sp, 07C00h ; Устанавливаем указатель стека на вершину стека
sti ; Разрешаем прерывания

; Устанавливаем видеорежим
mov ax, 3
int 10h
mov ah, 2h
mov dh, 0
mov dl, 0
xor bh, bh
int 10h

; Выводим имя
mov ax, 1301h
mov bp, fio
mov cx, 32 ; Увеличьте этот параметр на 28, чтобы вместить всю строку имени
mov bl, 02h
int 10h

; Перемещаем курсор в новую строку
mov ah, 2h
mov dl, 0
inc dh
int 10h

; Выводим факультет
mov ax, 1301h
mov bp, faculty
mov cx, 3
mov bl, 02h
int 10h

; Перемещаем курсор в новую строку
mov ah, 2h
mov dl, 0
inc dh
int 10h

; Выводим группу
mov ax, 1301h
mov bp, group
mov cx, 3
mov bl, 02h
int 10h

jmp $

fio db 'Pavlenko Aleksandr Vladimirovich',0
faculty db 'FMF',0
group db '403',0

times 510 - ($ - $$) db 0 ; Заполняем остаток сектора нулями
db 0x55, 0xAA ; Сигнатура загрузочного сектора




lab 15


org 0x7C00

start:     
; Отключаем прерывания
cli 

; Обнуляем регистры
xor ax, ax ; Обнуляем регистр ax
mov ds, ax ; Инициализируем dataSegment в ноль
mov es, ax ; Инициализируем es в ноль
mov ss, ax ; Инициализируем StackSegment в ноль
mov sp, 0x7C00 ; Устанавливаем указатель стека на вершину стека

; Разрешаем прерывания
sti 

; Задаем видеорежим
mov ax, 3
int 0x10
mov ah, 2h
mov dh, 0
mov dl, 0
xor bh, bh
int 0x10

; Вызываем подпрограмму printData, передаем параметры в регистрах
mov ax, 0x1301
mov bp, fio
mov cx, 32
mov bl, 0x2
call printData

mov ax, 0x1301
mov bp, faculty
mov cx, 3
mov bl, 0x2
call printData

mov ax, 0x1301
mov bp, group
mov cx, 3
mov bl, 0x2
call printData

jmp $

printData:
; Вызываем функцию BIOS для вывода текста
int 0x10

; Перемещаем курсор в новую строку
mov ah, 2h
mov dl, 0
inc dh
int 0x10

ret ; Возвращаем управление вызывающей программе

fio db 'Pavlenko Aleksandr Vladimirovich',0
faculty db 'FMF',0
group db '403',0

times 510 - ($ - start) db 0 ; Заполняем остаток сектора нулями
dw 0xAA55 ; Сигнатура загрузочного сектора

