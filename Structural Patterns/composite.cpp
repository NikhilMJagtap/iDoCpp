#include<iostream>
#include<vector>

/*
	Consider you a composite class. The objects (called as Leaf class) in this class usually have some behaviour 
	and composite class has some other. Often, it is required that they have similar behaviour. E.g.
	You have a Drawing class which has a function draw. A drawing is made up of multiple strokes. Stroke object 
	has a draw function as well. We can code this behaviour using composite pattern. 
	In this pattern, we create an interface, and implement it for both Composite class and Leaf class. Hence, 
	we get similar behaviour in both Composite class and Leaf class.
	Tree like structure is also used in composite class which gives required hierarchy.

*/

class Drawable
{
public:
	virtual ~Drawable() {}
	virtual void add_stroke(Drawable*) {}
	virtual void draw() = 0;
};

class Stroke : public Drawable
{
public:
	Stroke() {}
	~Stroke() {}
	void draw()
	{
		std::cout << "Painting a stroke.\n";
	}
};

class Drawing : public Drawable
{
private:
	std::vector<Drawable*> strokes;
public:
	Drawing() {}
	~Drawing() {}
	void add_stroke(Drawable *stroke)
	{
		strokes.push_back(stroke);
	}
	void draw()
	{
		std::cout << "Starting...\n";
		for(int i=0; i < strokes.size(); ++i)
			strokes.at(i)->draw();
		std::cout << "Drawing done.\n";
	}
};

int main()
{
	// leaf class behaviour
	Drawable *stroke1 = new Stroke();
	stroke1->draw();

	// composite class
	Drawable *drawing = new Drawing();
	drawing->add_stroke(stroke1);
	// adding more strokes
	Drawable *stroke2 = new Stroke();
	Drawable *stroke3 = new Stroke();
	Drawable *stroke4 = new Stroke();
	drawing->add_stroke(stroke2);
	drawing->add_stroke(stroke3);
	drawing->add_stroke(stroke4);
	drawing->draw();

	delete stroke1, stroke2, stroke3, stroke4, drawing;
	return 0;
}