//Write a program that searches the root tree of subtrees that are isomorphic to the specified target tree. 
//Use the algorithm for full traversal of the tree with backtracking.

#include "SubTreeFindingProblem.h"
#include <iostream>
using namespace std;
using namespace SubTreeFindingProblem;

int main(int argc, char* argv[])
{
	SubTreeFinder subtreefinder;

	if (argc < 4 || argc>4 || argv[1] == "-h")
	{
		subtreefinder.help();
	}
	else
	{
		Node *result;
		bool success = subtreefinder.run(argv[2], sizeof(argv[2]), argv[3], sizeof(argv[3]), result);
		if (!success)
			subtreefinder.help();
		else {
			if (result)
			cout << result->num << endl;
			else cout << "not found" << endl;
		}
	}
	system("pause");
	return 0;
}