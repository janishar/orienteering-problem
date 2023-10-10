#include<iostream>
using namespace std;
int const SIZE = 322560;
int combinationobjects[SIZE];
int factorial(int n)
{
	if (n == 1)
		return n;
	return n*factorial(n - 1);
}
void print(int mat[SIZE], int n)
{
	int nx = factorial(n);
	int count = 0;
	for (int i = 0; i<nx; i++)
	{
		for (int j = 0; j<n; j++)
		{
			cout << mat[count++] << " ";
		}
		cout << endl;
	}
}
void combination(int n)
{
	int count = 0,track=0, nx = factorial(n);
	int tempStore[SIZE];
	for (int i = 0; i<nx; i++)
	{
		for (int j = 0; j<n; j++)
		{
			tempStore[count++] = combinationobjects[j];
		}
	}
	int k = 1, d = 0,h=0,t = 0, shifter = 0, flag = 0, position = 0;
	count = 0;
	for (int dp = 0; dp<n - 1; dp++)
	{
		while (h<nx)
		{
			for (int dk = 0; dk<n - d; dk++)
			{
				for (int loop = 0; loop<factorial(n - k); loop++)
				{
					for (int dt = count*n; dt<count*n + n; dt++)
					{
						if (tempStore[dt] == 0)
						{
							position = dt;
							flag = 1;
							break;
						}
					}
					if (flag == 1)
					{
						for (int dl = count*n; dl<count*n + n; dl++)
						{
							if (tempStore[dl] != 0)
							{
								t = dl;
								break;
							}
						}
					}
					else if (flag == 0)
					{
						t = count*n;
					}
					while (1)
					{
						if (tempStore[t + shifter] == 0)
							shifter++;
						else
							break;
					}
					combinationobjects[count*n + d] = tempStore[t + shifter];
					tempStore[t + shifter] = 0;
					track++;
					count++;
					h++;
				}
				shifter++;
			}
			shifter = 0;
		}
		count = 0;
		k++;
		h = 0;
		d++;
	}
	for (int i = 0; i<nx; i++)
	{
		for (int j = i*n; j<i*n + n; j++)
		{
			if (tempStore[j] != 0)
			{
				combinationobjects[i*n + n - 1] = tempStore[j];
				track++;
				break;
			}
		}
	}
	cout << "total combination = " << int(track / n) << endl;
	cout << "..........................." << endl;
	print(combinationobjects, n);
}
int main()
{
	cout << "enter y to run the program or enter anything else to exit" << endl;
	char in;
	cin >> in;
	while (in == 'y')
	{
		cout << "enter the number of objects" << endl;
		int n;
		cin >> n;
		cout << "enter the objects" << endl;
		for (int i = 0; i<n; i++)
		{
			cin >> combinationobjects[i];
		}
		combination(n);
		cout << "enter y to run the program again or enter anything else to exit" << endl;
		cin >> in;
	}
	return 0;
}
