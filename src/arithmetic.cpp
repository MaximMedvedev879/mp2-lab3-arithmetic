// реализация функций и классов для вычисления арифметических выражений

#include <iostream>
#include <string>
#include "../include/arithmetic.h"

using namespace std;

int DeterminationType(char s) //type1-цифра; type2-буква ; type3-знаки операций ; type 4 - точка или запятая double; type 5 -пробел
{
	if (isdigit(s))
		return 1;
	else if (isalpha(s))
		return 2;
	else if (IsSign(s))
		return 3;
	else if ((s == '.') || (s == ','))
		return 4;
	else if (s == ' ')
		return 5;
	else
		return 0;
}

void ProcessingUnaryMinus(char* s, char* res) //обработка унарного минуса
{
	int len = strlen(s);
	bool isOpen = false;
	int j = 0;
	int type[256];
	for (int i = 0; i < len; i++)
		type[i] = DeterminationType(s[i]);
	type[len] = 0;
	if (s[0] == '-')
	{
		res[j] = '0';
		j++;
		res[j] = '-';
		j++;
	}
	else
	{
		res[j] = s[0];
		j++;
	}
	for (int i = 1; i < len; i++)
	{
		if (s[i] == '-')
		{
			if ((s[i - 1] == '(' || type[i - 1] == 3) && ((type[i + 1] == 1) || (type[i + 1] == 2) || s[i + 1] == '\0'))
			{
				res[j] = '(';
				j++;
				res[j] = '0';
				j++;
				res[j] = '-';
				j++;
				isOpen = true;
			}
			
					
		}
        else 
		if (isOpen && type[i] == 3) 
		{
				res[j] = ')';
				j++;
				res[j] = s[i];
				j++;
				isOpen = false;
		}
		
		else
		{
			res[j] = s[i];
			j++;
			
		}	
	}
	if (isOpen) {
		res[j] = ')';
		j++;
		isOpen = false;
	}
	res[j] = '\0';
}
	
bool ThereIsUnaryMinus(char* s)// проверка на наличие унарного минуса
{
	int i = 1;
	int flag = 0;
	int len = strlen(s);
	int type[256];
	for (int j = 0; j < len; j++)
		type[j] = DeterminationType(s[j]);
	type[len] = 0;
	if (s[0] == '-')
		flag = 1;
	while (s[i] != '\0')
	{
		if (s[i] == '-')
		{
			if ((s[i - 1] == '(' || type[i - 1] == 3) && ((type[i + 1] == 1) || (type[i + 1] == 2)))
			{
				flag = 1;
				break;
			}
		}
		i++;
	}
	if (flag == 1)
		return true;
	else
		return false;
}
void ReplacementPointToCommaInDouble(char* s)
{
	int len = strlen(s);
	int type[256];
	for (int i = 0; i < len; i++)
		type[i] = DeterminationType(s[i]);
	for (int i = 0; i < len; i++)
	{
		if (type[i] == 4)
		{
			if (s[i] == ',')//
				s[i] = '.';//
		}
	}
}


bool CheckBrackets(char* s)//проверка расставления скобок
{
	TStack<int> br(256);
	int len = strlen(s);
	int flag = 0;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '(')
			br.Push(i);
		else if (s[i] == ')')
		{
			if (br.IsEmpty())
			{
				cout << "Error in placing brackets at position  " << i + 1 << endl;
				flag = 1;
				break;
			}
			else
			{
				br.Pop();
			}

		}
	}
	if (flag == 1)
		return false;
	else
	{
		if (br.IsEmpty())
			return true;
		else
		{
			cout << "Error in placing brackets on positions ";
			while (br.IsEmpty() != true)
			{
				int res;
				res = br.Pop();
				res++;
				cout << res << ";";
			}
			cout << endl;
			return false;
		}
	}
}
bool CheckAmountOperands(char* s)// проверка на недостаток операндов
{
	int flag = 1;
	int len = strlen(s);
	for (int i = 1; i < len - 1; i++)
	{
		if (IsOperation(s[i]))
			if ((s[i - 1] == '(') || (s[i + 1] == ')'))
			{
				cout << "Lack of operands on the position " << i + 1 << endl;
				flag = 0;
				break;
			}
	}
	if (IsOperation(s[0]))
	{
		cout << "Lack of operands on the first position" << endl;
		flag = 0;
	}
	else if (IsOperation(s[len - 1]))
	{
		cout << "Lack of operands on the position  " << len << endl;
		flag = 0;
	}
	if (flag == 1)
		return true;
	else
		return false;

}
bool CheckOperationsInRow(char* s)//проверка на кол-во операций подряд
{
	int len = strlen(s);
	int flag = 0;
	for (int i = 0; i < len - 1; i++)
	{
		if (IsOperation(s[i]))
		{
			if (IsOperation(s[i + 1]))
			{
				cout << "Two operation signs in a row on the positions " << i + 1 << " and " << i + 2 << endl;
				flag = 1;
				break;
			}
		}
	}
	if (flag == 1)
		return false;
	else
		return true;
}

bool CheckPlaceDotsOrCommas(char* s)//проверка на правильную расстановку точек и запятых у double
{
	int len = strlen(s);
	int flag = 0;
	int type[256];
	for (int i = 0; i < len; i++)
		type[i] = DeterminationType(s[i]);
	if ((type[0] == 4) || (type[len - 1] == 4))
		return false;
	else
	{
		for (int i = 1; i < len - 1; i++)
			if (type[i] == 4)
			{
				if ((type[i - 1] != 1) || (type[i + 1] != 1))
					flag = 1;
				break;
			}
		if (flag == 1)
			return false;
		else
			return true;
	}
}
bool CheckCorrectnessOfSymbols(char* s)//проверка на наличие некорректных символов
{
	int len = strlen(s);
	int flag = 0;
	int type[256];
	for (int i = 0; i < len; i++)
		type[i] = DeterminationType(s[i]);
	for (int i = 0; i < len; i++)
		if (type[i] == 0)
		{
			cout << "Invalid character on the position " << i + 1 << endl;
			flag = 1;
			break;
		}
	if (flag == 1)
		return false;
	else
		return true;
}
bool CheckAmountLettersaInVars(char* s)//проверка на количество букв в переменных
{
	int len = strlen(s);
	int flag = 0;
	int type[256];
	for (int i = 0; i < len; i++)
		type[i] = DeterminationType(s[i]);
	for (int i = 0; i < len - 1; i++)
		if ((type[i] == 2) && (type[i + 1] == 2))
		{
			cout << "The variable name contains more than one letter per position " << i + 1 << endl;
			flag = 1;
			break;
		}
	if (flag == 1)
		return false;
	else
		return true;
}

bool CheckVariableToDigit(char* s) //проверка на наличие знака умножения между операндами
{
	int len = strlen(s);
	int flag = 0;
	int type[256];
	for (int i = 0; i < len; i++)
		type[i] = DeterminationType(s[i]);
	for (int i = 0; i < len; i++)
		if (((type[i] == 2) && (type[i + 1] == 1)) || ((type[i] == 1) && (type[i + 1] == 2)))
		{
			cout << "The operator *(multiplication) between operands on positions " << i << " and " << i + 1 << " is omitted" << ". " << "Correct option: x*A or A*x (A - const)" << endl;
			flag = 1;
			break;
		}
	if (flag == 1)
		return false;
	else
		return true;

}

bool CheckStr(char* s)//проверка на выполнение всех условий
{
	if ((CheckBrackets(s)) && (CheckAmountOperands(s)) && (CheckOperationsInRow(s)) && (CheckPlaceDotsOrCommas(s)) && (CheckCorrectnessOfSymbols(s)) && (CheckAmountLettersaInVars(s)) && CheckVariableToDigit(s))
		return true;
	else
		return false;
}

int Prioritet(char s)//приоритет операций
{
	switch (s)
	{
	case '(':
	{
		return 0;
	}
	case '+':
	{
		return 1;
	}
	case '-':
	{
		return 1;
	}
	case '*':
	{
		return 2;
	}
	case '/':
	{
		return 2;
	}
	case '^':
	{
		return 3;
	}
	}
}

bool IsSign(char s)// определение знак операции или нет
{
	int flag = 0;
	char sign[] = "-+*/()^";
	for (int i = 0; i < 7; i++)
		if (s == sign[i])
		{
			flag = 1;
			break;
		}
	if (flag == 1)
		return true;
	else
		return false;
}
bool IsOperation(char s)//определение знака операции, но без скобок
{
	int flag = 0;
	char sign[] = "-+*/^";
	for (int i = 0; i < 5; i++)
		if (s == sign[i])
		{
			flag = 1;
			break;
		}
	if (flag == 1)
		return true;
	else
		return false;
}

void FindVars(const char* s, int* res)//нахождение переменных в формуле
{
	int j = 0;
	int len = strlen(s);
	int type[256];
	for (int i = 0; i < len; i++)
		type[i] = DeterminationType(s[i]);
	for (int i = 0; i < len; i++)
		if (type[i] == 2)
		{
			res[j] = i;
			j++;
		}
}
bool CheckCorrecnessOfValuesOfVars(char* s) // проверка на то, что вместо значений не введены какие-то знаки, пробелы, скобки и тп
{
	int flag = 0;
	int len = strlen(s);
	int type[256];
	for (int i = 0; i < len; i++)
		type[i] = DeterminationType(s[i]);
	if ((IsSign(s[0])) && (s[0] != '-'))
		flag = 1;
	for (int i = 0; i < len; i++)
	{
		if ((type[i] == 0) || (type[i] == 2) || (type[i] == 5))
		{
			flag = 1;
			break;
		}
	}
	for (int i = 1; i < len; i++)
	{
		if (type[i] == 3)
		{
			flag = 1;
			break;
		}
	}
	if (CheckPlaceDotsOrCommas(s) != true)
		flag = 1;
	if (flag == 0)
		return true;
	else
		return false;
}

void InputValues(char* s, char* res) //функция для ввода значений переменных
{
	int* num;
	int Size = 256;
	int i = 0; int m = 0;
	int len = strlen(s);
	num = new int[Size];
	for (int j = 0; j < Size; j++)
		num[j] = -1;
	FindVars(s, num);
	if (num[0] != -1)
		cout << "Enter the values of the variables" << endl;
	for (int p = 0; p < len; p++)
	{
		if (num[i] != p)
		{
			res[m] = s[p];
			m++;
		}
		else
		{
			int flag = 1;
			char str[256];
			int j = 0;
			while (flag == 1)
			{
				cout << s[num[i]] << "=";
				gets_s(str);
				if (CheckCorrecnessOfValuesOfVars(str) != true)
				{
					cout << "The value is incorrect! Enter the value again " << endl;
				}
				else
				{
					if (str[0] == '-')
					{
						res[m] = '0';
						m++;
						res[m] = ' ';
						m++;
						j = 1;
						while (str[j] != '\0')
						{
							res[m] = str[j];
							m++;
							j++;
						}
						res[m] = ' ';
						m++;
						res[m] = '-';
						m++;
						p++;
					}
					else
					{
						while (str[j] != '\0')
						{
							res[m] = str[j];
							m++;
							j++;
						}
					}
					flag = 0;
				}
			}
			i++;
		}
	}
	res[m] = '\0';
	delete[]num;
}

double GetNumber(char* s)//получение числа из char
{
	double res = atof(s);
	return res;
}

void ConvertInPostfixNotation(const char* s, char* res)//перевод в постфиксную запись
{
	TStack<char> sg(256);
	int len = strlen(s);
	int type[256];
	for (int i = 0; i < len; i++)
		type[i] = DeterminationType(s[i]);
	int j = 0; int m = 0;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '(')
			sg.Push('(');
		if (s[i] == ')')
		{
			char a = sg.Pop();
			while (a != '(')
			{
				res[j] = a;
				j++;
				a = sg.Pop();
			}
		}
		if (IsOperation(s[i]))
		{
			if (sg.IsEmpty())
				sg.Push(s[i]);
			else
			{
				char op = sg.Get();
				while (Prioritet(s[i]) <= Prioritet(op))
				{
					res[j] = sg.Pop();
					j++;
					if (sg.IsEmpty() != true)
						op = sg.Get();
					else
						op = '(';
				}
				sg.Push(s[i]);
			}
		}
		if (type[i] == 1)
		{
			if ((type[i + 1] == 1) || (type[i + 1] == 4))
			{
				res[j] = s[i];
				j++;
			}
			else
			{
				res[j] = s[i];
				j++;
				res[j] = ' ';
				j++;
			}
		}
		if (type[i] == 2)
		{
			res[j] = s[i];
			j++;
			res[j] = ' ';
			j++;
		}
		if (type[i] == 4)
		{
			res[j] = s[i];
			j++;
		}
	}
	while (sg.IsEmpty() != true)
	{
		res[j] = sg.Pop();
		j++;
	}
	res[j] = '\0';
}


double EvaluationOfExpression(char* s)//вычисление выражения
{
	TStack <double> num(256);
	int len = strlen(s);
	int l = 0; int i = 0; int m = 0;
	double res;
	int type[256];
	for (int j = 0; j < len; j++)
		type[j] = DeterminationType(s[j]);
	while (s[i] != '\0')
	{
		if (type[i] == 1)
		{
			char str[256];
			int k = 0;
			double number;
			m = i;
			while (s[m] != ' ')
			{
				str[k] = s[m];
				m++;
				k++;
			}
			str[k] = '\0';
			l = m - i + 1;
			number = GetNumber(str);
			num.Push(number);
			i = i + l - 1;
		}
		if (IsOperation(s[i]))
		{
			double opright, opleft;
			opright = num.Pop();
			opleft = num.Pop();
			switch (s[i])
			{
			case '+':
			{
				res = opleft + opright;
				break;
			}
			case '-':
			{
				res = opleft - opright;
				break;
			}
			case '*':
			{
				res = opleft * opright;
				break;
			}
			case '/':
			{
				res = opleft / opright;
				break;
			}
			case '^':
			{
				int op;
				op = (int)opright;
				int count = 1;
				res = opleft;
				do
				{
					if (op == 0)
						res = 1;
					else if ((op != 1) && (op > 0))
						res = res * opleft;
					count++;
				} while (op > count);
				break;
			}
			}
			num.Push(res);
		}
		i++;
	}
	return num.Pop();
}
