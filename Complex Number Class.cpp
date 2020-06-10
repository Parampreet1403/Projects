//26/02/20 parampreet singh 
//assignment 5: c++ class to store and manipulate complex numbers

#include <iostream>
#include <string>
#include <cmath>
#include <math.h>

const double pi {3.14159265358979323846};

//questions:
/*
 void my_member_function(double my_double) const 
immutability
gurantees member data are not modified

use const to
1) prevent parameters being modified 
2)prevent member data being modified 
*/
//Asap questions 
/*
in addition function, temp is created as a complex_number hence c and temp are both destructed. (duplicate). How to fix?

*/

class complex_number  // z = x + iy type double
{
private:
    double x{};
    double y{};
    std::string complex{ "i" };
    std::string index{"0"};

public:
    //constructors and deconstuctor
    complex_number() {
        //std::cout << "default constructor: " << std::endl;
        std::cout << "Creating complex number [" << index << "]: " << x << " + " << y << complex << std::endl;
    }
    complex_number(double x_in, double y_in, std::string index_in) {
        //std::cout << "parameterised constructor: " << std::endl;
        x = x_in;
        y = y_in;
        index = index_in;
        if (y >= 0) {
            std::cout << "Creating complex number [" << index << "]: " << x << " + " << y << complex << std::endl;
        }
        else {
            std::cout << "Creating complex number [" << index << "]: " << x << " " << y << complex << std::endl;
        }

    }
    ~complex_number() { 
        std::cout << "Destroying complex number [" << index << "]" << std::endl;
    }


    //member functions:
    void return_real();
    void return_imaginary();
    void return_modulus();
    void return_argument();
    void return_complex_conjugate();


    //overloading:
    complex_number operator+ (const complex_number& a) const {
        complex_number temp{ x + a.x, y + a.y, index + "+" + a.index };
        return temp;
    }
    complex_number operator- (const complex_number& a) const {
        complex_number temp{ x - a.x, y - a.y, index + "-" + a.index };
        return temp;
    }
    complex_number operator* (const complex_number& a) const {
        complex_number temp{ (x * a.x) + -1 * (y * a.y), (y * a.x) + (x * a.y), index + "*" + a.index };
        return temp;
    }
    complex_number operator/ (const complex_number& a) const {
        complex_number temp{ x / a.x, y / a.y, index + "/" + a.index };
        return temp;
    }

    friend std::ostream& operator<< (std::ostream& os, const complex_number& a);
    friend std::istream& operator>> (std::istream& is, complex_number& a);
};


//member function declaration:
void complex_number::return_real() {
    std::cout << "the real part of compelx number [" << index << "]: " << x << std::endl;
}
void complex_number::return_imaginary() {
    std::cout << "the imaginary part of compelx number [" << index << "]: " << y << std::endl;
}
void complex_number::return_modulus() {
    double modulus = std::sqrt((x*x) + (y*y));
    std::cout << "the modulus of complex number [" << index << "]: " << modulus << std::endl;
}
void complex_number::return_argument() { //arg(z) = arctan(im/re)
    double argument = std::atan(y/x); //radians
    double argument_degrees = argument * (180 / pi);
    std::cout << "the argument of complex number [" << index << "]: " << argument_degrees << std::endl;
}
void complex_number::return_complex_conjugate() {
    if (y >= 0) { //evaluates for positive imaginary number
        double temp_y = -y;
        std::cout << "the complex conjugate of complex number [" << index << "]: " << x << " " << temp_y << complex << std::endl;
    }
    else {
        double temp_y = -y;
        std::cout << "the complex conjugate of complex number [" << index << "]: " << x << " + " << temp_y << complex << std::endl;
    }
}

//non-member funciton (friend):
std::ostream& operator<<(std::ostream& os, const complex_number& a) {
    if (a.y >= 0) {
        os << "*Complex number [" << a.index << "]: " << "(" << a.x << " + " << a.y << a.complex << ")" << std::endl;
    }
    else {
        os << "*Complex number [" << a.index << "]: " << "(" << a.x << " " << a.y << a.complex << ")" << std::endl;
    }

    return os;
}
std::istream& operator>>(std::istream& is, complex_number& a) {
    is >> a.x >> a.y >> a.complex;
    return is;
}


int main() {
    //complex_number default_constructor;
    complex_number a{3, 4, "1"};
    complex_number b{ 1, -2, "2" };
    
    a.return_real();
    a.return_imaginary();
    a.return_modulus();
    a.return_argument();
    a.return_complex_conjugate();

    b.return_real();
    b.return_imaginary();
    b.return_modulus();
    b.return_argument();
    b.return_complex_conjugate();
    
    complex_number c{ a + b };
    complex_number d{ a - b };
    complex_number e{ a * b };
    complex_number f{ a / b };
    
    std::cout << "Modified ostream for " << b;
    complex_number z;
    std::cout << "Please input the real and imaginary number in the form: 'a+bi' or 'a-bi'"<< std::endl;
    std::cin >> z;
    std::cout << z;

    return 0;
}