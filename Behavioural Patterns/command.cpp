#include<iostream>

/*
	Command pattern is used to encapsulate all information required to trigger some event or call. This
	information can include functions, objects, etc.
	There are four terms associated with command pattern.
	- Command: Object which invokes method of reciever and contains receiver
	- Receiver: Object which does all the work when command is called
	- Invoker: Invoker is what starts the command
	- Client: Invoker is held by Client

*/

// command interface
class Command
{
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
};

// class reciever
class Light
{
public:
	Light() {}
	~Light() {}
	void turn_on()
	{
		std::cout << "Turned on light!\n";
	}
	void turn_off()
	{
		std::cout << "Turned off light!\n";
	}
};

// class invoker
class Switch
{
public:
	void run_command(Command *command)
	{
		std::cout << "Running command from Switch!\n";
		command->execute();
	}
};

// concrete command
class TurnOnCommand : public Command
{
private:
	Light *light;  // notice this command has s receiver object 
	// you can say this is aggregation
public:
	TurnOnCommand(Light *light) 
	: light(light)
	{

	}
	void execute()
	{
		light->turn_on();
	}
};

// concrete command
class TurnOffCommand : public Command
{
private:
	Light *light;
public:
	TurnOffCommand(Light *light)
	: light(light)
	{

	}
	void execute()
	{
		light->turn_off();
	}
};

int main()
{
	// creating light and commands
	Light *light = new Light();
	TurnOnCommand *on = new TurnOnCommand(light);
	TurnOffCommand *off = new TurnOffCommand(light);
	// creating switch
	Switch *s = new Switch();
	// running command to turn ligth on
	s->run_command(on);
	// can run off command similarly
	// s->run_command(off);
	delete light, on, off, s;
	return 0;
}