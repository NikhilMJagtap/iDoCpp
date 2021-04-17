#include<iostream>

/*
	To understand a factory pattern, we can take this simple example where we are making a game. A player can summon two
	kinds of troops, namely Barbarian and Archer. They can equip and use the weapons Sword and Bow-Arrow respectively. 
	Whenever player decides to summon a troop, an object to troop is created, that weapon is equiped by that troop and
	then summoned on battleground.

	Normally, we will create an object of troop each time the player tries to summon a troop. But that will be too much
	of redundant task. Instead, we create another class called TroopFactory. Just simply passing the name to the create()
	function of that factory we will get desired troop.

	Notice that there is a better way to do this (in my opinion xD) which is Abstract Factory which allows you to use 
	factory for each Troop (BarbarianFactory and ArcherFactory in this case,) wrapped in one single Factory 
	(AbstractTroopFactory)

*/

class Weapon
{
public:
	/* All other functions related to weapon. Like choose, drop etc. */
};

class Sword : public Weapon
{
public:
	/* All other functions related to sword. Like swing, strike, defend, yield, sheath etc. */
};

class BowArrow : public Weapon
{
public:
	/* All other functions related to bow and arrow. Like draw, aim, release etc. */
};

class Troop 
{
public:
	std::string name;
	Troop(std::string name)
	{	
		this->name = name;
	}

	virtual void summon()
	{
		std::cout << "Summoning troop " << this->name  << " on battleground.\n";
	}

	~Troop()
	{

	}
};

class Barbarian : public Troop
{
public:
	Weapon* weapon;
	Barbarian(std::string name)
	: Troop(name)
	{
		this->equip();
	}

	void equip()
	{
		this->weapon = new Sword();
		std::cout << "Equiping sword!\n";
	}

	void summon()
	{
		std::cout << "Summoning barbarian " << this->name  << " on battleground.\n"; 
	}
};

class Archer : public Troop
{
public:
	Weapon* weapon;
	Archer(std::string name)
	: Troop(name)
	{
		this->equip();		
	}

	void equip()
	{
		this->weapon = new BowArrow();
		std::cout << "Equiping bow and arrow!\n";	
	}

	void summon()
	{
		std::cout << "Summoning archer " << this->name  << " on battleground.\n";
	}
};


// Now let us make our Factory

class TroopFactory
{
public:
	Troop* create(std::string type, std::string name)
	{
		if(!type.compare("barbarian"))
			return new Barbarian(name);
		else if(!type.compare("archer"))
			return new Archer(name);
		else
			throw new std::invalid_argument(type);
	}
};


// driver program
int main()
{
	TroopFactory troop_factory;
	Troop* barb1 = troop_factory.create("barbarian", "Conan the Barbarian");
	Troop* arch1 = troop_factory.create("archer", "Legolas");
	barb1->summon();
	arch1->summon();
	delete barb1;
	delete arch1;
	return 0;
}