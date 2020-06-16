// 03/03/20 - Parampreet Singh 
//Assigmnet 6, Matricies with deep copying 

#include <iostream>
#include <string>
#include <sstream>

class Matrix
{
private:
	size_t row{ 1 };
	size_t column{ 1 };
	double* matrix_pointer{ nullptr };
	double index{};

public:
	Matrix()
	{
		std::cout << "Default constructor. " << std::endl;
		size_t size{ row * column };
		matrix_pointer = new double[size] {};
	}

	Matrix(double row_in, double column_in, int index_in) //Empty Matrix
	{
		std::cout << "Parameterised constructor. " << std::endl;
		row = row_in;
		column = column_in;
		index = index_in;
		size_t size = row * column;
		matrix_pointer = new double[size] {};
	}

	Matrix(double row_in, double column_in, int index_in, double* array_in) //Filled matrix
	{
		std::cout << "Parameterised constructor (non-zero). " << std::endl;
		row = row_in;
		column = column_in;
		index = index_in;
		size_t size = row * column;
		matrix_pointer = new double[size] {};
		for (size_t i{}; i < size; i++)
		{
			matrix_pointer[i] = array_in[i]; //fills the matrix
		}
	}

	//Copy constructor
	Matrix(Matrix const& matrix)
	{
		row = matrix.row;
		column = matrix.column;
		size_t size = row * column;
		matrix_pointer = new double[size];
		index = matrix.index + 1;

		for (int i{}; i < size; i++) //matrix_pointer = matrix.matrix_pointer
		{
			matrix_pointer[i] = matrix.matrix_pointer[i];
		}
	}

	//Move constructor 
	Matrix(Matrix&& matrix)
	{
		row = matrix.row; //Stealing data
		column = matrix.column;
		size_t size = row * column;
		index = matrix.index + 0.5;
		matrix_pointer = matrix.matrix_pointer;

		matrix.row = 0; //Reallocating data
		matrix.column = 0;
		matrix.matrix_pointer = nullptr;
	}

	~Matrix()
	{
		std::cout << "Destructor." << std::endl;
		delete[] matrix_pointer;
	}

	//Member Function 
	void show();
	double location(int i, int j); //i = row & j = column
	Matrix sub_matrix(int i, int j);
	double det();

	//overload assigment operator for deep copy and self assigment 
	/*
	Matrix& operator=(const Matrix& matrix) {
		if (&matrix == this) //If both matrix are identical
		{
			return *this;
		}
		else
		{
			row = matrix.row;
			column = matrix.column;
			size_t size = row * column;

			delete[] matrix_pointer; //Delete all the data in the left matrix
			matrix_pointer = new double[size]; // and assign it new memory

			for (int i{}; i < size; i++) //matrix_pointer =  matrix.matrix_pointer
			{
				matrix_pointer[i] = matrix.matrix_pointer[i];
			}
		}
	}
	*/
	//overload assigmnet operator for Move constructor
	Matrix& operator=(Matrix&& matrix)
	{
		std::swap(row, matrix.row);
		std::swap(column, matrix.column);
		std::swap(matrix_pointer, matrix.matrix_pointer);
		return *this;
	}

	//Overloading 
	Matrix operator+ (Matrix& matrix) //const 
	{
		if (row == matrix.row && column == matrix.column)  //Checking dimension
		{
			size_t size = row * column;
			double* temp_array{ new double[size] };
			for (int i{}; i < row; i++)
			{
				for (int j{}; j < column; j++)
				{
					temp_array[j + (i)*column] = this->location(i, j) + matrix.location(i, j);
				}
			}
			double use_this_index = index + (matrix.index * 0.1);
			Matrix temp(row, column, use_this_index, temp_array);
			delete[] temp_array;
			return temp;
		}
		else
		{
			std::cerr << "Please make sure the Matricies are the same dimensions. " << std::endl;
		}
	}
	Matrix operator- (Matrix& matrix)
	{
		if (row == matrix.row && column == matrix.column)
		{
			size_t size = row * column;
			double* temp_array{ new double[size] };
			for (int i{}; i < row; i++)
			{
				for (int j{}; j < column; j++)
				{
					temp_array[j + (i)*column] = this->location(i, j) - matrix.location(i, j);
				}
			}
			double use_this_index = index + (matrix.index * 0.2);
			Matrix temp(row, column, use_this_index, temp_array);
			delete[] temp_array;
			return temp;
		}
		else
		{
			std::cerr << "Please make sure the Matricies are the same dimensions. " << std::endl;
		}
	}
	Matrix operator* (Matrix& matrix)
	{
		if (column == matrix.row) //Checking dimensions
		{
			size_t size = matrix.row * matrix.column;
			double* temp_array{ new double[size] };

			for (int i{}; i < row; i++)
			{
				for (int j{}; j < matrix.column; j++)
				{
					int sum{};
					for (int k{}; k < column; k++)
					{
						sum = sum + (this->location(i, k)) * (matrix.location(k, j));
						temp_array[i * matrix.column + j] = sum;
					}
				}
			}
			double use_this_index = index + (matrix.index * 0.3);
			Matrix temp(matrix.row, matrix.column, use_this_index, temp_array);
			delete[] temp_array;
			return temp;
		}
		else
		{
			std::cerr << "Please make sure the Matricies have the same column and row size. " << std::endl;
		}
	}

	//Friend Function 
	friend std::ostream& operator<< (std::ostream& os, const Matrix& a);
	friend std::istream& operator>> (std::istream& is, Matrix& a);
};


//Member Function declaration
void Matrix::show()
{
	std::cout << "Matrix [" << index << "]: " << "Rows: " << row << "   Columns: " << column << "  Size: " << row * column << std::endl;
}
double Matrix::location(int i, int j)   //Extracts value at given locaiton in matrix;
{
	int m = (i)*this->column + (j);
	return this->matrix_pointer[m];
}
Matrix Matrix::sub_matrix(int i, int j)
{
	size_t size = (this->row - 1) * (this->column - 1);
	double* temp_array{ new double[size] };
	int counter{};
	for (int x{}; x < this->row; x++)
	{
		for (int y{}; y < this->column; y++)
		{
			if (y == i || x == j);
			else
			{
				temp_array[counter] = this->location(x, y);
				counter++;
			}
		}
	}
	double use_this_index = (this->index + 0.6);
	Matrix temp(this->row - 1, this->column - 1, use_this_index, temp_array);
	delete[] temp_array;
	return temp;
}
double Matrix::det()
{
	size_t size{ this->column * this->row };
	double sum{};
	if (size == 1)
	{
		return this->matrix_pointer[0];
	}
	else
	{
		for (size_t i{}; i < this->column; i++)
		{
			Matrix minor = this->sub_matrix(i, 0);
			sum += pow(-1, i) * this->location(0, i) * minor.det();
		}
		return sum;
	}
}

//Non-Member Function (Friend):
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
	int counter{};
	size_t size = matrix.row * matrix.column;
	os << "Matrix [" << matrix.index << "]:" << std::endl;
	for (int i{}; i < matrix.row; i++)
	{
		if (i != 0)
		{
			os << "\n";
		}
		for (int j{}; j < matrix.column; j++)
		{
			os << matrix.matrix_pointer[counter] << " ";
			counter++;
			if (counter == size)
			{
				os << std::endl;
			}
		}
	}
	return os;
}
std::istream& operator>>(std::istream& is, Matrix& matrix) {
	size_t size = matrix.row * matrix.column;
	for (int i{}; i < size; i++)
	{
		is >> matrix.matrix_pointer[i];
	}
	return is;
}

int main()
{
	std::string line{ "____________________________________________________________________________________________________" };
	double my_array_0[12]{};
	double my_array_1[2]{ 1, 2 };
	double my_array_2[12]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	double my_array_3[16]{ 1, 3, 1, 4, 3, 9, 5, 15, 0, 2, 1, 1, 0, 4, 2, 3 }; // det = -4

	std::cout << line << std::endl;
	Matrix matrix0;
	Matrix matrix1(1, 2, 1, my_array_1);
	Matrix matrix2(3, 4, 2, my_array_2);
	std::cout << matrix0;
	std::cout << matrix1;
	std::cout << matrix2;

	//copy assigment operator deep copy
	std::cout << line << std::endl;
	std::cout << "Copying matrix[1] into matrix[0]: " << std::endl;
	//matrix0 = matrix1;
	std::cout << matrix0;
	std::cout << matrix1;

	//move assignment 
	std::cout << line << std::endl;
	std::cout << "Now move values from Matrix[1] to Matrix[2] (Swap)" << std::endl;
	std::cout << matrix1;
	std::cout << matrix2;
	matrix1 = std::move(matrix2);
	std::cout << "Moving..." << std::endl;
	std::cout << matrix1;
	std::cout << matrix2;

	std::cout << line << std::endl;
	std::cout << matrix0 << "Is left unchanged -> Deep Copy. " << std::endl;

	//copy constructor deep copy
	std::cout << line << std::endl;
	std::cout << "Constructing Matrix [3] from Matrix [2]" << std::endl;
	Matrix matrix3(matrix2);
	std::cout << matrix3;

	//move constructor 
	std::cout << line << std::endl;
	std::cout << "Moving with constructor from Matrix[2] to Matrix[2.5]: " << std::endl;
	std::cout << matrix2 << std::endl;
	std::cout << "Moving... " << std::endl;
	Matrix matrix2_5 = std::move(matrix2);
	std::cout << matrix2_5;
	std::cout << matrix2;
	std::cout << "\nAll the data in Matrix 2 is deleted." << std::endl;

	std::cout << line << std::endl;
	std::cout << matrix3 << "Is left unchanged -> Deep Copy. " << std::endl;

	//Inputting a  Matrix:
	std::cout << line << std::endl;
	std::cout << "Modified istream: " << std::endl;
	Matrix matrix4(2, 2, 4);
	matrix4.show();
	std::cout << "Please enter the numbers to fill the matrix: " << std::endl;
	std::cin >> matrix4;
	std::cout << matrix4;

	std::cout << line << std::endl;
	Matrix matrix5(2, 2, 5);
	matrix5.show();
	std::cout << "Please enter the numbers to fill the matrix: " << std::endl;
	std::cin >> matrix5;
	std::cout << matrix5;

	// addition, subtraction and multipication
	std::cout << line << std::endl;
	std::cout << "Addition: Matrix[4] + Matrix[5] = " << std::endl;
	std::cout << matrix4 + matrix5 << std::endl;

	std::cout << line << std::endl;
	std::cout << "Subtraction: Matrix[4] - Matrix[5] = " << std::endl;
	std::cout << matrix4 - matrix5 << std::endl;

	std::cout << line << std::endl;
	std::cout << "Multipication: Matrix[4] * Matrix[5] = " << std::endl;
	std::cout << matrix4 * matrix5 << std::endl;

	//removing row and column
	std::cout << line << std::endl;
	Matrix matrix6(4, 4, 6, my_array_3); 
	std::cout << "Removing row and column from Matrix 6: " << std::endl;
	std::cout << matrix6 << std::endl;
	std::cout << matrix6.sub_matrix(0, 0) << std::endl;
	
	//recursion
	std::cout << line << line << "\n" <<"Recursivly determining the determinant of Matrix[6]: " << "\n" << line << line << std::endl;
	std::cout << line << line << "\n" << "The determinant of Matrix[6] is: " << matrix6.det() << "\n" << line << line << std::endl;
	return 0;
}


