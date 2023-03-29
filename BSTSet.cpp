#include "BSTSet.h"
#include <iostream>
#include <vector>

using namespace std;

/*
Shakir Alam
400397108
alams36
*/

//Struct SNode represents a node in stack
struct SNode {
	TNode* info;
	SNode* next;
	//constructor
	SNode(TNode* t, SNode* n) : info(t), next(n) {}
};

//MyStack represents a stack data structure 
class MyStack {
private:
	struct SNode {
		TNode* info;
		SNode* next;
		SNode(TNode* t, SNode* n) : info(t), next(n) {}
	};
	SNode* head;
public:
	MyStack() : head(nullptr) {}
	//destructor
	~MyStack() {
		while (head) {
			SNode* temp = head;
			head = head->next;
			delete temp;
		}
	}
	//returns true is stack empty
	bool isEmpty() const { return head == nullptr; }
	//adds new TNode data to top of stack
	void push(TNode* t) {
		//create new node with TNode and the head
		head = new SNode(t, head);
	}
	//remove and return TNode data
	TNode* pop() {
		//if stack is not empty
		if (!isEmpty()) {
			//get the current head 
			SNode* oldHead = head;
			//get TNode from current
			TNode* tempData = head->info;
			//stack set from next node
			head = head->next;
			delete oldHead;
			//return TNode
			return tempData;
		}
		//if empty return null
		return nullptr;
	}
};

BSTSet::BSTSet() : root(nullptr) {
	//time complexity = O(1)
	//space complexity = O(1)
}

BSTSet::BSTSet(const std::vector<int>& input)
{
	//time complexity = O(n log n)
	//space complexity = O(n)
	/*add takes O(log n) time. The loop calls add n times, so total time complexity is O(n log n).
	The space complexity of this code is O(n) because it creates a binary search tree to store the input elements.*/
	root = nullptr;
	for (int v : input) {
		add(v);
	}
}

BSTSet::~BSTSet()
{
	//time complexity = Theta(n)
	//space complexity = O(1)
	clear(root);
}

void BSTSet::clear(TNode*& t) {
	//function recursively clears nodes in tree at t
	//time complexity = Theta(n)
	//space complexity = O(1)
	if (t == nullptr) {
		return;
	}
	clear(t->left);
	clear(t->right);
	delete t;
	t = nullptr;
}

bool BSTSet::isIn(int v) {
	//time complexity = Theta(log n)
	// space complexity = O(1) 
	return isIn(v, root);
}

bool BSTSet::isIn(int v, TNode*& t) {
	//time complexity = Theta(log n)
	// space complexity = O(1)
	if (t == nullptr) {
		return false;
	}
	if (v == t->element) {
		return true;
	}
	else if (v < t->element) {
		return isIn(v, t->left);
	}
	else {
		return isIn(v, t->right);
	}
}

void BSTSet::add(int v)
{
	//time complexity = O(logn)
	// space complexity: O(1)
	TNode** ptr = &root;
	while (*ptr) {
		if (v < (*ptr)->element) {
			ptr = &((*ptr)->left);
		}
		else if (v > (*ptr)->element) {
			ptr = &((*ptr)->right);
		}
		else {
			//v already exists
			return;
		}
	}
	*ptr = new TNode(v, nullptr, nullptr);
}

bool BSTSet::remove(int v)
{
	//time complexity = O(logn)
	//space complexity = Theta(1)
	return remove(v, root);
}

bool BSTSet::remove(int v, TNode*& t) {
	//time complexity = O(logn)
	//space complexity = Theta(1)
	if (t == nullptr) {
		return false;
	}

	if (v < t->element) {
		return remove(v, t->left);
	}

	if (v > t->element) {
		return remove(v, t->right);
	}

	if (t->left != nullptr && t->right != nullptr) {
		t->element = findMin(t->right);
		return remove(t->element, t->right);
	}

	TNode* tmp = t;

	if (t->left != nullptr) {
		t = t->left;
	}
	else {
		t = t->right;
	}

	delete tmp;
	return true;
}

int BSTSet::findMin(TNode*& t) {
	//time complexity = O(log n)
	//space complexity = Theta(1)
	TNode* current = t;
	while (current != nullptr && current->left != nullptr) {
		current = current->left;
	}
	if (current != nullptr) {
		return current->element;
	}
	else {
		throw std::runtime_error("error: tree empty, didn't plant the seed ");
	}
}

void BSTSet::Union(const BSTSet& s)
{
	//time complexity = O(n log n)
	//space complexity = O(n)
	if (s.root == nullptr) {
		return;
	}

	if (root == nullptr) {
		add(s.root->element);
		Union(s.root->left);
		Union(s.root->right);
	}
	else {
		Union(s.root);
	}
}

void BSTSet::Union(TNode* t) {
	//time complexity = O(n log n)
	//space complexity = O(n)
	if (t == nullptr) {
		return;
	}

	Union(t->left);
	Union(t->right);
	if (!isIn(t->element)) {
		add(t->element);
	}
}

void BSTSet::intersection(const BSTSet& s) {
	//time complexity = O(nlogn)
	//space complexity = O(n)
	BSTSet* temp = new BSTSet();

	//traverse the other set and add any elements that are also in this set to the temp set
	TNode* curr = s.root;
	while (curr != nullptr) {
		if (isIn(curr->element)) {
			temp->add(curr->element);
		}
		if (curr->left != nullptr) {
			intersection(curr->left, temp);
		}
		curr = curr->right;
	}

	//clear the current set and replace it with the intersection set
	clear(root);
	root = temp->root;
}

void BSTSet::intersection(TNode* t, BSTSet* temp) {
	//time complexity = O(n log n)
	//space complexity = O(n)
	if (!t) return;
	intersection(t->left, temp);
	intersection(t->right, temp);
	if (isIn(t->element)) temp->add(t->element);
}

void BSTSet::difference(const BSTSet& s) {
	//time complexity= O(n log n)
	//space complexity = Theta(1)
	difference(s.root);
}

void BSTSet::difference(TNode* t) {
	if (t) {
		//traverse left subtree
		for (TNode* current = t; current->left; current = current->left) {
			difference(current->left);
		}

		//traverse right subtree
		for (TNode* current = t; current->right; current = current->right) {
			difference(current->right);
		}

		//remove the matching element
		if (isIn(t->element)) {
			remove(t->element);
		}
	}
}

int BSTSet::size() {
	//time complexity = O(n)
	//space complexity = O(log n)
	return size(root);
}

int BSTSet::size(TNode* t) {
	//time complexity = O(n)
	//space complexity = O(log n)
	if (!t) {
		return 0;
	}
	return 1 + size(t->left) + size(t->right);
}

int BSTSet::height() {
	//time complexity = O(n)
	//space complexity = O(log n)
	return height(root);
}

int BSTSet::height(TNode* t) {
	//time complexity = O(n)
	//space complexity = O(log n)
	if (!t) {
		return -1;
	}
	int left_height = height(t->left);
	int right_height = height(t->right);
	return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

//create and use class MyStack
void BSTSet::printNonRec() {
	//time complexity = Theta(n)
	//space complexity = Theta(log n)
	MyStack s = MyStack();
	TNode* current = root;

	while (current != nullptr || !s.isEmpty()) {
		if (current != nullptr) {
			s.push(current);
			current = current->left;
		}
		else {
			current = s.pop();
			cout << current->element << ",";
			current = current->right;
		}
	}
}

//Do not modify following provided methods
void BSTSet::printBSTSet()
{
	if (root == NULL)
		std::cout << "";
	else {
		printBSTSet(root);
	}
}

void BSTSet::printBSTSet(TNode*& t)
{
	if (t != NULL) {
		printBSTSet(t->left);
		std::cout << t->element << ",";
		printBSTSet(t->right);
	}
}