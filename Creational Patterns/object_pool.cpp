#include<iostream>
#include<vector>
#include <memory>
/*
	Let us first understand what pool is.
	Pool in CS refers to collection of resources which are kept ready to use instead of creating them when
	required. For example, Operating System creates a thread pool and gives thread to required process instead
	of creating one during runtime. 
	Object pool works in similar way. Objects are created and kept ready to use instead of creating when 
	requested. Whenever object is no longer required, it is returned to the pool instead of destroying it.

	Now, best thing about using object pools in C++ is "Programmers own the memory!". And that's why, we can
	create our objects and destroy ONLY when we want to. Using smart pointers will solve this in great way.
	Whenever the object goes out of scope, destructor will be called. We usually delete the object to 
	avoid memory leaks. In object bool, we just return that object to our pool. 
*/


class CustomThread
{
public:
	int id;
	CustomThread(int thread_id)
	: id(thread_id)
	{
		std::cout << "Creating thread with ID " << thread_id <<"\n";
	}
	~CustomThread();
};

class Pool
{
private:
	// you might wanna use queue
	static std::vector<CustomThread*> pool;
	static Pool* instance;
	static int count;
	Pool()
	{
		// initialising the pool
		std::cout << "Initialising the pool.\n";
	}
	
public:
	// notice this singleton here
	static Pool* get_instance()
	{
		if(!instance)
			instance = new Pool();
		return instance;
	}
	static CustomThread* get_thread()
	{
		if(pool.size() <= 0) 
		// you can throw some error here that no threads available etc.
		{
			std::shared_ptr<CustomThread> thread = std::make_shared<CustomThread>(count);
			count++;
			std::cout << "Sending thread. " << pool.size() << " left\n";
			return thread.get();
		}
		CustomThread* thread_to_return = pool.back();
		pool.pop_back();
		std::cout << "Sending thread. " << pool.size() << " left\n";
		return thread_to_return;
	}
	static void return_to_pool(CustomThread* thread)
	{
		std::cout << "Received thread by ID " << thread->id << ". " << pool.size() << " left\n";
		pool.push_back(thread);
	}
};


CustomThread::~CustomThread()
{
	// we don't delete the instance but send it back to pool
	Pool::return_to_pool(this);
}

int Pool::count = 0;
std::vector<CustomThread*> Pool::pool;
Pool* Pool::instance = NULL;

void object_pool_demo()
{
	Pool* pool = Pool::get_instance();
	{
		CustomThread* ct = pool->get_thread();
		{
			CustomThread* ct1 = pool->get_thread();
			std::cout << ct1->id << "\n";
		}
		std::cout << ct->id << "\n";
	}
	CustomThread* ct2 = pool->get_thread();
	std::cout << ct2->id << "\n";
	std::cout << "Ending pool\n";
}

int main()	
{
	object_pool_demo();
	return 0;
}