#include<iostream>

class State
{
public:
	~State() = default;
	virtual void process() = 0;
	std::string state;
};

class ProcessingState : public State
{
public:
	ProcessingState() 
	{
		state = "Processing";
	}
	void process()
	{
		std::cout << "Processing ...\n";
	}
};

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

class Transaction : public State
{
private:
	State* state;
public:
	Transaction(State* state)
	: state(state)
	{

	}

	void set_state(State* new_state)
	{
		state = new_state;
	}

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