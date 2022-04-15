#include <iostream>

class Shape2D
{
public:
	Shape2D()
	{
		std::cout << "I'm shape!\n";
	}

	virtual void show() const
	{
		std::cout << "Shape has been shown\n";
	}

	virtual double square() const = 0;
};

class Circle : public Shape2D
{
	double m_radius;
public:
	Circle()
	{
		std::cout << "I'm circle!\n";
	}

	Circle(double radius) : Circle() 
	{ 
		m_radius = radius;
	}

	void show() const override
	{
		std::cout << "Circle has been shown\n";
	}

	double square() const override
	{
		return 3.1415*m_radius*m_radius;
	}

};

class Rectangle : public Shape2D
{
	double m_width;
	double m_height;
public:
	Rectangle()
	{
		std::cout << "I'm rectangle!\n";
	}

	Rectangle(double w, double h) : Rectangle() 
	{
		m_width = w;
		m_height = h;
	}

	void show() const override
	{
		std::cout << "Rectangle has been shown\n";
	}

	double square() const override
	{
		return m_width*m_height;
	}

	void shine()
	{
		std::cout << "I'm a shine rectangle!\n";
	}

};

void render(Shape2D** shapes, size_t size)
{
	for (size_t idx = 0; idx < size; ++idx)
	{
		shapes[idx]->show();
		Rectangle* rect = dynamic_cast<Rectangle*>(shapes[idx]);
		if (rect != nullptr)
			rect->shine();
	}
}

int main()
{
	float f = 1.5;
	std::cout << "f = " << 1.5 << "\n";
	std::cout << "static_cast<int>(f) = " << static_cast<int>(f) << "\n";
	std::cout << "reinterpret_cast<int&>(f) = " << reinterpret_cast<int const&>(f) << "\n";
	reinterpret_cast<int&>(f) = 5;
	std::cout << "f = " << f << "\n";

	int x = 4;
	int const& z = x;
	const_cast<int&>(z) = 5; // x == 5	
	std::cout << "x = " << x << "\n";

	Shape2D* shapes[3] = { new Circle(1), new Circle(2), new Rectangle(1,2)};
	render(shapes, 3);

	return 0;
}