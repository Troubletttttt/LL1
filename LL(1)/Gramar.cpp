#include "Gramar.h"

#include <string>
#include <sstream>

using namespace std;

Gramar::Gramar(istream &is) {
	string text;
	string right;
	

	while (getline(is, text)) {
		stringstream line(text);
		Sentence sentence;
		line >> sentence.first;
		line >> right;

		if (right != "null") {
			sentence.rule.resize(right.size());
			sentence.rule.assign(right.begin(), right.end());
		}

	}
}


Gramar::~Gramar() {
}
