//Implementation File
//Author: Derek Gordon
//Date: May 1st, 2012
//Project: BstClass
//Purpose: 
//		To implement the binary search tree
//	with a class template to allow use with
//	multiple data types.
//	
//		This tree is ordered and does not  
//	allow multiple entries of the same key.  
//
//Assumptions: 
//	-The client will specify a structure with a data key.
//	
//	-The client will write a function that is to print the
//		contents of an ItemRec.  This function will be passed
//		as a parameter into an InOrder public method of the class
//
//	-The client will need to do the same above to also print to a file.
//
//	-The client will use try catch blocks on any methods that could throw and exception.
//
//Error Handling:
//	-Errors will be thrown as a class to be handled within the client
//	-Delete on Empty
//	-Retrieve on Empty
//	-OutofMemory on Allocate
//	-Not Found on Delete
//	-Not Found on Retrieve
//	-Duplicate Key on Insert


template <class ItemType>
struct node
{
	node<ItemType>* left;
	ItemType data;
	node<ItemType>* right;
};

/*****************************Constructors/Destructors*******************************/

template <class ItemType>
BstClass<ItemType>::BstClass()
{
	root = nullptr;
}//end constructor

template <class ItemType>
BstClass<ItemType>::~BstClass()
{
	rClear(root);
}//end destructor

template <class ItemType>
BstClass<ItemType>::BstClass(/* in */const BstClass<ItemType>& orig)	//class to copy
{
	root = nullptr;
	node<ItemType>* trav = orig.root;
	rCopy(root, trav);
}//end copy constructor

/*************************************IsEmpty***************************************/

template <class ItemType>
bool BstClass<ItemType>::IsEmpty()
{
	return (root == nullptr);
}//end IsEmpty

/*************************************IsFull***************************************/

template <class ItemType>
bool BstClass<ItemType>::IsFull()
{
	return false;
}//end IsFull

/*************************************Clear***************************************/

template <class ItemType>
void BstClass<ItemType>::Clear()
{
	rClear(root);
}//end Clear

template <class ItemType>
void BstClass<ItemType>::rClear(/* in */node<ItemType>* & trav)	//location in tree
{
	if (trav != nullptr)
	{
		rClear(trav->left);
		rClear(trav->right);
		delete trav;
		trav = nullptr;
	}//end if
}//end rClear

/***********************************Insert***************************************/

template <class ItemType>
void BstClass<ItemType>::Insert(/* in */ItemType newItem)	//item to be inserted
{
	rInsert(newItem, root);
}//end Insert

//protected
template <class ItemType>
void BstClass<ItemType>::rInsert(/* in */ItemType newItem,		//item to be inserted
								/* in */node<ItemType>* & trav)	//location to test for possible insertion
{
	if(trav == nullptr)//location for insertion
	{
		trav = Allocate();
		trav -> data = newItem;
	}//end if
	
	//given whether the key is greater than or less than current node
	//recurse left or right
	else if(trav -> data.key < newItem.key)
		rInsert(newItem, trav -> right);

	else if(trav -> data.key > newItem.key)
		rInsert(newItem, trav -> left);

	else
		throw DuplicateKey("Duplicate Key, Cannot Insert");
}//end rInsert

/***********************************Delete***************************************/

template <class ItemType>
void BstClass<ItemType>::Delete(/* in */KeyType key)		//item to be deleted
{
	if(!IsEmpty())
		rDelete(key, root);
	else
		throw DelOnEmpty("List Is Empty, Cannot Delete");
}//end Delete

//protected
template <class ItemType>
void BstClass<ItemType>::rDelete(/* in */KeyType key,			//item to be deleted
								/* in */node<ItemType>* & trav)	//location to test for key
{
	//where key should be
	if(trav == nullptr)
		throw NotFound("Key not in list, Cannot Delete");

	//given whether the key is greater than or less than current node
	//recurse left or right
	else if(trav -> data.key < key)
		rDelete(key, trav -> right);	//recurse right

	else if(trav -> data.key > key)
		rDelete(key, trav -> left);		//recurse left

	else //==
	{
		node<ItemType> * prev;
		//no children
		if(trav -> left == nullptr && trav -> right == nullptr)
		{
			delete trav;
			trav = nullptr;
		}//end if

		//one child
		else if(trav -> left != nullptr && trav -> right == nullptr ||
			trav -> left == nullptr && trav -> right != nullptr)
		{
			node<ItemType> * temp = trav;
			//left occupied
			if(trav -> left != nullptr)
			{
				prev = GetPrev(trav->data.key, root);
				if(prev == nullptr)//at root
				{
					trav = trav -> left;
					delete temp;
				}//end if

				else
				{
					//connect tree past trav
					if(prev -> left == trav)
						prev -> left = trav -> left;
					else
						prev -> right = trav -> left;
					
					delete trav;
					trav = nullptr;
				}//end else
			}//end if

			else
			{
				//get parent node
				prev = GetPrev(trav->data.key, root);
				if(prev == nullptr)//at root
				{
					trav = trav -> right;
					delete temp;	
				}//end if

				else
				{
					//connect tree past trav
					if(prev -> left == trav)
						prev -> left = trav -> right;
					else
						prev -> right = trav -> right;
					
					delete trav;
				}//end else
			}//end else
		}//end else if

		//two children
		else
		{
			//Find InOrder Recurser(highest value left of trav)
			node<ItemType>* delThis = trav;
			node<ItemType>* temp = RightToNull(trav -> left);

			prev = GetPrev(temp -> data.key, root);
			if(prev != nullptr)//not at root
			{
				//disconnect from tree
				if(prev -> left == temp)
					prev -> left = nullptr;
				else
					prev -> right = nullptr;

				//get the parent node
				prev = GetPrev(trav -> data.key, root);

				if(prev == nullptr)//at root
				{
					temp -> right = trav -> right;
			
					while(temp -> left != nullptr)
						temp = temp -> left;

					temp -> left = trav -> left;
					trav = temp;

					delete delThis;
				}//end if

				else //at root
				{
				
					if(prev -> left == trav)
						prev -> left = temp;
					else
						prev -> right = temp;
				

					temp -> right = trav -> right;
			
					while(temp -> left != nullptr)
						temp = temp -> left;

					temp -> left = trav -> left;

					delete trav;
				}//end else
			}//end if
		}//end else
	}//end else
}//end rDelete

/***********************************Find***************************************/

template <class ItemType>
bool BstClass<ItemType>::Find(/* in */KeyType key)			//key to be searched for
{
	return rFind(key, root);
}//end Find

//protected
template <class ItemType>
bool BstClass<ItemType>::rFind(/* in */KeyType key,				//key to be searched for 
							   /* in */node<ItemType>* & trav)	//location to test for key		
{
	//at end of tree
	if(trav == nullptr)
		return false;

	//given whether the key is greater than or less than current node
	//recurse left or right
	else if(trav -> data.key < key)
		return rFind(key, trav -> right);

	else if(trav -> data.key > key)
		return rFind(key, trav -> left);

	else //==
		return true;
	
}//end rFind

/***********************************Retrieve***************************************/

template <class ItemType>
ItemType BstClass<ItemType>::Retrieve(/* in */KeyType key)	//key to be searched and retrieved
{
	ItemType data;
	if(!IsEmpty())
		 data = rRetrieve(key, root);
	else
		throw RetOnEmpty("List Is Empty, Cannot Retrieve");
	return data;
}//end Retrieve

template <class ItemType>
ItemType BstClass<ItemType>::rRetrieve(/* in */KeyType key,				//key to be searched and retrieved
									   /* in */node<ItemType>* & trav)	//location to test for key
{
	if(trav == nullptr)
		throw NotFound("Key not in list, Cannot Retrieve");

	//given whether the key is greater than or less than current node
	//recurse left or right
	else if(trav -> data.key < key)
		rRetrieve(key, trav -> right);

	else if(trav -> data.key > key)
		rRetrieve(key, trav -> left);

	else //==
		return trav->data;

}//end rRetrieve

/***********************************PreOrder***************************************/

template <class ItemType>
void BstClass<ItemType>::PreOrder(/* out */FunctionType1 visit)	//function for item to be passed for printing
{
	rPreOrder(visit, root);
}//end PreOrder

template <class ItemType>
void BstClass<ItemType>::fPreOrder(/* out */FunctionType2 visit, //function for item to be passed for file printing
								  /* out */ofstream & outFile)	//file to be passed into visit
{
	rfPreOrder(visit, outFile, root);
}//end fPreOrder


//Protected
template <class ItemType>
void BstClass<ItemType>::rPreOrder(/* out */FunctionType1 visit,		//function for item to be passed for printing
								  /* in */node<ItemType>* & trav)	//location in Tree
{
	if (trav != nullptr)
	{
		visit(trav->data);
		rPreOrder(visit, trav->left);
		rPreOrder(visit, trav->right);
	}//end if
}//end rPreOrder

template <class ItemType>
void BstClass<ItemType>::rfPreOrder(/* out */FunctionType2 visit,		//function for item to be passed for file printing
									/* out */ofstream & outFile,		//file to be passed into visit
									/* in */ node<ItemType>* & trav)	//location in tree
{
	if (trav != nullptr)
	{
		visit(trav->data, outFile);
		rfPreOrder(visit, outFile, trav->left);
		rfPreOrder(visit, outFile, trav->right);
	}//end if
}//end rfPreOrder

/***********************************InOrder***************************************/


template <class ItemType>
void BstClass<ItemType>::InOrder(/* out */FunctionType1 visit)	//function for item to be passed for printing
{
	rInOrder(visit, root);
}//end InOrder

template <class ItemType>
void BstClass<ItemType>::fInOrder(/* out */FunctionType2 visit, //function for item to be passed for file printing
								  /* out */ofstream & outFile)	//file to be passed into visit
{
	rfInOrder(visit, outFile, root);
}//end fInOrder

//Protected
template <class ItemType>
void BstClass<ItemType>::rInOrder(/* out */FunctionType1 visit,		//function for item to be passed for printing
								  /* in */node<ItemType>* & trav)	//location in Tree
{
	if (trav != nullptr)
	{
		rInOrder(visit, trav->left);
		visit(trav->data);
		rInOrder(visit, trav->right);
	}//end if
}//end rInOrder

template <class ItemType>
void BstClass<ItemType>::rfInOrder(/* out */FunctionType2 visit,	//function for item to be passed for file printing
								   /* out */ofstream & outFile,		//file to be passed into visit
								   /* in */ node<ItemType>* & trav)	//location in tree
{
	if (trav != nullptr)
	{
		rfInOrder(visit, outFile, trav->left);
		visit(trav->data, outFile);
		rfInOrder(visit, outFile, trav->right);
	}//end if
}//end rfInOrder

/***********************************PostOrder***************************************/

template <class ItemType>
void BstClass<ItemType>::PostOrder(/* out */FunctionType1 visit)//function for item to be passed for printing
{
	rPostOrder(visit, root);
}//end PostOrder

template <class ItemType>
void BstClass<ItemType>::fPostOrder(/* out */FunctionType2 visit, //function for item to be passed for file printing
								  /* out */ofstream & outFile)	//file to be passed into visit
{
	rfPostOrder(visit, outFile, root);
}//end fPostOrder

//Protected
template <class ItemType>
void BstClass<ItemType>::rPostOrder(/* out */FunctionType1 visit,		//function for item to be passed for printing
								  /* in */node<ItemType>* & trav)	//location in Tree
{
	if (trav != nullptr)
	{
		rPostOrder(visit, trav->left);
		rPostOrder(visit, trav->right);
		visit(trav->data);
	}//end if
}//end rPostOrder

template <class ItemType>
void BstClass<ItemType>::rfPostOrder(/* out */FunctionType2 visit,		//function for item to be passed for file printing
									 /* out */ofstream & outFile,		//file to be passed into visit
									 /* in */ node<ItemType>* & trav)	//location in tree
{
	if (trav != nullptr)
	{
		rfPostOrder(visit, outFile,trav->left);
		rfPostOrder(visit, outFile, trav->right);
		visit(trav->data, outFile);
	}//end if
}//end rfPostOrder

/***********************************Operator=***************************************/

template <class ItemType>
void BstClass<ItemType>::operator=(/* in */const BstClass<ItemType> & orig)	//class to be copied
{
	rClear(root);
	node<ItemType>* trav = orig.root;
	rCopy(root, trav);
}//end operator=

template <class ItemType>
void BstClass<ItemType>::rCopy(/* in */node <ItemType>* & target,	//node getting the data
							   /* in */node <ItemType>* & orig)		//node sending the data
{
	if(orig != nullptr)
	{
		target = Allocate();
		target -> data = orig -> data;
		rCopy(target -> left, orig -> left);
		rCopy(target -> right, orig -> right);
	}//end if
}//end rCopy

/***********************************Operator+***************************************/

template <class ItemType>
BstClass<ItemType> BstClass<ItemType>::operator+(/* in */BstClass<ItemType> & rtOp)
{
	int index = 0;	//index of array
	int arrSize = (CountNodes(rtOp.root)) + (CountNodes(root));
	vector<int> values(arrSize);//create an array of total values in two trees
	BstClass<ItemType> add;

	//use inorder on both trees to get values into array
	TreeToVec(values, index, root);

	TreeToVec(values, index, rtOp.root);

	//index contains the position of the last number in list 0-index
	int length = index;

	//sort the values
	bool swap = true;	//if there is a swap need to check entire vector again for no swaps
	int temp;			//holds value that is getting swapped
	 for(int i = 1; (i <= length) && swap; i++)
     {
          swap = false;	//no swap yet
         for (int j=0; j < (length -1); j++)
         {
              if (values[j+1] < values[j])    
              { //values out of order... need to swap
                    temp = values[j];
                    values[j] = values[j+1];
                    values[j+1] = temp;
                    swap = true;		// indicates that a swap occurred.
               }//end if
          }//end for
     }//end for

	 for(int i = 0; i < (length -1); i++)
	 {
		 if(values[i] == values[i+1])
		 {//duplicate keys... delete and shuffle
			 for(int j = i; j < length - 1; j++)
				 values[j] = values[j+1];
			 length--;//decrement length for key deleted
		 }//end if
	 }//end for

	 //Insert the values in vector into the new tree
	 //maintaining lowest possible hieght
	 add.root = VecToTree(values, 0, length - 1);
	 return add;
			
}//end operator +

template <class ItemType>
int BstClass<ItemType>::CountNodes(/* in */ node<ItemType>* & trav)			//location in tree
{
	if(trav == nullptr)//at end of tree
		return 0;
	else
		return (CountNodes(trav -> left) + CountNodes(trav -> right) + 1);
}//end CountNodes

template <class ItemType>
void BstClass<ItemType>::TreeToVec(/* out */vector<int>& values,				//holds values in tree
								   /* in/out */int& index,						//location in vector
								   /* in */node<ItemType>* & trav)				//location in tree
{
	if(trav != nullptr)
	{
		//check left node and insert into vector
		TreeToVec(values, index, trav -> left);
		values[index] = trav -> data.key;
		index++;	//move to next position in vector
		TreeToVec(values, index, trav -> right);	//check right node
	}//end if
}//end TreeToVec

template <class ItemType>
node<ItemType>* BstClass<ItemType>::VecToTree(/* in */vector<int>& values,		//contains values for tree
											  /* in */int lower,				//lower point in vector
											  /* in */int upper)				//higher point in vector
{
	if(lower > upper)
		return nullptr;

	//calculate midpoint
	int mid= lower + (upper - lower) / 2;
	
	//place value in a new node
	node<ItemType>* newItem = Allocate();
	newItem -> data.key = values[mid];
	//find succeeding nodes
	newItem -> left = VecToTree(values, lower, mid-1);
	newItem -> right = VecToTree(values, mid+1, upper);
	return newItem;
}//end VecToTree

/***********************************GetPrev***************************************/

template <class ItemType>
node<ItemType>* BstClass<ItemType>::GetPrev(/* in */KeyType key,			//key to find parant node of
											/* in */node<ItemType>* & trav)	//location in tree
{
	//given whether the key is greater than or less than current node
	//check left or right for = key
	if(key < trav -> data.key)
	{
		if(trav -> left -> data.key == key)
			return trav;
		else
			GetPrev(key, trav -> left);
	}//end if

	else if(key > trav -> data.key)
	{
		if(trav -> right -> data.key == key)
			return trav;
		else
			GetPrev(key, trav -> right);
	}//end else if
	else
		return nullptr;//key being searched is at root
}//end GetPrev

/***********************************RightToNull***************************************/

template<class ItemType>
node<ItemType>* BstClass<ItemType>::RightToNull(/* in */node<ItemType>* & trav)	//location in tree
{
	if(trav -> right != nullptr)
		return RightToNull(trav -> right);
	else
		return trav;
}//end RightToNull

/***********************************Allocate***************************************/

template <class ItemType>
node<ItemType>* BstClass<ItemType>::Allocate()
{
	node<ItemType>* newNode;
	newNode = new node<ItemType>;

	if (newNode == nullptr)
		throw OutOfMem("Node Creation Failed, Program Terminating...");
	else
	{
		newNode->left = nullptr;
		newNode->right = nullptr;
		return newNode;
	}//end else
}//end Allocate