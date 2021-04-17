#include<iostream>

/*
	Visitor pattern allows us to add functions (methods) to classes without changing the code of classes.
	That is, we can make different functions on different classes. And, add virtual functions to family of
	classes, without modifying classes. 
	The actual use of visitor patterns is tough to visualise. It is used when the language needs multiple
	dispatch to dynamically dispatch during run time. In multi-dispatch, function is chosen at run time
	based on type and arguments. Function "wash()" in class "car" depends on type of "car". But it can
	be made dependent of arguments passed to "wash()".
	Function dispatch is by only one parameter in single dispatch. 
	In the example below, there is an Item class, Milk, Fruit and Bread which are all derived from Item.
	The discount on these items depends on the item itself. Thus, we can simply write overloaded function
	of the discount in the Discounter class. The first dispatch call is made when discount is called.
	Appropriate function is selected for the second dispatch.
	Thus, we can pass any Item to any AbstractDiscounter and the correct discount function is called.
	To read more about this, I will recommend this stackoverflow thread/post
	https://stackoverflow.com/questions/3262811/what-is-single-and-double-dispatch
*/

class Item;
class Milk;
class Fruit;
class Bread;

class AbstractDiscounter
{
public:
	virtual void discount(Milk *milk) = 0;
	virtual void discount(Fruit *fruit) = 0;
	virtual void discount(Bread *bread) = 0;
};

class Discounter : public AbstractDiscounter
{
public:
	void discount(Milk *milk)
	{
		std::cout << "Discounting milk...\n";
	}
	void discount(Fruit *fruit)
	{
		std::cout << "Discounting fruit...\n";
	}
	void discount(Bread *bread)
	{
		std::cout << "Discounting bread...\n";
	}
};

class Item
{
public:
	virtual void discount(AbstractDiscounter *abd) = 0;
};

class Milk : public Item
{
public:
	void discount(AbstractDiscounter *abd)
	{
		abd->discount(this);
	}
};

class Fruit : public Item
{
public:
	void discount(AbstractDiscounter *abd)
	{
		abd->discount(this);
	}
};

class Bread : public Item
{
public:
	void discount(AbstractDiscounter *abd)
	{
		abd->discount(this);
	}
};

int main()
{
	Item *milk = new Milk();
	Item *fruit = new Fruit();
	Item *bread = new Bread();

	AbstractDiscounter *discounter = new Discounter();
	milk->discount(discounter);
	fruit->discount(discounter);
	bread->discount(discounter);
	delete milk, fruit, bread, discounter;
	return 0;
}