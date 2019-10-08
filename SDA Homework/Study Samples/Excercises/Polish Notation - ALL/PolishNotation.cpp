// PolishNotation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LStack.hpp"
#include "LQueue.hpp"
#include <string>
#include <iostream>

// Is char a single digit number?
bool isDigit(char ch)
{
	if (ch <= '9' && ch >= '0')
		return true;
	else
		return false;
}

// Convert char, that is a digit to integer single digit number
int parseDigit(char ch)
{
	if (ch <= '9' && ch >= '0')
		return ch - '0';
}

// Is char an accepted operator (One of: +-/*) ? 
bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	else
		return false;
}

/* 
	Evaluates a postfix notation expression.
	
	Limitation: Only single digit whole numbers
	allowed in the postfix notation expression!
	
	Example expresion: "123+-7/"			
*/
double EvaluatePostfixNotation(std::string postfixExpr)
{
	LStack<double> operands;
	
	for (int i = 0; i < postfixExpr.length(); i++)
	{
		char current = postfixExpr[i];
		
		if (isDigit(current))
		{
			operands.Push(parseDigit(current));
		}
		else
		{
			double a, b;
			switch (current)
			{
				case '+':
				{
					a = operands.Pop();
					b = operands.Pop();
					operands.Push(a + b);
				} break;

				case '-':
				{
					a = operands.Pop();
					b = operands.Pop();
					operands.Push(b - a);
				} break;

				case '*':
				{
					a = operands.Pop();
					b = operands.Pop();
					operands.Push(a * b);
				} break;

				case '/':
				{
					a = operands.Pop();
					b = operands.Pop();
					operands.Push(b / a);
				} break;
			}
		}
	}
	double result = operands.Pop();
	return result;
}

/*
	Evaluates a prefix notation expression.

	Limitation: Only single digit whole numbers
	allowed in the prefix notation expression!

	Example expresion: "123+-7/"
*/
double EvaluatePrefixNotation(std::string prefixExpr)
{
	LStack<double> operands;
	
	for (int i = prefixExpr.length(); i >= 0; i--)
	{
		char current = prefixExpr[i];

		if (isDigit(current))
		{
			operands.Push(parseDigit(current));
		}
		else
		{
			double a, b;
			switch (current)
			{
			case '+':
			{
				a = operands.Pop();
				b = operands.Pop();
				operands.Push(a + b);
			} break;

			case '-':
			{
				a = operands.Pop();
				b = operands.Pop();
				operands.Push(b - a);
			} break;

			case '*':
			{
				a = operands.Pop();
				b = operands.Pop();
				operands.Push(a * b);
			} break;

			case '/':
			{
				a = operands.Pop();
				b = operands.Pop();
				operands.Push(b / a);
			} break;
			}
		}
	}
	double result = operands.Pop();
	return result;
}

/*
	Parses string with single digit whole numbers in prefix notation
	to equivalent postfix notation.
*/
std::string PrefixToPostfix(std::string prefixExpr)
{
	LStack<std::string> st;
	for(int i = prefixExpr.length(); i >= 0; i--)
	{
		char current = prefixExpr[i];
		if (isDigit(current))
		{
			st.Push(std::string(1, current));
		}
		else if(isOperator(current))
		{
			std::string a = st.Pop();
			std::string b = st.Pop();
			std::string op = std::string(1, current);
			st.Push(a + b + op);
		}
	}
	return st.Pop();
}

/*
	Parses string with single digit whole numbers in postfix notation
	to equivalent prefix notation. 
*/
std::string PostfixToPrefix(std::string postfixExpr)
{
	LStack<std::string> st;
	for (int i = 0; i < postfixExpr.length(); i++)
	{
		char current = postfixExpr[i];
		if (isDigit(current))
		{
			st.Push(std::string(1, current));
		}
		else if (isOperator(current))
		{
			std::string a = st.Pop();
			std::string b = st.Pop();
			std::string op = std::string(1, current);
			st.Push(a + b + op);
		}
	}
	std::string result = st.Pop();
	std::reverse(result.begin(), result.end());
	return result;
}


// THE FOLLOWING 3 Don't work
int getWeight(char x)
{
	switch (x)
	{
		case '+': return 2;
		case '-': return 2;
		case '*': return 1;
		case '/': return 1;
		case '^': return 0;
	}
}
void print(LStack<char> st)
{
	while (!st.isEmpty())
	{
		std::cout<< st.Pop()<< " ";
	}
	std::cout << std::endl;
}
//does not work fully
std::string InfixToPostfix(char *source)
{

	LQueue<char> result;
	//стек, в който ще се пазят само операторите (+,-,*,/,^) и скоби
	LStack<char> st;
	//добавя се елемент в началото на стека, за да се улесни работата с него по-нататък
	st.Push('(');

	//допълнителни променливи, temp се инициализира, тъй като 
	//ще се използва в pop, където се подава параметър по псевдоним
	char ch, temp = 'a';

	for (int i = 0; i < strlen(source); i++)
	{
		ch = source[i];

		//цифрите се пращат направо в резултата без да се променя тяхната поредност. Ако 
		//в израза имахме променливи (a, b, c ...) те също щяха да се включат в този случай
		if (isDigit(ch))
		{
			result.push(ch);
		}
		else if (ch == '(')
		{
			st.Push(ch);
		}
		else if (ch == ')')
		{
			while (temp != '(')
			{
				temp = st.Pop();
				result.push(temp);
			}
		}
		else if (isOperator(ch))
		{
			while (temp != '(' && getWeight(ch) >= getWeight(temp))
			{
				temp = st.Pop();
				result.push(temp);
			}
			//връщане на последния оператор от стека обратно в него, в случай, че той е бил по-тежък от текущо разглеждания
			st.Push(temp);
			//отделно добавяме и текущо разглеждания оператор в стека
			st.Push(ch);
		}
	}

	//след обработка на целия израз трябва да се погрижим останалите в стека оператори да се добавят към резултата
	while (!st.isEmpty())
	{
		temp = st.Pop();
		if(temp != '(' && temp != 'a')
			result.push(temp);
	}
	
	// convert result queue to string
	std::string output = "";
	while (result.pop(ch))
		output.push_back(ch);
	return output;
}

// Some examples...
int main()
{
	std::string Postfix_expr = "45+3*7-";
	double result = EvaluatePostfixNotation(Postfix_expr);
	std::cout << Postfix_expr << " is equal to " << result << std::endl;
    
	std::string Prefix_expr = "*+123";
	Postfix_expr = PrefixToPostfix(Prefix_expr);
	std::cout << Prefix_expr << " converted to postfix is: " << Postfix_expr << std::endl;

	std::cout << "and back again to prefix:"<< PostfixToPrefix(Postfix_expr) << std::endl;
	std::cout << Prefix_expr << " is equal to " << EvaluatePrefixNotation(Prefix_expr) << std::endl;
	std::cout << PrefixToPostfix(Prefix_expr) << " is equal to " << EvaluatePostfixNotation(PrefixToPostfix(Prefix_expr)) << std::endl;
	
	std::cout << "this:" << InfixToPostfix("(1+2)-3")<<std::endl;
	
	return 0;
}

