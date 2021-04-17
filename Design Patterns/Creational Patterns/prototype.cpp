#include<iostream>

/*
	Before getting into a pattern, let us understand the prototype first. Prototype is an early model or sample 
	of a product on which the products are iterated and developed. 
	In many cases, creating objects is very expensive. But it is very easy to clone them, just copy them.
	Prototype pattern does exactly same thing with clone() function.
	Let us assume that creating a prototype object in this example is very expensive. So we create a clone method
	in concrete prototype class. There, we can easily create copies of this prototype we have already.
	Thus, we copy objects. To change attributes, we need to change them for new prototype objects.
*/

class Prototype
{
protected:
	std::string name;
public:
	Prototype(std::string name)
	: name(name)
	{

	}
	void show()
	{
		std::cout << "This is prototype " << name << std::endl;
	}
	void change_name(std::string name)
	{
		this->name = name;
	}
	virtual Prototype* clone() = 0;
};

class ConcretePrototype : public Prototype
{		
public:
	ConcretePrototype(std::string name)
	: Prototype(name)
	{

	}

	Prototype* clone()
	{
		return new ConcretePrototype(*this);
	}
};

class PrototypeFactory
{
private:
	ConcretePrototype* prototype;
public:
	PrototypeFactory()
	{
		prototype = new ConcretePrototype("default_product");
	}

	Prototype* create_prototype()
	{
		return this->prototype->clone();
	}
};

int main()
{
	PrototypeFactory* prototype_factory = new PrototypeFactory();
	Prototype* p1 = prototype_factory->create_prototype();
	p1->change_name("Product-v1");
	p1->show();
	Prototype* p2 = prototype_factory->create_prototype();
	p2->change_name("Product-v2");
	p2->show();
	// these objects are not same in memory. They are just clones
	if(p1 == p2)
		std::cout << "Same objects";
	return 0;
}