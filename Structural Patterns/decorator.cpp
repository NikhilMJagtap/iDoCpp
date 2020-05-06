#include<iostream>

/*
	Sometimes we need to change the behaviour of an object at runtime. We need to change behaviour of
	only one object and not all objects of same class. Decorator pattern helps to solve this problem.

	Consider this simple scenario. We have some plain fries. We are eating plain fries at that time.
	When we put cheese on it, we are eating fries with cheese. This is change in behaviour of object
	and not the class because all the other Fries are still plain.
	We try to model this as follows. We make an abstract class Fries and concrete PlainFries class which 
	extends Fries, overrrides its eat function. We also have CheeseFries class which stores fries object
	and overrides the eat method. Now this is changing behaviour of eat function only. (For function
	which does not provide different behaviour, one should call function of fries object inside cheesefries
	object.)
	Finally, in main, I change behaviour of one of the objects.
	PS: this is different than @ decorator in python which is similar to annotations in java like @Override
*/

class Fries
{
public:
	virtual void eat() const = 0;
};

class PlainFries : public Fries
{
public:
	void eat() const override
	{
		std::cout << "Eating plain fries.\n";
	} 
};

class CheeseFries : public Fries
{
private:
	Fries* fries;
	std::string cheese;
public:
	CheeseFries(Fries* fries, std::string cheese)
	: fries(fries), cheese(cheese)
	{
	
	}
	void eat() const override
	{
		std::cout << "Eating fires with " << cheese << " cheese.\n";
	}
};

int main()
{
	// normal behaviour of objects
	Fries* fries = new PlainFries();
	Fries* another_fries = new PlainFries();
	fries->eat();
	fries->eat();
	// changing behaviout of only one object
	fries = new CheeseFries(fries, "Jalapeno");
	fries->eat();
	// this object's behaviour is not changed
	another_fries->eat();
	delete fries, another_fries;

}