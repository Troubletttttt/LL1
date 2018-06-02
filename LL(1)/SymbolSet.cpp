#include "SymbolSet.h"

using namespace std;

SymbolSet::~SymbolSet() {
}

FirstSet::FirstSet(const BastSet &bs, string str) : SymbolSet(str){
	//bs.print_gramar_rule(bs.gramar_rule);

	//初始化firs集
	for (auto i = bs.not_end.begin(); i != bs.not_end.end(); ++i) {
		auto t = bs.gramar_rule.find(*i);
		data.insert(pair<char, set<char>>(*i, set<char>()));

		rsize_t count = bs.gramar_rule.count(*i);
		//cout << t->first  << " " << count << ":" << endl;
		for (size_t c = 0; c < count; c++, ++t) {
			auto g = t->second;
			if (g.size() == 0) {
				data[*i].insert(NULL_CHAR);
				break;
			}
			for (size_t j = 0; j < g.size(); j++) {
				data[*i].insert(g[j]);
				if (bs.null_not_end.find(g[j]) == bs.null_not_end.end() ||
					bs.not_end.find(g[j]) == bs.not_end.end()) {
					//不是非终结符，并且不能推导出空字符
					break;
				}
			}
		}
		
	}

	bool flage = true;
	while (flage) {
		//遍历data，first集没有再发生变化为止
		flage = false;
		for (auto i = data.begin(); i != data.end(); i++) {
			for (auto j = i->second.begin(); j != i->second.end();) {
				if (bs.not_end.find(*j) != bs.not_end.end()) {
					flage = true;
					//非终结符					
					insert_symbols(*j, i->first);
					j =  (i->second.erase(j));					
				} else {
					++j;
				}
			}
		}
	}
}
void FirstSet::insert_symbols(char from, char to) {
	for (auto i = data[from].begin(); i != data[from].end(); i++) {
		data[to].insert(*i);
	}
}

FollowSet::FollowSet(const BastSet &bs, const FirstSet &fs,
	const string s) : SymbolSet(s) {

	data[bs.start].insert('#');

	//bs.print_gramar_rule(bs.gramar_rule);
	//初始化follow集
	for (auto i = bs.gramar_rule.begin(); i != bs.gramar_rule.end(); i++) {
		for (auto j = i->second.begin(); j != i->second.end(); j++) {
			if (bs.not_end.find(*j) != bs.not_end.end()) {
				//非终结符
				if (j + 1 == i->second.end()) {
					if (*j != i->first)	data[*j].insert(i->first);
				} else {
					char c = *(j + 1);
					if (bs.not_end.find(c) == bs.not_end.end()) {
						//终结符，直接插入
						data[*j].insert(c);
					} else {
						//非终结符，将First集插入，再判断是否为空
						for (auto k = fs.data.find(c)->second.begin();
							k != fs.data.find(c)->second.end(); k++) {
							if(*k != NULL_CHAR) data[*j].insert(*k);
						}
						if (bs.null_not_end.find(c) != bs.null_not_end.end()) {
							//可以推导出空
							if(*j != i->first)	data[*j].insert(i->first);
						}
					}
				}
			}
		}
	}
	//cout << *this << endl;
	

	//多次迭代，直到不再插入符号为止
	bool flage = true;
	while (flage) {
		flage = false;
		//将Follow集中的非终结符的Follow中的符号插入到本身的符号集中
		for (auto i = data.begin(); i != data.end(); i++) {
			for (auto j = i->second.begin(); j != i->second.end();) {
				if (bs.not_end.find(*j) != bs.not_end.end()) {
					flage = true;
					//非终结符
					for (auto k = data[*j].begin(); k != data[*j].end(); k++) {
						if(*k != i->first)	data[i->first].insert(*k);
					}
					
					j = i->second.erase(j);
				} else {
					j++;
				}
			}
		}

	}
	
	//cout << *this << endl;

}

ostream & operator<<(ostream &os, const SymbolSet &ss) {
	for (auto i = ss.data.begin(); i != ss.data.end(); i++) {
		os << ss.name << "(" <<  i->first << ")  =  { ";
		for (auto j = i->second.begin(); j != i->second.end(); j++) {
			os << *j << " ";
		}
		os << "}" << endl;
	}
	return os;
}
