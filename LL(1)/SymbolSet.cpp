#include "SymbolSet.h"

using namespace std;

SymbolSet::~SymbolSet() {
}

FirstSet::FirstSet(const BastSet &bs, string str) : SymbolSet(str){
	//bs.print_gramar_rule(bs.gramar_rule);

	//��ʼ��firs��
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
					//���Ƿ��ս�������Ҳ����Ƶ������ַ�
					break;
				}
			}
		}
		
	}

	bool flage = true;
	while (flage) {
		//����data��first��û���ٷ����仯Ϊֹ
		flage = false;
		for (auto i = data.begin(); i != data.end(); i++) {
			for (auto j = i->second.begin(); j != i->second.end();) {
				if (bs.not_end.find(*j) != bs.not_end.end()) {
					flage = true;
					//���ս��					
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
	//��ʼ��follow��
	for (auto i = bs.gramar_rule.begin(); i != bs.gramar_rule.end(); i++) {
		for (auto j = i->second.begin(); j != i->second.end(); j++) {
			if (bs.not_end.find(*j) != bs.not_end.end()) {
				//���ս��
				if (j + 1 == i->second.end()) {
					if (*j != i->first)	data[*j].insert(i->first);
				} else {
					char c = *(j + 1);
					if (bs.not_end.find(c) == bs.not_end.end()) {
						//�ս����ֱ�Ӳ���
						data[*j].insert(c);
					} else {
						//���ս������First�����룬���ж��Ƿ�Ϊ��
						for (auto k = fs.data.find(c)->second.begin();
							k != fs.data.find(c)->second.end(); k++) {
							if(*k != NULL_CHAR) data[*j].insert(*k);
						}
						if (bs.null_not_end.find(c) != bs.null_not_end.end()) {
							//�����Ƶ�����
							if(*j != i->first)	data[*j].insert(i->first);
						}
					}
				}
			}
		}
	}
	//cout << *this << endl;
	

	//��ε�����ֱ�����ٲ������Ϊֹ
	bool flage = true;
	while (flage) {
		flage = false;
		//��Follow���еķ��ս����Follow�еķ��Ų��뵽����ķ��ż���
		for (auto i = data.begin(); i != data.end(); i++) {
			for (auto j = i->second.begin(); j != i->second.end();) {
				if (bs.not_end.find(*j) != bs.not_end.end()) {
					flage = true;
					//���ս��
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
