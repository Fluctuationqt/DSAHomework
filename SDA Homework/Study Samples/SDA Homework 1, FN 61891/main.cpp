/*  
	#################################################################
	Subject : Expression evaluating algorithm, SDA, Homework1, Group3 
	Author  : Ivo Yakov, FN 61891, FMI Sofia.
	##################################################################
*/
#include "stdafx.h"
#include <iostream>
#include "Stack.hpp"
#include "assert.h"

enum Symbol { Operator, Operand, ClosingBracket, InvalidSymbol };
Symbol getType(const char character)
{
	if (character == 'f' || character == 'l' || character == 'm')
		return Operator;
	else if (character >= '0' && character <= '9')
		return Operand;
	else if (character == ')')
		return ClosingBracket;
	else if (character != '(' && character != ',')
		return InvalidSymbol;
}

// Returns the n-th number in the Fibonacci series
unsigned int fibonacci(int n) {
	if (n == 0 || n == 1)
		return n;
	else
		return fibonacci(n - 1) + fibonacci(n - 2);
}

// Operation method l
unsigned int l(int x) {
	return fibonacci(x) % 10;
}

// Operation method f
int f(int x)
{
	return (x * x * x) % 10;
}

// Operation method m
int m(int x, int y)
{
	return (x > y) ? x : y;
}

// This method accepts an expression string argument
// and evaluates it to a single digit positive number. 
// Expression Syntax: 
//        expr = 0~9 | f(expr) | l(expr) | m(expr)
// Where: 
//        f(x) = (x*x*x) % 10
//        l(x) = (n-th fibbonaci num) % 10,
//        m(x,y) => (x > y) ? x : y;
// The result of this evaluation is an int in the range of [0,9]
// Example: 
//        eval("m(f(0),l(0))") => 0
int eval(const char* expr)
{
	size_t length = strlen(expr);
	Stack<char> operators(length);
	Stack<unsigned char> operands(length);

	// loop through the expression one token at a time
	for (size_t i = 0; i < length; i += 1)
	{
		// get the current character and it's type 
		char current = expr[i];
		Symbol type = getType(current); 
		switch (type)
		{
			case Operator: // if it is an operator push it to the operators stack
				operators.Push(current);
				break;
			case Operand: // if it is an operand push it to the operands stack
				operands.Push(current - '0');
				break;
			case InvalidSymbol: // if it is an invalid symbol throw an exception
				throw std::exception("invalid expression symbol. Allowed characters: l m f ( ) ,");
				break;
			case ClosingBracket: // if it is a closing bracket evaluate the tops of both stacks
				{
					switch (operators.Pop()) // Pop an operator and check what it is
					{
					case 'm': // Binary operation, pop two operands evaluate them and push the result back
						operands.Push(m(operands.Pop(), operands.Pop()));
						break;
					case 'f': // Unary operation, pop one operand evaluate it and push the result back
						operands.Push(f(operands.Pop()));
						break;
					case 'l': // Unary operation, pop one operand evaluate it and push the result back
						operands.Push(l(operands.Pop()));
						break;
					}	
				}
				break;
		}
	}

	// If both stacks weren't empty at the end throw an exception. Otherwise return
	// the expression result (the last element in the opperands stack)
	int result = operands.Pop();
	if (!operands.isEmpty() || !operators.isEmpty())
		throw std::exception("invalid expression. Brackets or opperands missmatched.");
	else
		return result;
}

// Tests for the eval() method
void UnitTests()
{
	// fibonacci tests
	assert(eval("l(0)") == 0);
	assert(eval("l(1)") == 1);
	assert(eval("l(2)") == 1);
	assert(eval("l(3)") == 2);
	assert(eval("l(4)") == 3);
	assert(eval("l(5)") == 5);
	assert(eval("l(6)") == 8);
	assert(eval("l(7)") == 3);
	assert(eval("l(8)") == 1);
	assert(eval("l(9)") == 4);

	// mod 10 of x^3 tests
	assert(eval("f(0)") == 0);
	assert(eval("f(1)") == 1);
	assert(eval("f(2)") == 8);
	assert(eval("f(3)") == 7);
	assert(eval("f(9)") == 9);

	// max tests
	assert(eval("m(0,1)") == 1);
	assert(eval("m(2,3)") == 3);
	assert(eval("m(8,9)") == 9);
	assert(eval("m(0,0)") == 0);

	// nested tests
	assert(eval("m(f(0),l(0))") == 0);
	assert(eval("m(f(9),l(9))") == 9);
	assert(eval("f(l(9))") == 4);
	assert(eval("f(l(0))") == 0);
	assert(eval("l(f(9))") == 4);
	assert(eval("l(f(0))") == 0);
	assert(eval("l(f(m(f(3),l(0))))") == 2);
	assert(eval("m(m(3,4),m(0,0))") == 4);
	assert(eval("m(m(3,4),m(9,9))") == 9);
	assert(eval("m(m(4,4),m(4,4))") == 4);
	assert(eval("m(f(l(3)),f(m(2,4)))") == 8);
	assert(eval("l(m(f(l(3)),f(m(2,4))))") == 1);
	assert(eval("f(m(6,l(8)))") == 6);

	// exception tests
	int exceptionCounter = 0;
	try { eval("f(m())"); }
	catch (std::exception ex) { exceptionCounter++; }
	try { eval(")"); }
	catch (std::exception ex) { exceptionCounter++; }
	try { eval("f(m(3,))"); }
	catch (std::exception ex) { exceptionCounter++; }
	try { eval("f(m(p(l(3)),4))"); }
	catch (std::exception ex) { exceptionCounter++; }
	try { eval("))"); }
	catch (std::exception ex) { exceptionCounter++; }
	try { eval("()"); }
	catch (std::exception ex) { exceptionCounter++; }
	try { eval("f(3,4)"); }
	catch (std::exception ex) { exceptionCounter++; }
	assert(exceptionCounter == 7);
}

// Homework test example
int main() 
{
	const char* expression = "f(m(6,l(8)))";
	
	try 
	{
		std::cout << "Result: " << eval(expression) << std::endl;
	}
	catch (std::exception ex)
	{
		std::cout << "Could not compute expression, reason: " << ex.what() << std::endl;
	}
	
	// UnitTests();

	system("pause");
	return 0;
}