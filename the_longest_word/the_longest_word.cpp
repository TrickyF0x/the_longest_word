#include "pch.h"
#include "lw_finder.h"
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);//для корректного отображения в консоли кириллицы
	SetConsoleOutputCP(1251);

	LongWord sentense;//создаем объект

	sentense.set_line();//задаем строку
	sentense.find_word();//ищем слово

	system("pause");
	return 0;
}