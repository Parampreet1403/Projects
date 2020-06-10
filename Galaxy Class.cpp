#include <iostream>
#include <vector>
#include<string>

class Galaxy {
private:
	std::string hubble_type{};
	double redshift{};
	double total_mass{};
	double stellar_mass_fraction{};
	std::vector<double> vector_galaxy_properties{};
	std::vector<std::string> vector_satellite{};
	std::vector<Galaxy> vector_sat_galaxy{};

public:
	//Default Constructor
	Galaxy() {
		std::cout << "Default Constructor:" << std::endl;
		hubble_type = "E0" ;
		redshift = 0 ;
		total_mass = pow(10, 7);
		stellar_mass_fraction = 0;
		vector_galaxy_properties.insert(vector_galaxy_properties.end(), { redshift, total_mass, stellar_mass_fraction});
	}

	//Parameterised Constructor
	Galaxy(std::string h_t, double r_s, double t_m, double s_m_f) {
		std::cout << "Parameterised Constructor: " << std::endl;
		hubble_type = h_t;
		redshift = r_s;
		total_mass = t_m;
		stellar_mass_fraction = s_m_f;
		vector_galaxy_properties.insert(vector_galaxy_properties.end(), { redshift, total_mass, stellar_mass_fraction });
	}

	//Deconstructor
	~Galaxy() {
		std::cout << "Destructor: " << hubble_type << " destroyed" << std::endl;
	}

	//Member Functions
	void print_string();
	void vector_print_properties();
	void change_hubble_type();
	double get_stellar_mass();
	void add_satellite_galaxy(Galaxy &satellite_galaxy);
	void vector_print_string(Galaxy &g);
};

//Member Functions to print Galaxy data
void Galaxy::print_string() {
	std::cout << "Printing vector_hubble_type: "<< hubble_type << std::endl;
}
void Galaxy::vector_print_properties() {
	std::cout << "Printing vector_hubble_properties: " << std::endl;
	std::vector<double> name{ vector_galaxy_properties };
	std::vector<std::string> string { "Redshift", "Total mass", "Stellar mass fraction" };
	auto iterator_i = string.begin();
	if (!name.empty()) { //Iterated two vectors of same length simulatenously
		for (auto iterator = name.begin(); iterator != name.end(); iterator++ ) {
			std::cout << *iterator_i << ": "<< *iterator << std::endl;
			iterator_i++;
		}
	}
}

void Galaxy::change_hubble_type() {
	std::cout << "Please enter the new hubble type. " << std::endl;
	std::string new_hubble_type{};
	std::getline(std::cin, new_hubble_type);
	hubble_type = new_hubble_type;
}

double Galaxy::get_stellar_mass() {
	double stellar_mass{ total_mass * stellar_mass_fraction };
	return stellar_mass;
}

//static int coutner;
//counter++;

void Galaxy::add_satellite_galaxy(Galaxy &satellite_galaxy) {
	vector_sat_galaxy.push_back(satellite_galaxy);
	/*
	bool gate{ true };
	while (gate == true) {
		std::cout << "Please eneter a satellite. " << std::endl;
		std::cout << "Please enter 'x' when finished. " << std::endl;
		vector_sat_galaxy.push_back();
		std::string line{};
		std::getline(std::cin, line);
		if (line == "x") {
			std::cout << "Number of satellites stored: " << vector_satellite.size() << std::endl;
			break;
		}
		else {
			vector_satellite.push_back(line);
		}
	}*/
}

//Print satellites
void Galaxy::vector_print_string (Galaxy &g) {
	std::cout << "Number of satellites stored: "<< vector_sat_galaxy.size() << std::endl;
	std::cout << "Printing satellites for " << hubble_type <<": " << std::endl;
	std::cout << "Type: " << g.hubble_type << std::endl;
	std::cout << "redshift: " << g.redshift << std::endl;
	std::cout << "total mass: " << g.total_mass << std::endl;
	std::cout << "stellar mass fraction: " << g.stellar_mass_fraction << std::endl;
	/*
	std::vector<std::string> name = vector_satellite;
	if (!name.empty()) { 
		for (auto iterator = name.begin(); iterator != name.end(); iterator++) {
			std::cout << *iterator << std::endl;
		}
	}
	*/
}

int main() {
	std::cout << "---------------------------------------" << std::endl;

	Galaxy example_1;
	example_1.print_string();
	example_1.vector_print_properties();
	double example_1_stellar_mass = example_1.get_stellar_mass();
	std::cout << "The Stellar Mass of Example 1 is: " << example_1_stellar_mass << std::endl;
	
	std::cout << "---------------------------------------\n" << std::endl;
	
	Galaxy example_2("E1", 1, pow(10, 8), 0.01);
	example_2.print_string();
	example_2.vector_print_properties();
	double example_2_stellar_mass = example_2.get_stellar_mass();
	std::cout << "The Stellar Mass of Example 2 is: " << example_2_stellar_mass << std::endl;

	std::cout << "---------------------------------------\n" << std::endl;

	Galaxy example_3("Irr", 10, pow(10, 12), 0.05);
	example_3.print_string();
	example_3.vector_print_properties();
	double example_3_stellar_mass = example_3.get_stellar_mass();
	std::cout << "The Stellar Mass of Example 3 is: " << example_3_stellar_mass << std::endl;
	example_3.change_hubble_type();
	example_3.print_string();


	std::cout << "---------------------------------------\n" << std::endl;

	Galaxy example_4("Sa", 5, pow(10, 9), 0.15);
	example_4.print_string();
	example_4.vector_print_properties();
	double example_4_stellar_mass = example_4.get_stellar_mass();
	std::cout << "The Stellar Mass of Example 4 is: " << example_4_stellar_mass << std::endl;
	example_4.add_satellite_galaxy(example_3);
	example_4.vector_print_string(example_3);

	std::cout << "---------------------------------------\n" << std::endl;
	return 0;
}