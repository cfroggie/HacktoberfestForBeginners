/* 
Implementation of the class My_matrix
*/

#include "My_matrix.h"
#include <stdexcept>

//default constructor
My_matrix::My_matrix() : m(0), n(0)                        //0 rows, 0 columns
{
  ptr = nullptr;
}

void My_matrix::allocate_memory()
{
  ptr = new int*[n]();
  for(int i = 0; i < n; ++i){
	  ptr[i] = new int[m]();                               //this should init all new ints to 0
  }
}

//parameter constructor
My_matrix::My_matrix(int n1, int m1) : n(n1), m(m1)
{
  allocate_memory();
}

//copy constructor
My_matrix::My_matrix(const My_matrix& mat) : n(mat.number_of_rows()), m(mat.number_of_columns())
{
  allocate_memory();
  for(int i = 0; i < n; ++i){
	  for(int j = 0; j < m; ++j){
		  ptr[i][j] = mat(i, j);
	  }
  }
}

// move constructor (optional)
My_matrix::My_matrix(My_matrix&& mat)
{
  My_matrix* mat2 = *new My_matrix();
  *mat2 = *mat;
}

//destructor
My_matrix::~My_matrix()
{
  for(int i = 0; i < n; ++i){
	  delete[] ptr[i];
  }
  delete[] ptr;
}

//copy assignment operator
My_matrix& My_matrix::operator=(const My_matrix& mat)
{
  return *new My_matrix(mat);
}

// move assignment operator (optional)
My_matrix& My_matrix::operator=(My_matrix&& mat)
{
  this->n = mat->n;
  this->m = mat->m;
  delete *this;
  this->ptr = mat->ptr;
  //delete mat;
}

int My_matrix::number_of_rows() const
{
  return n;
}

int My_matrix::number_of_columns() const
{
  return m;
}

//overloaded to access to ith row
int* My_matrix::operator()(int i) const
{
  return ptr[i];
}

//overloaded to access (i,j) element
int& My_matrix::operator()(int i, int j) const
{
  return ptr[i][j];
}

//overloaded to access (i,j) element
int& My_matrix::operator()(int i, int j)
{
  return ptr[i][j];
}

//overloaded to access (i,j) element
int& My_matrix::elem(int i, int j) const
{
  if (i < 0 || i >= n) throw out_of_range("Out of range");
  if (j < 0 || j >= m) throw out_of_range("Out of range");
  return ptr[i][j];
}

//overloaded to access (i,j) element
int& My_matrix::elem(int i, int j)
{
  if (i < 0 || i >= n) throw out_of_range("Out of range");
  if (j < 0 || j >= m) throw out_of_range("Out of range");
  return ptr[i][j];
}

//prints contents of matrices, row by row
ostream& operator<<(ostream& out, const My_matrix& mat)
{
  for(int i = 0; i < mat.number_of_rows(); ++i){
	  for(int j = 0; j < mat.number_of_columns(); ++j){
		  out << mat(i, j) << " ";
	  }
	  out << '\n';
  }
  return out;
}

//reads input, row by row, to a matrix
istream& operator>>(istream& in, My_matrix& mat)
{
  in >> mat.n >> mat.m;
  mat.allocate_memory();
  
  try{
	  for(int i = 0; i < mat.number_of_rows(); ++i){
		  for(int j = 0; j < mat.number_of_columns(); ++j){
			  in >> mat(i, j);
		  }
	  }
  }
  catch(exception &e){
	  throw invalid_input();
  }
  return in;
}

//adding matrices of n*m, n*m size
My_matrix operator+(const My_matrix& mat1, const My_matrix& mat2)
{
  if(mat1.number_of_rows() != mat2.number_of_rows() || mat1.number_of_columns() != mat2.number_of_columns()){
	  throw incompatible_matrices();
  }
  My_matrix sum(mat1.number_of_rows(), mat1.number_of_columns());
  for(int i = 0; i < mat1.number_of_rows(); i++){
	  for(int j = 0; j < mat1.number_of_columns(); j++){
		  sum(i, j) = mat1(i, j) + mat2(i, j);
	  }
  }
  return sum;
}

//multiplying matrices of n*m, m*p size
My_matrix operator*(const My_matrix& mat1, const My_matrix& mat2)
{
  if(mat1.number_of_columns() != mat2.number_of_rows()){
	  throw incompatible_matrices();
  }
  My_matrix product(mat1.number_of_rows(), mat2.number_of_columns());
  for(int i = 0; i < mat1.number_of_rows(); ++i){
	 for(int j = 0; j < mat2.number_of_columns(); ++j){
		  product(i, j) = product[i][j];
	 }
  }
  return product;
}
