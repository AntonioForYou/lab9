#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

Matrix::Matrix(string txt)
{
	int pis = 1;
	int rows, cols; ifstream fin(txt);

	fin >> rows;
	fin >> cols;
	
	A.resize(rows);

	for (int i = 0; i < rows; i++)
	{
		A[i].resize(cols);
		for (int j = 0; j < cols; j++)
		{
			fin >> A[i][j];
		}
	}
	fin.close();

	A_clon = A;
}

void Matrix::SweepMethod()
{
	vector<double> x(A.size()), b(A.size()), a(A.size() - 1), c(A.size() - 1), d(A.size()), p(A.size() - 1), q(A.size() - 1);

	for (int i = 0; i < A.size() - 1; i++)
	{
		c[i] = A[i][i + 1];
		a[i] = A[i + 1][i];
	}


	for (int i = 0; i < A.size(); i++)
	{
		d[i] = A[i][A[0].size() - 1];
		b[i] = A[i][i];
	}


	double sum; unsigned int k = 0;

	for (int i = 0; i < A.size(); i++)
	{
		if (i == 0)
			sum = fabs(c[i]);
		else if (i == A.size() - 1)
			sum = fabs(a[i - 1]);
		else
			sum = fabs(a[i]) + fabs(c[i]);

		if (b[i] > sum)
			k++;
		sum = 0;
	}

	//if (k > 0)
	//{
		p[0] = -c[0] / b[0];
		q[0] = d[0] / b[0];


		for (int i = 1; i < A.size() - 1; i++)
		{		
			p[i] = -c[i] / (b[i] + a[i - 1] * p[i - 1]);
			q[i] = (d[i] - a[i - 1] * q[i - 1]) / (b[i] + a[i - 1] * p[i - 1]);
		}

		x[x.size() - 1] = (d[x.size() - 1] - a[x.size() - 2] * q[x.size() - 2]) / (b[x.size() - 1] + a[x.size() - 2] * p[x.size() - 2]);

		for (int i = x.size() - 2; i >= 0; i--)
		{
			x[i] = p[i] * x[i + 1] + q[i];
		}


		cout << "X = {";
		for (int i = 0; i < x.size(); i++)
		{
			if (i == x.size() - 1)
			{
				cout << fixed << setprecision(4) << x[i] << "}";
			}
			else
			{
				cout << fixed << setprecision(4) << x[i] << ", ";
			}
		}

		cout << endl; 

		/*double*/ sum = 0;

		for (int i = 0; i < A.size(); i++)
		{
			sum = 0;
			for (int j = 0; j < A.size(); j++)
			{
				sum += A[i][j] * x[j];
			}

			cout << sum << " = " << A[i][A.size()] << endl;
		}

	//}
	//else
	//	cout << "               !" << endl;
}

vector<vector<double>> Matrix::GetMatrixWithoutRowCol(int row, int col, vector<vector<double>> newMatrix)
{
	int offsetRow = 0, offsetCol = 0, size = newMatrix.size(); vector<vector<double>> newMatrix2(size - 1);

	for (size_t i = 0; i < size - 1; i++)
	{
		newMatrix2[i].resize(size - 1);
	}


	for (int i = 0; i < size - 1; i++)
	{
		if (i == row)
			offsetRow = 1;

		offsetCol = 0;

		for (int j = 0; j < size - 1; j++)
		{
			if (j == col)
				offsetCol = 1;

			newMatrix2[i][j] = newMatrix[i + offsetRow][j + offsetCol];
		}
	}


	return newMatrix2;
}

double Matrix::det(vector<vector<double>> newMatrix, int size)
{
	double det = 0; int degree = 1;


	if (size == 1)
		return newMatrix[0][0];

	if (size == 2)
		return newMatrix[0][0] * newMatrix[1][1] - newMatrix[0][1] * newMatrix[1][0];

	vector<vector<double>> newMatrix2(size - 1);

	for (size_t i = 0; i < size - 1; i++)
	{
		newMatrix2[i].resize(size - 1);
	}

	for (size_t j = 0; j < size; j++)
	{
		newMatrix2 = this->GetMatrixWithoutRowCol(0, j, newMatrix);

		det = det + (degree * newMatrix[0][j] * this->det(newMatrix2, newMatrix2.size()));

		degree = -degree;
	}

	return det;
}

vector<vector<double>> Matrix::getData()
{
	return A;
}


void Matrix::display()
{
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A[i].size(); j++)
		{
			if (j == A.size())
			{
				cout.width(10); cout << left; cout << "|"; cout << fixed << setprecision(4) << A[i][j] << " ";
			}
			else
			{
				cout.width(10); cout << left; cout << fixed << setprecision(4) << A[i][j] << " ";
			}

		}
		cout << endl;
	}
	cout << endl;
}


void Matrix::GaussMethod()
{

	if (this->det(this->getData(), A.size()) != 0)
	{ 
		cout << "                          : " << this->det(this->getData(), A.size()) << endl; //                              .                 -                 ,                 -              .

		cout << endl;

		double time;

		for (int r = 0; r < A.size() - 1; r++) //           .                                       .
		{
			for (int j = r + 1; j < A.size(); j++)
			{
				if (A[j][r] == 0) //       1.1            .
					continue;

				time = -A[r][r] / A[j][r]; //       1.2.1            .

				for (int i = 0; i < A[0].size(); i++) //       1.2.3            .
				{
					A[j][i] *= time;
					A[j][i] += A[r][i];

					if (fabs(A[j][i]) < epsilon) //                             ,                        ,                           .                    ,                                   .                                                .
						A[j][i] = 0;
				}
			}
		}

		cout << "                                       : \n" << endl; //             ,                                .
		this->display();

		for (int r = A.size() - 1; r >= 0; r--) //             .
		{
			for (int j = A.size() - 1; j > r; j--) 
			{
				A[r][A.size()] -= A[r][j]; //                     b                               .
				A[r][j] = 0; //                  .
			}

			A[r][A.size()] /= A[r][r]; //                        b            ,                                 .

			A[r][r] = 1; //                                                    1.

			for (int m = r; m > 0; m--)
				A[m - 1][r] *= A[r][A[0].size() - 1]; //                 Xi.       2                .
		}

		//                   .

		cout << "X = {";

		for (int i = 0; i < A[0].size() - 1; i++)
		{
			if (i == A[0].size() - 2)
			{
				cout << fixed << setprecision(4) << A[i][A[0].size() - 1] << "}";
			}
			else
			{
				cout << fixed << setprecision(4) << A[i][A[0].size() - 1] << ", ";
			}
		}
		cout << endl;


		this->display();

		double sum;

		//                        ,                   .             A[i][j]           b                         .                            .

		cout << "X_         = {";

		for (int i = 0; i < A.size(); i++)
		{
			sum = 0;

			for (int j = 0; j < A.size(); j++)
			{
				sum += A[i][j] * A[i][A.size()];
			}
			
			if (i == A.size() - 1)
			{
				cout << fixed << setprecision(4) << sum << "}";
			}
			else
			{
				cout << fixed << setprecision(4) << sum << ", ";
			}
		}

		cout << endl;

		
	}
	else
		cout << "                       .                                                   !" << endl;



	
}