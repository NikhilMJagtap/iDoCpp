#include<iostream>
#include<vector>
/*
	In design patterns, iterator is used to traverse a container and access its elements. The main advantage of
	iterator pattern is that it decouples algorithm from container.
	In C++, iterators are implemented using pointers. We call it "iterator concept" in C++ but it's a same thing.
	Iterators in C++ can be thought as an abstraction of pointers. 
	Iterators in Java are different. We implement next() and hasNext() methods (functions of Java '_' )
	and return Iterator<String> in constructor of iterator. Now most of the containers support iterators in STL
	of C++ except Stack, Queue and Priority Queue. These iterators can be Bidirectional, random access, forward, 
	input and output. Refer cppreference to read about it.

	For comparing iterator and other ways like simple for look, I will just link a post here
	https://stackoverflow.com/questions/14373934/iterator-loop-vs-index-loop

	You should use iterators when you are writing a generic code, container type might change or writing template
	code. It will be wrong to say that iterators are faster than other methods but 

*/

/*
	I cannot stress this enough:
	This cpp file was not needed. I added this cause I cannot say that this repo as iteartor example and not 
	put any code for it.
	Here is my 10 lines of code.
*/

int main()
{	
	// using iterator in vector
	std::vector<int> v = {1,2,3,4,5};
	std::vector<int>::iterator it;
	for(it = v.begin(); it != v.end(); ++it)  // mind this ++it
	{
		std::cout << *it << "\n";
	}
	// a better way is
	for(auto i = v.begin(); i != v.end(); ++i)
		std::cout << *i << "\n";
	return 0;
}