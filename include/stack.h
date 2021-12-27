// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#ifndef __STACK_H__
#define __STACK_H__
#include <iostream>
using namespace std;
const int MAXSIZE = 1000000000;

template <class ValType>
class TStack
{
private:
	ValType* stack;
	int size;
	int end; //индекс последнего элемента

public:
	TStack(int n = MAXSIZE);
	TStack(const TStack& v);
	~TStack();
	ValType Pop(); //извлечение элемента
	ValType Get(); //извлечение элемента без удаления
	void Push(double elem); //вставка элемента
	bool IsEmpty(); //проверка на пустоту
	ValType View(); //просмотр верхнего элемента
	int End(); //получение индекса последнего элемента
	int Size(); //получение количества элементов в стеке
	void Clear(); //очистка стека
};

template <class ValType>
TStack<ValType>::TStack(int n)
{
	if ((n <= 0) || (n > MAXSIZE)) throw "incorrect n";
	else
	{
		stack = new ValType[n];
		end = -1;
		size = n;
	}
}

template <class ValType>
TStack<ValType>::TStack(const TStack<ValType>& v)
{
	size = v.size;
	end = v.end;
	stack = new ValType[size];
	for (int i = 0; i < end; i++)
		stack[i] = v.stack[i];
}

template <class ValType>
TStack<ValType>::~TStack()
{
	delete[]stack;
}
template <class ValType>
ValType TStack <ValType>::Pop()
{
	if ((*this).IsEmpty()) throw "Stack is empty";
	else
	{
		ValType res;
		res = stack[end];
		end--;
		return res;
	}
}
template <class ValType>
ValType TStack<ValType>::Get()
{
	if ((*this).IsEmpty()) throw "Stack is empty";
	else
		return stack[end];
}

template <class ValType>
int TStack <ValType>::Size()
{
	return (end + 1);
}

template <class ValType>
int TStack <ValType>::End()
{
	return end;
}

template <class ValType>
void TStack<ValType>::Push(double elem)
{
	if (end == size)
	{
		ValType* temp = stack;
		stack = new ValType[2*size];
		for (int i = 0; i < size; i++)
			stack[i] = temp[i];
		delete[]temp;

		size = 2 * size;
	}
	end++;
	stack[end] = elem;
}
template <class ValType>
void TStack<ValType>::Clear()
{
	end = -1;
	size = 0;
	delete[]stack;
	stack = new ValType[size];
}

template <class ValType>
bool TStack<ValType>::IsEmpty()
{
	if (end == -1)
		return true;
	else return false;

}


template <class ValType>
ValType TStack <ValType>::View()
{
	if (IsEmpty()) throw "Stack is empty";
	else
		return stack[end];
}
#endif
