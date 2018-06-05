#pragma once

#define NULL_CHAR '\\'

#include <map>
#include	 <vector>
#include <iostream>
#include <set>

class BastSet {
	friend class FollowSet;
	friend class FirstSet;
	friend class SelectSet;
public:
	BastSet(std::istream &);
	~BastSet();
	std::multimap<char, std::vector<char>> get_gramar_rule() const {
		return gramar_rule;
	}
	char get_start() const { return start; }
	
private:
	void build_null_not_end();
	bool had_end(std::vector<char>);	
	void print_gramar_rule(std::multimap<char, std::vector<char>>) const;
	void print_vector_char(std::vector<char> &vc) const;

	std::multimap<char, std::vector<char>> gramar_rule;
	std::set<char> not_end, null_not_end, end_char, all_char;
	char start;
};

