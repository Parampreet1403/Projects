//Parampreet Singh - Assigment 7
// 11/03/19

#include <iostream>
#include<string>
#include<vector>
#include<cstring>
#include<math.h>

//Prints a vector of type double
void show(std::vector<double> vector)
{
	std::vector<double> name = vector;
	std::cout << "[";
	if (!name.empty())
	{
		for (auto iterator = name.begin(); iterator != name.end(); iterator++)
		{
			if (iterator == name.end() - 1)
			{
				std::cout << *iterator << "]" << std::endl;
			}
			else
			{
				std::cout << *iterator << ", ";
			}

		}
	}
}

//Dot product of two vectors
double dot_product(std::vector<double> const vector1, std::vector<double> const vector2)
{
	double temp{};
	if (vector1.size() == vector2.size())
	{
		for (int i{}; i < vector1.size(); i++) temp += vector2[i] * vector1[i];
		return temp;
	}
	else std::cerr << "Vectors do not have same length." << std::endl;
	return temp;
}

//Base
class Vector
{
private:
	std::string name{ "default" };
	int length{ 0 };
	std::vector<double> my_vector{};

public:

	//Default constructor 
	Vector() { std::cout << "Default Constructor: Vector" << std::endl; }

	//Parametrised constructor 
	Vector(std::string name_in, std::vector <double> vector_in)
	{
		std::cout << "Parameterised Constructor: Vector" << std::endl;
		name = name_in;
		my_vector = vector_in;
		length = my_vector.size();
	}

	//Parametrised constructor for Four_vector
	Vector(std::string name_in, double x_in, double y_in, double z_in)
	{
		std::cout << "Parameterised Constructor: Vector(x, y, z)" << std::endl;
		name = name_in;
		my_vector.push_back(x_in), my_vector.push_back(y_in), my_vector.push_back(z_in);
		length = my_vector.size();
	}

	//Destructor 
	~Vector()
	{
		std::cout << "Destructor: Vector" << std::endl;
	}

	//copy constructor 
	Vector(Vector const& vector)
	{
		name = vector.name + ".Copy";
		my_vector = vector.my_vector;
		length = my_vector.size();
	}

	//move constructor 
	Vector(Vector&& vector)
	{
		name = vector.name + ".Steal"; //Stealing data
		my_vector = vector.my_vector;
		length = vector.length;

		vector.my_vector.clear(); //Reallocating data
		vector.length = vector.my_vector.size();
	}

	//copy assigmnet operator 
	Vector& operator=(const Vector& vector)
	{
		if (&vector == this)  return *this; //If both vectors the same return vector 
		else
		{
			name = vector.name; //Add copy?
			my_vector = vector.my_vector;
			length = my_vector.size();
		}
	}

	//move assigment operator 
	Vector& operator=(Vector&& vector)
	{
		std::swap(name, vector.name);
		std::swap(length, vector.length);
		std::swap(my_vector, vector.my_vector);
		return *this;
	}

	//overload () -> access the vector 
	double operator()(int i)
	{
		double temp{};
		if (i <= this->my_vector.size())
		{
			int count{};
			for (count; count < this->my_vector.size(); count++)
			{
				if (count == i)
				{
					temp = (this->my_vector[i]);
					return temp;
				}
			}
		}
		else
		{
			std::cout << "The index is outside of the vector range (" << this->my_vector.size() << ")." << std::endl;
		}

	}

	//Member Function
	std::string get_name() const { return name; }
	double get_length() const { return length; }
	std::vector <double> get_vector() const { return my_vector; }

	//Dot product of two Vector classes
	double dot(Vector& const vector) const
	{
		double temp{};
		std::vector<double> vector1 = this->my_vector;
		if (this->length == vector.length)
		{
			for (int i{}; i < this->length; i++)
			{
				temp += this->my_vector[i] * vector(i);
			}
			std::cout << "The dot product of " << this->name << " and " << vector.name << " is: ";
			std::cout << temp << std::endl;
			return temp;
		}
		else
		{
			std::cerr << this->name << " and " << vector.name << " are not of the same length." << std::endl;
			return temp;
		}
	}

	//Friend Function 
	friend std::ostream& operator<< (std::ostream& os, const Vector& vector);
};

//Minkowski 4-vectors || Derived
class Four_vector : public Vector
{
private:
	double distance{};
	double x{};
	double y{};
	double z{};
	std::vector <double> position_vector{};

public:
	//Default constructor 
	Four_vector()
	{
		Vector{};
		distance = 0;
		x, y, z = 0;
		position_vector.push_back(0), position_vector.push_back(0), position_vector.push_back(0);
	}

	//Parameterised constructor(ct, x, y, z)
	Four_vector(double distance_in, double x_in, double y_in, double z_in, std::string name_in) : Vector{ name_in, x_in, y_in, z_in } //Vector construction
	{
		std::cout << "Parameterised constructor: Four_vector(ct, x, y, z)" << std::endl;
		distance = distance_in;
		x = x_in;
		y = y_in;
		z = z_in;
		position_vector.push_back(x), position_vector.push_back(y), position_vector.push_back(z);
	}

	//Parameterised constructor(ct, R)
	Four_vector(std::string name_in, std::vector<double> position_vector_in, double distance_in) : Vector{ name_in, position_vector_in } //Vector Construction
	{
		std::cout << "Parameterised constructor: Four_vector(distance, position_vector)" << std::endl;
		distance = distance_in;
		position_vector = position_vector_in;
		x = position_vector[0];
		y = position_vector[1];
		z = position_vector[2];
	}

	//Destructor
	~Four_vector()
	{
		std::cout << "Destructor: Four_vector" << std::endl;
	}

	//copy constructor
	Four_vector(Four_vector const& four_vector)
	{
		distance = four_vector.distance;
		x = four_vector.x;
		y = four_vector.y;
		z = four_vector.z;
	}

	//move constructor 
	Four_vector(Four_vector&& four_vector)
	{
		distance = four_vector.distance; //Stealing data
		x, y, z = four_vector.x, y, z;
		position_vector = four_vector.position_vector;

		four_vector.distance = 0; //Reallocating data
		four_vector.x, y, z = 0;
		four_vector.position_vector.clear();
		four_vector.position_vector.push_back(0), four_vector.position_vector.push_back(0), four_vector.position_vector.push_back(0);
	}

	//copy assigmnet operator 
	Four_vector& operator=(const Four_vector& four_vector)
	{
		if (&four_vector == this)  return *this; //If both four_vectors are the same return four_vector 
		else
		{
			distance = four_vector.distance;
			x, y, z = four_vector.x, y, z;
		}
	}

	//move assigment operator 
	Four_vector& operator=(Four_vector&& four_vector)
	{
		std::swap(distance, four_vector.distance);
		std::swap(x, four_vector.x);
		std::swap(y, four_vector.y);
		std::swap(z, four_vector.z);
		return *this;
	}

	//accessors return 4 vector component 
	double operator()(const char* input)
	{
		if (input == "d") return this->distance;
		else if (input == "x") return this->x;
		else if (input == "y") return this->y;
		else if (input == "z") return this->z;
		else std::cerr << "Input for Four_vector('d/x/y/z') invalid: "; return 0;
	}

	//Accessors returing 4 vector components
	//void operator[](std::string input) //distance x, y, z
	void operator[](std::string input)
	{
		std::vector<double> temp{};
		for (int i{}; i < input.size(); i++)
		{
			if (input[i] == 'd') temp.push_back(this->distance);
			else if (input[i] == 'x') temp.push_back(this->x);
			else if (input[i] == 'y') temp.push_back(this->y);
			else if (input[i] == 'z') temp.push_back(this->z);
		}
		std::cout << this->get_name() << "(ct, x, y, z): ";
		show(temp);
	}

	//Member Function 
	double dot(Four_vector& const four_vector) const //Overriden function
	{
		double temp{};
		double product{};
		double this_length = this->get_length();
		std::string this_name = this->get_name();
		std::vector<double> this_vector = this->get_vector();

		double vector_length = four_vector.get_length();
		std::string vector_name = four_vector.get_name();
		std::vector<double> vector_vector = four_vector.get_vector();
		if (this_length == vector_length)
		{
			for (int i{}; i < this_length; i++)
			{
				temp += this_vector[i] * vector_vector[i];
			}
			product = (this->distance * four_vector.distance) - temp;
			std::cout << "The dot product of " << this_name << " and " << vector_name << " is: ";
			std::cout << product << std::endl;
			return product;
		}
		else
		{
			std::cerr << this_name << " and " << vector_name << " are not of the same length." << std::endl;
			return temp;
		}
	}
	//std::vector<double> get_beta() const { return beta; }
	Four_vector lorentz_boosted(const std::vector<double> beta_in) const
	{
		double beta_squared = dot_product(beta_in, beta_in);
		double gamma = 1 / (sqrt(1 - beta_squared));
		double ct_prime = gamma * (this->distance - (dot_product(beta_in, this->position_vector)));
		double temp_constant = ((gamma - 1) * (dot_product(beta_in, position_vector) / beta_squared)) - (gamma * this->distance);
		std::vector<double> beta_prime{};
		std::vector<double> position_vector_prime{};
		for (int i{}; i < beta_in.size(); i++)
		{
			position_vector_prime.push_back(position_vector[i] + (temp_constant * beta_in[i]));
		}
		Four_vector four_vector_boosted(this->get_name() + ".Boosted", position_vector_prime, ct_prime);
		std::cout << four_vector_boosted << std::endl;
		return four_vector_boosted;
	}

	//overload ostream
	friend std::ostream& operator<< (std::ostream& os, const Four_vector& four_vector);
};


class particle  //public Vector, Four_vector
{
private:
	std::vector<double> particle_four_vector{ 0, 0, 0, 0 };
	double mass{};
	std::vector<double> particle_beta{ 0, 0, 0 };

public:
	//Default Constructor 
	particle()
	{
		std::cout << "Default constructor: " << std::endl;
	}

	//parameterised constructor																									  
	particle(std::vector<double> four_vector, double mass_in, std::vector<double> three_vector) 
	{
		std::cout << "Parameterised constructor: Particle" << std::endl;
		particle_four_vector.clear();
		particle_beta.clear();

		mass = mass_in;
		particle_four_vector = four_vector;
		particle_beta = three_vector;
	}

	//Destructor
	~particle()
	{
		std::cout << "Destructor: Particle" << std::endl;
	}

	//Member Function
	double gamma()
	{
		double temp{};
		temp = 1 / (sqrt(1 - dot_product(this->particle_beta, this->particle_beta)));
		return temp;
	}

	// E = gamma * m * c^2
	double total_energy()
	{
		double temp{};
		temp = this->gamma() * this->mass; // * c^2
		return temp;
	}

	// p = gamma * m * v -> Becomes: p = gamma * m * beta
	double momentum() 
	{
		double beta{};
		for (int i{}; i < this->particle_beta.size(); i++)
		{
			beta += pow(this->particle_beta[i], 2);
		}
		beta = sqrt(beta); // Magnitude of beta
		double temp2 = this->gamma() * this->mass * beta;
		return temp2;
	}
};

//Non-Member Function (Friend):
std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
	std::vector<double> name = vector.my_vector;
	os << vector.name << ": [";
	for (auto iterator = name.begin(); iterator != name.end(); iterator++)
	{
		if (iterator == name.end() - 1)
		{
			std::cout << *iterator;
		}
		else
		{
			std::cout << *iterator << ", ";
		}
	}
	os << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Four_vector& four_vector)
{
	std::string name = four_vector.get_name();
	os << "Name: " << name << "\nDistance(ct): " << four_vector.distance << "\nPosition[x, y, z]: ";
	show(four_vector.position_vector);
	return os;
}

int main()
{
	std::string line = "________________________________________________________________________________________________";
	
	//Vector class:
	std::cout << line << std::endl;

	std::vector <double> my_vector_1{ 1, 2, 3};
	std::vector <double> my_vector_2{ 4, 5, 6};
	std::vector <double> my_vector_3{ 1, 2, 3, 4};

	Vector vector_default();
	Vector vector1("Vector_1", my_vector_1);

	std::cout << vector1.get_name() << "(1): " << vector1(1) << std::endl;
	vector1(10);
	Vector vector2("Vector_2", my_vector_2);
	Vector vector3("Vector_3", my_vector_3);

	vector1.dot(vector2);
	vector1.dot(vector3);

	std::cout << vector3 << std::endl;


	//Minkowski 4-vectors || Derived class:
	std::cout << line << std::endl;

	Four_vector four_vector_1(10, 1, 2, 3, "Four_vector_1"); //(ct, x, y, z)
	Four_vector four_vector_2("Four_vector_2", my_vector_2, 10); //(R, ct)

	four_vector_2["d, x, y, z"];
	std::cout << four_vector_2.get_name() << ": ct = (" << four_vector_2("d") << ") " << std::endl;
	four_vector_2["d, x"];

	four_vector_1.dot(four_vector_2);

	std::vector<double> beta1{ .1, .5, .6 };
	four_vector_1.lorentz_boosted(beta1);
	std::cout << four_vector_2 << std::endl;

	//Particle class:
	std::cout << line << std::endl;

	std::vector<double> particle_four_vector{10, 5, 6, 7}; //(ct, x, y, z)
	double particle_mass{1};
	std::vector<double> particle_three_vector{.1, .2, .3}; //Beta (B = v/c)


	particle particle_1(particle_four_vector, particle_mass, particle_three_vector);

	std::cout << "Particle_1: " << std::endl;
	std::cout << "Gamma: " << particle_1.gamma() << std::endl;
	std::cout << "Total_enery: " << particle_1.total_energy() << " MeV" << std::endl;
	std::cout << "Momentum: " << particle_1.momentum()  << " MeV/c"<< std::endl;
	std::cout << line << std::endl;
	std::cout << "\n\n\n\n\n\n";
	std::cout << "DESTROYING... stuff: " << std::endl;

	return 0;
}

//Note to marker: 
