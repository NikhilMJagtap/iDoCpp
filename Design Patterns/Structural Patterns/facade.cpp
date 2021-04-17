#include<iostream>

/*
	Facade pattern literally does what facade means. 
	Consider a complex system which has many subsystems. We cannot give access of all these system to client
	directly. It does not only complicate things, but also overloads our client.
	One good rule is to keep things simple on client's side and hide all things on our end. That is what facade
	pattern can do.
	Consider this example of wending machine. Wending machine is a complex system whatever you say. It has 
	coin system, item selection, dispatch, alert and what not. But should we create a lever for buyer to
	dispatch the object? Of course not. We should hide it. In this example, I have shown some simple sub
	systems of wending machine and then there is this FacadeWendingMachine which is accessed by client.
*/

// there are so many subsystems inside a wending machine but I am showing only a dew.

class CoinSystem
{
	// all the work of coin system
public:
	bool is_valid_coin(int a)
	{
		// should check coin is real or no using weight and shape
		return a == 5 ? true : false;
	}
};

class DispatchSystem
{
	// All the work of dispatch system
public:
	void dispatch(std::string item)
	{
		std::cout << "Dispatched " << item << std::endl;
	}
};

class BillingSystem
{
	// Billing system does a lot of work
public:
	void print_bill()
	{
		std::cout << "Printing bill.\n";
	}
};

// and a lot of mini system wending machine might have

class FacadeWendingMachine
{
private:
	// all systems of machine
	BillingSystem *bs;
	CoinSystem *cs;
	DispatchSystem *ds;
public:
	FacadeWendingMachine()
	{
		bs = new BillingSystem();
		cs = new CoinSystem();
		ds = new DispatchSystem();
	}
	~FacadeWendingMachine()
	{
		delete bs, cs, ds;
	}
	void enter_coin(int a)
	{
		if(cs->is_valid_coin(a))
		{
			ds->dispatch("selected item");
			bs->print_bill();
		}
	}
	// some more functions of facade
	void select_item() {}
	void show_item_list() {}
	void alert_buyer() {}
	void process_transaction() {}
};

int main()
{
	FacadeWendingMachine *facade = new FacadeWendingMachine();
	facade->enter_coin(5);
	delete facade;
	return 0;
}