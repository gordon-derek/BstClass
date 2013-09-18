//Specification File
//Author: Derek Gordon
//Date: November 14, 2011
//Modified: March 28,2012
//			April 22, 2012
//			May 8th, 2012
//	- classes modified to handle possible exceptions
//		to be thrown by a Binary Search Tree
//Purpose: To handle an exception that
//	is thrown by another class. The
//	exception will be thrown as a class
//	the class will then be caught by the
//	client that is testing the piece of code
//
//Assumptions:
//	The Exception thrown is a valid class.

#include <string>
using namespace std;

class DelOnEmpty
{
public:
	DelOnEmpty(){}//default constructor, does nothing
	DelOnEmpty(string theMessage) : message(theMessage){}
	string GetMessage() const {return message;}

private:
	string message;
};//end DelOnEmpty

class NotFound
{
public:
	NotFound(){}//default constructor, does nothing
	NotFound(string theMessage) : message(theMessage){}
	string GetMessage() const {return message;}

private:
	string message;
};//end NotFound

class DuplicateKey
{
public:
	DuplicateKey(){}//default constructor, does nothing
	DuplicateKey(string theMessage) : message(theMessage){}
	string GetMessage() const {return message;}

private:
	string message;
};//end DuplicateKey
	
class RetOnEmpty
{
public:
	RetOnEmpty(){}//default constructor, does nothing
	RetOnEmpty(string theMessage) : message(theMessage){}
	string GetMessage() const {return message;}
private:
	string message;
};//end RetOnEmpty
	
class OutOfMem
{
public:
	OutOfMem(){}//default constructor, does nothing
	OutOfMem(string theMessage) : message(theMessage){}
	string GetMessage() const {return message;}
private:
	string message;
};//end OutOfMem
	

	