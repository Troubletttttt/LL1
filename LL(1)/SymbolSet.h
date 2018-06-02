#pragma once

#include <map>
#include <set>
#include <iostream>
#include <string>

#include "BastSet.h"

class FirstSet;
class FollowSet;

class SymbolSet {
	friend std::ostream & operator<<(std::ostream &, const SymbolSet &);
public:
	SymbolSet(const std::string str) : name(str) {}
	~SymbolSet();
protected:
	std::map<char, std::set<char>> data;
	std::string name;
};
class FirstSet : public SymbolSet {
	friend class FollowSet;
	//friend std::ostream & operator<<(std::ostream &, const SymbolSet &);
public:
	FirstSet(const BastSet &, const std::string );
	FirstSet(std::istream &is, const std::string str) :
		FirstSet(BastSet(is), str) {}
private:
	void insert_symbols(char from, char to);
};
class FollowSet : public SymbolSet {
public:
	FollowSet(const BastSet &, const FirstSet &, const std::string);
};

std::ostream & operator<<(std::ostream &, const SymbolSet &);

