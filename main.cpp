#include <iostream>
#include "HuffmanTree.h"
using namespace std;

int main() {
	HuffmanTree hTree;

	string s = "abcd";
	vector<int> freq = { 1, 4, 10, 15 };

	hTree.buildTree(s, freq);
	hTree.printCodes();
	cout << endl;

	hTree.addCharacter('e', 20);
	hTree.printCodes();
	cout << endl;

	hTree.removeCharacter('a');
	hTree.printCodes();

	return 0;
}