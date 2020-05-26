/*
Author: Alex Rodriguez
Class: ECE4122  
Last Date Modified: 9/19/2019
Description:
This is the header file of the ECE_Matrix class. This outlines the available member functions to support the test file that was provided.
Allows creating matrices of different sizes, and perfoming operations such as adding, subtracting two matrices, adding and subtracting a matrix and a double,

*/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;


class ECE_Matrix
{
	int numRows; // number of rows in matrix
	int numCols; // number of columns in matrix
	vector <vector<double> > m_matrix; // a vector of a vector in order to make a numRows x numCols matrix


public:
	ECE_Matrix(); // default constructor 
	ECE_Matrix(const int &size, const double &value); // matrix with dimensions size x size and all elements as value
	ECE_Matrix(const int &m, const int &n, const double &value); // matrix with dimensions mxn and all elements as value
	ECE_Matrix(const char * file); // reads in a text file to create matrix 
	int get_NumRows() const;
	int get_NumCols() const;


	//operator assignments
	// Add two ECE_Matricies
    ECE_Matrix operator+(ECE_Matrix const &) const; 
    // Add a ECE_matrix and a double
    ECE_Matrix operator+(double const &) const; 
    // Add a double and a ECE_Matrix
    friend ECE_Matrix operator+(double const&, ECE_Matrix const &);
    // Subtract two ECE_Matricies
    ECE_Matrix operator-(ECE_Matrix const &) const; 
    // Subtract a ECE_matrix and a double
    ECE_Matrix operator-(double const &) const; 
    // Subtract a double and a ECE_Matrix
    friend ECE_Matrix operator-(double const&, ECE_Matrix const &);
    // Multiply a ECE_matrix and a double
    ECE_Matrix operator*(double const &) const; 
    // Multiply a double and a ECE_Matrix
    friend ECE_Matrix operator*(double const&, ECE_Matrix const &);
    // Take the transpose of a matrix
    ECE_Matrix transpose()const;
    // Divide a ECE_matrix and a double
    ECE_Matrix operator/(double const &) const; 

    //Addition assignment 
    ECE_Matrix& operator+=(ECE_Matrix const &); 
    //Subtraction assignment 
    ECE_Matrix& operator-=(ECE_Matrix const &); 




	


    // printing operator for displaying matrices neatly
	friend ostream& operator<<(ostream& os, const ECE_Matrix& m);	
};

