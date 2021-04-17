#include<iostream>

/*
	Dependency injection, is a big task on its own. Some objects, are dependent on other objects. They are 
	called as dependencies of that object. We can create those objects' dependencies in the constructor of
	that object. But this, literally binds the object to those dependencies and cannot be change easily.
	Dependency injection in simple terms is -
		- Decoupling the dependencies and the dependent objects
		- Injecting the dependencies in the object when required
	Now we have some terms in this. Serivce, client and injector. A client is the one which needs or has some
	dependencies. These dependencies are service/s. The code which will supply or inject dependencies is injector.
	An interface is used to define how services can be used.
	A good analogy I found on wikipedia is this -
	service - an electric, gas, hybrid, or diesel car
	client - a driver who uses the car the same way regardless of the engine
	interface - automatic, ensures driver does not have to understand engine details like gears
	injector - the parent who bought the kid the car and decided which kind

	A lot of heavy lifting of this is done by a framework, usually. For example Spring and Guice for Java.
	One such good framework for C++ is Fruit by Google. Boost DI is another good one.

	A scenario here is :
	We have a computer class (again) which has some dependencies. One such dependency is our keyboard.
	Usually, you will create a Computer class and then create a keyboard object right inside the constructor
	of computer. But this just binds keyboard class to Computer class. This is tight coupling which is not so
	great.
	Instead, we pass a keyboard object to constructor of computer. Setter method can be used as well.
*/

class Keyboard
{
public:
	virtual void type() = 0;
	virtual ~Keyboard() = default;
};

class MembraneKeyboard : public Keyboard
{
public:
	void type()
	{
		std::cout << "Membran ekeyboarf is s osticky!!\n";
	}
};


class MechanicalKeyboard : public Keyboard
{
public:
	void type()
	{
		std::cout << "Mechanical keyboard is better, no?\n";
	}
};

class Computer
{
private:
	Keyboard* keyboard = nullptr;
public:
	Computer(Keyboard* k)
	: keyboard(k)
	{

	}

	void needs_input()
	{
		if(keyboard == nullptr)
		{
			throw std::invalid_argument("No keyboard attached.");
		}
		else 
		{
			keyboard->type();
		}
	}

	void change_keyboard(Keyboard* k)
	{
		this->keyboard = k;
	}
};

int main()
{
	// creating dependencies
	Keyboard* k = new MembraneKeyboard();
	Keyboard* mk = new MechanicalKeyboard();
	// injecting them
	Computer* comp = new Computer(k);
	comp->needs_input();
	// injecting dependencies
	comp->change_keyboard(mk);
	comp->needs_input();
	delete k, mk, comp;
}