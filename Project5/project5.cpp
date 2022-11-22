// Computing Structures Fall 2022
// Project 5

#include <iostream>
#include <stack>
#include <vector>

using namespace std;
int displayIndex;
////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBTNode
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBTNode
{
	template <class DT>
	friend ostream& operator<< (ostream& s, ArrayBTNode<DT>& node);
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
	_info = new DT(info);
	_left = -1;
	_right = -1;
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
	//*_info = info;
	delete _info;
	_info = new DT(info);
}

template <class DT>
void ArrayBTNode<DT>::setInfoNull() {
	delete _info;
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
	delete _info;
	_left = -1;
	_right = -1;
}

template <class DT>
bool ArrayBTNode<DT>:: operator< (const ArrayBTNode<DT>& x) {
	return *_info < *x._info;
}

template <class DT>
bool ArrayBTNode<DT>:: operator> (const ArrayBTNode<DT>& x) {
	return *_info > *x._info;
}

template <class DT>
bool ArrayBTNode<DT>:: operator== (const ArrayBTNode<DT>& x) {
	return *_info == *x._info;
}

template <class DT>
bool ArrayBTNode<DT>:: operator<= (const ArrayBTNode<DT>& x) {
	return *_info <= *x._info;
}

template <class DT>
bool ArrayBTNode<DT>:: operator>= (const ArrayBTNode<DT>& x) {
	return *_info >= *x._info;
}

template <class DT>
bool ArrayBTNode<DT>:: operator!= (const ArrayBTNode<DT>& x) {
	return *_info != *x._info;
}

template <class DT>
ostream& operator<< (ostream& s, ArrayBTNode<DT>& node) {
	//s << "Info: " << node->_info << ", Left: " << node.getleft() << ", Right: " << node.getright() << endl;
	node.display();
	return s;
}

template <class DT>
void ArrayBTNode<DT>::display() {
	cout << "Info: " << *getinfo() << ", Left: " << getleft() << ", Right: " << getright() << endl;
	//cout << *this << endl;
}


////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBST
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBST
{
	template <class DT>
	friend ostream& operator<< (ostream& s, ArrayBST<DT>& tree);
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
	bool isEmpty();
	int Height();
	int Size();
	int rootIndex();
	int maxSize();

	// Mutator Methods
	void setData(int index, DT& value);
	void setLeft(int index, int value);
	void setRight(int index, int value);

	// Display methods and traversals
	void display(ostream& os);
	void displayPreOrder(ostream& os);
	void displayInOrder(ostream& os);
	void _PreOrder(int post);
	void _InOrder(int pos);
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
	_numNodes = 0;
	_size = 0;
	// no need to initialize _tree vector and _freeLocations stack
}

template <class DT>
ArrayBST<DT>::ArrayBST(int k) {
	_rootIndex = k - 1;
	_numNodes = 0;
	_size = k;
	// initialize the vector with NULL nodes and fill the stack
	_tree.reserve(k);
	for (int i = 0; i < k; i++) {
		// push NULL node
		_freeLocations.push(i);
		_tree.push_back(ArrayBTNode<DT>());
	}
}

// accessors

template <class DT>
bool ArrayBST<DT>::isEmpty() {
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
	_tree[index].setInfo(value);
}

template <class DT>
void ArrayBST<DT>::setLeft(int index, int value) {
	_tree[index].setLeft(value);
}

template <class DT>
void ArrayBST<DT>::setRight(int index, int value) {
	_tree[index].setRight(value);
}

template <class DT>
void ArrayBST<DT>::insert(DT& object) {
	if (_numNodes < _size) {
		// Get a location to insert a new node
		int freeIndex = _freeLocations.top();
		_freeLocations.pop();
		// Increment the number of nodes
		_numNodes++;
		_tree[freeIndex].setInfo(object);
		// Start traversing the tree (in this case, the vector)
		int currIndex = _rootIndex;
		if (freeIndex != _rootIndex) { // only traverse the tree if there are more than 1 node, otherwise, it is the first insertion
			// traverse the tree
			while (true) {
				if (_tree[currIndex] > _tree[freeIndex]) { // go left
					if (_tree[currIndex].getleft() == -1) {
						_tree[currIndex].setLeft(freeIndex);
						break;
					}
					else { // this means there is already a node here
						// update the current index to that index
						currIndex = _tree[currIndex].getleft();
					}
				}
				else { // go right
					if (_tree[currIndex].getright() == -1) {
						_tree[currIndex].setRight(freeIndex);
						break;
					}
					else {
						currIndex = _tree[currIndex].getright();
					}
				}
			}
		}
	}
	else { // full tree
		cout << "Cannot insert data, BST Full." << endl;
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
		if ((_tree[pos]).getright() != -1) {
			return _find(object, _tree[pos].getright());
		}
		return false;
	}
	else {
		if ((_tree[pos]).getleft() != -1) {
			return _find(object, _tree[pos].getleft());
		}
		return false;
	}
}

template <class DT>
int ArrayBST<DT>::findIndex(DT& object) {
	int index = _rootIndex;
	bool found = false;
	while (found == false) {
		if (*_tree[index].getinfo() == object) {
			found = true;
		}
		else if (*_tree[index].getinfo() < object) {
			index = _tree[index].getright();
		}
		else {
			index = _tree[index].getleft();
		}
	}

	return index;
}

// display methods

template <class DT>
void ArrayBST<DT>::display(ostream& os) {
	// will call displayPreOrder and displayInOrder
	os << "Pre Order Traversal:" << endl;
	displayPreOrder(os);
	os << endl;
	os << "In Order Traversal:" << endl;
	displayInOrder(os);
}

template<class DT>
void ArrayBST<DT>::_PreOrder(int pos) {
	cout << *_tree[pos].getinfo() << " ";
	if (_tree[pos].getleft() != -1) {
		_PreOrder(_tree[pos].getleft());
	}
	if (_tree[pos].getright() != -1) {
		_PreOrder(_tree[pos].getright());
	}
}

template <class DT>
void ArrayBST<DT>::displayPreOrder(ostream& os) {
	// root, left tree, right tree
	_PreOrder(_rootIndex);
}

template<class DT>
void ArrayBST<DT>::_InOrder(int pos) {
	if (_tree[pos].getleft() != -1) {
		_InOrder(_tree[pos].getleft());
	}
	cout << *_tree[pos].getinfo() << " ";
	if (_tree[pos].getright() != -1) {
		_InOrder(_tree[pos].getright());
	}
}

template <class DT>
void ArrayBST<DT>::displayInOrder(ostream& os) {
	// left tree, root, right tree
	_InOrder(_rootIndex);
}

template <class DT>
ostream& operator<< (ostream& s, ArrayBST<DT>& tree) {
	// will call display here
	// in main, simply use cout << myBST
	tree.display(s);
	return s;
}

template <class DT>
void ArrayBST<DT>::printRaw() {
	cout << "Raw Data: " << endl;
	for (int i = 0; i < _size; i++) {
		if (_tree[i].getinfo() != NULL) {
			cout << "Index " << i << ": ";
			// _tree[i].display();
			cout << _tree[i];
		}
	}
	cout << "Free Indexes: " << endl;
	if (_freeLocations.empty() == true) {
		cout << "None";
		return;
	}
	stack<int> newStack = _freeLocations;
	while (!newStack.empty() && newStack.top() != 0) {
		cout << newStack.top() << ", ";
		newStack.pop();
	}
	cout << newStack.top();
}

template <class DT>
ArrayBST<DT>::~ArrayBST() {
	_rootIndex = -1;
	_numNodes = -1;
	_size = -1;
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
	ArrayBST<int> myBST = ArrayBST<int>(inputSize);
	displayIndex = myBST.rootIndex();
	// TODO: input loop for commands
	char command;
	cin >> command;

	while (!cin.eof()) {
		switch (command) {
			case 'I': {
				int value;
				cin >> value;
				cout << "Inserting " << value << endl;
				myBST.insert(value);
				break;
			}
			case 'O': {
				cout << "Information in Tree:" << endl;
				cout << myBST << endl;
				// reset global index
				displayIndex = myBST.rootIndex();
				break;
			}
			case 'A': {
				myBST.printRaw();
				cout << endl;
				break;
			}
			case 'F': {
				int value;
				cin >> value;
				cout << "Finding " << value << endl;
				if (myBST.find(value) == true) {
					cout << "Number found at index " << myBST.findIndex(value) << "." << endl;
				}
				else {
					cout << "Number not found." << endl;
				}
				break;
			}
			default: cout << "It broke :(" << endl;
		}
		cin >> command;
	}
	return 0;
}