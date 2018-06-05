#pragma once

#include <vector>
#include <string>
#include <iostream>

class Sentence;
class Gramar {
public:
	Gramar(std::istream &);
	~Gramar();
private:
	std::vector<Sentence> sentences;
	std::vector<char> not_end;
};
class Sentence {
	friend class Gramar;
public:
	Sentence() : rule(vector<char>()){}
private:
	char first;
	std::vector<char> rule;
};

