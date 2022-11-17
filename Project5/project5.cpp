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
	_info = new DT(info);
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
	_info = new DT(info);
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
	s << "Info: " << node->_info << ", Left: " << node.getleft() << ", Right: " << node.getright() << endl;
	return s;
}

template <class DT>
void ArrayBTNode<DT>::display() {
	cout << "Info: " << *_info << ", Left: " << getleft() << ", Right: " << getright() << endl;
	//cout << *this << endl;
}


////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBST
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBST
{
	friend ostream& operator<< (ostream& s, const ArrayBST<DT>& tree);
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
	_numNodes = 0;
	_size = 0;
	// no need to initialize _tree vector and _freeLocations stack
}

template <class DT>
ArrayBST<DT>::ArrayBST(int k) {
	_rootIndex = -1;
	_numNodes = 0;
	_size = k;
	// initialize the vector with NULL nodes and fill the stack
	_tree.reserve(k);
	//ArrayBTNode<DT>* temp = new ArrayBTNode<DT>(); // this node will have NULL info and -1 for left and right
	for (int i = 0; i < k; i++) {
		// push NULL node
		//_tree.push_back(temp);
		// fill the stack
		//_tree[i].setInfoNull();
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
	//template <class DataType
	//	void BinarySearchTree<DataType>::insert(DataType& data)
	//{
	//	if (_subtree) throw BinarySearchTreeChangedSubtree();
	//	BinarySearchTree<DataType>* bst = _find(data);
	//	if (bst->isEmpty())
	//	{
	//		bst->_info = new DataType(data);
	//		bst->_left = makeSubtree();
	//		bst->_right = makeSubtree();
	//	}
	//	else
	//	{
	//		delete bst->_info;
	//		bst->_info = new DataType(data);
	//	}
	//}

	// insert node into _tree vector
	// pop one free space from stack
	
	// make a new node with info being
	// what's in object
	//ArrayBTNode<DT>* temp = new ArrayBTNode<DT>();
	//temp->setInfo(object);
	//// index to put into tree vector is the top of the stack
	//int index = _freeLocations.top();
	//// not sure how to set left and right here
	//if (find(object) == true) {
	//	cout << "Node already exists" << endl;
	//}
	//else {
	//	// trying to set left and right index
	//	for (ArrayBTNode<DT> node : _tree) {
	//		if (temp > node) {
	//			// trying to use the find() method
	//			// of a vector to get the index
	//			temp->setRight(_tree.find(node));
	//			break;
	//		}
	//		else if (temp < node) {
	//			temp->setLeft(_tree.find(node));
	//			break;
	//		}
	//		else {
	//			continue;
	//		}
	//	}
	//	_tree.insert(index, temp);
	//	// pop the top of the stack out since
	//	// it's no longer free
	//	_freeLocations.pop();
	//	// update index
	//	index = _freeLocations.top();
	//}
	int index = _rootIndex;
	int parent = -1; // parent of index
	ArrayBTNode<DT>* temp = new ArrayBTNode<DT>();
	temp->setInfo(object);
	
	if (_numNodes < _size) {
		if (parent == -1) {
			_rootIndex = _freeLocations.top();
			_freeLocations.pop();
			//_tree[_rootIndex].setInfo(object);
			_tree.push_back(*temp);
			_numNodes++;
			//cout << endl << "Inserting " << object << endl;
		}
		else if (object < *_tree[parent].getinfo()) {
			temp->setLeft(_freeLocations.top());
			_freeLocations.pop();
			//_tree[_tree[parent].getleft()].setInfo(object);
			_tree.push_back(*temp);
			_numNodes++;
			// cout << endl << "Inserting " << object << endl;
		}
		else {
			temp->setRight(_freeLocations.top());
			_freeLocations.pop();
			//_tree[_tree[parent].getright()].setInfo(object);
			_tree.push_back(*temp);
			_numNodes++;
			//cout << endl << "Inserting " << object << endl;
		}
	}
	else {
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
		if ((_tree[pos]).getRight() != -1) {
			return _find(object, _tree[pos].getRight());
		}
		return false;
	}
	else {
		if ((_tree[pos]).getLeft() != -1) {
			return _find(object, _tree[pos].getLeft());
		}
		return false;
	}
}

template <class DT>
int ArrayBST<DT>::findIndex(DT& object) {
	if (find(object) == true) {
		// object in the next line needs to be replaced with an ArrayBTNode node
		std::vector<int>::iterator it = std::find(_tree.begin(), _tree.end(), object);
		int index = std::distance(_tree.begin(), it);
		return index;
	}
	return 0;
}

// display methods

template <class DT>
ostream& operator<< (ostream& s, const ArrayBST<DT>& tree) {
	return s;
}

template <class DT>
void ArrayBST<DT>::display(ostream& os) const {

}

template <class DT>
void ArrayBST<DT>::displayPreOrder(ostream& os) const {

}

template <class DT>
void ArrayBST<DT>::displayInOrder(ostream& os) const {

}

template <class DT>
void ArrayBST<DT>::printRaw() {
	cout << "Raw Data: " << endl;
	for (int j = 0; j < _numNodes; j++) {
		cout << "Index " << j << ": ";
		/*for (ArrayBTNode<DT> i : _tree) {
			i.display();
		}*/
		_tree[j].display();
	}
	cout << "Free Indexes: " << endl;
	stack<int> newStack = _freeLocations;
	while (!newStack.empty()) {
		cout << newStack.top() << " ";
		newStack.pop();
	}
	if (_freeLocations.empty() == true) {
		cout << "None";
	}
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
	

	// TODO: input loop for commands

	/*ArrayBTNode<int>* test = new ArrayBTNode<int>();
	int testint = 10;
	test->setInfo(testint);
	test->display();
	int pointer = 80;
	myBST.insert(pointer);
	myBST.printRaw();*/
	ArrayBST<int> myBST = ArrayBST<int>(inputSize);
	/*int value = 7;
	myBST.insert(value);
	int value2 = 17;
	myBST.insert(value2);
	myBST.printRaw();*/
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
				cout << "Pre Order Traversal" << endl;
				//myBST.displayPreOrder
				cout << "In Order Traversal" << endl;
				//myBST.displayInOrder
				break;
			}
			case 'A': {
				// cout << "Raw Data:" << endl;
				myBST.printRaw();
				cout << endl;
				break;
			}
			case 'F': {
				int value;
				cin >> value;
				cout << "Finding " << value << endl;
				//myBST.findIndex(value);
				break;
			}
			default: cout << "It broke :(" << endl;
		}
		cin >> command;
	}
	return 0;
}