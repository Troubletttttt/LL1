#include <iostream>
#include <fstream>
#include <string>

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

	vector<char> vc = select_set.find('A', '#');
	string s(vc.begin(), vc.end());
	cout << s << endl;

	system("pause");

	return 0;
}