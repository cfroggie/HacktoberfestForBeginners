// main.cpp
// Tests all functionality of the class My_matrix class.

#include <iostream>
#include <fstream>
#include "My_matrix.h"

using namespace std;

int main(){
  
  // Some test cases are expected to throw an exception.
  // Add more try and catch blocks as necessary for your code
  // to finish execution.
    
  try{
	//******************************************************************//
    // Test 1
    // * Create an object of type My_matrix, called m1, using constructor
    // * Initialize m1 in main (by assigning numbers to matrix elements)
    // * Display m1 on the screen using the operator <<
	
	My_matrix m1 = My_matrix(2, 2);
	m1(0, 0) = 2;
	m1(0, 1) = 4;
	m1(1, 0) = 6;
	m1(1, 1) = 8;
	
	cout << "Test 1 output: " << endl << m1 << endl;
	
	//******************************************************************//
    // Test 2
    // * Create an object of type My_matrix, called m2, using (default)
    //   constructor
    // * Open an input file containing a matrix (row by row)
    // * Initialize m2 by reading from the input file using
    //   the operator >>
    // * Open an output file (can be empty)
    // * Write m2 to the output file using the operator <<
	
	ifstream fIn("input.txt", ios::in);
	ofstream fOut("output.txt", ios::out /*| ios::app*/ );
	
	My_matrix m2;
	fIn >> m2;
	fOut << m2;
	
	fIn.close();
	fOut.close();
	
	//******************************************************************//
    // Test 3
    // * Use the copy constructor to make a copy of m1 called m3
    // * Apply the copy assignment to m1 called m4
    // * Display m3 and m4 on the screen using the operator <<
	
	My_matrix m3(m1);
	My_matrix m4 = m1;
	
	cout << "Test 3 output: " << endl << m3 << endl << m4 << endl;
	
	//******************************************************************//
    // Test 4
    // * Test the matrix multiplication operator (operator*)
    // * Apply the multiplication operator to valid and invalid cases
    // * Display the resulting matrix and its number of rows and columns
	
	My_matrix val1 = My_matrix(2, 2);
	val1(0, 0) = 1;
	val1(0, 1) = 0;
	val1(1, 0) = 10;
	val1(1, 1) = 2;
	My_matrix val2 = My_matrix(2, 2);
	val2(0, 0) = 3;
	val2(0, 1) = 5;
	val2(1, 0) = 4;
	val2(1, 1) = 2;
	
	My_matrix inVal = My_matrix(1, 2);
	inVal(0, 0) = 3;
	inVal(0, 1) = 5;
	
	My_matrix valProd = val1 * val2;
	cout << "Valid matrix multiplication: " << endl;
	cout << valProd;
	cout << "Rows: " << valProd.number_of_rows() << endl;
	cout << "Columns: " << valProd.number_of_columns() << endl;
	
	try
	{
		//Invalid matrix multiplication, error is thrown
		cout << endl << "Invalid matrix multiplication: ";
		My_matrix inValProd = val1 * inVal;
	}
	catch(exception &error)
	{
		cerr << endl << "Error: " << error.what() << endl;
	}
	
   	//******************************************************************//
    // Test 5
    // * Test the matrix addition operator (operator+)
    // * Apply the multiplication operator to valid and invalid cases
    // * Display the resulting matrix and its number of rows and columns
		
	My_matrix valSum = val1 + val2;

	cout << endl << "Valid matrix addition: " << endl;
	cout << valSum;
	cout << "Rows: " << valSum.number_of_rows() << endl;
	cout << "Columns: " << valSum.number_of_columns() << endl;

	try
	{
		//Invalid matrix addition, error is thrown
		cout << endl << "Invalid matrix addition: ";
		My_matrix inValSum = val1 + inVal;
	}
	catch(exception &error)
	{
		
		cerr << endl << "Error: " << error.what() << endl;
	}
	
	//******************************************************************//
	//Move constructor test
	
	cout << endl << "Move constructor test: " << endl;
	My_matrix testMat = My_matrix(2, 2);
	testMat(0, 0) = 1;
	testMat(0, 1) = 2;
	testMat(1, 0) = 3;
	testMat(1, 1) = 4;
	cout << testMat << endl;
	
	My_matrix *Q = &testMat;
	My_matrix test2 = My_matrix(*Q);
	cout << test2 << endl;
	
	//******************************************************************//
	//Move assignment test
	
	cout << "Move assignment test: " << endl;
	My_matrix testMat2 = My_matrix(2, 2);
	testMat2(0, 0) = 4;
	testMat2(0, 1) = 3;
	testMat2(1, 0) = 2;
	testMat2(1, 1) = 1;
	cout << testMat2 << endl;
	
	My_matrix *Q2 = &testMat2;
	Q2 = Q;
	cout << testMat2 << endl;
	
	//******************************************************************//
  } catch(exception &error){
    cerr << "Error: " << error.what() << endl;
  }
}
