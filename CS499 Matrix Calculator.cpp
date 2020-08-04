// CS499 Matrix Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.


/*
Project Title:		Project_10
Project File:		Project_10.cpp
Name:				Tyler Dukes
Course Section:		CPE 211-02
Lab Section:		2
Due Date:			4/20/2018
Description:		A program that calculates determinants and performs other mathematical operations on matrices
*/

//#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <climits>
#include <math.h>

using namespace std;

typedef float MX[3][3];

struct arr
{
	MX matrix;
	int row;
	int col;
	
};

void OpenIn(ifstream&, string&);

void Determinant(float&, arr&);
void Transpose(arr&, arr&);
void Addition(arr&, arr&, arr&);
void Subtraction(arr&, arr&, arr&);
void Multiplication(arr&, arr&, arr&);
void Inverse(float&, arr&, arr&);

void ReadOne(ifstream&, arr&);
void ReadTwo(ifstream&, arr&, arr&);

/*
 I initially planned to combine many of these print functions into a smaller number to reduce the size of the program since they
 contain many common elements, but due to small differences, such as how the determinant function prints a number rather than a matrix, 
 for example, I think now that doing so would come at the cost of simplicity and ease of understanding.
*/
void PrintDeterminantMatrix(float&, arr&);
void PrintTransposeMatrix(arr&, arr&);
void PrintAddMatrix(arr&, arr&, arr&);
void PrintSubtMatrix(arr&, arr&, arr&);
void PrintMultipleMatrix(arr&, arr&, arr&);
void PrintInverseMatrix(arr&, arr&, float&);
void PrintInverseProof(arr&, arr&, arr&);

int main()
{
	string input;
	ifstream inFile;
	float det;
	int OPcode = 0;
	arr m1;
	arr m2;
	arr result;

	OpenIn(inFile, input);

	while (!inFile.eof())
	{
		inFile >> OPcode;

		if (OPcode == 1)
		{
			ReadOne(inFile, m1);
			Determinant(det, m1);
			PrintDeterminantMatrix(det, m1);
			inFile.ignore(INT_MAX, '\n');
			OPcode = 0;
			continue;
		}
		else if (OPcode == 2)
		{
			ReadOne(inFile, m1);
			Transpose(m1, result);
			PrintTransposeMatrix(m1, result);
			inFile.ignore(INT_MAX, '\n');
			OPcode = 0;
			continue;
		}
		else if (OPcode == 3)
		{
			ReadTwo(inFile, m1, m2);
			Addition(m1, m2, result);
			PrintAddMatrix(result, m1, m2);
			inFile.ignore(INT_MAX, '\n');
			OPcode = 0;
			continue;
		}
		else if (OPcode == 4)
		{
			ReadTwo(inFile, m1, m2);
			Subtraction(m1, m2, result);
			PrintSubtMatrix(result, m1, m2);
			inFile.ignore(INT_MAX, '\n');
			OPcode = 0;
			continue;
		}
		else if (OPcode == 5)
		{
			ReadTwo(inFile, m1, m2);
			Multiplication(m1, m2, result);
			PrintMultipleMatrix(m1, m2, result);
			inFile.ignore(INT_MAX, '\n');
			OPcode = 0;
			continue;
		}
		else if (OPcode == 6)
		{
			ReadOne(inFile, m1);
			Inverse(det, m1, result);
			PrintInverseMatrix(m1, result, det);
			inFile.ignore(INT_MAX, '\n');
			OPcode = 0;
			continue;
		}
	}
	return 0;
}
void OpenIn(ifstream& inFile, string& input)
{
	cout << endl;
	cout << "Enter name of input file or Control-C to quit program: ";
	getline(cin, input, '\n');
	cout << input;
	cout << endl;

	inFile.open(input.c_str());

	while (inFile.fail())
	{
		inFile.clear();
		cout << endl;

		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Input file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << input << endl;
		cout << "==> Please try again..." << endl;
		cout << string(47, '*') << endl;

		cout << endl;
		cout << "Enter name of input file or Control-C to quit program: ";
		getline(cin, input, '\n');
		cout << input;
		cout << endl;

		inFile.open(input.c_str());
	}

	return;
}
void Determinant(float& det, arr& m1)
{
	//cout << " Determinant! \n\n" << endl;
	
	//calculating the determinant by diagonal multiplication
	//
	//        |a b c|
	//   det  |d e f|
	//        |g h i| 
	//
	//   det = ((aei)+(bfg)+(cdh))-((gec)+(hfa)+(idb))

	float add, sub;
	float aei, bfg, cdh, gec, hfa, idb;
	aei = (m1.matrix[0][0]) * (m1.matrix[1][1]) * (m1.matrix[2][2]);
	bfg = (m1.matrix[0][1]) * (m1.matrix[1][2]) * (m1.matrix[2][0]);
	cdh = (m1.matrix[0][2]) * (m1.matrix[1][0]) * (m1.matrix[2][1]);

	gec = (m1.matrix[2][0]) * (m1.matrix[1][1]) * (m1.matrix[0][2]);
	hfa = (m1.matrix[2][1]) * (m1.matrix[1][2]) * (m1.matrix[0][0]);
	idb = (m1.matrix[2][2]) * (m1.matrix[1][0]) * (m1.matrix[0][1]);

	add = (aei)+(bfg)+(cdh);
	sub = (gec)+(hfa)+(idb);
	det = add - sub;

	return;
}
void Transpose(arr& m1, arr& result)
{
	//cout << "   MAKE IT DO THE FLIP!   \n\n" << endl;
	
	for (result.row = 0; result.row < 3; result.row++)
	{
		for (result.col = 0; result.col < 3; result.col++)
		{
			result.matrix[result.row][result.col] = m1.matrix[result.col][result.row];
		}
	}
	return;
}
void Addition(arr& m1, arr& m2, arr& result)
{
	//cout << "   ADDITION!   \n\n" << endl;

	//add into result
	for (result.row = 0; result.row < 3; result.row++)
	{
		for (result.col = 0; result.col < 3; result.col++)
		{
			result.matrix[result.row][result.col] = (m1.matrix[result.row][result.col] + m2.matrix[result.row][result.col]);
		}
	}
	return;
}
void Subtraction(arr& m1, arr& m2, arr& result)
{
	//cout << "   NEGATIVE ADDITION!   \n\n" << endl;

	//subtract m2 from m1 and put those values into result
	for (result.row = 0; result.row < 3; result.row++)
	{
		for (result.col = 0; result.col < 3; result.col++)
		{
			result.matrix[result.row][result.col] = (m1.matrix[result.row][result.col] - m2.matrix[result.row][result.col]);
		}
	}

	return;
}
void Multiplication(arr& m1, arr& m2, arr& result)
{
	//cout << "   SUPER-HECKIN'-RAPID ADDITION!   \n\n" << endl;

	for (result.row = 0; result.row < 3; result.row++)
	{
		for (result.col = 0; result.col < 3; result.col++)
		{
			result.matrix[result.row][result.col] = 0;
			for (int d = 0; d < 3; d++)
			{
				result.matrix[result.row][result.col] += m1.matrix[result.row][d] * m2.matrix[d][result.col];
			}
		}
	}
	return;
}
void Inverse(float& det, arr& m1, arr& result) 
{
	//STEP ONE - Obtain determinant to use in calculation of inverse.
	Determinant(det, m1);

	//No determinant = no inverse
	if (det == 0) {
		return;
	}

	//STEPS TWO and THREE - Matrix of minors & cofactors
				/*
						|a b c|
					A =	|d e f|
						|g h i|
				   |
				   |
				   |
				   |->	| +(ei-hf)	-(di-gf)	+(dh-ge)	|
						| 									|
						|									|
						| -(bi-hc)	+(ai-gc)	-(ah-gb)	|
						|									|
						|									|
						| +(bf-ec	-(af-dc)	+(ae-db)	|
				*/
	
	//Variables created to make code easier to understand in the minor and cofactor calculation block below
	float a = m1.matrix[0][0];
	float b = m1.matrix[0][1];
	float c = m1.matrix[0][2];
	float d = m1.matrix[1][0];
	float e = m1.matrix[1][1];
	float f = m1.matrix[1][2];
	float g = m1.matrix[2][0];
	float h = m1.matrix[2][1];
	float i = m1.matrix[2][2];
	
	//Calculate the element values for the minor and cofactor matrix
	float MinorAndCofactor_A = +((e * i) - (h * f));
	float MinorAndCofactor_B = -((d * i) - (g * f));
	float MinorAndCofactor_C = +((d * h) - (g * e));
	float MinorAndCofactor_D = -((b * i) - (h * c));
	float MinorAndCofactor_E = +((a * i) - (g * c));
	float MinorAndCofactor_F = -((a * h) - (g * b));
	float MinorAndCofactor_G = +((b * f) - (e * c));
	float MinorAndCofactor_H = -((a * f) - (d * c));
	float MinorAndCofactor_I = +((a * e) - (d * b));
	
	// Create the minor and cofactor matrix
	arr MCmatrix;
	MCmatrix.matrix[0][0] = MinorAndCofactor_A;
	MCmatrix.matrix[0][1] = MinorAndCofactor_B;
	MCmatrix.matrix[0][2] = MinorAndCofactor_C;
	MCmatrix.matrix[1][0] = MinorAndCofactor_D;
	MCmatrix.matrix[1][1] = MinorAndCofactor_E;
	MCmatrix.matrix[1][2] = MinorAndCofactor_F;
	MCmatrix.matrix[2][0] = MinorAndCofactor_G;
	MCmatrix.matrix[2][1] = MinorAndCofactor_H;
	MCmatrix.matrix[2][2] = MinorAndCofactor_I;

	//STEP FOUR - Transpose of Minors and Cofactors Matrix
	/*

						| +(ei-hf)	-(bi - hc)	+(bf-ec)	|
						| 									|
						|									|
						| -(di-gf)	+(ai-gc)	-(af - dc)	|
						|									|
						|									|
						| +(dh-ge)	-(ah-gb)	+(ae-db)	|

				*/
	Transpose(MCmatrix, result);

	//STEP FIVE - Multiply each element of the resulting Minors and Cofactors Matrix by: (determinant)^-1
	float inverseDet = pow(det, -1);
	
	for (result.row = 0; result.row < 3; result.row++)
	{
		for (result.col = 0; result.col < 3; result.col++)
		{
			result.matrix[result.row][result.col] = (result.matrix[result.row][result.col] * inverseDet);
		}
	}

	//Calculation complete. Return to call print function
	return;
}
void ReadOne(ifstream& inFile, arr& m1) {
	
	for (m1.row = 0; m1.row < 3; m1.row++)
	{
		for (m1.col = 0; m1.col < 3; m1.col++)
		{
			
			inFile >> m1.matrix[m1.row][m1.col];
			

		}
	}
	return;
}
void ReadTwo(ifstream& inFile, arr& m1, arr& m2) {
	for (m1.row = 0; m1.row < 3; m1.row++)
	{
		for (m1.col = 0; m1.col < 3; m1.col++)
		{
			inFile >> m1.matrix[m1.row][m1.col];
		}
	}

	// read matrix 2
	for (m2.row = 0; m2.row < 3; m2.row++)
	{
		for (m2.col = 0; m2.col < 3; m2.col++)
		{
			inFile >> m2.matrix[m2.row][m2.col];
		}
	}
}

void PrintDeterminantMatrix(float& det, arr& m1)
{
	cout << endl;
	cout << string(47, '*') << endl;
	cout << string(15, '*') << " Find Determinant " << string(14, '*') << endl;
	cout << endl;
	cout << "Input matrix:" << endl;
	for (m1.row = 0; m1.row < 3; m1.row++)
	{

		for (m1.col = 0; m1.col < 3; m1.col++)
		{
			cout << left << setw(6) << m1.matrix[m1.row][m1.col];
		}
		cout << endl;
	}
	cout << endl;
	cout << "The determinant is: " << det << endl;
	cout << endl;
//	cout << string(15, '*') << " Task Finished " << string(17, '*') << endl;
//	cout << string(47, '*') << endl;
	return;
}
void PrintTransposeMatrix(arr& m1, arr& result)
{
	cout << endl;
	cout << string(47, '*') << endl;
	cout << string(15, '*') << " Find Transpose " << string(16, '*') << endl;
	cout << endl;
	cout << "Input matrix:" << endl;

	for (m1.row = 0; m1.row < 3; m1.row++)
	{

		for (m1.col = 0; m1.col < 3; m1.col++)
		{
			cout << left << setw(6) << m1.matrix[m1.row][m1.col];
		}
		cout << endl;
	}
	cout << endl;
	cout << "The transpose is:" << endl;
	for (result.row = 0; result.row < 3; result.row++)
	{
		for (result.col = 0; result.col < 3; result.col++)
		{
			cout << left << setw(6) << result.matrix[result.row][result.col];
		}
		cout << endl;
	}
	cout << endl;
//	cout << string(15, '*') << " Task Finished " << string(17, '*') << endl;
//	cout << string(47, '*') << endl;
	return;
}
void PrintAddMatrix(arr& result, arr& m1, arr& m2)
{
	cout << endl;
	cout << string(47, '*') << endl;
	cout << string(15, '*') << " Add Two Matrices " << string(14, '*') << endl;
	cout << endl;
	cout << "Matrix A:" << endl;
	for (m1.row = 0; m1.row < 3; m1.row++)
	{

		for (m1.col = 0; m1.col < 3; m1.col++)
		{
			cout << left << setw(6) << m1.matrix[m1.row][m1.col];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Matrix B:" << endl;
	for (m2.row = 0; m2.row < 3; m2.row++)
	{

		for (m2.col = 0; m2.col < 3; m2.col++)
		{
			cout << left << setw(6) << m2.matrix[m2.row][m2.col];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Matrix A + Matrix B:" << endl;
	for (result.row = 0; result.row < 3; result.row++)
	{

		for (result.col = 0; result.col < 3; result.col++)
		{
			cout << left << setw(6) << result.matrix[result.row][result.col];
		}
		cout << endl;
	}
	cout << endl;
//	cout << string(15, '*') << " Task Finished " << string(17, '*') << endl;
//	cout << string(47, '*') << endl;
	return;
}
void PrintSubtMatrix(arr& result, arr& m1, arr& m2)
{
	cout << endl;
	cout << string(47, '*') << endl;
	cout << string(15, '*') << " Subtract Two Matrices " << string(9, '*') << endl;
	cout << endl;
	cout << "Matrix A:" << endl;
	for (m1.row = 0; m1.row < 3; m1.row++)
	{

		for (m1.col = 0; m1.col < 3; m1.col++)
		{
			cout << left << setw(6) << m1.matrix[m1.row][m1.col];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Matrix B:" << endl;
	for (m2.row = 0; m2.row < 3; m2.row++)
	{

		for (m2.col = 0; m2.col < 3; m2.col++)
		{
			cout << left << setw(6) << m2.matrix[m2.row][m2.col];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Matrix A - Matrix B:" << endl;
	for (result.row = 0; result.row < 3; result.row++)
	{

		for (result.col = 0; result.col < 3; result.col++)
		{
			cout << left << setw(6) << result.matrix[result.row][result.col];
		}
		cout << endl;
	}
	cout << endl;
//	cout << string(15, '*') << " Task Finished " << string(17, '*') << endl;
//	cout << string(47, '*') << endl;
	return;
}
void PrintMultipleMatrix(arr& m1, arr& m2, arr& result)
{
	cout << endl;
	cout << string(47, '*') << endl;
	cout << string(15, '*') << " Multiply Two Matrices " << string(9, '*') << endl;
	cout << endl;
	cout << "Matrix A:" << endl;
	for (m1.row = 0; m1.row < 3; m1.row++)
	{

		for (m1.col = 0; m1.col < 3; m1.col++)
		{
			cout << left << setw(6) << m1.matrix[m1.row][m1.col];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Matrix B:" << endl;
	for (m2.row = 0; m2.row < 3; m2.row++)
	{

		for (m2.col = 0; m2.col < 3; m2.col++)
		{
			cout << left << setw(6) << m2.matrix[m2.row][m2.col];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Matrix A * Matrix B:" << endl;
	for (result.row = 0; result.row < 3; result.row++)
	{

		for (result.col = 0; result.col < 3; result.col++)
		{
			cout << left << setw(6) << result.matrix[result.row][result.col];
		}
		cout << endl;
	}
	cout << endl;
//	cout << string(15, '*') << " Task Finished " << string(17, '*') << endl;
//	cout << string(47, '*') << endl;
}
void PrintInverseMatrix(arr& m1, arr& result, float& det)
{
	cout << endl;
	cout << string(47, '*') << endl;
	cout << string(13, '*') << " Inverse of a Matrix " << string(13, '*') << endl;
	cout << endl;
	cout << "Input Matrix:\n" << endl;
	for (m1.row = 0; m1.row < 3; m1.row++)
	{

		for (m1.col = 0; m1.col < 3; m1.col++)
		{
			cout << left << setw(6) << m1.matrix[m1.row][m1.col];
		}
		cout << endl;
	}
	// If the matrix has no inverse, explain and return
	if (det == 0) {
		cout << "\nThis matrix has no inverse because its determinant is " << det << endl;
		cout << endl;
		cout << string(15, '*') << " Task Finished " << string(17, '*') << endl;
		cout << string(47, '*') << endl;
		return;
	}

	cout << endl;
	cout << "Inverse of the Input Matrix:\n" << endl;
	for (result.row = 0; result.row < 3; result.row++)
	{

		for (result.col = 0; result.col < 3; result.col++)
		{
			cout << left << setprecision(4) << setw(10) << showpoint << fixed << result.matrix[result.row][result.col];
		}
		cout << endl;
	}
	//Prove that the answer is correct
	arr m2 = result;
	Multiplication(m1, m2, result);
	PrintInverseProof(m1, m2, result);

	cout << endl;
//	cout << string(15, '*') << " Task Finished " << string(17, '*') << endl;
	cout << string(47, '*') << endl;
	cout << string(47, '*') << endl;
}
void PrintInverseProof(arr& m1, arr& m2, arr& result)
{
	//Proof 
	cout << endl;
	cout << string(5, '*') << " Proof: (A * A^-1 = I) " << string(9, '*') << endl;
	cout << endl;
	cout << "Matrix A:" << endl;
	for (m1.row = 0; m1.row < 3; m1.row++)
	{

		for (m1.col = 0; m1.col < 3; m1.col++)
		{
			cout << left << setw(10) << m1.matrix[m1.row][m1.col];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Matrix A^-1:" << endl;
	for (m2.row = 0; m2.row < 3; m2.row++)
	{

		for (m2.col = 0; m2.col < 3; m2.col++)
		{
			cout << left << setw(10) << m2.matrix[m2.row][m2.col];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Matrix A * Matrix A^-1:" << endl;
	for (result.row = 0; result.row < 3; result.row++)
	{

		for (result.col = 0; result.col < 3; result.col++)
		{
			cout << left << setw(10) << setprecision(0) << result.matrix[result.row][result.col];
		}
		cout << endl;
	}
	cout << endl;
	return;
}