#include<iostream>
#include<map>
#include<vector>

/*
	If we have a class which is inside another class (i.e. the class is member of another class), then 
	whenever we create an object of outer class, we create an object of inner class. Now what is the problem
	with this behaviour? Consider this example. We are making an ordering system for Pizzas. We have Pizza object
	and Topping object. We store topping objects inside Pizza. If we make topping object everytime we create new
	Pizza object is created or topping is added into Pizza, we are certainly gonna run out of memory.
	Instead, we can create Topping objects and SHARE them with all the Pizza objects. We need Topping objects just
	to store. Thus we don't need to change them and hence they can be shared among Pizza objects.
	In this example, I use multiton pattern for Topping so I can share them among Pizzas. Then inside Pizza 
	object, I store a vector of Topping objects. Whenever a toppping is added, I get instance of Topping from
	multiton class and just push it in toppings vector of that pizza. Thus, we can save a lot of memory for
	storing topping objects.
*/

class Topping
{
private:
	std::string topping;
	Topping(std::string topping)
	: topping(topping)
	{

	}
	static std::map<std::string, Topping*> toppings;
public:
	static Topping* get_topping(std::string toping_name)
	{
		if(toppings.find(toping_name) == toppings.end())
		{
			toppings[toping_name] = new Topping(toping_name);
		}
		return toppings[toping_name];
	}
	std::string show()
	{
		return topping;
	}
};

class Pizza
{
private:
	std::vector<Topping*> toppings;
public:
	Pizza(){}
	~Pizza(){}
	void add_topping(std::string topping)
	{
		toppings.push_back(Topping::get_topping(topping));
	}
	void show_topping()
	{
		std::cout << "Toppings => ";
		for(int i=0; i<toppings.size(); ++i)
		{
			std::cout << toppings.at(i)->show() << ", ";
		}
		std::cout << std::endl;
	}
};

std::map<std::string, Topping*> Topping::toppings;

int main()
{
	Pizza *p = new Pizza();
	p->add_topping("Pepperoni");
	p->add_topping("Mushrooms");
	p->add_topping("Extra Cheese");
	p->show_topping(); 
	Pizza *p1 = new Pizza();
	p1->add_topping("Extra Cheese");
	p1->show_topping(); 
	return 0;
}