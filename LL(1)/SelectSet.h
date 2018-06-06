#pragma once

#include <vector>
#include <set>
#include <map>
#include <string>

#include "BastSet.h"
#include "SymbolSet.h"

class SelectSet {
	friend std::ostream& operator<<(std::ostream &, const SelectSet &);
public:
	SelectSet(const FirstSet &, const FollowSet &, BastSet &);
	~SelectSet();

	std::vector<char> find(const char ne, const char ec) const {
		std::pair<const char, const char> p(ne, ec);
		return predict_anaysis_table.find(p)->second;
	}
private:	
	std::map<std::pair<const char, std::vector<char>>, 
		std::set<char>> select_data;
	std::map<std::pair<const char, const char>,
		std::vector<char>> predict_anaysis_table;
	
	bool can_to_empty(const std::vector<char> &, BastSet &);	
	
};
std::ostream& operator<<(std::ostream &, const SelectSet &);


