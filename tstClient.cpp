//FileName : tstClient.cpp
//Project : BstClass
//Author : Derek Gordon
//Date : May 3rd, 2012
//Purpose : This file is designed to test
//	all the methods of the BstClass to 
//	find any imperfections or errors within the class.
//
//Input: 
//	-There is no user input in the test client
//
//Processing:
//	-The client inserts random numbers into BstClass to 
//	test its ability to handle insertions and maintain order.
//	The client also tests for duplicate key entries, calling
//	methods that would require a find before them without a
//	find.  Operators are tested to be functional.
//
//Output:
//	-all output is printed both to the screen and to a file
//	which is declared as constant FILENAME.
//
//Assumptions:
//	
//
//Error Handling:
//	-The client trys and methods that may throw an exception.
//		Then catches the exception and outputs a message to the screen.
//  -Exceptions that should be caught(class to catch)-
//	-Delete on Empty(DelOnEmpty())
//	-Retrieve on Empty(RetOnEmpty())
//	-OutofMemory on Allocate(OutOfMem())
//	-Not Found on Delete(NotFound())
//	-Not Found on Retrieve(NotFound())
//	-Duplicate Key on Insert(DuplicateKey())

typedef int KeyType;
struct ItemRec
{
	KeyType key;
};//end struct

#include <fstream>	//for file i/o
#include <iostream>	//for screen i/o
using namespace std;

#include "BstClass.h"//binary search tree

//file to write to
const string FILENAME = "tree.out";

void PrintScreen(/* in */ItemRec&);	//item being returned from Order
//	- takes the ItemRec returned by one of the Order methods
//		and outputs its key to the screen.
void PrintFile(/* in */ItemRec& item,		//item being returned from fOrder
			   /* out */ ofstream& file);	//file to print to
//	- takes the ItemRec returned by one of the Order methods
//		and outputs its key to a file.

void main()
{
	BstClass<ItemRec> test;
	ItemRec data;
	ofstream outFile;

	outFile.open(FILENAME);

	//Test order of many numbers
	outFile << " Inserted " << endl;
	for( int i = 0; i < 100; i++)
	{
		try
		{
			data.key = rand() % 500;
			test.Insert(data);
			outFile << data.key << endl;
		}//end try
		catch(DuplicateKey exc)
		{
			cout << exc.GetMessage() << endl;
		}//end catch
	}//end for

	//should be in binary tree
	if(test.Find(169))
		cout << "169 Found!" << endl;

	//not in tree
	if(test.Find(-42))
		cout << "Silly Boy -42 is not in tree" << endl;
	else
		cout << "GOOD!" << endl;

	//item in list
	data.key = 350;
	try
	{
		test.Delete(350);
		cout << " 350 Deleted" << endl;
	}//end try
	catch(DelOnEmpty exc)
	{cout << exc.GetMessage() << endl;}//end catch
	catch(NotFound exc)
	{cout << exc.GetMessage() << endl;}//end catch

	//not in list
	try
	{
		test.Delete(-42);
		cout << " BAD! " << endl;
	}//end try
	catch(DelOnEmpty exc)
	{cout << exc.GetMessage() << endl;}//end catch
	catch(NotFound exc)
	{cout << exc.GetMessage() << endl;}//end catch

	//Test Printing of Tree
	cout << "InOrder" << endl;
	test.InOrder(PrintScreen);
	cout << endl << "PreOrder" << endl;
	test.PreOrder(PrintScreen);
	cout << endl << "PostOrder" << endl;
	test.PostOrder(PrintScreen);

	//test file output
	outFile << endl << "InOrder" << endl;
	test.fInOrder(PrintFile, outFile);
	outFile << endl << "PreOrder" << endl;
	test.fPreOrder(PrintFile, outFile);
	outFile << endl << "PostOrder" << endl;
	test.fPostOrder(PrintFile, outFile);

	//clear contents of tree
	test.Clear();

	//test few numbers operator= so on
	data.key = 50;
	test.Insert(data);
	data.key = 25;
	test.Insert(data);
	data.key = 75;
	test.Insert(data);

	cout << endl << "InOrder" << endl;
	test.InOrder(PrintScreen);
	outFile << endl << "InOrder" << endl;
	test.fInOrder(PrintFile, outFile);

	//test copy constructor/operator=
	BstClass<ItemRec> copy(test);

	cout << endl << "InOrder--copy" << endl;
	copy.InOrder(PrintScreen);
	outFile << endl << "InOrder--copy" << endl;
	copy.fInOrder(PrintFile, outFile);

	//should throw exception
	try
	{
		copy.Retrieve(40);
		cout << " BAD! " << endl;
	}//end try
	catch(RetOnEmpty exc)
	{cout << exc.GetMessage() << endl;}//end catch
	catch(NotFound exc)
	{cout << exc.GetMessage() << endl;}//end catch
	
	//used for initial testing of count nodes
	//cout << test + copy << endl;
	
	//test operator + with two of the same trees
	cout << endl << "add = test + copy(two same trees)" << endl;
	outFile << endl << "add = test + copy(two same trees)" << endl;
	BstClass<ItemRec> add = test + copy;
	add.InOrder(PrintScreen);
	add.fInOrder(PrintFile, outFile);

	//Test with no duplicate keys
	cout << endl << "add = test + copy(no similar values)" << endl;
	outFile << endl << "add = test + copy(no similar values)" << endl;
	test.Clear();
	copy.Clear();
	for(int i = 0; i < 25; i++)
	{
		try
		{
			data.key = rand() % 75;
			test.Insert(data);
			data.key = (rand() % 75) + 120;
			copy.Insert(data);
		}//end try
		catch(DuplicateKey exc)
		{cout << exc.GetMessage() << endl;}//end catch
	}//end for
	add = test + copy;
	add.InOrder(PrintScreen);
	add.fInOrder(PrintFile, outFile);

	//test with some duplicate keys
	cout << endl << "add = test + copy(some similar values)" << endl;
	outFile << endl << "add = test + copy(some similar values)" << endl;
	test.Clear();
	copy.Clear();
	data.key = 75;
	test.Insert(data);
	data.key = 50;
	test.Insert(data);
	for(int i = 0; i < 15; i++)
	{
		try
		{
			data.key = rand() % 100;
			test.Insert(data);
			data.key = (rand() % 100) + 50;
			copy.Insert(data);
		}//end try
		catch(DuplicateKey exc)
		{cout << exc.GetMessage() << endl;}//end catch
	}//end for

	add = test + copy;
	add.InOrder(PrintScreen);
	add.fInOrder(PrintFile, outFile);

	outFile.close();
}//end main

/******************************************************************/

//Pre: item contains a valid ItemRec returned from one of the Order
//	methods in BstClass
//Post: the keytype key of item is printed to the screen
//Purpose: To take the ItemRec returned and print it's key to the screen
void PrintScreen(/* in */ItemRec & item)	//item being returned from Order
{
	cout << item.key << endl;
}//end PrintScreen

/******************************************************************/

//Pre: item contains a valid ItemRec returned from one of the fOrder
//	methods in BstClass
//Post: the keytype key of item is printed to a file
//Purpose: To take the ItemRec returned and print it's key to a file
void PrintFile(/* in */ItemRec& item,		//item being returned from fOrder
			   /* out */ ofstream& file)	//file to print to
{
	file << item.key << endl;
}//end PrintFile