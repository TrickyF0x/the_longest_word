#pragma once
#include <cstdlib>
#include <vector>
#include <iterator>
#include <iostream>
#include <ctype.h>
#include <Windows.h>

class LongWord
{
private:
	std::istream& getline(std::istream& is, std::vector<char> &buffer)
	{
		std::istream::sentry s(is);
		if (s)
		{
			std::istreambuf_iterator<char> it(is);
			std::istreambuf_iterator<char> end;

			const size_t grow = 128;
			buffer.reserve(grow);

			while (it != end && *it != '\n')
			{
				if (buffer.size() == buffer.capacity() - 1)
				{
					buffer.reserve(buffer.size() + grow);
				}

				buffer.push_back(*it++);
			}
			buffer.push_back('\0');
		}
		return is;
	}

	bool polindrome(int start, int end, std::vector<char> &line)
	{
		while (1)
		{
			if (line[start] != line[end])
				break;
			if (start == end)
				break;
			++start;
			--end;
		}
		if (start == end)
			return true;
		else
			return false;
	}

public:
	std::vector<char> line;//вектор можно принять за динамический массив размера n

	void set_line()
	{
		printf("Введите строку:\t");
		getline(std::cin, line);
		line.shrink_to_fit();
	}

	void find_word()
	{
		int start, end, sizecur = 0, sizeprev = 0, max[3], count = 0;
		int unsigned i = 0;
		bool ok = false;

		max[2] = 0;//конец подстроки

		while (i < line.size() - 1)
		{
			if (line[i] != ' ')//если пробел
			{
				sizeprev = sizecur;
				start = i;//начало подстроки
				while (1)//определяем подстроку
				{
					if ((i == line.size() - 1) || (line[i] == ' '))//+ пока не дойдем до пробела или конца
						break;
					++i;
				}
				++count;
				end = i - 1;
				sizecur = end - start;//размер подстроки
				int j = start;
				while (j <= end)
				{
					if (isdigit((unsigned char)line[j]) == false)//есть ли число в подстроке
						ok = true;//чисел нет
					else
					{
						ok = false;//найдено число
						sizecur = 0;
						--count;
						break;
					}
					++j;
				}
				if (((sizecur >= sizeprev) && (sizecur >= max[2])) && (ok == true))//запоминаем самую большую подстроку без чисел
				{
					max[0] = start;//начало подстроки
					max[1] = end;//конец подстроки
					max[2] = sizecur + 1;//длина подстроки
				}
			}
			else
				++i;
		}
		//printf("Parametres: start %d,  end %d,  lenght %d\n", max[0], max[1], max[2] + 1);//параметры подстроки
		if (count == 0)//в задании указано - подстрокА, т.е. рассматриваем лишь одно слово (первое что удовлетворит условию)
		{
			printf("Все подстроки содержат числа\n");
		}
		else
		{
			printf("Самая длинная подстрока: ");
			int j = max[1];
			if (polindrome(max[0], max[1], line))
			{
				i = max[0];
				while (i <= max[1])
				{
					printf("%c", line[i]);
					++i;
				}
				printf(" - является палиндромом\n");
			}
			else
			{
				while (1)//переворот подстроки на экране
				{
					printf("%c", line[j]);
					--j;
					if (j < max[0]) break;
				}
				j = max[1];
				i = max[0];
				while (1)
				{
					if ((i >= j) || (j <= 0))
						break;
					std::swap(line[i], line[j]);
					++i;
					--j;
				}
				printf("\nПолучившееся строка:\t%s\n", line.data());
			}
		}
	}
	
};