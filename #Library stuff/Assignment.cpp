// Course:  CS213 - Programming II  - 2018
// Title:   Assignment I - Task 1 - Problem 0
// Program: CS213-2018-A1-T1-P0
// Purpose: Illustrating operator overloading by an example involving matricies.
// Author:  Ahmed Nasr Eldardery
// Date:    26 September 2018
// Version: 2

//Dardery's Notes:
//* This implementation is quite different from the one prepared by Dr. Elramly,
//    it uses oop techniques and memory management to avoid memory leaks.
//* The structure code is different, but the logic behind the arithmetic operators
//    is the same
//* Notice that the + and - operators are defined in terms of the += and -=
//	  operators respectivelly and not the other way around,
//	  this is done to avoid an unneccessary copy. The same is applied for scalar *
//* The 2D pointer array was requested in the assigment for team 0, however it should be
//    noted that this is not the most efficient way to store such an array, a better way
//    would be to save it as 1D array and access it using (i * col + j).
//    This is what was requested from team 1.
#include <iostream>
#include <iomanip>

using namespace std;

struct matrix
{
	int** data;
	int row, col;
	void allocate_memory(const int row, const int col) {
		this->row = row;
		this->col = col;
		if (row + col == 0) return;	//An empty matrix should not be initialized.

		data = new int*[row];

		for (int i = 0; i < row; i++)
			data[i] = new int[col];
	}

	// a constructor that takes the rows and columns count and initializes the memory with zeros.
	matrix(const int row = 0, const int col = 0) {
		allocate_memory(row, col);
	}

	template<class T>
	matrix<T>::matrix(const int row, const int col, const T * num)
	{
	}

	// a constructor that takes the rows and columns count and initializes the memory with memory from the 2D num array.
	// it first calls the above constructor.
	matrix(const int row, const int col, const int* num) : matrix(row, col) {
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				data[i][j] = *(num++);
	}

	// a copy constructor, extremly important to overload
	// this is what gets called when 'matrix mat = mat1;' is called
	// notice that it uses the = operator defined below.
	matrix(const matrix& old) {
		*this = old;
	}
	// a similar constructor, but for moving. Used when old is disposable,
	// such as if it is the return value of a function or a calculation.
	// std::move is there so that the second = operator is used instead of the first.
	matrix(matrix&& old) {
		*this = std::move(old);
	}

	// a copy operator for the = operator
	matrix& operator=(const matrix& old) {
		if (this->row + this->col != 0)
			this->~matrix();

		allocate_memory(old.row, old.col);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				data[i][j] = old[i][j];
		}
		return *this;
	}
	// a move operator for the = operator
	matrix& operator=(matrix&& old) {
		this->~matrix();
		data = old.data;
		row = old.row; col = old.col;
		old.row = old.col = 0;
		return *this;
	}
	//overloaded the [] operators so that the matrix' data can be accessed using
	//mat[i][j] instead of mat.data[i][j].
	int* operator[] (int i) const {
		return data[i];
	}

	//Deallocated the dynamic memory allocated by the constructor.
	~matrix() {
		if (row + col == 0) return;
		for (int i = 0; i < row; i++)
			delete[] data[i];
		delete[] data;
	}
};

matrix operator+  (const matrix& mat1, const matrix& mat2); // Add if same dimensions
matrix operator-  (const matrix& mat1, const matrix& mat2); // Sub if same dimensions
matrix operator*  (const matrix& mat1, const matrix& mat2); // Multi if col1 == row2
matrix operator+  (const matrix& mat1, const int scalar);   // Add a scalar
matrix operator-  (const matrix& mat1, const int scalar);   // Subtract a scalar
matrix operator*  (const matrix& mat1, const int scalar);   // Multiple by scalar

matrix operator-  (const matrix& mat1);                     // Unary negative

//redundant operators for reordering the operands
matrix operator+  (const int scalar, const matrix& mat1);   // Add a scalar
matrix operator-  (const int scalar, const matrix& mat1);   // Subtract a scalar
matrix operator*  (const int scalar, const matrix& mat1);   // Multiple by scalar


matrix& operator+= (matrix& mat1, const matrix& mat2);      // mat1 changes and is returned
matrix& operator-= (matrix& mat1, const matrix& mat2);      // mat1 changes and is returned
matrix& operator*= (matrix& mat, const matrix& mat2);		// mat1 changes and is returned
matrix& operator+= (matrix& mat, const int scalar);         // mat1 changes and is returned
matrix& operator-= (matrix& mat, const int scalar);         // mat1 changes and is returned
matrix& operator*= (matrix& mat, const int scalar);			// mat1 changes and is returned
matrix& operator++ (matrix& mat);                           // Add 1 to each element ++mat (prefix)
matrix  operator++ (matrix& mat, int);                      // Add 1 to each element mat++
matrix& operator-- (matrix& mat);    	                    // Sub 1 from each element --mat
matrix  operator-- (matrix& mat, int);    	                // Sub 1 from each element mat--

istream& operator>> (istream& in, matrix& mat);
ostream& operator<< (ostream& out, const matrix& mat);

bool   operator== (const matrix& mat1, const matrix& mat2);	// True if identical
bool   operator!= (const matrix& mat1, const matrix& mat2); // True if not same

bool   is_square(const matrix& mat);  // True if square matrix
bool   is_symetric(const matrix& mat);  // True if square and symmetric
bool   is_identity(const matrix& mat);  // True if square and identity
matrix transpose(const matrix& mat);    // Return new matrix with the transpose

int main()
{
	cout << left;

	int data1[] = { 1,2,3,4,5,6,7,8 };
	int data2[] = { 13,233,3,4,5,6 };
	int data3[] = { 10,100,10,100,10,100,10,100 };

	//Memory leakage test
	//If the implementation didn't have a destructor this would easily take over 3 GB of memory
	//and would probably crash
	/*
		for (int i = 0; i < 1e4; ++i) {
			matrix test1(160, 128);
			matrix test2(320, 64);
			matrix temp = test1;
			test1 = test2;
			test2 = temp;
			temp = 3 * test1;
			temp = test1 * 11;
			temp = test1 + test2;
		}
	*/

	matrix mat1(4, 2, data1),
		mat2(2, 3, data2),
		mat3(4, 2, data3),
		mat4 = mat3 * 2 + mat1 * 7,
		mat5;
	cout << "Matrix 1 is:" << endl << mat1 << endl;
	cout << "Matrix 2 is:" << endl << mat2 << endl;
	cout << "Matrix 3 is:" << endl << mat3 << endl;
	cout << "Matrix 4 is:" << endl << mat4 << endl;
	cout << "Enter matrix 5, rows columns and then data:" << endl;
	cin >> mat5;
	cout << "Matrix 5 is:" << endl << mat5 << endl;
	cout << "Matrix 1 + Matrix 3:" << endl;
	cout << (mat1 + mat3) << endl << endl;
	cout << "Matrix 3 + Matrix 3:" << endl;
	cout << (mat3 + mat3) << endl << endl;

	cout << "mat4 = 7 * mat1 + mat3 * 2 is: " << ((7 * mat1 + mat3 * 2 == mat4) ? "true" : "false") << endl;
	cout << "++++++mat1:" << endl;
	cout << ++++++mat1 << endl;
	cout << "mat1++:" << endl;
	cout << mat1++ << endl;
	cout << "Matrix 1 is:" << endl << mat1 << endl;
	cout << "mat4 = 7 * mat1 + mat3 * 2 is: " << ((7 * mat1 + mat3 * 2 == mat4) ? "true" : "false") << endl;
	cout << "----mat1:" << endl;
	cout << ----mat1 << endl;

	mat1 += mat3 += mat3;
	cout << "After doing mat1 += mat3 += mat3:" << endl;
	cout << "Matrix 1 is:" << endl << mat1 << endl;
	cout << "Matrix 2 is:" << endl << mat2 << endl;
	cout << "Matrix 3 is:" << endl << mat3 << endl;
	cout << "fail test: (shouldn't output anything)" << endl;
	cout << mat1 + mat2;
	return 0;
}

matrix operator+(const matrix& mat1, const matrix& mat2)
{
	matrix mat = mat1;
	mat += mat2;
	return mat;
}

matrix operator-(const matrix& mat1, const matrix& mat2)
{
	matrix mat = mat1;
	mat -= mat2;
	return mat;
}

matrix operator*(const matrix& mat1, const matrix& mat2)
{
	if (mat1.col != mat2.row) return matrix(0, 0);
	matrix mat(mat1.row, mat2.col);
	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat2.col; ++j)
			for (int k = 0; k < mat1.col; ++k)
				mat[i][j] += mat1[i][k] * mat2[k][j];

	return mat;
}

matrix operator+(const matrix& mat1, const int scalar)
{
	matrix mat = mat1;
	mat += scalar;
	return mat;
}
matrix operator-(const matrix& mat1, const int scalar)
{
	matrix mat = mat1;
	mat -= scalar;
	return mat;
}
matrix operator*(const matrix& mat1, const int scalar)
{
	matrix mat = mat1;
	mat *= scalar;
	return mat;
}


matrix operator-(const matrix& mat1) {
	matrix mat = matrix(mat1.row, mat1.col);
	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat1.col; ++j)
			mat[i][j] = -mat1[i][j];
	return mat;
}

matrix operator+(const int scalar, const matrix & mat1)
{
	return mat1 + scalar;
}
matrix operator-(const int scalar, const matrix & mat1)
{
	return mat1 + (-scalar);
}
matrix operator*(const int scalar, const matrix & mat1)
{
	return mat1 * scalar;
}

matrix& operator+=(matrix & mat1, const matrix& mat2)
{
	if (mat1.col != mat2.col || mat1.row != mat1.row)
		return mat1 = matrix(0, 0);

	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat1.col; ++j)
			mat1[i][j] += mat2[i][j];
	return mat1;
}

matrix& operator-=(matrix & mat1, const matrix& mat2)
{
	if (mat1.col != mat2.col || mat1.row != mat1.row)
		return mat1 = matrix(0, 0);

	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat1.col; ++j)
			mat1[i][j] -= mat2[i][j];
	return mat1;
}
matrix & operator*=(matrix & mat, const matrix & mat2)
{
	return mat = mat * mat2;
}
matrix& operator+=(matrix & mat, const int scalar)
{
	for (int i = 0; i < mat.row; ++i)
		for (int j = 0; j < mat.col; ++j)
			mat[i][j] += scalar;
	return mat;
}
matrix& operator-=(matrix & mat, const int scalar)
{
	for (int i = 0; i < mat.row; ++i)
		for (int j = 0; j < mat.col; ++j)
			mat[i][j] -= scalar;
	return mat;
}

matrix & operator*=(matrix & mat, const int scalar)
{
	for (int i = 0; i < mat.row; ++i)
		for (int j = 0; j < mat.col; ++j)
			mat[i][j] *= scalar;
	return mat;
}

matrix& operator++ (matrix& mat) {
	return mat += 1;
}

matrix operator++ (matrix& mat, int) {
	matrix tmp(mat);
	++mat;
	return tmp;
}

matrix& operator-- (matrix& mat) {
	return mat -= 1;
}

matrix operator-- (matrix& mat, int) {
	matrix tmp(mat);
	--mat;
	return tmp;
}

istream & operator>>(istream & in, matrix & mat)
{
	int row, col;
	in >> row >> col;
	mat.allocate_memory(row, col);

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			in >> mat[i][j];
	return in;
}

ostream & operator<<(ostream & out, const matrix& mat)
{
	for (int i = 0; i < mat.row; ++i) {
		for (int j = 0; j < mat.col; ++j)
			out << setw(5) << mat[i][j];
		out << '\n';
	}
	return out;
}

bool operator==(const matrix& mat1, const matrix& mat2)
{
	if (mat1.col != mat2.col || mat1.row != mat1.row) return false;
	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat1.col; ++j)
			if (mat1[i][j] != mat2[i][j])
				return false;

	return true;
}

bool operator!=(const matrix& mat1, const matrix& mat2)
{
	return !(mat1 == mat2);
}

bool is_square(const matrix & mat)
{
	return mat.row == mat.col;
}

bool is_symetric(const matrix & mat)
{
	if (!is_square(mat)) return false;
	for (int i = 0; i < mat.row; i++)
		for (int j = 0; j < mat.col; j++)
			if (mat[j][i] != mat[i][j]) return false;
	return true;
}

bool is_identity(const matrix & mat)
{
	if (!is_square(mat)) return false;
	for (int i = 0; i < mat.row; i++)
		for (int j = 0; j < mat.col; j++)
			if (mat[i][j] != (i == j)) return false;
	return true;
}

matrix transpose(const matrix& mat)
{
	matrix tranmat(mat.col, mat.row);
	for (int i = 0; i < mat.row; i++)
		for (int j = 0; j < mat.col; j++)
			tranmat[j][i] = mat[i][j];
	return tranmat;
}
