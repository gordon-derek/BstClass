//Specification File
//Author: Derek Gordon
//Date: May 1st, 2012
//Project: BstClass
//Purpose: 
//		To create a binary search tree
//	with a class template to allow use with
//	multiple data types.
//	
//		This tree is ordered and does not  
//	allow multiple entries of the same key.  
//
//		A client can use this class to add entries,
//	which will be ordered within the class and retrieve
//	any record that has been inserted.
//
//		Find needs to be called prior to making any insertions,
//	deletions, or retrievals.  If the client does not call Find
//	an Exception may be thrown.
//
//		The client is expected to use a try catch block to test
//	methods outlined in Error Handling.  If the client does not
//	use a try catch block with the below methods the program may
//	become unstable.
//
//Assumptions: 
//	-The client will specify a structure with a data key.
//	-This data key will have a typedef'd KeyType key of integer datatype.
//	
//	-The client will write a function that is to print the
//		contents of an ItemRec.  This function will be passed
//		as a parameter into an InOrder public method of the class
//
//	-The client will need to do the same above to also print to a file.
//
//Error Handling:
//	-Errors will be thrown as a class to be handled within the client
//	-Delete on Empty
//	-Retrieve on Empty
//	-OutofMemory on Allocate
//	-Not Found on Delete
//	-Not Found on Retrieve
//	-Duplicate Key on Insert

/***************************Summary Of Methods*************************************/
//
//BstClass();
//	-Constructor, initializes pdms to their default values
//
//	~BstClass();
//	-Deconstructor, returns memory back to the system
//
//	BstClass(/* in */const BstClass<ItemType>& orig);			//class to copy
//	-Copy Constructor, performs a deep copy of orig
//
//	bool IsEmpty();
//	-returns true if the list is empty
//
//	bool IsFull();
//	-returns true if the list is full(not possible with dynamically allocated memory)
//
//	void Clear();
//	-wrapper method, calls rClear which removes all the nodes in the tree, returning memory to system
//
//	void Insert(/* in */ItemType newItem);						//item to be inserted
//	-wrapper method, calls rInsert which processes the tree recursively until the desired
//		location is reached.
//
//	void Delete(/* in */KeyType key);							//item to be deleted
//	-wrapper method, calls rDelete which finds the key and deletes the node adjusting tree
//		accordingly
//
//	bool Find(/* in */KeyType key);								//key to be searched for
//	-wrapper method, calls rFind which processes the tree recursively until the desired key
//		is found. returns false if not found.
//
//	ItemType Retrieve(/* in */KeyType key);						//key to be searched and retrieved
//	-wrapper method, calls rRetrieve which processes the tree recursively until the desired
//		key is found. Returns key to client.
//
//	void PreOrder(/* out */FunctionType1 visit);				//function for item to be passed for printing
//	-wrapper method, calls rPreOrder which processes the tree recursively using NLR.  This
//		outputs to the screen the contents of the tree pre order.
//
//	void fPreOrder(/* out */FunctionType2 visit,				//function for item to be passed for file printing
//				   /* out */ofstream & outFile);				//file to be passed into visit
//	-wrapper method, calls rfPreOrder which processes the tree recursively using NLR.  This
//		outputs the contents of the tree pre order to a file.
//
//	void InOrder(/* out */FunctionType1 visit);					//function for item to be passed for printing
//	-wrapper method, calls rInOrder which processes the tree recursively using LNR.  This outputs
//		the contents of the tree in order to the screen.
//
//	void fInOrder(/* out */FunctionType2 visit,					//function for item to be passed for file printing
//				  /* out */ofstream & outFile);					//file to be passed into visit
//	-wrapper method, calls rfInOrder which processes the tree recursively using LNR.  This outputs
//		the contents of the tree in order to a file.
//
//	void PostOrder(/* out */FunctionType1 visit);				//function for item to be passed for printing
//	-wrapper method, calls rPostOrder which processes the tree recursively using LRN.  This outputs
//		the contents of the tree post order to the screen.
//
//	void fPostOrder(/* out */FunctionType2 visit,				//function for item to be passed for file printing
//				   /* out */ofstream & outFile);				//file to be passed into visit
//	-wrapper method, calls rfPostOrder which processes the tree recursively using LRN.  This outputs
//		the contents of the tree post order to a file.
//
//	void operator=(/* in */const BstClass<ItemType> & orig);	//class to be copied
//	-wrapper method, calls rCopy which performs a deep copy of orig.
//
//	BstClass<ItemType> operator+(/* in */BstClass<ItemType> & rtOp);//tree to merge
//	-merges rtOp with the applying class object and returns the merged tree at minimum
//		possible hieght.
//
//protected:
//	void rInsert(/* in */ItemType newItem,						//item to be inserted
//				/* in */node<ItemType>* & trav);				//location to test for possible insertion
//	-processes the tree recursively until the desired location is reached.
//
//	void rDelete(/* in */KeyType key,							//item to be deleted
//				/* in */node<ItemType>* & trav);				//location to test for key
//	-processes the tree recursively, finds the key and deletes the node adjusting tree accordingly
//
//	bool rFind(/* in */KeyType key,								//key to be searched for 
//			   /* in */node<ItemType>* & trav);					//location to test for key
//	-processes the tree recursively until the desired key is found. returns false if not found.
//
//	ItemType rRetrieve(/* in */KeyType key,						//key to be searched and retrieved
//					   /* in */node<ItemType>* & trav);			//location to test for key
//	-processes the tree recursively until the desired key is found. Returns key to client.
//
//	void rCopy(/* in */node <ItemType>* & target,				//node getting the data
//			   /* in */node <ItemType>* & orig);				//node sending the data
//	-processes the tree recursively in PreOrder creating a deep copy of the tree.
//
//	void rClear(/* in */node<ItemType>* & trav);				//location in tree
//	-processes the tree recursively in PostOrder returning the memory to the system.
//
//	void rPreOrder(/* out */FunctionType1 visit,				//function for item to be passed for printing
//				   /* in */node<ItemType>* & trav);				//location in Tree
//	-processes the tree recursively using NLR. Passing each node -> data to the function defined in
//		the client to output the data to the screen
//
//	void rfPreOrder(/* out */FunctionType2 visit,				//function for item to be passed for file printing
//					/* out */ofstream & outFile,				//file to be passed into visit
//					/* in */ node<ItemType>* & trav);			//location in tree
//	-processes the tree recursively using NLR. Passing each node -> data to the function defined in
//		the client to output the data to a file
//
//	void rInOrder(/* out */FunctionType1 visit,					//function for item to be passed for printing
//				  /* in */node<ItemType>* & trav);				//location in Tree
//	-processes the tree recursively using LNR. Passing each node -> data to the function defined in
//		the client to output the data to the screen
//
//	void rfInOrder(/* out */FunctionType2 visit,				//function for item to be passed for file printing
//				   /* out */ofstream & outFile,					//file to be passed into visit
//				   /* in */ node<ItemType>* & trav);			//location in tree
//	-processes the tree recursively using LNR. Passing each node -> data to the function defined in
//		the client to output the data to a file
//
//	void rPostOrder(/* out */FunctionType1 visit,				//function for item to be passed for printing
//					/* in */node<ItemType>* & trav);			//location in Tree
//	-processes the tree recursively using LRN. Passing each node -> data to the function defined in
//		the client to output the data to the screen
//
//	void rfPostOrder(/* out */FunctionType2 visit,				//function for item to be passed for file printing
//					 /* out */ofstream & outFile,				//file to be passed into visit
//					 /* in */ node<ItemType>* & trav);			//location in tree
//	-processes the tree recursively using LRN. Passing each node -> data to the function defined in
//		the client to output the data to a file
//
//	node<ItemType>* GetPrev(/* in */KeyType key,				//key to find parant node of
//							/* in */node<ItemType>* & trav);	//location in tree
//	-processes the list recursively until it find the parent node of key. Returns the
//		node or nullptr if at root.
//
//	node<ItemType>* RightToNull(/* in */node<ItemType>* & trav);//location in tree
//	-travel's to node-> right until approaches nullptr, to get the inorder precurser.
//
//	int CountNodes(/* in */ node<ItemType>* & trav);			//location in tree
//	-counts the total nodes within the tree.
//
//	node<ItemType>* VecToTree(vector<int>& values, int lower, int upper);
//	-processes the vector, creating a tree of minimum hieght.
//
//	void TreeToVec(vector<int>& values, int& index, node<ItemType>* & trav);
//	-processes the tree, placing all nodes (in order) in the vector.
//
//private:
//	node<ItemType>* Allocate();//returns a new node, throws error if out of memory
//
/*******************************************************************************************************/

#include <vector>	//for use of vectors.
#include "exceptions.h" //for exception handling

//declaration of a pointer to the clients method to print ItemType
//to the screen.

typedef void (*FunctionType1) (ItemRec&);

//declaration of a pointer to the clients method to print ItemType
//to a file.

typedef void (*FunctionType2) (ItemRec&, ofstream&);

template <class ItemType>
struct node; //forward declaration

template <class ItemType>
class BstClass
{
public:
	BstClass();
	//Constructor
	//Pre: Class has been instantiated
	//Post: PDM's have been set to initial values
	//Purpose: To create the class object and set PDM's to initial values

	~BstClass();
	//Deconstructor
	//Pre: Class Exists
	//Post: All memory has been returned to the system
	//Purpose: Destroy the class object returning all memory to the system

	BstClass(/* in */const BstClass<ItemType>& orig);			//class to copy
	//Copy Constructor
	//Pre: Class Exists
	//Post: A deep copy of orig has been made
	//Purpose: To perform a deep copy of orig to the applying class object

	bool IsEmpty();
	//Pre: Class Exists
	//Post: whether the tree is empty or not is returned
	//Purpose: return true if the binary search tree is empty, false otherwise

	bool IsFull();
	//Pre: Class Exists
	//Post: whether the list is full or not is returned
	//Purpose: return true if the tree is full, false otherwise

	void Clear();
	//wrapper
	//Pre: class exists
	//Post: all values within the tree are deleted
	//Purpose: to delete all values in the tree

	void Insert(/* in */ItemType newItem);						//item to be inserted
	//wrapper
	//Pre: Find has been called and returned false, newItem's key field contains a value
	//Post: newItem is inserted into the tree at the correct location
	//Purpose: to insert newItem into the tree and maintain order

	void Delete(/* in */KeyType key);							//item to be deleted
	//wrapper
	//Pre: Find has been called and returned true, key contains a valid value
	//Post: the key has been deleted and tree adjusted accordingly
	//Purpose: to delete the requested key from the tree

	bool Find(/* in */KeyType key);								//key to be searched for
	//wrapper
	//Pre: key contains a valid value
	//Post: true is returned if the key is already in the tree, false otherwise
	//Purpose: to check the list to see if a value has already been inputted

	ItemType Retrieve(/* in */KeyType key);						//key to be searched and retrieved
	//wrapper
	//Pre: key contains a valid value, Find has been called and returned true
	//Post: returns the ItemType of the key
	//Purpose: to return the ItemType of the desired key.

	void PreOrder(/* out */FunctionType1 visit);				//function for item to be passed for printing
	//wrapper
	//Pre: visit is a function that has been created in the class that takes an ItemRec parameter,
	//	this function outputs each ItemType to the screen.
	//Post: the tree is processed NLR outputting each node -> data to the screen.
	//Purpose: to print the contents of the tree in Pre order to the screen

	void fPreOrder(/* out */FunctionType2 visit,				//function for item to be passed for file printing
				   /* out */ofstream & outFile);				//file to be passed into visit
	//wrapper
	//Pre: visit is a function that has been created in the class that takes an ItemRec and ofstream parameter,
	//	this function outputs each ItemType to a file.
	//Post: the tree is processed NLR outputting each node -> data to a file.
	//Purpose: to print the contents of the tree in Pre order to a file

	void InOrder(/* out */FunctionType1 visit);					//function for item to be passed for printing
	//wrapper
	//Pre: visit is a function that has been created in the class that takes an ItemRec parameter,
	//	this function outputs each ItemType to the screen.
	//Post: the tree is processed LNR outputting each node -> data to the screen.
	//Purpose: to print the contents of the tree in Pre order to the screen

	void fInOrder(/* out */FunctionType2 visit,					//function for item to be passed for file printing
				  /* out */ofstream & outFile);					//file to be passed into visit
	//wrapper
	//Pre: visit is a function that has been created in the class that takes an ItemRec and ofstream parameter,
	//	this function outputs each ItemType to a file.
	//Post: the tree is processed LNR outputting each node -> data to a file.
	//Purpose: to print the contents of the tree in Pre order to a file

	void PostOrder(/* out */FunctionType1 visit);				//function for item to be passed for printing
	//wrapper
	//Pre: visit is a function that has been created in the class that takes an ItemRec parameter,
	//	this function outputs each ItemType to the screen.
	//Post: the tree is processed LRN outputting each node -> data to the screen.
	//Purpose: to print the contents of the tree in Pre order to the screen

	void fPostOrder(/* out */FunctionType2 visit,				//function for item to be passed for file printing
				   /* out */ofstream & outFile);				//file to be passed into visit
	//wrapper
	//Pre: visit is a function that has been created in the class that takes an ItemRec and ofstream parameter,
	//	this function outputs each ItemType to a file.
	//Post: the tree is processed LRN outputting each node -> data to a file.
	//Purpose: to print the contents of the tree in Pre order to a file

	void operator=(/* in */const BstClass<ItemType> & orig);	//class to be copied
	//Pre: class exists and orig contains values
	//Post: a deep copy of orig has been performed
	//Purpose: to perform a deep copy of the original class object

	BstClass<ItemType> operator+(/* in */BstClass<ItemType> & rtOp);//tree to be copied
	//Pre: both classes exist
	//Post: a class object that contains a merger of rtOp and the applying class object
	//	that is at minimum possible hieght.
	//Purpose: to form a merger of the two classes and re-balance the tree to minimum hieght.

protected:
	void rInsert(/* in */ItemType newItem,						//item to be inserted
				/* in */node<ItemType>* & trav);				//location to test for possible insertion
	//Pre: newItem contains a valid ItemType, trav contains a pointer in the tree
	//Post: newItem has been inserted at the proper location in the tree to maintain order
	//Purpose: process the tree recursively until a valid location for newItem to be
	//	inserted is found.

	void rDelete(/* in */KeyType key,							//item to be deleted
				/* in */node<ItemType>* & trav);				//location to test for key
	//Pre: key contains a valid KeyType, trav contains a pointer in the tree
	//Post: Once found key has been deleted and the tree adjusted accordingly
	//Purpose: To find the key in the tree and remove it, adjusting the tree to maintain order

	bool rFind(/* in */KeyType key,								//key to be searched for 
			   /* in */node<ItemType>* & trav);					//location to test for key
	//Pre: key contains a valid KeyType, trav contains a pointer in the tree
	//Post: true is returned if key is in the tree, false otherwise
	//Purpose: to find whether a key is already in the tree.

	ItemType rRetrieve(/* in */KeyType key,						//key to be searched and retrieved
					   /* in */node<ItemType>* & trav);			//location to test for key
	//Pre: key contains a valid KeyType, trav contains a pointer in the tree
	//Post: the ItemType if found is returned
	//Purpose: if the key is found within the tree, to return that ItemType to the client

	void rCopy(/* in */node <ItemType>* & target,				//node getting the data
			   /* in */node <ItemType>* & orig);				//node sending the data
	//Pre: target contains the location in tree getting the ItemType, orig contains
	//	the location in the tree sending the datatype.
	//Post: the data in orig has been copied to target
	//Purpose: to copy the ItemType in orig over to target.

	void rClear(/* in */node<ItemType>* & trav);				//location in tree
	//Pre: trav contains the location in the tree to be deleted
	//Post: trav is tested to be the bottom node in the tree, trav is deleted
	//Purpose: To delete the tree from the bottom up node by node

	void rPreOrder(/* out */FunctionType1 visit,				//function for item to be passed for printing
				   /* in */node<ItemType>* & trav);				//location in Tree
	//Pre: visit is a function that has been created in the class that takes an ItemRec parameter,
	//	this function outputs each ItemType to the screen.
	//Post: the tree is processed NLR outputting each node -> data to the screen.
	//Purpose: to print the contents of the tree in Pre order to the screen

	void rfPreOrder(/* out */FunctionType2 visit,				//function for item to be passed for file printing
					/* out */ofstream & outFile,				//file to be passed into visit
					/* in */ node<ItemType>* & trav);			//location in tree
	//Pre: visit is a function that has been created in the class that takes an ItemRec and ofstream parameter,
	//	this function outputs each ItemType to a file.
	//Post: the tree is processed NLR outputting each node -> data to a file.
	//Purpose: to print the contents of the tree in Pre order to a file

	void rInOrder(/* out */FunctionType1 visit,					//function for item to be passed for printing
				  /* in */node<ItemType>* & trav);				//location in Tree
	//Pre: visit is a function that has been created in the class that takes an ItemRec parameter,
	//	this function outputs each ItemType to the screen.
	//Post: the tree is processed LNR outputting each node -> data to the screen.
	//Purpose: to print the contents of the tree in Pre order to the screen

	void rfInOrder(/* out */FunctionType2 visit,				//function for item to be passed for file printing
				   /* out */ofstream & outFile,					//file to be passed into visit
				   /* in */ node<ItemType>* & trav);			//location in tree
	//Pre: visit is a function that has been created in the class that takes an ItemRec and ofstream parameter,
	//	this function outputs each ItemType to a file.
	//Post: the tree is processed LNR outputting each node -> data to a file.
	//Purpose: to print the contents of the tree in Pre order to a file

	void rPostOrder(/* out */FunctionType1 visit,				//function for item to be passed for printing
					/* in */node<ItemType>* & trav);			//location in Tree
	//Pre: visit is a function that has been created in the class that takes an ItemRec parameter,
	//	this function outputs each ItemType to the screen.
	//Post: the tree is processed LRN outputting each node -> data to the screen.
	//Purpose: to print the contents of the tree in Pre order to the screen

	void rfPostOrder(/* out */FunctionType2 visit,				//function for item to be passed for file printing
					 /* out */ofstream & outFile,				//file to be passed into visit
					 /* in */ node<ItemType>* & trav);			//location in tree
	//Pre: visit is a function that has been created in the class that takes an ItemRec and ofstream parameter,
	//	this function outputs each ItemType to a file.
	//Post: the tree is processed LRN outputting each node -> data to a file.
	//Purpose: to print the contents of the tree in Pre order to a file

	node<ItemType>* GetPrev(/* in */KeyType key,				//key to find parant node of
							/* in */node<ItemType>* & trav);	//location in tree
	//Pre: key contains a valid key in the list
	//Post: the parent node of key is returned
	//Purpose: to find the parent node of the key and return it to the client

	node<ItemType>* RightToNull(/* in */node<ItemType>* & trav);//location in tree
	//Pre: trav contains a valid location within the tree
	//Post: trav contains the inorder precurser of the original calling node
	//Purpose: To find the InOrder precurser of the original calling node

	int CountNodes(/* in */ node<ItemType>* & trav);			//location in tree
	//Pre: trav contains a valid location within the tree(initially root)
	//Post: the total number of nodes within the tree is returned
	//Purpose: to count the total number of nodes within the tree.

	node<ItemType>* VecToTree(/* in */vector<int>& values,		//contains values for tree
							  /* in */int lower,				//lower point in vector
							  /* in */int upper);				//higher point in vector
	//Pre: values contains values to be made into a tree, lower contains the lower point
	//	to be tested, upper contains the upper point to be tested
	//Post: mid is calculated and the node returned's data is set to values[mid]
	//Purpose: to build the tree from a vector complete to minimum hieght.

	void TreeToVec(/* out */vector<int>& values,				//holds values in tree
				   /* in/out */int& index,						//location in vector
				   /* in */node<ItemType>* & trav);				//location in tree
	//Pre: values contains an empty vector of CountNodes size, index contains
	//	the current location in the vector(0 initially), trav contains the 
	//	current location in the tree
	//Post: vector contains all the values in the tree
	//Purpose: to transfer all the values stored in the tree to a vector, for merging.

private:
	node<ItemType>* Allocate();//returns a new node, throws error if out of memory
	node<ItemType>* root;//root of tree
};
#include "BstClass.cpp"