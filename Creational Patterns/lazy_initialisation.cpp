#include<iostream>
#include <map>

/*
	Lazy initialisation is a way of initialising object, allocating memory or computing a value, only at the
	time it is required or requested, not before that. Suppose you have some object which uses a stack for some
	operation. Now, initialising that stack as soon as the object is created is un-necessary. That operation
	might never get called. Thus, in lazy initialisation, we initialise that stack just when function doing
	that operation is called. 
	Another example would be a singleton pattern with lazy init. We don't initialise the instance and create
	it only when get_instance is called for the first time. It is very common in resource intensive tasks.
	In this example, we have a book class and a map of books. We create that book only when it is required
	instead of creating all the books inside constructor or declaration of library.
*/

class Book
{
private:
	std::string name;
	Book(std::string name_) : name(name_) {std::cout << "Book created!\n";}
public:
	static Book* get_book(std::string name_);
};

std::map<std::string, Book*> library;

Book* Book::get_book(std::string name_)
{
	// if book not in libraryy
	if(library.find(name_) == library.end())
	{
		// create that book and insert in library.
		Book* book = new Book(name_);
		library[name_] = book;
		return book; 
	} else 
	{
		return library[name_];
	}
}

int main()
{
	// creating some books.
	Book* book1 = Book::get_book("Storm of Swords");
	Book* book2 = Book::get_book("Dance of Dragons");
	Book* book3 = Book::get_book("Storm of Swords");
	// notice that book constructor will be called only twice, and not thrice
	// You can also check that book 1 and 3 are same objects
	// if(book1 == book3)
	// 	std::cout << "Same book objects\n";
	delete book1;
	delete book2;
	delete book3;
}