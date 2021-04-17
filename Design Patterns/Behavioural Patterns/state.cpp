#include<iostream>

/*
	Sometimes, we have to maintain a state of the object. The object can go from one state to another, and
	its behaviour depends on the state. For example, a process which is in pending state, will eventually
	go to computing and many other subsequent states.
	State design pattern makes this very easy to implement. We create multiple states whichever we need.
	The state interface or abstract class can be used to achieve it in better way. Then the object has a
	state member. Ideally, we should change the state of the object whenever we use some processing
	of that state. We can pass the object to the processing function and new state as well. Thus, the 
	object is processed and new state is assigned.
	In this example, consider a transaction, implemented as class Transaction. The transaction can be in some
	states, say Processing, Completed or Failed states. State interface is used for all the states
	ProcessingState, CompleteState, FailedState. Transaction by default goes into the processing state
	so the constructor of transaction takes the state. (Note that we can use flyweight pattern here
	to avoid making so many state objects paired with AbstractFactory pattern.)
	Process function of transaction calls the function of state. Thus, execution depends on the state
	of the object. We can implement it in a way that transaction;s state changes with the process calls.
	
*/

// state interface
class State
{
public:
	~State() = default;
	// function to process the state
	virtual void process() = 0;
	std::string state;
};

// a state for transaction
class ProcessingState : public State
{
public:
	ProcessingState() 
	{
		state = "Processing";
	}
	// process function specific to this state
	void process()
	{
		std::cout << "Processing ...\n";
	}
};

// a state for transaction
class CompleteState : public State
{
public:
	CompleteState() 
	{
		state = "Completed";
	}
	void process()
	{
		std::cout << "Completed...\n";
	}
};

// a state for transaction
class FailedState : public State
{
public:
	FailedState()
	{
		state = "Failed";
	}
	void process()
	{
		std::cout << "Failed...\n";
	}
};

// Transaction
class Transaction
{
private:
	// state of the transaction
	State* state;
public:
	Transaction(State* state)
	: state(state)
	{

	}

	// setting the state of transaction
	void set_state(State* new_state)
	{
		state = new_state;
	}

	// processing based on the state
	void process()
	{
		state->process();
	}

	void show()
	{
		std::cout << "This transaction is in " << state->state << " state!\n";
	}
};

int main()
{
	State *s = new ProcessingState();
	Transaction *trxn = new Transaction(s);
	trxn->process();
	trxn->show();
	State *com = new CompleteState();
	trxn->set_state(com);
	trxn->process();
	trxn->show();
	return 0;
}