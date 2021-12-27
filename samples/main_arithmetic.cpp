// реализация пользовательского приложения

#include <iostream>
#include <string>
#include "arithmetic.h"
#define MAX_SIZE 256;
int main()
{
	char str[256];
	int Size = MAX_SIZE;
	int flag1 = 1; 
	int p = 0;
	char* newstr;

	newstr = new char[Size];
	cout << "A calculator that performs the calculation of an arithmetic expression with real numbers." << endl;
	cout << "The expression as operands can contain variables and real numbers, including negative ones." << endl;
	cout << "To enter real numbers, use a dot (.) on the keyboard";
	cout << "Variable names can contain only one letter." << endl;
	cout << "Acceptable operations : +, -, /, *, ^. " << endl;
	while (flag1 == 1)
	{
		cout << "Enter the expression: ";
		gets_s(str); 
		ReplacementPointToCommaInDouble(str);
		if (ThereIsUnaryMinus(str))
		{
			ProcessingUnaryMinus(str, newstr);
		}
		else
		{
			int i = 0;
			while (str[i] != '\0')
			{
				newstr[i] = str[i];
				i++;
			}
			newstr[i] = '\0';
		}

		if (CheckStr(newstr) != true)
			cout << "The expression is incorrect! Enter the expression again " << endl;
		else
		{
			double result;
			int flag2 = 1;
			char* newstr1;
			char* newstr2;
			newstr1 = new char[Size];
			newstr2 = new char[Size];
			ConvertInPostfixNotation(newstr, newstr1);
			while (flag2 == 1)
			{
				InputValues(newstr1, newstr2);
			    ReplacementPointToCommaInDouble(newstr2);
				result = EvaluationOfExpression(newstr2);
				cout << "The result of the expression = " << result << endl;
				
					flag2 = 0;
			}
			flag1 = 0;
			delete[]newstr1;
			delete[]newstr2;
		}

	}
	delete[]newstr;
	return 0;
}
