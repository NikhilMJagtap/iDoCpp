#include<iostream>

/*
	Just like bridge connects two ends, Bridge Pattern connects two things. The first one is a class,
	and the second one is its implementation. Often, the class declartion changes and so does it's 
	implementation. Now we cannot write these codes again and again. That is the main basis of patterns.
	So we use this pattern, which binds class to its implementation. 
	In this example, we have a class Server and its implementation i.e. ServerFunctions may change over. Instead of writing 
	that in class definition, we create another interface of implementation. We create abstract 
	implementations and then bridge the appropriate implementation with its class.

	PS:
	An important concept to note is pimpl (pointer to implementation in C++). If there is only one 
	implementation and we use bridge, it becomes similar to pimpl. 
*/

// interface for our ServerFunctions
class ServerFunctions
{
public:
	virtual ~ServerFunctions(){}
	virtual void send_response() = 0;
};

// Concrete ServerFunction
class ServerFunctionsV1 : public ServerFunctions
{
public:
	void send_response()
	{
		std::cout << "This is version 1 of server.\n";
	}
};

// Another Concrete ServerFunction
class ServerFunctionsV2 : public ServerFunctions
{
public:
	void send_response()
	{
		std::cout << "This is version 2 of server.\n";
	}
};


class Server
{
private:
	ServerFunctions* implementation;
public:
	Server(ServerFunctions* impl)
	: implementation(impl)
	{

	}
	void send_response()
	{
		implementation->send_response();
	}
};


int main()
{
	// using server with ServerFunctionsV1
	ServerFunctions* sf1 = new ServerFunctionsV1();
	Server* server1 = new Server(sf1);
	server1->send_response();

	// using server with ServerFunctionsV1
	ServerFunctions* sf2 = new ServerFunctionsV2();
	Server* server2 = new Server(sf2);
	server2->send_response();

	// clean up
	delete sf1, server1, sf2, server2;
	return 0;
}