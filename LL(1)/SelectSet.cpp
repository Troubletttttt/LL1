#include "SelectSet.h"

using namespace std;

SelectSet::SelectSet(const FirstSet &first, const FollowSet &follow, BastSet &bs) :
	select_data() {
	for (auto i = bs.gramar_rule.begin(); i != bs.gramar_rule.end(); i++) {
		set<char> s;
		
		for (auto j = i->second.begin(); j != i->second.end(); ++j) {
			add_char_set(s, first, *j);
		}

		if (can_to_empty(i->second, bs)) {
			//推导出空表达式
			add_char_set(s, follow, i->first);
			s.erase(NULL_CHAR);			
		}

		for (auto k = s.begin(); k != s.end(); k++) {
			cout << *k << " ";
		}
		
		pair<decltype(i), set<char>>p(i, s) ;
		select_data.insert(p);
	}
}

bool SelectSet::can_to_empty(const vector<char> &vc, BastSet &bs) {
	for (auto i = vc.begin(); i != vc.end(); i++) {
		if (*i == NULL_CHAR || 
			bs.null_not_end.find(*i) == bs.null_not_end.end()) {
			return false;
		}
	}
	return true;
}
void SelectSet::add_char_set(set<char> &s, const SymbolSet &from, char c) {
	auto b = from.data.find(c)->second.begin();
	auto e = from.data.find(c)->second.end();
	s.insert(b, e);
}

SelectSet::~SelectSet() {
}
