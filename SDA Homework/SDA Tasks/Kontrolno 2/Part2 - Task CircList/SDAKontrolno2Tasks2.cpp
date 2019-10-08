// SDAKontrolno2Tasks2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include "CircList.hpp"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

CList<char>* CreateCListForWord(string word)
{
	CList<char>* result = new CList<char>();
	for (int i = 0; i < word.length(); i++)
	{
		char letter = word[i];
		result->toEnd(letter);
	}
	return result;
}

bool CheckForWord(Node<char>* from, string word)
{
	int i = 0;
	while(i < word.length())
	{
		if (word[i] == from->data)
		{
			//cout << "match:" << from->data << endl;
			i++;
		}
		else
		{
			//cout << "failed to match:" << word[i] << " and " << from->data;
			return false;
		}
		from = from->next;
		
	}
	return true;
}

bool CheckForWordInCList(CList<char>* ls, string word)
{
	ls->ResetIterator();
	Node<char>* current;
	do
	{
		current = ls->Iterate();
		if (current->data == word[0])
		{
			if (CheckForWord(current, word))
				return true;
		}
	} while (current != ls->End());
	return false;
}

list<CList<char>*>* CreateSentenceMatcher(string patterns)
{
	list<CList<char>*>* sentenceMatcher = new list<CList<char>*>();
	istringstream iss(patterns);
	string pattern;
	while (iss >> pattern)
	{
		CList<char>* patternMatcher = CreateCListForWord(pattern);
		sentenceMatcher->push_back(patternMatcher);
	}
	return sentenceMatcher;
}

enum Direction { Forwards, Backwards };

void MatchSentence(list<CList<char>*>* sentenceMatcher, string sentence)
{
	cout << "Checking sentence: " << sentence << endl;
	istringstream iss(sentence);
	string word;
	auto iter = sentenceMatcher->begin();
	Direction iterDir = Forwards;
	while (iss >> word)
	{
		if (iter == sentenceMatcher->begin())
		{
			iterDir = Forwards;
		}
		if (iter == sentenceMatcher->end())
		{
			iterDir = Backwards;
			iter--;
		}

		CList<char>* wordMatcher = *iter;
		if (CheckForWordInCList(wordMatcher, word))
			cout << "matched: " << word << endl;
		else
			cout << "didnt match: " << word << endl;

		if (iterDir == Forwards)
			iter++;
		else
			iter--;
	}
}

bool MatchSentence2(list<CList<char>*>* sentenceMatcher, string sentence)
{
	cout << "Checking sentence: " << sentence << endl;
	istringstream iss(sentence);
	string word;
	auto iter = sentenceMatcher->begin();
	Direction iterDir = Forwards;
	while (iss >> word)
	{
		if (iter == sentenceMatcher->begin())
		{
			iterDir = Forwards;
		}
		if (iter == sentenceMatcher->end())
		{
			iterDir = Backwards;
			iter--;
		}

		CList<char>* wordMatcher = *iter;
		if (!CheckForWordInCList(wordMatcher, word))
			return false;

		if (iterDir == Forwards)
			iter++;
		else
			iter--;
	}
	return true;
}

void Example1()
{
	list<CList<char>*>* sentenceMatcher = CreateSentenceMatcher("card ab letterman");
	string sentence = "card ab manr letter baba dcard a manlet dog";
	MatchSentence(sentenceMatcher, sentence);
	cout << endl;
}

void Example2()
{
	list<CList<char>*>* sentenceMatcher = CreateSentenceMatcher("card ab letterman");
	string sentence = "card ab man letter baba dcard a manlet";
	if (MatchSentence2(sentenceMatcher, sentence))
		cout << "Sentence Matched" << endl;
	else
		cout << "Sentence didn't match" << endl;
}

int main()
{	
	//Example1();
	//Example2();
	
    return 0;
}

