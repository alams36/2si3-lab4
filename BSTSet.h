#ifndef BSTSET_H_
#define BSTSET_H_
#include "TNode.h"
#include <vector>
class BSTSet
{
private:
	// must contain only one private field
	TNode* root = NULL;
public:
	// required constructors/destructor
	BSTSet();
	BSTSet(const std::vector<int>& input);
	~BSTSet();

	// required methods
	bool isIn(int v);
	void add(int v);
	bool remove(int v);
	void Union(const BSTSet& s);
	void intersection(const BSTSet& s);
	void difference(const BSTSet& s);
	int size();
	int height();
	void printNonRec(); // create and use class MyStack

	// provided recursive print method
	void printBSTSet();

	// Used for testing
	TNode* getRoot()
	{
		return root;
	}
	//bonus

private:
	// basic operations
	void add(int v, TNode*& t);
	bool remove(int v, TNode*& t);
	bool isIn(int v, TNode*& t);
	// set operations
	void Union(TNode* t);
	void intersection(TNode* t, BSTSet* temp);
	void difference(TNode* t);
	// helper methods
	void printBSTSet(TNode*& t);
	void clear(TNode*& t);
	int findMin(TNode*& t);
	int size(TNode* t);
	int height(TNode* t);
};
#endif /* BSTSET_H_ */