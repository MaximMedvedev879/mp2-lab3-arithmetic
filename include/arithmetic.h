// объявление функций и классов для вычисления арифметических выражений
#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "stack.h"

using namespace std;

int DeterminationType(char s);
void ProcessingUnaryMinus(char* s, char* res);
bool ThereIsUnaryMinus(char* s);
void ReplacementPointToCommaInDouble(char* s);

bool CheckBrackets(char* s);
bool CheckAmountOperands(char* s);
bool CheckOperationsInRow(char* s);
bool CheckPlaceDotsOrCommas(char* s);
bool CheckCorrectnessOfSymbols(char* s);
bool CheckAmountLettersaInVars(char* s);
bool CheckVariableToDigit(char* s);
bool CheckStr(char* s);

int Prioritet(char s);
bool IsSign(char s);
bool IsOperation(char s);
void FindVars(const char* s, int* res);
bool CheckCorrecnessOfValuesOfVars(char* s);
void InputValues(char* s, char* res);
double GetNumber(char* s);

void ConvertInPostfixNotation(const char* s, char* res);
double EvaluationOfExpression(char* s);

#endif
