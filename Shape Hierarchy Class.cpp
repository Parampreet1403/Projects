// Parampreet Singh - 25/03/2020 Assignment 8


#include <iostream>
#include <vector>
#include <cmath>


//Constants:
double pi{ 3.14159 };
double Knud_Thomsen_constant{ 1.6 };


//Abstract Base class - interface for all shapes
class Shape
{
public:
	virtual ~Shape() { std::cout << "Destructor: Shape" << std::endl; }
	virtual double area() = 0; //Pure virtual funciton
	virtual double volume() = 0;
};


//Abstract dervied class 2D shape 
class Shape_2D : public Shape
{
public:
	virtual ~Shape_2D() { std::cout << "Destructor: Shape_2D" << std::endl; }
};

class Square : public Shape_2D
{
private:
	double side{};
public:
	Square()
	{
		std::cout << "Default Constructor: Square" << std::endl;
	}

	Square(double side_in) 
	{
		std::cout << "Parameterised constructor: Square" << std::endl;
		side = side_in;
	}

	~Square()
	{
		std::cout << "Destructor: Square" << std::endl;
	}

	double area()
	{
		double area{ side * side };
		std::cout << "Area of Square is: " << area << std::endl;
		return area;
	}

	double volume()
	{
		std::cout << "Volume of Square is: 0 " << std::endl;
		return 0;
	}
};

class Rectangle : public Shape_2D
{
private:
	double long_side{};
	double short_side{};

public:
	Rectangle()
	{
		std::cout << "Default Constructor: Rectangle" << std::endl;
	}

	Rectangle(double long_side_in, double short_side_in)
	{
		std::cout << "Parameterised constructor: Rectangle" << std::endl;
		long_side = long_side_in;
		short_side = short_side_in;
	}

	~Rectangle()
	{
		std::cout << "Destructor: Rectangle" << std::endl;
	}

	double area() 
	{
		double area{ long_side * short_side };
		std::cout << "Area of Rectangle is: " << area << std::endl;
		return area;
	}

	double volume()
	{
		std::cout << "Volume of Rectangle is: 0" << std::endl;
		return 0;
	}
};

class Ellipse : public Shape_2D
{
private:
	double major{ 0 };
	double minor{ 0 };

public: 
	Ellipse()
	{
		std::cout << "Default Constructor: Ellipse" << std::endl;
	}

	Ellipse(double major_in, double minor_in)
	{
		std::cout << "Parametrised constructor: Ellipse" << std::endl;
		major = major_in;
		minor = minor_in;
	}

	~Ellipse()
	{
		std::cout << "Destructor: Ellipse" << std::endl;
	}

	double area()
	{
		double area{ major * minor * pi };
		std::cout << "Area of Ellipse is " << area << std::endl;
		return area;
	}

	double volume()
	{
		std::cout << "Volume of Ellipse is 0 " << std::endl;
		return 0;
	}
};

class Circle : public Shape_2D
{
private:
	double radius{ 0 };

public: 
	Circle()
	{
		std::cout << "Default Constructor: Circle" << std::endl;
	}

	Circle(double radius_in)
	{
		std::cout << "Parametrised constructor: Circle" << std::endl;
		radius = radius_in;
	}
	
	~Circle()
	{
		std::cout << "Destructor: Circle" << std::endl;
	}

	double area()
	{
		double area{ pi * pow(radius, 2) };
		std::cout << "Area of Circle is: " << area << std::endl;
		return area;
	}

	double volume()
	{
		std::cout << "Volume of Circle is: 0 " << std::endl;
		return 0;
	}
};


//Abstract derived class 3D shape  
class Shape_3D : public Shape
{
public:
	virtual ~Shape_3D() { std::cout << "Destructor: Shape_3D" << std::endl; }
};

class Cuboid : public Shape_3D
{
private:
	double height{ 0 };
	double length{ 0 };
	double width{ 0 };

public:
	Cuboid()
	{
		std::cout << "Default Constructor: Cuboid" << std::endl;
	}

	Cuboid(double height_in, double length_in, double width_in)
	{
		std::cout << "Parametrised constructor: Cuboid" << std::endl;
		height = height_in;
		length = length_in;
		width = width_in;
	}

	~Cuboid()
	{
		std::cout << "Destructor: Cuboid " << std::endl;
	}

	double area()
	{
		double surface_area{};
		surface_area = (height * width * 2) + (width * length * 2) + (length * height * 2);
		std::cout << "Surface Area of Cuboid is: " << surface_area << std::endl;
		return surface_area;
	}

	double volume()
	{
		double volume{height*width*length};
		std::cout << "Volume of Cuboid is: " << volume << std::endl;
		return volume;
	}
};

class Cube : public Shape_3D
{
private:
	double side{};

public:
	Cube()
	{
		std::cout << "Default Constructor: Cube" << std::endl;
	}

	Cube(double side_in)
	{
		std::cout << "Parameterised constructor: Cube " << std::endl;
		side = side_in;

	}

	~Cube()
	{
		std::cout << "Destructor: Cube " << std::endl;
	}

	double area()
	{
		double surface_area{side*side*6};
		std::cout << "Surface Area of Cube is: " << surface_area << std::endl;
		return surface_area;
	}

	double volume()
	{
		double volume{pow(side, 3)};
		std::cout << "Volume of Cube is: " << volume << std::endl;
		return volume;
	}
};

class Ellipsoid : public Shape_3D
{
private:
	double axis_1{};
	double axis_2{};
	double axis_3{};

public:
	Ellipsoid()
	{
		std::cout << "Default Constructor: Ellipsoid" << std::endl;
	}

	Ellipsoid(double axis_1_in, double axis_2_in, double axis_3_in)
	{
		std::cout << "Parametrised constructor: Ellipsoid " << std::endl;
		axis_1 = axis_1_in;
		axis_2 = axis_2_in;
		axis_3 = axis_3_in;
	}

	~Ellipsoid()
	{
		std::cout << "Destructor: Ellipsoid" << std::endl;
	}

	double area()
	{
		double surface_area{};
		double temp{};
		temp = (pow(axis_1 * axis_2, Knud_Thomsen_constant) + pow(axis_1 * axis_3, Knud_Thomsen_constant) + pow(axis_2 * axis_3, Knud_Thomsen_constant)) / 3;
		surface_area = 4 * pi * pow(temp, (1 / Knud_Thomsen_constant));
		std::cout << "Surface Area (approximate) of Ellipsoid is: " << surface_area << std::endl;
		return surface_area;
	}

	double volume()
	{
		double volume{ 1.33333 * pi * axis_1 * axis_2 * axis_3 };
		std::cout << "Volume (appoximate) of Ellipsoid is: " << volume << std::endl;
		return volume;
	}

};

class Sphere : public Shape_3D
{
private:
	double radius{};
	
public:
	Sphere()
	{
		std::cout << "Default Constructor: Sphere" << std::endl;
	}

	Sphere(double radius_in)
	{
		std::cout << "Parameterised constructor: Sphere " << std::endl;
		radius = radius_in;
	}

	~Sphere()
	{
		std::cout << "Destructor: Sphere" << std::endl;
	}

	double area()
	{
		double surface_area{ 4 * pi * pow(radius, 2) };
		std::cout << "Surface Area of Sphere is: " << surface_area << std::endl;
		return surface_area;
	}

	double volume()
	{
		double volume{ 1.33333 * pi * pow(radius, 3) };
		std::cout << "Volume of Sphere is: " << volume << std::endl;
		return volume;
	}
};


class Prism : public Shape_3D
{
private:
	double depth{};
	Shape* temp{};

public:
	Prism()
	{
		std::cout << "Default Constructor: Prism" << std::endl;
	}

	Prism(double depth_in, Shape* base_class_pointer)
	{
		std::cout << "Parameterised constructor: Prism " << std::endl;
		depth = depth_in;
		temp = base_class_pointer;
	}

	~Prism()
	{
		std::cout << "Destructor: Prism" << std::endl;
	}

	double area()
	{
		double surface_area{};
		return surface_area;
	}

	double volume()
	{
		double volume{ depth * temp->area() };
		std::cout << "Volume of Prism is: " << volume << std::endl;
		return volume;
	}
};


int main()
{
	std::string line{ "________________________________________________________" };
	std::vector<Shape*> shape_pointer{};

	//2D Shapes
	shape_pointer.push_back(new Rectangle{4, 2}); // [0]
	shape_pointer.push_back(new Square{ 3 }); // [1]
	shape_pointer.push_back(new Ellipse{ 5, 2 }); // [2]
	shape_pointer.push_back(new Circle{ 5 }); // [3]
	std::cout << line << std::endl;

	//3D Shapes
	shape_pointer.push_back(new Cuboid{ 1, 3, 2 }); // [4]
	shape_pointer.push_back(new Cube{ 2 }); // [5] 
	shape_pointer.push_back(new Ellipsoid{ 1, 2, 3 }); // [6]
	shape_pointer.push_back(new Sphere{ 4 }); // [7]

	std::cout << line << std::endl;

	//Accessing 2D Shape information 
	shape_pointer[0]->area();
	shape_pointer[0]->volume();
	std::cout << line << std::endl;
	shape_pointer[1]->area();
	shape_pointer[1]->volume();
	std::cout << line << std::endl;
	shape_pointer[2]->area();
	shape_pointer[2]->volume();
	std::cout << line << std::endl;
	shape_pointer[3]->area();
	shape_pointer[3]->volume();
	std::cout << line << std::endl;

	//Accessing 3D Shape information
	shape_pointer[4]->area();
	shape_pointer[4]->volume();
	std::cout << line << std::endl;
	shape_pointer[5]->area();
	shape_pointer[5]->volume();
	std::cout << line << std::endl;
	shape_pointer[6]->area();
	shape_pointer[6]->volume();
	std::cout << line << std::endl;
	shape_pointer[7]->area();
	shape_pointer[7]->volume();

	//Constructing Prism
	std::cout << line << std::endl;
	Prism prism(2, shape_pointer[0]); //depth, shape_pointer[shape_number]
	//prism.area();
	prism.volume();


	//Cleaning up memory leaks
	std::cout << line << std::endl;
	std::cout << "shape_pointer has size: " << shape_pointer.size() << " || Going to Destroy..." << std::endl;
	std::cout << line << std::endl;
	for (auto iterator = shape_pointer.begin(); iterator < shape_pointer.end(); iterator++)
	{
		delete* iterator;
	}
	shape_pointer.clear();
	std::cout << line << std::endl;
	std::cout << "shape_pointer has size: " << shape_pointer.size() << std::endl;
	std::cout << line << std::endl;

	return 0;
}

//-------------------------------------------- Unused Code -----------------------------------------------

	/*
	std::cout << line << std::endl;
	Rectangle rectangle(4, 2); // long, short
	rectangle.area();
	rectangle.volume();

	std::cout << line << std::endl;
	Square square(3); //length
	square.area();
	square.volume();

	std::cout << line << std::endl;
	Ellipse ellipse(5, 2); // major, minor
	ellipse.area();
	ellipse.volume();

	std::cout << line << std::endl;
	Circle circle(5); //Radius
	circle.area();
	circle.volume();

	std::cout << line << std::endl;
	Cuboid cuboid(1, 3, 2); //height, length, width
	cuboid.area();
	cuboid.volume();

	std::cout << line << std::endl;
	Cube cube(2); //length
	cube.area();
	cube.volume();

	std::cout << line << std::endl;
	Ellipsoid ellipsoid(1, 2, 3); //axis_1, axis_2, axis_3
	ellipsoid.area();
	ellipsoid.volume();

	std::cout << line << std::endl;
	Sphere sphere(4); //Radius
	sphere.area();
	sphere.volume();

	*/

