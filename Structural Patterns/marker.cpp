#include<iostream>

/*
	Marker interface is much much famous in Java than C++. Serializable or Cloneable are examples. In Java,
	marker interfaces can be redundant today cause we have annotations.
	Marker interface is an empty interface which works as a metadata to the class which implements marker.
	Thus they allow us to add metadata to the objects at runtime.

*/

class Mark
{
public:
	virtual ~Base() {}
};

class CheckedBox : public Mark
{
public:
	CheckedBox(){}
	~CheckedBox(){}
	// all other methods of CheckedBox
};

int main()
{
	// creating objects of checked box
	// To system it is very clear that CheckedBox objects are marked with Mark and hence certain type of operation
	// is allowed or not allowed to that object at runtime.
	CheckedBox *cb = new CheckedBox();
	// do operations which are allowed for marked objects
	delete cb;
}