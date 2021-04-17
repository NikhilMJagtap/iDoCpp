#include<iostream>
#include<vector>
/*
	A lot of softwares are event driven. An event in one object might trigger other objects. Observer pattern
	is helpful in order to solve this requirement. In observer pattern, an object (called as subject xD) 
	maintains a list of objects (called as observers) which are dependent on subject. An event in subject
	can trigger the event. Then a method of observer is called thus observer gets notified about the
	event just occured in subject. It makes the most sense to use observers in threads running in background
	but we are not doing that here. 
	Observer pattern makes it easier to solve the one-to-many dependency making them loosely coupled. 

	In this example, I have a Shop class which has some stock of items. One can purchase the item from
	stock and restock it. The stock is reduced and increased alongside. There is also supplier class.
	Here, shop is a subject and Suppliers are observer. Whenever the stock in shop goes below some
	threshold (member of shop class), all observers of that shop are notified by calling the notify method of 
	the observer. In the main function, a shop object is created and some suppliers are added to observe
	the shop object.

	IMPORTANT:
	Observer pattern is different that PubSub model and reactive programming.
	Reactive programming is out of the scope of this file but I am providing something very famous in this
	https://github.com/ReactiveX/RxCpp

	In observer pattern, subject is fully aware of the observers. It literally maintains the list of the
	observers. In PubSub, both subject and observer (subscribers) are independent. Both publishers and
	subscribers can be scaled on their own. Also, PubSub is more loosely coupled than observer. PubSub can
	be preferred easily over observer pattern if observer pattern makes your software components tightly
	coupled.
*/

class Supplier
{
private:
	std::string name;
public:
	Supplier(std::string name)
	: name(name) 
	{

	}
	~Supplier() = default;
	void notify()
	{
		std::cout << name << " is notified!\n";
	}
};

class Shop
{
private:
	int stock;
	std::string name;
	int threshold = 2;
	std::vector<Supplier*> observers;
public:
	Shop(std::string name)
	: name(name), stock(10)
	{

	}

	void purchase(int n)
	{
		if(stock < n)
		{
			std::cout << "Out of stock!\n";
			return;
		}
		stock -= n;
		std::cout << "Purchased!\n";
		if(stock <= threshold)
		{
			for(int i=0; i<observers.size(); ++i)
				observers.at(i)->notify();
		}
		
	}

	void observe(Supplier *supplier)
	{
		observers.push_back(supplier);
	}

	void restock(int n)
	{
		stock += n;
		std::cout << "Restocked!\n";
	}
};

int main()
{
	Shop *shop = new Shop("SuperMarkt");
	Supplier *supplier1 = new Supplier("Supplier One");
	Supplier *supplier2 = new Supplier("Supplier Two");
	shop->observe(supplier1);
	shop->observe(supplier2);
	shop->purchase(5);
	// no notifications yet
	shop->purchase(3);
	// notify should get called
	shop->restock(3);
	Supplier *supplier3 = new Supplier("Supplier Three");
	shop->observe(supplier3);
	shop->purchase(3);
	delete shop, supplier1, supplier2, supplier3;
	return 0;
}