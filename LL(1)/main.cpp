#include <iostream>
#include <fstream>
#include <string>

#include "BastSet.h"
#include "SymbolSet.h"

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

	

	system("pause");

	return 0;
}