#include<iostream>

/*
	Chain of resposibility pattern is a series of processing objects. The object on which some operations
	are to be performed, is passed to some object. This object performs whichever operations are possible.
	If some are not, it passes the object to next handler in the chain. This way, the object passes
	from one handler to another until it is handled and operated completely. 
	One might think that this is just if-else-if. And yes, it is in some way. But you can add handlers in 
	chain during runtime as well. Such mechanism can be implemented very easily.
	In this example, we consider assembly line of a car. First we have to assemble chassi, then engine, then
	transmission and so on. We can always append more handlers. The car is passed from chassi to engine
	to transmission and till the end.
	Real examples are payment system, logging system, etc.
*/

class Car
{
public:
	std::string chassi; 
	std::string engine; 
	std::string transmission;
	std::string paint;
	void show()
	{
		std::cout << chassi << " " << engine << " " << transmission << " " << paint << "\n";
	} 
};

class WorkStation
{
public:
	virtual ~WorkStation() {}
	virtual Car* work() = 0;
};

class PaintStation : public WorkStation
{
public:
	PaintStation(){	}
	Car* work(Car *car)
	{
		std::cout << "Paint added!\n";
		car->paint = "Red";
		return car;
	}
};

class TransmissionStation : public WorkStation
{
private:
	PaintStation *paintStation;
public:
	Car* work(Car *car)
	{
		std::cout << "Transmission added!\n";
		car->engine = "Transmission";
		return paintStation->work(car);
	}
	~TransmissionStation()
	{
		delete paintStation;
	}
};

class EngineStation : public WorkStation
{
private:
	TransmissionStation *transmissionStation;
public:
	Car* work(Car *car)
	{
		std::cout << "Pinston engine added!\n";
		car->engine = "Piston Engine";
		return transmissionStation->work(car);
	}
	~EngineStation()
	{
		delete transmissionStation;
	}
};

class ChassiStation : public WorkStation
{
private:
	EngineStation *engineStation;
public:
	Car* work(Car *car)
	{
		std::cout << "Aluminium Chassi added!\n";
		car->chassi = "AluminiumChassi";
		return engineStation->work(car);
	}
	~ChassiStation()
	{
		delete engineStation;
	}
};

class AssemblyLine
{
private:
	ChassiStation *cs;
	EngineStation *es;
	TransmissionStation *ts;;
	PaintStation *ps;
public:
	AssemblyLine() {}

	Car* assemble(Car *car)
	{	
		std::cout << "Assembly started!\n";
		if(!car->chassi.compare("")){
			std::cout << "Chassi\n";
			car = cs->work(car);
		}
		else if(!car->engine.compare(""))
		{
			std::cout << "Engine\n";
			car = es->work(car);
		}
		else if(!car->transmission.compare(""))
		{
			std::cout << "Transmission\n";
			car = ts->work(car);
		}
		else if(!car->paint.size() || car->paint.size()==0)
		{
			std::cout << "Painting\n";
			car = ps->work(car);
		}
		std::cout << "Assembly ended!\n";
		return car;
	}

	~AssemblyLine()
	{
		delete cs, es, ts, ps;
	}
};

int main()
{
	AssemblyLine *al = new AssemblyLine();
	Car *car = new Car();
	al->assemble(car);
	car->show();
	delete car, al;
	return 0;
}