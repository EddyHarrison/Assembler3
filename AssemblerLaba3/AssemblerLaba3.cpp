#include <iostream>
#include <conio.h>

int main() {
	// Меняем язык вывода на русский, чтобы русский выводился на консоль корректно 
	 setlocale(0, "rus");
	double a = 0, b = 0, c = 0, x1 = 0, x2 = 0, step = 0;
	double x, y;
	int key;
	double ten = 10, five = 5, two = 2;
	char s[] = "%lf";
	const char* mes1 = "Введите значения: a b c x1 x2 dx через пробел \n";
	const char* mes2 = "\n НАЖМИТЕ ENTER ЧТОБЫ ПРОДОЛЖИТЬ, ESC - ВЫХОД\n";
	const char* cls = "cls"; // очистка 

	char m1[] = "-----------------------------\n";
	char m2[] = "|      x      |      y      |\n";
	char m3[] = "-----------------------------\n";
	char s0[] = "| %11.3lf | %11.3lf |\n";
	char s1[] = "| %11.3lf | ----------- |\n";

	_asm {
		finit //инициализация сопроцессора
		get_data :
		mov eax, cls // положили в eax - cls 
			push eax     // поместили eax в стек 
			call system  // вызов функции system (для очистки экрана) 
			add esp, 4   // возвращение указателя esp в исходное состояние 
			//Вывод сообщения 

			mov eax, mes1 // положили в eax - cls 
			push eax     // поместили eax в стек 
			call printf  // вызов функции printf 
			add esp, 4   // возвращение указателя esp в исходное состояние 

			//=====Ввод значений=====
			lea eax, a // помещаем в eax адрес переменной a 
			push eax   // помещаем eax в стек 
			lea eax, s // помещаем в eax адрес переменной s 
			push eax   // помещаем eax в стек 
			call scanf // вызов функции scanf 
			add esp, 8 // возвращаем указатель esp в исходное состояние 

			lea eax, b // помещаем в eax адрес переменной b
			push eax   // помещаем eax в стек 
			lea eax, s // помещаем в eax адрес переменной s 
			push eax   // помещаем eax в стек 
			call scanf // вызов функции scanf 
			add esp, 8 // возвращаем указатель esp в исходное состояние 

			lea eax, c // помещаем в eax адрес переменной c
			push eax   // помещаем eax в стек 
			lea eax, s // помещаем в eax адрес переменной s 
			push eax   // помещаем eax в стек 
			call scanf // вызов функции scanf 
			add esp, 8 // возвращаем указатель esp в исходное состояние 

			lea eax, x1 // помещаем в eax адрес переменной x1 
			push eax   // помещаем eax в стек 
			lea eax, s // помещаем в eax адрес переменной s 
			push eax   // помещаем eax в стек 
			call scanf // вызов функции scanf 
			add esp, 8 // возвращаем указатель esp в исходное состояние 

			lea eax, x2 // помещаем в eax адрес переменной x2 
			push eax   // помещаем eax в стек 
			lea eax, s // помещаем в eax адрес переменной s 
			push eax   // помещаем eax в стек 
			call scanf // вызов функции scanf 
			add esp, 8 // возвращаем указатель esp в исходное состояние 

			lea eax, step // помещаем в eax адрес переменной step 
			push eax   // помещаем eax в стек 
			lea eax, s // помещаем в eax адрес переменной s 
			push eax   // помещаем eax в стек 
			call scanf // вызов функции scanf 
			add esp, 8 // возвращаем указатель esp в исходное состояние 

			//=====Заголовок таблицы=====
			lea ebx, m1
			push ebx
			call printf
			add esp, 4
			lea ebx, m2
			push ebx
			call printf
			add esp, 4
			lea ebx, m3
			push ebx
			call printf
			add esp, 4
			//=====Таблица значений=====
			fld x1  // st(0) = x1 
			fstp x  // x = st(0) == x1 
			fldz    // st(0) = 0
			begin :
		fld x2  // st(0) = x2 -> st(1)=0
			fsub x  // st(0) = x2-x 
			fcomip st(0), st(1) // сравнение st(0) и 0
			jb pre_end  // если (x2-x)<2 переходим к end 

			//=====Расчет=====
			// случай x<0, b!=0, y=a*x*x*x+b*x*x
			fld x // st(0)=x -> st(1)=0 
			fcomip st(0), st(1) // -> st(0)=0
			jnb l2 // если x >= 0 переходм на l2 
			fld b //st(0)=b -> st(1)=0
			fcomip st(0), st(1) // -> st(0)=0
			je l2 // если b==0 переходим на l2 
			fld x //st(0)=a -> st(1)=0
			fmul two //умножение на 2
			fsub c //st(0)= 2x-c

			fld c // st(0)=c -> st(1)=2x-c
			fmul x // st(0) = st(0)*x -> st(0)=cx 
			fsub a // st(0) = st(0)-a -> st(0)=cx-a

			fdivp st(1), st(0) // st(0) = st(0)/st(1) -> st(0)=(2x-c)/(cx-a)

			mov esi, -1 //инциализация регистра значением -1
			push esi //загрузка регистра в стек
			fild dword ptr[esp] //инициализация st(0)
			pop esi  //выгружаем регистр из стека
			fmulp st(1), st(0) //умножение
			fstp y // y=st(0) -> y=-(2x-c)/(cx-a) -> st(0)=0?? 
			mov key, 0 //key = 0 (значение y определено)
			jmp l1 //переход на метку l1

			// случай x>0, b=0,  y=(x-a)/(x-c)
			l2 :
		fld x //st(0) = x -> st(1)=0 
			fcomip st(0), st(1) // -> st(0)=0
			jbe l3 //если x <= 0 (x меньше или равно 0) переходим на метку l3
			fld b //st(0) = b -> st(1)=0
			fcomip st(0), st(1) // -> st(0)=0
			jne l3 //если b != 0 (b не равно 0) переходим на метку l3
			fld x //st(0) = x -> st(1) = 0 
			fsub c 	//st(0) = st(0)-c -> st(0) = x-c
			fcomip st(0), st(1) // -> st(0)=0
			je l4 //если (x-c) = 0 переходим на метку l4
			fld x //st(0) = x -> st(1) = 0
			fsub a //st(0) = st(0)-a (st(0) == x-a)
			fld x //st(2) = 0 -> st(1) = x-a -> st(0) = x]
			fsub c //st(0) = st(0)-c (st(0) == x-c)
			fdivp st(1), st(0) // st(1) = 0 -> st(0) = (x-a)/(x-c)
			fstp y //y = st(0) и вытолкнуть (y == (x-a)/(x-c)) -> st(0) == 0
			mov key, 0 //key = 0 (значение y определено)
			jmp l1 //переход на метку l1
		// случай иначе,     y=(x+5)/(c(x-10))
			l3 :
		fld c  // st(0)=c -> st(1)=0
			fcomip st(0), st(1)  // st(0)=0
			je l4  // если с==0 переходим на l4 
			fld x // st(0)=x -> st(1)=0
			fsub ten // st(0)=x-10
			fcomip st(0), st(1) // -> st(0)=0
			je l4 // если x-10 == 0 то переходим на метку l4
			fld x // st(0)=x -> st(1)=0
			fdiv c// st(0) = x/c
			mov esi, -1 //инциализация регистра значением -1
			push esi //загрузка регистра в стек
			fild dword ptr[esp] //инициализация st(0)
			pop esi  //выгружаем регистр из стека
			fmulp st(1), st(0) //умножение

			fld c  // st(0)=c -> st(1)=x/-c -> st(2)=0
			mov esi, -1 //инциализация регистра значением -1
			push esi //загрузка регистра в стек
			fild dword ptr[esp] //инициализация st(0)
			pop esi  //выгружаем регистр из стека
			fmulp st(1), st(0) //умножение
			fdiv x //
			fdiv two
			faddp st(1), st(0) // 
			fstp y // 
			mov key, 0
			jmp l1
			// деление на 0 
			l4 :
		mov key, 1
			l1 :
			//=====Вывод строки таблицы =====
			cmp key, 0 // сравнение значений key и 0
			je l5      // если key == 0 переходим на l5 
			sub esp, 8 // уменьшим указатель esp на 8 
			fld x      // st(0)=x 
			fstp qword ptr[esp] // загрузить в сегмент стека st(0) 
			lea eax, s1 // поместить адрес строки s1 в eax 
			push eax    // поместить eax в стек 
			call printf // вызов функции printf 
			add esp, 12 // вовзращаем указатель esp в исходное состояние 
			jmp l6      // переходим к метке l6
			l5 :
		sub esp, 8  // уменьшим указатель esp на 8
			fld y       // st(0)=x 
			fstp qword ptr[esp] // загрузить в сегмент стека st(0) 
			sub esp, 8  // уменьшим указатель esp на 8 
			fld x       // st(0)=x 
			fstp qword ptr[esp] // загрузить в сегмент стека st(0) 
			lea eax, s0 // поместить адрес строки s0 в eax 
			push eax    // поместить eax в стек 
			call printf // вызов функции printf 
			add esp, 20 // вовзращаем указатель esp в исходное состояние 
			l6:
		fld x      // st(0)=x 
			fadd step  // st(0)=x+step или x+dx
			fstp x     // выталкиваем st(0) 
			jmp begin  // переходим на метку begin
			pre_end :
		// вывод сообщения 
		mov eax, mes2  // поместили значение mes2 в регистр eax 
			push eax       // поместили eax в стек 
			call printf    // вызов функции printf для вывода сообщения 
			add esp, 4     // возвращаем указатель esp в исходное состояние  

			call getch     // вызов функции getch - считывание символа с клавиатуры 
			cmp eax, 27    // сравнение результата getch с 27 (esc) 
			je end         // если eax = 27 переход на метку end 
			cmp eax, 13    // сравнение результата getch c 13 (enter) 
			je get_data       // если eax = 13 переход на метку enter 
			jmp get_data    // если eax не 13 и не 27, переход к метке pre_end для повторного вопроса 
			end :
	}

	return 0;
}
