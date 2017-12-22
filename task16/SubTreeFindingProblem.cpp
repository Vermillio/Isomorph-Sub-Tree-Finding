#include "SubTreeFindingProblem.h"
#include <fstream>
#include <iostream>
#include <Queue>
#include <ctime>

using namespace std;
using namespace SubTreeFindingProblem;




void Tree::genRand(int size)
{
	srand(clock());
	nodeNum = size;
	vector<Node*> tree(size);
	tree[0] = new Node(0);
	for (int i = 1; i < size; ++i)
	{
		tree[i] = new Node(i);
		tree[rand() % i]->children.push_back(tree[i]);
	}
	root = tree[0];
}

int SubTreeFindingProblem::Tree::size() const
{
	return nodeNum;

}

Node * SubTreeFindingProblem::Tree::getRoot() const
{
	return root;
}

void SubTreeFindingProblem::Tree::writeGvFile(string filename)
{
	ofstream fout(filename + ".gv", ios::out | ios::trunc);
	fout << "digraph ";
	fout << "{" << endl;
	queue<Node*> stk;
	stk.push(root);
	while (!stk.empty())
	{
		Node* cur = stk.front();
		for (auto child : cur->children)
		{
			fout << cur->num << "->" << child->num << ";" << endl;
			stk.push(child);
		}
		stk.pop();
	}
	fout << " }";
	fout.close();
}

bool SubTreeFindingProblem::Tree::readFile(char * filename)
{
	ifstream fin(filename, ios::in);
	char buff = ' ';
	while (!fin.eof() && buff != '{')
		fin >> buff;
	if (fin.eof())
		return false;
	
	while (!fin.eof())
	{
		fin >> buff;
		//TODO: PARSE FILE
	}
}

//ostream & SubTreeFindingProblem::Tree::operator<<(ostream & c)
//{
	// TODO: вставьте здесь оператор return
//}

Tree::Tree() : nodeNum(0), root(nullptr)
{
}


Tree::~Tree()
{
}

Node * SubTreeFindingProblem::SubTreeFinder::findProc(Node * what, Node * where)
{
	queue<Node*> stk;
	stk.push(where);
	while (!stk.empty())
	{
		Node * t1 = stk.front();
		Node * t2 = areIdentic(what, t1);
		if (t2)
			return t2;
		for (auto it : t1->children)
			stk.push(it);
		stk.pop();
	}
	return nullptr;
}

Node * SubTreeFindingProblem::SubTreeFinder::areIdentic(Node * pat, Node * tree)
{
	if (!tree)
		return nullptr;
	if (tree->children.size() < pat->children.size())
		return nullptr;

	bool *used = new bool[tree->children.size()];
	for (int i = 0; i < tree->children.size(); ++i)
		used[i] = false;
	int *indices = new int[pat->children.size()];
	for (int i = 0; i < pat->children.size(); ++i)
		indices[i] = -1;

	int p = 0;
	int t = 0;
	while (p < pat->children.size())
	{
		if (!pat->children[p])
		{
			++p;
			continue;
		}
		while (t < tree->children.size())
		{
			if (tree->children[t] && !used[t])
			{
				Node * tmp = areIdentic(pat->children[p], tree->children[t]);
				if (tmp)
				{
					indices[p] = t;
					used[t] = true;
				}
			}
			if (indices[p] == t)
				break;
			if (p >= pat->children.size())
				break;
			++t;
		}
		t = 0;
		if (indices[p] == -1)
		{
			if (p == 0)
				return nullptr;
			int k = p - 1;
			while (k>=0 && !pat->children[k])
				--k;
			if (!pat->children[k])
				return nullptr;
			used[indices[k]] = false;
			t = indices[k] + 1;
			indices[k] = -1;
			p = k-1;
		}
		++p;
	}
	delete[] used;
	delete[] indices;


	//queue<Node*> stkp;
	//for (auto it : pat->children)
	//	stkp.push(it);
	//queue<Node*> stkt;
	//for (auto it : tree->children)
	//	stkt.push(it);

	//while (!stkp.empty())
	//{

	//}

	return tree;
}

Node * SubTreeFindingProblem::SubTreeFinder::findSubtree(Tree what, Tree where)
{
	if (where.size() < what.size())
		return nullptr;
	return	findProc(what.getRoot(), where.getRoot());
}

void SubTreeFindingProblem::SubTreeFinder::test()
{
	int size1 = 100, size2 = 4;
	
	Tree tr;
	tr.genRand(size1);
	tr.writeGvFile("haystack");

	Tree pat;
	pat.genRand(size2);
	pat.writeGvFile("needle");
//	if (size1 < 20)
//	{
//		cout << "TREE : ";
//	}
	Node *res = findSubtree(pat, tr);
	if (res)
		cout << "FOUND: " << res->num << endl;
	else cout << "NOT FOUND" << endl;
}

void SubTreeFindingProblem::SubTreeFinder::help()
{
	cout << "task16.exe [COMMAND1] [COMMAND2] [COMMAND3] [COMMAND4]" << endl;
	cout << "COMMAND1" << endl;
	cout << "  -h			help" << endl;
	cout << "  -print		print result" << endl;
	cout << "  -return      return result (won't be able to see it, option for other apps)" << endl;
	cout << "  -fileout     write result to file output.txt" << endl;
	cout << endl;
	cout << "COMMAND2 - what to search, COMMAND3 - where to search" << endl;
	cout << "<size>					generate test tree of size <size>" << endl;
	cout << "<existing filename> 	use existing file <filename> (.gv, .dot)" << endl;
	cout << endl;
}

bool SubTreeFindingProblem::SubTreeFinder::run(char * _what, int sz1, char * _where, int sz2, Node *&result)
{
	Tree whatTr, whereTr;

	if ((sz1 > 4 && !strcmp(&_what[sz1 - 4], ".dot")) || (sz1 > 3 && !strcmp(&_what[sz1 - 3], ".gv")))
	{
		if (!whatTr.readFile(_what))
			return false;
	}
	else
	{
		whatTr.genRand(atoi(_what));
		whatTr.writeGvFile("needle.gv");
	}

	if ((sz2 > 4 && !strcmp(&_where[sz2 - 4], ".dot")) || (sz2 > 3 && !strcmp(&_where[sz2 - 3], ".gv")))
	{
		if (!whereTr.readFile(_where))
			return false;
	}
	else
	{
		whereTr.genRand(atoi(_where));
		whereTr.writeGvFile("haystack.gv");
	}

	result = findSubtree(whatTr, whereTr);
	return true;
}
