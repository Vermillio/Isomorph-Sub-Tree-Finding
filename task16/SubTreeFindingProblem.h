#pragma once
#include <vector>

using namespace std;

namespace SubTreeFindingProblem {
	
	struct Node
	{
		int num;
		vector<Node*> children;
		Node() {};
		Node(int val) : num(val) {};
	};

	class Tree
	{
		int nodeNum;

		Node *root;

		//void print(ostream &c, Node *t, int level);

	public:

		void genRand(int sz);
		int size() const;
		Node *getRoot() const;
		void writeGvFile(string treename);
		bool readFile(char * filename);
		Tree();
		~Tree();
	};


	class SubTreeFinder
	{
		Node *findProc(Node *what, Node *where);
		Node* areIdentic(Node * N, Node * H);
	public:
		Node* findSubtree(Tree needle, Tree haystack);
		void test();
		void help();
		bool run(char * _what, int sz1, char * _where, int sz2, Node *& result);
	};
}


