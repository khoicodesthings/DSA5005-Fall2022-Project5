// Computing Structures Fall 2022
// Project 5

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBTNode
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBTNode
{
	friend ostream& operator<< (ostream& s, const ArrayBTNode<DT>& node);
protected:
	// Instance Variables
	DT* _info;
	int _left;
	int _right;

public:
	// Constructors and Destructor
	ArrayBTNode();
	ArrayBTNode(DT& info);
	~ArrayBTNode();

	// getter Methods
	DT* getinfo();
	int getleft();
	int getright();

	// setter Methods
	void setInfo(DT& info);
	void setInfoNull(); // Sets _info to Null
	void setLeft(int left);
	void setRight(int right);

	// Display Method
	// Outputs data in _info, _left, _right
	void display();

	// Overloaded Comparison Operators
	// Used for comparing _info field with other ArrayBTNodes
	bool operator<(const ArrayBTNode<DT>& x);
	bool operator>(const ArrayBTNode<DT>& x);
	bool operator==(const ArrayBTNode<DT>& x);
	bool operator>=(const ArrayBTNode<DT>& x);
	bool operator<=(const ArrayBTNode<DT>& x);
	bool operator!=(const ArrayBTNode<DT>& x);

	// TODO: Overloaded Ostream Operator - Uses display method to output ArrayBTNode contents
};

// Constructors

// Default
template <class DT>
ArrayBTNode<DT>::ArrayBTNode() {
	_info = NULL;
	_left = -1;
	_right = -1;
}

// Non-default
template <class DT>
ArrayBTNode<DT>::ArrayBTNode(DT& info) {
	_info = info;
}

// Getters

template <class DT>
DT* ArrayBTNode<DT>::getinfo() {
	return _info;
}

template <class DT>
int ArrayBTNode<DT>::getleft() {
	return _left;
}

template <class DT>
int ArrayBTNode<DT>::getright() {
	return _right;
}

// Setters
template <class DT>
void ArrayBTNode<DT>::setInfo(DT& info) {
	_info = info;
}

template <class DT>
void ArrayBTNode<DT>::setInfoNull() {
	_info = NULL;
}

template <class DT>
void ArrayBTNode<DT>::setLeft(int left) {
	_left = left;
}

template <class DT>
void ArrayBTNode<DT>::setRight(int right) {
	_right = right;
}

// Destructor
template <class DT>
ArrayBTNode<DT>::~ArrayBTNode() {
	_info = NULL;
	_left = -1;
	_right = -1;
}

template <class DT>
bool ArrayBTNode<DT>:: operator< (const ArrayBTNode<DT>& x) {
	return ((*_info) < *(x.getinfo()));
}

template <class DT>
bool ArrayBTNode<DT>:: operator> (const ArrayBTNode<DT>& x) {
	return ((*_info) > *(x.getinfo()));
}

template <class DT>
bool ArrayBTNode<DT>:: operator== (const ArrayBTNode<DT>& x) {
	return ((*_info) == *(x.getinfo()));
}

template <class DT>
bool ArrayBTNode<DT>:: operator<= (const ArrayBTNode<DT>& x) {
	return ((*_info) <= *(x.getinfo()));
}

template <class DT>
bool ArrayBTNode<DT>:: operator>= (const ArrayBTNode<DT>& x) {
	return ((*_info) >= *(x.getinfo()));
}

template <class DT>
bool ArrayBTNode<DT>:: operator!= (const ArrayBTNode<DT>& x) {
	return ((*_info) != *(x.getinfo()));
}

template <class DT>
ostream& operator<< (ostream& s, const ArrayBTNode<DT>& node) {
	s << "Info: " << node.getinfo() << ", Left: " << node.getleft() << ", Right: " << node.getright() << endl;
	return s;
}

template <class DT>
void ArrayBTNode<DT>::display() {
	cout << "Info: " << getinfo() << ", Left: " << getleft() << ", Right: " << getright() << endl;
	//cout << *this << endl;
}


////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBST
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBST
{
protected:
	// Instance Variables
	vector<ArrayBTNode<DT> > _tree;    // Vector of ArrayBTNodes used to create a tree
	int _rootIndex;            // Index of the root node in _tree
	int _numNodes;             // Number of nodes in the tree
	int _size;                 // Maximum size of the _tree array
	stack<int> _freeLocations; // Stack containing indexes of freeLocations in the _tree array

public:
	// Constructors and Destructor
	ArrayBST();
	ArrayBST(int k); // initialize the vector with NULL nodes and fill the stack
	~ArrayBST();

	// Accessor Methods
	bool isEmpty() const;
	int Height();
	int Size();
	int rootIndex();
	int maxSize();

	// Mutator Methods
	void setData(int index, DT& value);
	void setLeft(int index, int value);
	void setRight(int index, int value);

	// Display methods and traversals
	void display(ostream& os) const;
	void displayPreOrder(ostream& os) const;
	void displayInOrder(ostream& os) const;
	void printRaw(); // Display the array and all of its contents

	// BST Specific Methods
	void insert(DT& object);
	bool find(DT& object);
	bool _find(DT& object, int pos);
	int findIndex(DT& object);
	//void remove(DT& object); // extra credit

	// TODO: Overridden ostream operator for ArrayBST - this will call the pre order and in order methods
};

// constructors

// default
template <class DT>
ArrayBST<DT>::ArrayBST() {
	_rootIndex = -1;
	_numNodes = -1;
	_size = -1;
	// no need to initialize _tree vector and _freeLocations stack
}

template <class DT>
ArrayBST<DT>::ArrayBST(int k) {
	// initialize the vector with NULL nodes and fill the stack
	ArrayBTNode<DT>* temp = new ArrayBTNode<DT>(); // this node will have NULL info and -1 for left and right
	for (int i = 0; i < k; i++) {
		// push NULL node
		_tree.push_back(temp);
		// fill the stack
		_freeLocations.push(i);
	}
}

// accessors

template <class DT>
bool ArrayBST<DT>::isEmpty() const {
	return _tree.empty();
}

template <class DT>
int ArrayBST<DT>::Height() {
	// root to the furthest leaf
	return _numNodes; // not correct
}

template <class DT>
int ArrayBST<DT>::Size() {
	return _numNodes;
}

template <class DT>
int ArrayBST<DT>::maxSize() {
	return _size;
}

template <class DT>
int ArrayBST<DT>::rootIndex() {
	return _rootIndex;
}



// mutators
template <class DT>
void ArrayBST<DT>::setData(int index, DT& value) {
	_tree[index].setinfo(value);
}

template <class DT>
void ArrayBST<DT>::setLeft(int index, int value) {
	_tree[index].setleft(value);
}

template <class DT>
void ArrayBST<DT>::setRight(int index, int value) {
	_tree[index].setright(value);
}

template <class DT>
void ArrayBST<DT>::insert(DT& object) {
	// insert node into _tree vector
	// pop one free space from stack
	
	// make a new node with info being
	// what's in object
	ArrayBTNode<DT>* temp = new ArrayBTNode<DT>();
	temp->setInfo(object);
	if (find(object) == true) {
		cout << "Node already exists" << endl;
	}
	else {
		_tree.push_back(temp);
		_freeLocations.pop();
	}
}

template <class DT>
bool ArrayBST<DT>::find(DT& object) {
	return _find(object, rootIndex());
}

template <class DT>
bool ArrayBST<DT>::_find(DT& object, int pos) {
	if (*(_tree[pos].getinfo()) == object) return true;

	if (*(_tree[pos].getinfo()) < object) {
		if (*(_tree[pos]).getright() != -1) {
			_find(object, _tree[pos].getright());
		}
		return false;
	}
	else {
		if (*(_tree[pos]).getleft() != -1) {
			_find(object, _tree[pos].getleft());
		}
		return false;
	}
}




////////////////////////////////////////////////////////////////////////////////////////
// Main Method
////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	// Get input for the size of the tree
	int inputSize;
	cin >> inputSize;
	cout << "Number of maximum nodes: " << inputSize << endl;
	// Create a BST of the size inputSize
	//ArrayBST<int> myBST = ArrayBST<int>(inputSize);

	// TODO: input loop for commands

	ArrayBTNode<int>* test = new ArrayBTNode<int>();

	test->display();
	return 0;
}