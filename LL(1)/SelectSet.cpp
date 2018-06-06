#include "SelectSet.h"

using namespace std;

SelectSet::SelectSet(const FirstSet &first, const FollowSet &follow, BastSet &bs) :
	select_data() {	

	for (auto i = bs.gramar_rule.begin(); i != bs.gramar_rule.end(); i++) {
		set<char> s;

		pair<const char, vector<char>> sentence(i->first, i->second);
		
		for (auto j = i->second.begin(); j != i->second.end(); ++j) {
			if (bs.not_end.find(*j) == bs.not_end.end()) {
				s.insert(*j);
				break;
			} else {				
				s.insert(first.data.find(*j)->second.begin(),
					first.data.find(*j)->second.end());
				if (bs.null_not_end.find(*j) == bs.null_not_end.end()) {
					break;
				}
			}
			
		}
		if (can_to_empty(i->second, bs)) {
			s.insert(follow.data.find(i->first)->second.begin(),
				follow.data.find(i->first)->second.end());
		}

		s.erase(NULL_CHAR);			

		select_data.insert(pair<pair<const char, vector<char>>,
			set<char>>(sentence, s));
		//构建预测分析表
		for (auto c = s.begin(); c != s.end(); c++) {
			if (sentence.second.empty()) {
				sentence.second.push_back(NULL_CHAR);
			}
			predict_anaysis_table.insert(pair<pair<const char, const char>,
				vector<char>>(pair<const char, const char>(i->first, *c),
					sentence.second));			
		}
	}
	/*for (auto i = select_data.begin(); i != select_data.end(); i++) {
		pair <const char, vector<char>> sen = i->first;
		cout << sen.first << " ";
	}*/
	//for (auto i = predict_anaysis_table.begin();
	//	i != predict_anaysis_table.end(); i++) {
	//	cout << i->first.first << " " << i->first.second << " ";
	//	string s(i->second.begin(), i->second.end());
	//	cout << s << endl;	
	//	/*if (s.empty()) {
	//		cout << NULL_CHAR << endl;	
	//	} else {
	//		cout << s << endl;
	//	}*/
	//	
	//}
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

ostream& operator<<(ostream &os, const SelectSet &s) {
	for (auto i = s.select_data.begin(); i != s.select_data.end(); i++) {
		os << "SELECT( ";
		os << i->first.first << " -> ";
		for (auto j = i->first.second.begin(); j != i->first.second.end(); j++) {
			os << *j;
		}
		os << " )";

		os << " = { ";

		for (auto j = i->second.begin();  j != i->second.end(); j++) {
			os << *j << " ";
		}

		os << "}" << endl;	;
	}
	return os;
}

SelectSet::~SelectSet() {
}
