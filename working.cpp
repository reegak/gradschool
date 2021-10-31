#include<iostream>
#include<fstream>

int main()
{
	std::ifstream file("D.txt");
	int rows;
	int cols;

	std::cout << "How many rows are in the matrix? \n";
	std::cin >> rows;
	std::cout << "How many columns are in the matrix? \n";
	std::cin >> cols;
	std::cout << "rows: " << rows << " cols: " << cols << "\n";

	double matrix[rows][cols];
	double A[rows][cols];
	if (file.is_open())
	{
		while (!file.eof())
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					file >> matrix[i][j];
				}

			}
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			A[i][j] = matrix[i][j];
		}

	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "\n";

	}
	std::cout << "\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << A[i][j] << "\t";
		}
		std::cout << "\n";

	}

	
	int zeros = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == j && matrix[i][j] == 0)
			{
				std::cout << "There are zeros in the main diagonal\n";
				
				zeros++;
			}
		}
	}

	std::cout << "There are " << zeros << " zeros in the main diagonal\n";
	//LU decomposition
	double lower[rows][cols];
	double upper[rows][cols];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (j < i)
			{
				lower[j][i] = 0;
			}
			
			else
			{
				lower[j][i] = matrix[j][i];
				for (int k = 0; k < i; k++)
				{
					lower[j][i] = lower[j][i] - lower[j][k] * upper[k][i];
				}
			}
		}
		for (int j = 0; j < rows; j++)
		{
			if (j < i)
			{
				upper[i][j] = 0;
			}
			else if (j == i)
			{
				upper[i][j] = 1;
			}
			else
			{
				upper[i][j] = matrix[i][j] / lower[i][i];
				for (int k = 0; k < i; k++)
				{
					upper[i][j] = upper[i][j] - ((lower[i][k] * upper[k][j]) / lower[i][i]);
				}
			}
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << upper[i][j] << "\t";
		}
		std::cout << "\n";

	}
	std::cout << "\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << lower[i][j] << "\t";
		}
		std::cout << "\n";

	}
	//which pivot?
	std::cout << "Which method? \nie 1 for no pivoting, 2 partial pivoting or 3 complete pivoting\n";
	int method;
	std::cin >> method;

	//pivot

	switch (method)
	{
	case 1:
	{
		std::cout << "Method: no pivoting\n";
		if (zeros >0)
		{
			std::cout << "There are zeros in the main diagonal! Cannot proceed!\n";
			return 0;
		}
		//LU decomposition
		double L[rows][cols];
		double U[rows][cols];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (j < i)
				{
					L[j][i] = 0;
				}
				else
				{
					L[j][i] = matrix[j][i];
					for (int k = 0; k < i; k++)
					{
						L[j][i] = L[j][i] - L[j][k] * U[k][i];
					}
				}
			}
			for (int j = 0; j < rows; j++)
			{
				if (j < i)
				{
					U[i][j] = 0;
				}
				else if (j == i)
				{
					U[i][j] = 1;
				}
				else
				{
					U[i][j] = matrix[i][j] / L[i][i];
					for (int k = 0; k < i; k++)
					{
						U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
					}
				}
			}
		}
		std::cout << "Upper Matrix:\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << U[i][j] << "\t";
			}
			std::cout << "\n";

		}
		std::cout << "\n";
		std::cout << "Lower Matrix:\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << L[i][j] << "\t";
			}
			std::cout << "\n";

		}
		break;
	}
	case 2:
	{
		std::cout << "Method: partial pivoting\n";
		int n = 0;
		do
		{
			double temp;
			double max = 0;
			int l = n;
			for (int i = n; i < cols; i++)
			{
				for (int j = n; j < rows; j++)
				{
					temp = matrix[j][i];
					if (temp > max)
					{
						max = temp;
						l = j;

					}
				}
			}
			for (int i = n; i < cols; i++)
			{
				double alpha = matrix[l][i];
				matrix[l][i] = matrix[n][i];
				matrix[n][i] = alpha;
			}
			for (int j = n; j < cols; j++)
			{
				double beta = matrix[j][l];
				matrix[j][l] = matrix[j][n];
				matrix[j][n] = beta;
			}
			n++;
		} while (rows > n && cols > n);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << matrix[i][j] << "\t";
			}
			std::cout << "\n";

		}
		//LU decomposition
		double L[rows][cols];
		double U[rows][cols];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (j < i)
				{
					L[j][i] = 0;
				}
				else
				{
					L[j][i] = matrix[j][i];
					for (int k = 0; k < i; k++)
					{
						L[j][i] = L[j][i] - L[j][k] * U[k][i];
					}
				}
			}
			for (int j = 0; j < rows; j++)
			{
				if (j < i)
				{
					U[i][j] = 0;
				}
				else if (j == i)
				{
					U[i][j] = 1;
				}
				else
				{
					U[i][j] = matrix[i][j] / L[i][i];
					for (int k = 0; k < i; k++)
					{
						U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
					}
				}
			}
		}
		std::cout << "Upper Matrix:\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << U[i][j] << "\t";
			}
			std::cout << "\n";

		}
		std::cout << "\nLower Matrix:\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << L[i][j] << "\t";
			}
			std::cout << "\n";

		}
		break;
	}
	case 3:
	{
		std::cout << "Method: complete pivoting\n";
		int n = 0;
		do
		{

			double temp;
			double max = 0;
			int l, m = n;
			for (int i = n; i < cols; i++)
			{
				for (int j = n; j < rows; j++)
				{
					temp = matrix[j][i];
					if (temp > max)
					{
						max = temp;
						l = j;
						m = i;
					}
				}
			}
			for (int i = n; i < cols; i++)
			{
				double alpha = matrix[l][i];
				matrix[l][i] = matrix[n][i];
				matrix[n][i] = alpha;
			}
			for (int j = n; j < cols; j++)
			{
				double beta = matrix[j][m];
				matrix[j][m] = matrix[j][n];
				matrix[j][n] = beta;
			}
			n++;
		} while (rows > n && cols > n);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << matrix[i][j] << "\t";
			}
			std::cout << "\n";

		}
		std::cout << "\n";
		//LU decomposition
		double L[rows][cols];
		double U[rows][cols];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (j < i)
				{
					L[j][i] = 0;
				}
				else
				{
					L[j][i] = matrix[j][i];
					for (int k = 0; k < i; k++)
					{
						L[j][i] = L[j][i] - L[j][k] * U[k][i];
					}
				}
			}
			for (int j = 0; j < rows; j++)
			{
				if (j < i)
				{
					U[i][j] = 0;
				}
				else if (j == i)
				{
					U[i][j] = 1;
				}
				else
				{
					U[i][j] = matrix[i][j] / L[i][i];
					for (int k = 0; k < i; k++)
					{
						U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
					}
				}
			}
		}
		std::cout << "Upper Matrix:\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << U[i][j] << "\t";
			}
			std::cout << "\n";

		}
		std::cout << "\nLower Matrix:\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << L[i][j] << "\t";
			}
			std::cout << "\n";

		}
		break;
	}
	default:
	{
		std::cout << "Please choose another choice\n";
		break;
	}
	}



	file.close();

}