#include<iostream>

/*
	Front contoller are very common used in web applications. In this, a single component is responsible
	for processing the calls to applications or requests in terms of web. This becomes like a bottleneck for
	system. Everything passes through the front controller. 
	In this example, we have a client system and an admin system. Admin can ship orders and client can add orders
	Now, front controller is what which redirects these calls to concerende system. Also, Auth class has auth
	static function which checks caller is admin or client. Of course, there will be database to check it xD
	You might find front controller same as facade pattern. There is nothing wrong it, they are quite similar at
	first glance. But actually they are not.
	Front contoller is used to perform the standard behaviour for each request. Like the auth function we have in
	this example. Facade, on other hand, is used to hide complexity. Facade should be as simple as possible and
	with minimal to none logic. 
	
*/

class ClientSystem
{
public:
	ClientSystem() {}
	~ClientSystem() {}
	void start_session()
	{
		std::cout << "Started client session.\n";
	}
	void add_order()
	{
		std::cout << "Client added order.\n";
	}
};

class AdminSystem
{
public:
	AdminSystem() {}
	~AdminSystem() {}
	void ship_order()
	{
		std::cout << "Admin shipped order.\n";
	}
	void start_session()
	{
		std::cout << "Started admin session.\n";
	}
};

class Auth
{
public:
	static bool auth(std::string name)
	{
		if(!name.compare("admin"))
			return true;
		else
			return false;
	}
};

class FrontController
{
private:
	ClientSystem *cs;
	AdminSystem *as;
public:
	FrontController() 
	{
		cs = new ClientSystem();
		as = new AdminSystem();
	}
	~FrontController() 
	{
		delete cs, as;
	}
	void start_session(std::string name)
	{
		if(Auth::auth(name))
			as->start_session();
		else
			cs->start_session();
	}
	void add_order(std::string name)
	{
		if(Auth::auth(name))
			std::cout << "You are admin. Cannot add order.\n";
		else
			cs->add_order();
	}
	void ship_order(std::string name)
	{
		if(Auth::auth(name))
			as->ship_order();
		else
			std::cout << "You are client. Cannot ship order.\n";
	}
	// some more functions for front controller
};

int main()
{
	FrontController *fc = new FrontController();
	fc->start_session("admin");
	fc->ship_order("admin");
	fc->start_session("client");
	fc->add_order("client");
	fc->ship_order("client");
	delete fc;
	return 0;
}