// Parampreet Singh - 28/01/20 
// Calculating the energy for a given transition

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

std::string poisitive_interger_validation(std::string a) {
    int b{};
    while (std::getline(std::cin, a)) { // creates loop for input 
        std::stringstream a_valid{ a };
        if (a_valid >> b) { // checks to see if input in interger 
            if (std::stoi(a) > 0) { // checks to see if input is positive 
                if (a_valid.eof()) {
                break; 
                }
            }
        }
        std::cout << "Please enter a valid value. ";
    }
    return a;
}

int energy_calculation(std::string z, std::string n_i, std::string n_f, std::string unit) {
    float energy{};
    while (std::getline(std::cin, unit)) { //Creates loop for input 
        if (unit == "y") { //Calculates energy in J
            std::cout << "\nYou have chosen to calculate in J \n";
            double electron_volt_to_joules{ 1.6 * pow(10, -19) };
            energy = electron_volt_to_joules * 13.6 * pow(std::stoi(z), 2) * ((1 / pow(std::stoi(n_f), 2)) - (1 / pow(std::stoi(n_i), 2)));
            std::cout << "The energy for the transition is " << std::setprecision(2) << energy << " J.\n\n";
            break;
        }
        else if (unit == "n") { // Calculates energy in eV
            std::cout << "\nYou have chosen to calculate in eV \n";
            energy = 13.6 * pow(std::stoi(z), 2) * ((1 / pow(std::stoi(n_f), 2)) - (1 / pow(std::stoi(n_i), 2)));
            std::cout << "The energy for the transition is " << std::setprecision(2) << energy << " eV.\n\n";
            break;
        }
        else {
            std::cout << "Please type either 'y' or 'n'. \n";
        }
    }
    return energy;
}

int main() {

    std::cout << "Would you like to calculate the energy for a transition? \n"
        "Select 'y' for yes and 'n' for no. \n";

    std::string answer{};

    while (std::getline(std::cin, answer)) {
        if (answer == "y") {
            std::string atomic_number;
            std::cout << "Please enter the atomic number. \n";
            atomic_number = poisitive_interger_validation(atomic_number);
            
            std::string initial_quantum_number;
            std::cout << "Please enter the inital quantum number. \n";
            initial_quantum_number = poisitive_interger_validation(initial_quantum_number);

            std::string final_quantum_number;
            std::cout << "Please enter the final quantum number. \n";
            final_quantum_number = poisitive_interger_validation(final_quantum_number);

            bool gate{ true };
            while (gate == true) { //loops to ensure initial quantum number is greater than final
                if (std::stoi(final_quantum_number) >= std::stoi(initial_quantum_number )) {
                    std::cout << "The initial quantum number needs to be greater than the final. \n";
                    std::cout << "Please enter a valid input\n\n";

                    std::cout << "Please enter the inital quantum number. \n";
                    initial_quantum_number = poisitive_interger_validation(initial_quantum_number);
                    std::cout << "Please enter the final quantum number. \n";
                    final_quantum_number = poisitive_interger_validation(final_quantum_number);
                }
                else {
                    break;
                }
            }

            std::cout << "\nThe atomic number you chose is " << atomic_number << " \n";
            std::cout << "The initial quantum number you chose is " << initial_quantum_number << " \n";
            std::cout << "The final quantum number you chose is " << final_quantum_number << " \n\n";

            std::cout << "Please type 'y' if you would like to work in J or 'n' if you would like to work in eV. \n";
            std::string unit;
            float calculated_energy{};
            calculated_energy = energy_calculation(atomic_number, initial_quantum_number, final_quantum_number, unit);
        }
        else if (answer == "n") {
            std::cout << "Thank you for your time. \n";
            break;
        }
        else {
            std::cout << "Please either enter 'y' or 'n' \n";
        }
        std::cout << "Would you like to calculate another transition? \n"
            "Select 'y' for yes and 'n' for no. \n";
    }
    return 0;
}
