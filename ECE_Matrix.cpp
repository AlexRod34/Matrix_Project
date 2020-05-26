/*
Author: Alex Rodriguez
Class: ECE4122  
Last Date Modified: 9/19/2019
Description:
This file implements the header file ECE_Matrix.h to provide the class ECE_Matrix with constructors and operators overloaded in order to 
add, subtract matrices, multiply matrices with doubles, take the transpose of a matrix, and adding a matrix to another matrix via the += or subtract via 
the -= along with overloading the << operator to display the matrices.
*/
#include "ECE_Matrix.h"
#include <iostream>
#include "stdlib.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>


using namespace std;

ECE_Matrix::ECE_Matrix() // default constructor of size 0x0
{
	numRows = 0;
	numCols = 0;
}


ECE_Matrix::ECE_Matrix(const int &size, const double &value) // constructor sizexsize matrix, assigns single value to all elements
	{
		numRows = size;
		numCols = size;
		m_matrix.resize(size);
		for(int i = 0; i < size; i++)
		{
			m_matrix[i].resize(size, value); // adjusts the number of columns in each row and assigns value 
		}
	}
ECE_Matrix::ECE_Matrix(const int &m, const int &n, const double &value) //constructor mxn matrix, assigns single value to all elements
	{
		numRows = m;
		numCols = n;
		m_matrix.resize(m);
		for(int i = 0; i < m; i++)
		{
			m_matrix[i].resize(n, value); // adjusts the number of columns in each row and assigns value 
		}
	}
ECE_Matrix::ECE_Matrix(const char * file) //reads in a text file
	{
		ifstream myFile (file); // reads file
		string val;
		int rowIndex = 0;
		int colIndex = 0;
		double temp;
		

		if(myFile.is_open())
		{
			if(getline(myFile, val)) // reads in first row of dimensions
			{
				stringstream stream_val(val); // gets each number in the current line one at a time
				stream_val >> numRows; // first row in text file, 1st element 
				stream_val >> numCols; // first row in text file, 2nd element
				m_matrix.resize(numRows); // resizes the number of rows
				// adjusts how many columns in matrix
				for(int i = 0; i < numRows; i++)
				{
					m_matrix[i].resize(numCols); // resizes the number of columns in each row
				}
					// assigns matrix data to this m_matrix 
				while(getline(myFile, val)) // gets next line, starting at second line in file
				{
					stringstream stream_val(val);
					colIndex = 0; 
					while(1) // gets each number in each column until there is no valid column(stream_val) left, then moves to next row(line)
					{
						stream_val  >> m_matrix[rowIndex][colIndex]; //current number in matrix 
						if(!stream_val) // if no more elements left in row, go to next row
						{
							break;
						}
						colIndex++; // next column
					}
					rowIndex++; // next row
				}
			}

			
			myFile.close();
		}
		
	}

int ECE_Matrix::get_NumRows() const // gets num of rows
 {
     return this->numRows;
 }

 int ECE_Matrix::get_NumCols() const // gets num of cols
 {
     return this->numCols;
 }

//---------------------------------------------------------
// Add two ECE_Matricies
ECE_Matrix ECE_Matrix::operator+(ECE_Matrix const &rhs) const
{
	
    ECE_Matrix newMatrix(*this); // matrix to return
    int origlhsrows = newMatrix.numRows; // keeps track of left matrix row size
    int origlhscols = newMatrix.numCols; // keeps track of right matrix row size

    newMatrix.numRows = fmax(newMatrix.numRows,rhs.numRows); // gets new size of matrix
    newMatrix.numCols = fmax(newMatrix.numCols,rhs.numCols); // gets new size of matrix
    newMatrix.m_matrix.resize(newMatrix.numRows); // adjusts number of rows
		for(int i = 0; i < newMatrix.numRows; i++)
		{
			newMatrix.m_matrix[i].resize(newMatrix.numCols,0); // adjusts number of columns
		}

		for(int i = 0; i < newMatrix.numRows; i++) //adds the two matrices together, if a matrix does not have the element due to dimension disagreement, a zero is implied for the missing element.
    	{
        	for(int j = 0; j < newMatrix.numCols; j++)
        	{
        		if(j <= (fmin(origlhscols,rhs.numCols)-1) && i <= (fmin(origlhsrows,rhs.numRows)-1)) // for all the elements that are within the dimension agreements
        		{
        			newMatrix.m_matrix[i][j] = newMatrix.m_matrix[i][j] + rhs.m_matrix[i][j];

        		}
        		else if (origlhscols < rhs.numCols) // if one matrix has more columns than the other
        		{
        			newMatrix.m_matrix[i][j] = rhs.m_matrix[i][j];

        		}
        		else if (origlhsrows < rhs.numRows) // if one matrix has more rows than the other
        		{
        			newMatrix.m_matrix[i][j] = rhs.m_matrix[i][j];
        		}
        	}
    	}
    return newMatrix;
}
// Add a ECE_matrix and a double
ECE_Matrix ECE_Matrix::operator+(double const &inDouble) const
{
    ECE_Matrix newMatrix(*this); // matrix to return
    for(int i = 0; i < newMatrix.numRows; i++)
    {
        for(int j = 0; j < newMatrix.numCols; j++)
        {
            newMatrix.m_matrix[i][j] = newMatrix.m_matrix[i][j] + inDouble; // adds the double to each element in the left side matrix
        }
    }

    return newMatrix;
}    
// Add a double and a ECE_Matrix   
ECE_Matrix operator + ( double const &lhs, ECE_Matrix const &rhs) 
{ 
    ECE_Matrix newMatrix(rhs); // matrix to return
    for(int i = 0; i < newMatrix.numRows; i++)
    {
        for(int j = 0; j < newMatrix.numCols; j++)
        {
            newMatrix.m_matrix[i][j] = newMatrix.m_matrix[i][j] + lhs; // adds a double to each element in the right side matrix
        }
    }

    return newMatrix;
} 

// Subtract two ECE_Matricies
ECE_Matrix ECE_Matrix::operator-(ECE_Matrix const &rhs) const
{
    ECE_Matrix newMatrix(*this); // matrix to return
    int origlhsrows = newMatrix.numRows; // keeps track of left matrix row size
    int origlhscols = newMatrix.numCols; // keeps track of right matrix row size

    newMatrix.numRows = fmax(newMatrix.numRows,rhs.get_NumRows());  // gets new size of matrix
    newMatrix.numCols = fmax(newMatrix.numCols,rhs.get_NumCols()); // gets new size of matrix
    newMatrix.m_matrix.resize(newMatrix.numRows); // adjusts number of rows

		for(int i = 0; i < newMatrix.numRows; i++)
		{
			newMatrix.m_matrix[i].resize(newMatrix.numCols,0); // adjusts number of columns
		}

		for(int i = 0; i < newMatrix.numRows; i++) //adds the two matrices together, if a matrix does not have the element due to dimension disagreement, a zero is implied for the missing element.
    	{
        	for(int j = 0; j < newMatrix.numCols; j++)
        	{
        		if(j <= (fmin(origlhscols,rhs.get_NumCols())-1) && i <= (fmin(origlhsrows,rhs.get_NumRows())-1)) // for all the elements that are within the dimension agreements
        		{
        			newMatrix.m_matrix[i][j] = newMatrix.m_matrix[i][j] - rhs.m_matrix[i][j];

        		}
        		else if (origlhscols < rhs.get_NumCols()) // if one matrix has more columns than the other
        		{
        			newMatrix.m_matrix[i][j] = 0 - rhs.m_matrix[i][j];

        		}
        		else if (origlhsrows < rhs.get_NumRows()) // if one matrix has more rows than the other
        		{
        			newMatrix.m_matrix[i][j] = 0 - rhs.m_matrix[i][j];
        		}
        	}
    	}



    return newMatrix;
}
// Subtract a ECE_matrix and a double
ECE_Matrix ECE_Matrix::operator-(double const &inDouble) const
{
    ECE_Matrix newMatrix(*this); // matrix to return
    for(int i = 0; i < newMatrix.numRows; i++)
    {
        for(int j = 0; j < newMatrix.numCols; j++)
        {
            newMatrix.m_matrix[i][j] = newMatrix.m_matrix[i][j] - inDouble; // subtracts the double from element in the left side matrix
        }
    }

    return newMatrix;
}    
// Subtract a double and a ECE_Matrix   
ECE_Matrix operator - ( double const &lhs, ECE_Matrix const &rhs) 
{ 
    ECE_Matrix newMatrix(rhs); // matrix to return
    for(int i = 0; i < newMatrix.numRows; i++)
    {
        for(int j = 0; j < newMatrix.numCols; j++)
        {
            newMatrix.m_matrix[i][j] = lhs - newMatrix.m_matrix[i][j] ; // subtracts each element in right side matrix from the double 
        }
    }

    return newMatrix;
} 

// Multiply a ECE_matrix and a double
ECE_Matrix ECE_Matrix::operator*(double const &inDouble) const
{
    ECE_Matrix newMatrix(*this); // matrix to return
    for(int i = 0; i < newMatrix.numRows; i++)
    {
        for(int j = 0; j < newMatrix.numCols; j++)
        {
            newMatrix.m_matrix[i][j] = newMatrix.m_matrix[i][j]*inDouble; // multiply each element in matrix with double
        }
    }

    return newMatrix;
}    
// Multiply a double and a ECE_Matrix   
ECE_Matrix operator * ( double const &lhs, ECE_Matrix const &rhs) 
{ 
    ECE_Matrix newMatrix(rhs); // matrix to return
    for(int i = 0; i < newMatrix.numRows; i++)
    {
        for(int j = 0; j < newMatrix.numCols; j++)
        {
            newMatrix.m_matrix[i][j] = lhs*newMatrix.m_matrix[i][j] ; // multiply the double with each element in matrix
        }
    }

    return newMatrix;
} 
    
ECE_Matrix ECE_Matrix::transpose() const
{
	ECE_Matrix newMatrix(*this); // matrix to return
	newMatrix.numRows = this->numCols; // new row size is col size
	newMatrix.numCols = this->numRows; // new col size is row size
	newMatrix.m_matrix.resize(this->numCols); // adjusts the matrix row size
		for(int i = 0; i < this->numCols; i++)
		{
			newMatrix.m_matrix[i].resize(this->numRows); // adjusts the matrix col size
		}

	for (int i = 0; i < newMatrix.numCols; i++)
	{
		for ( int j = 0; j < newMatrix.numRows; j++)
		{
			newMatrix.m_matrix[j][i] = this->m_matrix[i][j]; // row elements become col elements
		}
	}
	return newMatrix;
}


// Divide a ECE_matrix and a double
ECE_Matrix ECE_Matrix::operator/(double const &inDouble) const
{
    ECE_Matrix newMatrix(*this); // matrix to return
    if(inDouble == 0.0) // if divide by zero, set all elements to zero
    {
	    for(int i = 0; i < newMatrix.numRows; i++)
	    {
	    	for(int j = 0; j < newMatrix.numCols; j++)
	        {
	            newMatrix.m_matrix[i][j] = 0;
	        }
	    }
    }
    else // divide each element in matrix by double
    {
	    for(int i = 0; i < newMatrix.numRows; i++)
	    {
	        for(int j = 0; j < newMatrix.numCols; j++)
	        {
	            newMatrix.m_matrix[i][j] = newMatrix.m_matrix[i][j]/inDouble;
	        }
	    }

    }

    return newMatrix;
}    

ECE_Matrix& ECE_Matrix::operator+=(ECE_Matrix const &rhs)
{
	*this = *this + rhs; // adds the right hand side matrix to current left matrix
	return *this;
}
    
ECE_Matrix& ECE_Matrix::operator-=(ECE_Matrix const &rhs)
{
	*this = *this - rhs; // subtracts the right hand side matrix from current left matrix
	return *this;
}
    
    
 //------------------------------------------------------------
 // Stream insertion operator
ostream& operator<<(ostream& os, const ECE_Matrix& m) // displays the entire matrix using << operator
{
    for(int i = 0; i < m.numRows; i++)
    {
        for(int j = 0; j < m.numCols; j++)
        {
            os << scientific << right << setw(12) << setprecision(3) << m.m_matrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}  