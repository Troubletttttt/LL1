#include "BastSet.h"

#include <sstream>

using namespace std;

BastSet::BastSet(istream &is) {
	string line;
	char left;
	string right;	

	while (getline(is, line)) {
		stringstream ss(line);
		ss >> left >> right;

		vector<char> x;
		if (right != "null") {
			x.resize(right.size());
			x.assign(right.begin(), right.end());
		}

		for (auto c = x.begin(); c != x.end(); c++) {
			all_char.insert(*c);
		}

		gramar_rule.insert(pair<char, vector<char>>(left, x));		
		if (not_end.empty()) {
			start = left;
		}
		not_end.insert(left);
	}
	//print_gramar_rule(gramar_rule);
	build_null_not_end();
	for (auto i = all_char.begin(); i != all_char.end(); i++) {
		if (not_end.find(*i) == not_end.end()) {
			end_char.insert(*i);
		}
	}
}

bool BastSet::had_end(vector<char> vc) {
	//是否含有终结符
	for (auto i = vc.begin(); i != vc.end(); ++i) {
		if (not_end.find(*i) == not_end.end()) {
			//符号不是非终结符，也就是说是终结符
			return true;
		}
	}
	return false;
}
void BastSet::build_null_not_end() {
	map<char, int> state;
	//初始化
	for (auto t = not_end.begin(); t != not_end.end(); ++t) {
		state[*t] = 0;
	}
	//将可以直接推导出null的非终结符置1，并去除含有终结符的文法
	multimap<char, vector<char>> temp_rule;
	for (auto t = gramar_rule.begin(); t != gramar_rule.end(); ++t) {
		vector<char> x = (*t).second;
		if (x.size() == 0) {
			state[(*t).first] = 1;
		} else if (!had_end(x)) {
			//不含有终结符
			temp_rule.insert(*t);
		}		
	}
	for (auto t = not_end.begin(); t != not_end.end(); ++t) {
		//将每个没有表达式的非终结符设置为-1
		if (state[*t] == 0 && temp_rule.find(*t) == temp_rule.end()) {
			state[*t] = -1;
		}
	}

	//cout << endl;
	//print_gramar_rule(temp_rule);
	bool flage = true;
	while (flage) {		
		//(4)直到非终结符的特征没有没变，退出循环
		flage = false;

		//(3)扫描产生式右部的每一符号，
		auto it = temp_rule.begin();
		while (it != temp_rule.end()) {
			auto it_c = (*it).second.begin();
			while (it_c != (*it).second.end()) {
				//若所扫描到的非终结符在标志位1，则删去该非终结符
				if (state[*it_c] == 1) {
					flage = true;
					it_c = (*it).second.erase(it_c);
				} else if (state[*it_c] == -1) {
					//若所扫描到的非终结符标志位为-1，则删去该产生式
					flage = true;
					char x = (*it).first;
					it = temp_rule.erase(it) ;
					//若产生式的左部的非终结符的有关产生式都被删除
					//则吧数组中非终结符的特征改为-1
					if (temp_rule.find(x) == temp_rule.end()) {
						state[x] = -1;
					}
					if (it == temp_rule.end()) {
						;
					} else {
						--it;
					}
					break;
				}else {
					++it_c;
				}				
			}
			//若产生式的右部为空，则标志位改为1，并删除该产生式
			if (it != temp_rule.end() && (*it).second.size() == 0) {
				state[(*it).first] = 1;
				char index = (*it).first;
				auto erase_it = temp_rule.find(index);
				while (erase_it != temp_rule.end() && 
					(*erase_it).first == index) {
					erase_it = temp_rule.erase(erase_it);
				}
				it = erase_it;
			} else if(it != temp_rule.end()) {
				++it;
			}
			
		}	

	}
	//将可推导出空的插入set中
	for (auto i = state.begin(); i != state.end(); ++i) {
		if ((*i).second == 1) {
			null_not_end.insert((*i).first);
		}
		//cout << (*i).first << " " << (*i).second << endl;
	}

}
void BastSet::print_gramar_rule(multimap<char, vector<char>> rule) const {
	for (auto i = rule.begin(); i != rule.end(); ++i) {
		cout << (*i).first << '\t';
		for (auto j = (*i).second.begin(); 
			j != (*i).second.end(); ++j) {
			cout << (*j) << " ";
		}
		cout << endl;
	}
}
void BastSet::print_vector_char(vector<char> &vc) const {
	if (vc.size() == 0) {
		cout << "null";
		return;
	}
	for (size_t i = 0; i < vc.size(); i++) {
		cout << vc[i];
	}
}

BastSet::~BastSet() {
}
