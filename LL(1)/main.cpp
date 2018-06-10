#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#include "BastSet.h"
#include "SymbolSet.h"
#include "SelectSet.h"

using namespace std;

int main() {

	string dir = "C:\\Users\\muzha\\source\\repos\\LL(1)\\";
	ifstream fin(dir + "testLL1.txt");
	ofstream save_first(dir + "LL1_first.txt");

	BastSet bs(fin);
	FirstSet fs(bs, "FIRST");
	FollowSet follow(bs, fs, "FOLLOW");
	cout << fs << endl;
	cout << follow << endl; 
	/*cout << fs << endl;
	save_first << fs;
	cout << bs.get_start() << endl;*/
	SelectSet select_set = SelectSet(fs, follow, bs);
	cout << select_set << endl;

	cout << "预测分析表：" << endl;
	select_set.print_pre(cout);

	/*vector<char> vc = select_set.find('A', '#');
	string s(vc.begin(), vc.end());
	cout << s << endl;*/

	string text;
	stack<char> anaysis_stack;	

	cin >> text;
	//把起始符号入栈
	anaysis_stack.push('#');
	anaysis_stack.push(bs.get_start());

	cout << "步骤" << "\t" << "栈顶" << '\t'
		<< "栈大小" << '\t' << "剩余输入串" << endl;;

	char c;
	int pos = 0, step = 0;
	while (!anaysis_stack.empty()) {
		c = anaysis_stack.top();
		anaysis_stack.pop();

		if (c == text[pos]) {
			pos++;
		} else {
			vector<char> next = select_set.find(c, text[pos]);
			if (next.empty()) {
				cout << "error" << endl;
				return - 1;
			} else if (next.size() == 1 && next[0] == NULL_CHAR) {
				;
			} else {
				for (auto i = next.rbegin(); i != next.rend(); i++) {
					anaysis_stack.push(*i);
				}
			}
		}
		
		if (!anaysis_stack.empty()) {
			cout << step << "\t" << anaysis_stack.top() << '\t'
				<< anaysis_stack.size() << '\t';
		} else {
			cout << step << "\t" << "empty"
				<< '\t';
		}
		
		for (auto j = pos; j < text.size(); j++) {
			cout << text[j];
		}
		cout << endl;
		step++;
		
	}
	cout << "语法正确" << endl;

	system("pause");

	return 0;
}