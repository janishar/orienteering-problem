#include <iostream>
#include <iomanip>
using namespace std;
int x1 = 0, y1 = 0;
int C, R;
char maze[100][100];
int mazeCopy[100][100];
int converter(char x)
{
	if (x == '#')
		return -5;
	else if (x == '.')
		return -4;
	else if (x == 'G')
		return -3;
	else if (x == 'S')
		return -2;
	else if (x == '@')
		return -1;
	else
		return -10000;
}
void print(int r, int c)
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cout << setw(7) << mazeCopy[i][j] << setw(7);
		}
		cout << endl;
	}
	cout << endl
			 << endl;
}
void find(int x)
{
	int flag = 0;
	for (int i = 0; i < R && flag == 0; i++)
	{
		for (int j = 0; j < C && flag == 0; j++)
		{
			if (mazeCopy[i][j] == x)
			{
				x1 = i;
				y1 = j;
				flag = 1;
				break;
			}
		}
	}
}
void mover(int i, int j, int k)
{
	if (mazeCopy[i + 1][j] != -5 && mazeCopy[i + 1][j] != k && mazeCopy[i + 1][j] >= -5)
		mazeCopy[i + 1][j] = (k + 1);
	if (mazeCopy[i - 1][j] != -5 && mazeCopy[i - 1][j] != k && mazeCopy[i - 1][j] >= -5)
		mazeCopy[i - 1][j] = (k + 1);
	if (mazeCopy[i][j + 1] != -5 && mazeCopy[i][j + 1] != k && mazeCopy[i][j + 1] >= -5)
		mazeCopy[i][j + 1] = (k + 1);
	if (mazeCopy[i][j - 1] != -5 && mazeCopy[i][j - 1] != k && mazeCopy[i][j - 1] >= -5)
		mazeCopy[i][j - 1] = (k + 1);
}
bool goalReach(int i, int j)
{
	if (mazeCopy[i + 1][j] == -3 || mazeCopy[i - 1][j] == -3 || mazeCopy[i][j + 1] == -3 || mazeCopy[i][j - 1] == -3)
		return true;
	else
		return false;
}
int shortestPathFinder()
{
	int count = 0, pathMarker = -1000;

	find(-2);
	mazeCopy[x1][y1] = -1001;
	for (int k = 0; k < 1000; k++)
	{

		while (count <= 4 * k)
		{
			find(k);
			if (goalReach(x1, y1) == true)
			{
				cout << "goal reached" << endl;
				return k + 1;
			}
			else
			{
				mazeCopy[x1][y1] = pathMarker;
				mover(x1, y1, k);
				// print(R,C);
				count++;
			}
		}
		pathMarker++;
		count = 1;
	}
	return 0;
}
void input()
{
	cout << "enter mess rows and columns" << endl;
	cin >> R;
	cin >> C;
	cout << "enter the map" << endl;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> maze[i][j];
			mazeCopy[i][j] = converter(maze[i][j]);
		}
	}
}
int main()
{
	input();
	print(R, C);
	int shortestDist = shortestPathFinder();
	print(R, C);
	cout << "min distance = " << shortestDist << endl;
	return 0;
}
