#include<iostream>
#include<vector>
/*
	More than often, we need to create objects which are very complex. Moreover, they need to be of various forms
	as well. That is where we use builder pattern. We simply write a builder class to abstract the creation of
	those complex objects. An example will make it more clear.
	We are building a computer. Yes, a computer. But we can assemble one with GPU, without GPU, with SSD 
	and there are so many possible configs. That makes it really complex. 
	In this example, suppose we can create an object of a computer. It has a list of hardware it can have.
	We also can modify these builds, a simple PC (which is nothing extra), an office PC (which has extra RAM and
	SSD) and a gaming PC (which has extra RAM and SSD and GPU as well).
	Manually, we can create these objects in independent classes, but imagine thousands of such rigs, meh, too
	much of a task for a programmer.
	We create a Builder class, which has a Computer object and can add specs to that Computer object.
	Then we get a ConcreteBuilder class (note that, implementing a ConcreteBuilder directly makes sense here
	cause we have only one Builder. But if we have more, an interface or an abstract class is better option)
	And then a director class which has a builder object. We put all our variants in this director class.
	There we list functions which can customise our rigs. 
	Simply calling build_x_pc and then get_product gives us our desired object.
	When we get an addition, say our clients selling PC for Digital Artists, we simply have to add one
	function in our director, instead of creating a separate class.

	This does not only give huge absraction, but code reusability.
*/

// Firstly, this is our computer class which has the list of its specs
class Computer
{
private:
	std::vector<std::string> specs;
public:
	Computer()
	{
		specs.push_back("Motherboard");
		specs.push_back("CPU 4 Cores");
		specs.push_back("RAM 4GB");
		specs.push_back("Hard Drive 512GB");
	}

	void add_spec(std::string hardware)
	{
		this->specs.push_back(hardware);
	}

	void list_specs()
	{
		for(int i=0; i<this->specs.size(); ++i)
		{
			std::cout << this->specs.at(i) << std::endl;
		}
	}

	~Computer()
	{

	}
};

// now we need a builder itself with this abstract class
class Builder
{
public:
	virtual void add_extra_ram(int gb) const = 0;
	virtual void add_ssd(int gb) const = 0;
	virtual void add_gpu(int gb) const = 0;
};


// concerete builder is concrete class from Builder. We can create variations of this using extending Builder
class ConcreteBuilder : public Builder
{
private:
	Computer* computer;
public:
	ConcreteBuilder()
	{
		computer = new Computer();
	}

	void add_extra_ram(int gb) const override
	{
		this->computer->add_spec("RAM " + std::to_string(gb) + "GB");
	}

	void add_ssd(int gb) const override
	{
		this->computer->add_spec("SSD " + std::to_string(gb) + "GB");
	}

	void add_gpu(int gb) const override
	{
		this->computer->add_spec("GPU " + std::to_string(gb) + "GB");
	}


	Computer* get_product()
	{
		Computer* product = this->computer;
		this->computer = new Computer();
		return product;
	}

	~ConcreteBuilder()
	{

	}
};

// And finally we need a Director class
class Director
{
private:
	Builder* builder;
public:
	Director(Builder* builder)
	{
		this->builder = builder;
	}

	void build_simple_pc()
	{
		// nothing added extra
	}

	void build_office_pc()
	{
		this->builder->add_extra_ram(8);
		this->builder->add_ssd(128);
	}

	void build_gaming_pc()
	{
		this->builder->add_extra_ram(8);
		this->builder->add_ssd(512);
		this->builder->add_gpu(6);
	}

	~Director()
	{

	}
};

int main()
{
	// first we get our concrete builder and director
	ConcreteBuilder* concrete_builder = new ConcreteBuilder();
	Director* director = new Director(concrete_builder);

	// let us build a simple PC
	director->build_simple_pc();
	Computer* comp1 = concrete_builder->get_product();
	std::cout << "\nListing Simple PC specs...\n";
	comp1->list_specs();

	// now let us build office pc
	director->build_office_pc();
	Computer* comp2 = concrete_builder->get_product();
	std::cout << "\nListing Office PC specs...\n";
	comp2->list_specs();

	// and at the end we build gaming pc
	director->build_gaming_pc();
	Computer* comp3 = concrete_builder->get_product();
	std::cout << "\nListing Office PC specs...\n";
	comp3->list_specs();
	return 0;
}