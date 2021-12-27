// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <arithmetic.h>

TEST(Arithmetic, can_identify_type)
{
	int types[6];
	char str[] = "1.2*x ";
	for (int i = 0; i < 6; i++)
		types[i] = DeterminationType(str[i]);
	EXPECT_EQ(1, types[0]);
	EXPECT_EQ(4, types[1]);
	EXPECT_EQ(1, types[2]);
	EXPECT_EQ(3, types[3]);
	EXPECT_EQ(2, types[4]);
	EXPECT_EQ(5, types[5]);
}

TEST(Arithmetic, can_check_brackets)
{
	char str[] = "(1.2+b)*x";
	EXPECT_TRUE(CheckBrackets(str));
}

TEST(Arithmetic, can_check_amout_of_operands)
{
	char str[] = "1+";
	EXPECT_TRUE(!CheckAmountOperands(str));
}

TEST(Arithmetic, can_check_operations_in_row)
{
	char str[] = "1+*x+y";
	EXPECT_TRUE(!CheckOperationsInRow(str));
}

TEST(Arithmetic, can_check_place_dots_or_commas)
{
	char str[] = "1.2+x-2";
	EXPECT_TRUE(CheckPlaceDotsOrCommas(str));
}

TEST(Arithmetic, can_check_correctness_of_symbols)
{
	char str[] = "1+2&x*y";
	EXPECT_TRUE(!CheckCorrectnessOfSymbols(str));
}
TEST(Arithmetic, can_check_amount_of_letters_in_vars)
{
	char str[] = "1+xy";
	EXPECT_TRUE(!CheckAmountLettersaInVars(str));
}
TEST(Arithmetic, can_check_str_at_all)
{
	char str[] = "(1+2&x*yz*";
	EXPECT_TRUE(!CheckStr(str));
}

TEST(Arithmetic, can_identify_prioritet)
{
	int pr;
	char str[] = "1.2*x";
	pr = Prioritet(str[3]);
	EXPECT_EQ(2, pr);
}

TEST(Arithmetic, can_identify_sign)
{
	char str[] = "(1.2*x)+3";
	EXPECT_TRUE(IsSign(str[0]));
}

TEST(Arithmetic, can_identify_operation)
{
	char str[] = "(1.2*x)+3";
	EXPECT_TRUE(IsOperation(str[4]));
}

TEST(Arithmetic, can_identify_unary_minus)
{
	char str[] = "(-1.2*x)+3";
	EXPECT_TRUE(ThereIsUnaryMinus(str));
}

TEST(Arithmetic, can_process_unary_minus_at_the_beginning)
{
	char str[] = "-5*x";
	char newstr[256];
	ProcessingUnaryMinus(str, newstr);
	EXPECT_EQ('0', newstr[0]);
	EXPECT_EQ('-', newstr[1]);
	EXPECT_EQ('5', newstr[2]);
	EXPECT_EQ('*', newstr[3]);
	EXPECT_EQ('x', newstr[4]);
}

TEST(Arithmetic, can_process_unary_minus_after_open_bracket)
{
	char str[] = "1+(-2)";
	char newstr[256];
	ProcessingUnaryMinus(str, newstr);
	EXPECT_EQ('1', newstr[0]);
	EXPECT_EQ('+', newstr[1]);
	EXPECT_EQ('(', newstr[2]);
	EXPECT_EQ('0', newstr[3]);
	EXPECT_EQ('-', newstr[4]);
	EXPECT_EQ('2', newstr[5]);
	EXPECT_EQ(')', newstr[6]);
}

TEST(Arithmetic, can_get_number)
{
	char str[] = "5.5";
	EXPECT_EQ(5.5, GetNumber(str));
}

TEST(Arithmetic, can_find_vars)
{
	char str[] = "6.5+x*(y+z)";
	int res[4];
	for (int i = 0; i < 4; i++)
		res[i] = -1;
	FindVars(str, res);
	EXPECT_EQ(4, res[0]);
	EXPECT_EQ(7, res[1]);
	EXPECT_EQ(9, res[2]);
	EXPECT_EQ(-1, res[3]);
}

TEST(Arithmetic, can_convert_in_postfix_notation)
{
	char str[] = "6.5+x";
	char newstr[15];
	ConvertInPostfixNotation(str, newstr);
	EXPECT_EQ('6', newstr[0]);
	EXPECT_EQ('.', newstr[1]);
	EXPECT_EQ('5', newstr[2]);
	EXPECT_EQ(' ', newstr[3]);
	EXPECT_EQ('x', newstr[4]);
	EXPECT_EQ(' ', newstr[5]);
	EXPECT_EQ('+', newstr[6]);
}

TEST(Arithmetic, can_add_values)
{
	char str[] = "1.5+3";
	double res;
	char newstr[15];
	ConvertInPostfixNotation(str, newstr);
	res = EvaluationOfExpression(newstr);
	EXPECT_EQ(4.5, res);
}
TEST(Arithmetic, can_subtract_values)
{
	char str[] = "6.5-5";
	double res;
	char newstr[15];
	ConvertInPostfixNotation(str, newstr);
	res = EvaluationOfExpression(newstr);
	EXPECT_EQ(1.5, res);
}
TEST(Arithmetic, can_multiply_values)
{
	char str[] = "5.5*2";
	double res;
	char newstr[15];
	ConvertInPostfixNotation(str, newstr);
	res = EvaluationOfExpression(newstr);
	EXPECT_EQ(11, res);
}
TEST(Arithmetic, can_divide_values)
{
	char str[] = "11/2";
	double res;
	char newstr[15];
	ConvertInPostfixNotation(str, newstr);
	res = EvaluationOfExpression(newstr);
	EXPECT_EQ(5.5, res);
}
TEST(Arithmetic, can_involute_values)
{
	char str[] = "2^5";
	double res;
	char newstr[15];
	ConvertInPostfixNotation(str, newstr);
	res = EvaluationOfExpression(newstr);
	EXPECT_EQ(32, res);
}

TEST(Arithmetic, can_calculate_expression_with_brackets)
{
	char str[] = "(5+2*7)*3-21";
	double res;
	char newstr[50];
	ConvertInPostfixNotation(str, newstr);
	res = EvaluationOfExpression(newstr);
	EXPECT_EQ(36, res);
}
TEST(Arithmetic, can_calculate_expression_without_brackets)
{
	char str[] = "5+2*7*3-21";
	double res;
	char newstr[50];
	ConvertInPostfixNotation(str, newstr);
	res = EvaluationOfExpression(newstr);
	EXPECT_EQ(26, res);
}
TEST(Arithmetic, can_replacement_point_to_comma)
{
	char str[] = "5,2";
	ReplacementPointToCommaInDouble(str);
	EXPECT_EQ('.', str[1]);
}
