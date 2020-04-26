#include<iostream>
#include<map>
/*
	If singleton exists, there should be multiton, right?
	Multiton class allows us to have multiple named instances of a class. So there is not exactly one single
	instance, but for one name, there is only one instance.
	We are building on the previous example of singleton class. We need DatabaseManager instance, say. But we need
	one instance for each type. We have 3 types (say) SQL, NoSQL and ObjectOriented.
	We create a map which can hold instance of that class for that type. If not found, we create and insert the
	instance into map. Else, we return the previous instance only.

	Multiton class gives a great way to deal with multiple but still unique and singleton objects. (in the sense
	that each object of multiton class is only one instace for that key or name). But just like Singleton,
	it makes unit testing very painful. It becomes single source to get objects, but also a source of memory
	leak. 
	A memory leak might happen on line 71 of this program, so be aware of that :)

*/

// enum for types of dbms
enum types {
	SQL,
	NoSQL,
	ObjectOriented
};

// our multiton databasemanager class
class DatabaseManager
{
private:
	// private instaces stored in map
	static std::map<types, DatabaseManager*> instances;
	types type;
	// private constructor
	DatabaseManager(types t)
	: type(t)
	{

	}
public:
	// public and static method to get instances
	static DatabaseManager* get_instance(types type)
	{
		if(instances.find(type) == instances.end())
		{	
			DatabaseManager* instance = new DatabaseManager(type);
			instances[type] = instance;
		}
		return instances[type];
	}
	// all other methods of DatabaseManager like read write ... 
	void run()
	{
		std::cout << "This is " << type << " instance\n";
	}
};

// init map of instances
std::map<types, DatabaseManager*> DatabaseManager::instances;

// runner
int main()
{
	types t1 = SQL, t2 = NoSQL, t3 = ObjectOriented;
	DatabaseManager* db1 = DatabaseManager::get_instance(t1);
	DatabaseManager* db2 = DatabaseManager::get_instance(t2);
	DatabaseManager* db3 = DatabaseManager::get_instance(t3);
	db1->run();
	db2->run();
	db3->run();
	types t4 = SQL, t5 = ObjectOriented;
	DatabaseManager* db4 = DatabaseManager::get_instance(t4);
	DatabaseManager* db5 = DatabaseManager::get_instance(t5);
	db4->run();
	db5->run();
	delete db1, db2, db3;
	// we should not do this cause db1 instance is already delete. Thus, it may produce memory leaks
	// db4->run();
	// db5->run();
	delete db4, db5;
}