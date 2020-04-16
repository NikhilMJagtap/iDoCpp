#include<iostream>

/*
	This is very simple example of abstract factory. Let us say we want to create some shapes. If we have 10 shapes, 
	let's say, then we need to take care of making constructor to each one, giving right types and all. Instead, we 
	create a base class Shape and extend each shape to it. Classes Triangle and Circle extend to them. 
	Then, we create a base factory as ShapeFactory. Consider factory.cpp example in case you want to know how factories
	work. Then, we create a factory for each shape. We then create another class AbstractShapeFactory. This class wraps
	all the factories and shapes for us. We just send type of shape which we want. It gives us that shapefactory and
	then its shape can be used using create. 

	Advantage of this pattern is in its name. Abstraction. Notice how the developer who is calling AbstractFactory 
	need not worry about how shape factories are implemented, how shapes are implemented. Just call factory with
	type you want and it will give you that shape. It also makes it easier to add new shape. Say Square is to be added. 
	We just have to make a Square class, extend Shape, create SquareFactory and add it in AbstractShapeFactory. 

	The developer who is working on higher level of this, (which means the one who must not care about how shapes are
	on lower level and just create them, draw them and remove them,) should never care about which calls are made to
	get that shape. Just call draw() method on shape you have.
*/




/* Class shape is parent class to other classes which are shapes, i.e. circle triangle square */

class Shape
{
protected:
	std::string name;
public:
	Shape(std::string name)
	{
		this->name = name;
	}

	std::string get_name()
	{
		return this->name;
	}
	virtual void draw()
	{
		std::cout << "Drawing " << this->name << " shape.\n";
	}

	~Shape()
	{

	}
};

/* Class triangle inherits Shape */
class Triangle : public Shape
{
protected:
	
public:
	Triangle(std::string name)
	: Shape(name)
	{

	} 

	void draw()
	{
		std::cout << "Drawing triangle with name " << this->name << ".\n";
	}

	~Triangle()
	{

	}
};

/* Class Circle inherits Shape */
class Circle : public Shape 
{
protected:
	
public:
	Circle(std::string name)
	: Shape(name)
	{
		
	}

	void draw()
	{
		std::cout << "Drawing circle with name " << this->name << ".\n";
	}

	~Circle()
	{

	}
};

// Now let us implement some factories, one for each Shape

class ShapeFactory
{
public:
	virtual Shape* create(std::string name)
	{
		return new Shape(name);
	}
};


class TriangleFactory : public ShapeFactory
{
	Shape* create(std::string name)
	{
		return new Triangle(name);
	}
};


class CircleFactory : public ShapeFactory
{
	Shape* create(std::string name)
	{
		return new Circle(name);
	}
};


// abstract factory for shapes
class AbstractShapeFactory
{
public:
	ShapeFactory* factory(std::string type)
	{
		if(!type.compare("triangle"))
			return new TriangleFactory();
		else if(!type.compare("circle"))
			return new CircleFactory();
		else
			throw new std::invalid_argument(type);
	}
};


// main Driver class
int main()
{
	AbstractShapeFactory asf;
	ShapeFactory* sf = asf.factory("circle");
	Shape* shape = sf->create("Circle with radius 10px");
	shape->draw();
	Shape* shape2 = asf.factory("triangle")->create("Right angled triangle");
	shape2->draw();
	return 0;
}