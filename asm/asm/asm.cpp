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



