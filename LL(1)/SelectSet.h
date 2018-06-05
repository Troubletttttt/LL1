#pragma once

#include <vector>
#include <set>
#include <map>
#include <memory>
#include <unordered_map>

#include "BastSet.h"
#include "SymbolSet.h"

class SelectSet {
public:
	SelectSet(const FirstSet &, const FollowSet &, BastSet &);
	~SelectSet();
private:	
	std::unordered_map<const std::multimap<char, std::vector<char> >::iterator,
		std::set<char>> select_data;
	
	bool can_to_empty(const std::vector<char> &, BastSet &);
	void add_char_set(std::set<char> &s, const SymbolSet &, char c);
};

