#include<iostream>

/*
	This pattern is very common. Many people are using it (you might be using this as well!) but are not aware
	of its name. The singleton pattern means that there can be only on object of a class. Even if there is a way
	to create new object, the same object is returned instead of new object. 
	Now let us come back to use case of this singleton class. You might recall that in Factory and AbstractFactory
	example, we can create as many factories as we want. But there is only one factory needed. The same factory 
	object can do a lot of work for us. That is why, almost 100% of the time, Factories are implemented using
	singleton. Even Facade pattern is often singleton.

	Consider a database system. We have a database manager class which can do all the writing and reading to DB.
	Now, we don't want multiple managers to be created as it will lead to well known issues in DBMS and bread ACID
	properties of DB. Thus, we implement singleton pattern for DatabaseManager class. There will be only one instance
	of that class giving us some room to avoid aforementioned cases of DB failure.

	Now, I will be adding Factory example as singleton as well. One should (mostly if not always) use singleton
	pattern in Factory and AbstractFactory. It is almost a thumb rule in my opinion.
	
*/


// Database manager class which will be singleton
class DatabaseManager
{
// First of all, we want to create a constructor for this class and make it private.
// This way, we make sure that only this class can create object of this class.
private:
	DatabaseManager()
	{
		std::cout << "Creating DatabaseManager object..\n";
	}
// now we want one single instance of this object. Let us create one in private section only.
// Now, instance can be created by this class and can be accessed by this class only.
	static DatabaseManager *instance;
// why static, we will see that in a minute.
// We also want this one instance to be accessible, so we make a getter for that but make it public and static.
public:
	static DatabaseManager* get_instance()
	{
		if(!instance) // if we dont have any instace, we create one
			instance = new DatabaseManager(); // we can do this cause we are in same class
		else
			std::cout << "Instance is already created...\n";
		return instance;
	}
// Now I will answer why static.
// Since we cannot create objects of DatabaseManager, and we still want to access this instance, 
// We use static so that we can access this method without refering any object.
	void read(){}
	void write(){}
	// other functions of database manager
};


// we mark this null so that it can be initialised
DatabaseManager *DatabaseManager::instance = NULL;


// main driver
int main()
{
	DatabaseManager *dbm = dbm->get_instance();
	DatabaseManager *dbm2 = dbm2->get_instance();
	//  notice constructor is called only once
	// then we can do operations on dbm and dbm2 which are actually same objects in memory as well.
	dbm->read();
	dbm2->write();
	delete dbm;
	delete dbm2;
	return 0;
}

// These are simple steps to create singleton
/*
1. create private constructor
2. private static instance of same class
3. public static get_instance
*/