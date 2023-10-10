#include <iostream>
#include <iomanip>

using namespace std;

class orienteering
{
private:
	static const int N = 250;

public:
	int x1 = 0, y1 = 0, xx1, yy1, helper = 0, totalCheckpoints = 0, combinationObjects[7 * 5040], dist[2 * 5040];
	int C, R, m = 0, k = 0, checkpoint = -3, min = 0, x;
	char maze[N][N], mazeShow[N][N];
	int mazeCopy[N][N], mazeSave[N][N], mazePath[N][N], mazePathclean[N][N], pathMemory[5 * N][2];
	inline void checkmap();
	void find(int x);
	void input();
	int converter(char x);
	void copyMaze(int maze1[N][N], int maze2[N][N]);
	void print(char mat[N][N]);
	int shortestPathFinder(int a, int b);
	bool goalReach(int b, int i, int j);
	void convergenceHelper(int x, int y, int k, int val);
	void mover(int i, int j, int k);
	void combination(int n);
	int exchanger(int n, int rot, int t);
	void distanceCal(int n);
	void bestRouteFinder(int n);
	int pathFinder(int a, int b, int x, int y);
	void looker(int i, int j);
	void pathViewer(int a, int b);
	void copyMaze(char maze1[N][N], char maze2[N][N]);
	void sgRoute();
	void mazeReorient();
	void print(int mat[10000], int n, int s);
	int factorial(int n);
};
void orienteering::print(int mat[10000], int n, int s)
{
	int count = 0;
	cout << endl
			 << endl;
	for (int i = 0; i < s; i++)
	{
		cout << mat[i] << " ";
		count++;
		// cout<<"count = "<<count<<endl;
		if (count == n)
		{
			cout << endl
					 << endl;
			count = 0;
		}
	}
	cout << endl
			 << endl;
}
void orienteering::sgRoute()
{
	int a, b, shortestDist, loop = 0, tDist = 0;
	while (loop <= totalCheckpoints)
	{
		if (totalCheckpoints == 0)
		{
			a = -2;
			b = -3;
		}
		else
		{
			a = -2 - loop;
			b = -4;
		}
		copyMaze(maze, mazeShow);
		copyMaze(mazePathclean, mazePath);
		shortestDist = shortestPathFinder(a, b);
		find(-10000);
		pathFinder(a, b, x1, y1);
		pathViewer(a, b);
		print(mazeShow);
		k = 0;
		loop++;
		tDist += shortestDist;
		cout << "distance traveled = " << shortestDist << endl
				 << endl;
	}
	cout << "total distance traveled = " << tDist << endl
			 << endl;
}
void orienteering::copyMaze(char maze1[N][N], char maze2[N][N])
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			maze2[i][j] = maze1[i][j];
		}
	}
}
void orienteering::pathViewer(int a, int b)
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (mazeShow[i][j] == '.')
				mazeShow[i][j] = ' ';
			if (mazePath[i][j] != 0 && mazeSave[i][j] != b)
				mazeShow[i][j] = '.';
		}
	}
}
void orienteering::looker(int i, int j)
{
	if (mazeCopy[i + 1][j] == mazeCopy[i][j] + 1)
	{
		xx1 = i + 1;
		yy1 = j;
	}
	else if (mazeCopy[i - 1][j] == mazeCopy[i][j] + 1)
	{
		xx1 = i - 1;
		yy1 = j;
	}
	else if (mazeCopy[i][j + 1] == mazeCopy[i][j] + 1)
	{
		xx1 = i;
		yy1 = j + 1;
	}
	else if (mazeCopy[i][j - 1] == mazeCopy[i][j] + 1)
	{
		xx1 = i;
		yy1 = j - 1;
	}
	else
	{
		helper = 1;
	}
}
int orienteering::pathFinder(int a, int b, int x, int y)
{
	looker(x, y);
	if (helper == 0)
	{
		mazePath[xx1][yy1] = ++k;
		if (mazeSave[xx1][yy1] == b)
			return 1;
		pathMemory[m][0] = x;
		pathMemory[m][1] = y;
		m++;
		int aa = pathFinder(a, b, xx1, yy1);
	}
	else if (helper == 1)
	{
		k--;
		mazeCopy[x][y] = 0;
		mazePath[x][y] = 0;
		if (mazeSave[x][y] == b)
			return 1;
		m--;
		helper = 0;
		int ab = pathFinder(a, b, pathMemory[m][0], pathMemory[m][1]);
	}
	return 0;
}
void orienteering::distanceCal(int n)
{
	int count = 0;
	int nx = factorial(n);
	for (int i = 0; i < nx; i++)
	{
		dist[count] = i;
		count++;
		dist[count] = shortestPathFinder(-2, combinationObjects[i * n]);
		for (int j = i * n; j < (i + 1) * n - 1; j++)
		{
			dist[count] += shortestPathFinder(combinationObjects[j], combinationObjects[j + 1]);
		}
		dist[count] += shortestPathFinder(combinationObjects[(i + 1) * n - 1], -3);
		count++;
	}
	// dist[count] = shortestPathFinder(combinationObjects[4], combinationObjects[5]);
}
void orienteering::bestRouteFinder(int n)
{
	int c = 1, tDist, flag;
	int nx = factorial(n);
	min = dist[1];
	while (1)
	{
		flag = 0;
		tDist = 0;
		for (int i = 1; i < 2 * nx; i += 2)
		{
			if (dist[i] == min)
			{

				dist[i] = -1;
				x = dist[i - 1];
				break;
			}
			else
			{
				x = -2;
			}
		}
		if (x == -2)
			break;
		for (int i = 1; i < 2 * nx; i += 2)
		{
			if (min > dist[i] && dist[i] > 0)
			{
				min = dist[i];
				dist[i] = -1;
				x = dist[i - 1];
			}
		}
		int a, b;
		int shortestDist;
		cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx " << endl;
		cout << endl
				 << "best route option " << c++ << endl;
		cout << "x = " << x << endl;
		for (int i = x * n - 1; i < (x + 1) * n; i++)
		{
			copyMaze(maze, mazeShow);
			copyMaze(mazeSave, mazeCopy);
			copyMaze(mazePathclean, mazePath);
			if (flag == 0)
			{
				a = -2;
				b = combinationObjects[x * n];
				flag = 1;
			}
			else if (flag == 1 && i != (x + 1) * n - 1)
			{
				a = combinationObjects[i];
				b = combinationObjects[i + 1];
			}
			else if (i == (x + 1) * n - 1)
			{
				a = combinationObjects[(x + 1) * n - 1];
				b = -3;
			}
			shortestDist = shortestPathFinder(a, b);
			tDist += shortestDist;
			find(-10000);
			pathFinder(a, b, x1, y1);
			pathViewer(a, b);
			print(mazeShow);
			cout << "distance traveled = " << shortestDist << endl
					 << endl;
			k = 0;
		}
		cout << "total distance traveled = " << tDist << endl;
	}
}
int orienteering::factorial(int n)
{
	if (n == 1)
		return n;
	return n * factorial(n - 1);
}
void orienteering::combination(int n)
{
	int count = 0, track = 0, nx = factorial(n);
	int tempStore[35280];
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tempStore[count++] = combinationObjects[j];
		}
	}
	int k = 1, d = 0, h = 0, t = 0, shifter = 0, flag = 0, position = 0;
	count = 0;
	for (int dp = 0; dp < n - 1; dp++)
	{
		while (h < nx)
		{
			for (int dk = 0; dk < n - d; dk++)
			{
				for (int loop = 0; loop < factorial(n - k); loop++)
				{
					for (int dt = count * n; dt < count * n + n; dt++)
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
						for (int dl = count * n; dl < count * n + n; dl++)
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
						t = count * n;
					}
					while (1)
					{
						if (tempStore[t + shifter] == 0)
							shifter++;
						else
							break;
					}
					combinationObjects[count * n + d] = tempStore[t + shifter];
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
	for (int i = 0; i < nx; i++)
	{
		for (int j = i * n; j < i * n + n; j++)
		{
			if (tempStore[j] != 0)
			{
				combinationObjects[i * n + n - 1] = tempStore[j];
				track++;
				break;
			}
		}
	}
	cout << "total combination = " << int(track / n) << endl;
	cout << "..........................." << endl;
	// print(combinationObjects, n);
}
void orienteering::mover(int i, int j, int k)
{
	if (mazeCopy[i + 1][j] != -1000 && mazeCopy[i + 1][j] != k && mazeCopy[i + 1][j] >= -1000)
		mazeCopy[i + 1][j] = (k + 1);
	if (mazeCopy[i - 1][j] != -1000 && mazeCopy[i - 1][j] != k && mazeCopy[i - 1][j] >= -1000)
		mazeCopy[i - 1][j] = (k + 1);
	if (mazeCopy[i][j + 1] != -1000 && mazeCopy[i][j + 1] != k && mazeCopy[i][j + 1] >= -1000)
		mazeCopy[i][j + 1] = (k + 1);
	if (mazeCopy[i][j - 1] != -1000 && mazeCopy[i][j - 1] != k && mazeCopy[i][j - 1] >= -1000)
		mazeCopy[i][j - 1] = (k + 1);
}
void orienteering::convergenceHelper(int x, int y, int k, int val)
{
	if (mazeCopy[x + 1][y] == k)
		mazeCopy[x + 1][y] = val;
	if (mazeCopy[x - 1][y] == k)
		mazeCopy[x - 1][y] = val;
	if (mazeCopy[x][y + 1] == k)
		mazeCopy[x][y + 1] = val;
	if (mazeCopy[x][y - 1] == k)
		mazeCopy[x][y - 1] = val;
}
bool orienteering::goalReach(int b, int i, int j)
{
	if (mazeCopy[i + 1][j] == b || mazeCopy[i - 1][j] == b || mazeCopy[i][j + 1] == b || mazeCopy[i][j - 1] == b)
		return true;
	else
		return false;
}
int orienteering::shortestPathFinder(int a, int b)
{
	if (a == b)
		return 0;
	copyMaze(mazeSave, mazeCopy);
	int count = 0, pathMarker = -10000;
	find(a);
	mazeCopy[x1][y1] = 0;
	for (int k = 0; k < 1000; k++)
	{

		while (count <= 4 * k)
		{
			find(k);
			if (goalReach(b, x1, y1) == true)
			{
				mazeCopy[x1][y1] = pathMarker;
				find(b);
				mazeCopy[x1][y1] = pathMarker + 1;
				convergenceHelper(x1, y1, k, pathMarker);
				return k + 1;
			}
			else
			{
				mazeCopy[x1][y1] = pathMarker;
				mover(x1, y1, k);
				count++;
			}
		}
		pathMarker++;
		count = 1;
	}
	return 0;
}
void orienteering::find(int x)
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
void orienteering::print(char mat[N][N])
{
	cout << endl;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cout << setw(1) << mat[i][j];
		}
		cout << endl;
	}
	cout << endl
			 << endl;
}
void orienteering::copyMaze(int maze1[N][N], int maze2[N][N])
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			maze2[i][j] = maze1[i][j];
		}
	}
}
void orienteering::checkmap()
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if ((i == 0 || i == R - 1 || j == 0 || j == C - 1) && maze[i][j] != '#')
			{
				cout << "invalid map : open boundary" << endl;
				input();
				break;
			}
			else if ((maze[i][j] != '.' && maze[i][j] != 'S' && maze[i][j] != 's' && maze[i][j] != 'G' && maze[i][j] != 'g' && maze[i][j] != '#' && maze[i][j] != '@'))
			{
				cout << "invalid map : only '.','#','G','S','@' charecters are allowed" << endl;
				input();
				break;
			}
		}
	}
}
int orienteering::converter(char x)
{
	if (x == '#')
		return -1000;
	else if (x == '.')
		return -1;
	else if (x == 'G')
		return -3;
	else if (x == 'S')
		return -2;
	else if (x == '@')
		return (--checkpoint);
	else
		return -1000000;
}
void orienteering::mazeReorient()
{
	int mat[4 * N], count = 0;
	for (int i = 0; i < 4 * totalCheckpoints; i += 4)
	{
		int x = -4 - count++;
		find(x);
		mat[i] = x;
		mat[i + 1] = x1;
		mat[i + 2] = y1;
		mat[i + 3] = shortestPathFinder(-2, x);
		copyMaze(mazeSave, mazeCopy);
		k = 0;
	}
	count = 0;
	for (int i = 3; i < 4 * (totalCheckpoints - 1); i += 4)
	{
		for (int j = i + 4; j < 4 * totalCheckpoints; j += 4)
		{
			if (mat[i] > mat[j])
			{
				count = mat[i];
				mat[i] = mat[j];
				mat[j] = count;
				count = mat[i - 3];
				mat[i - 3] = mat[j - 3];
				mat[j - 3] = count;
				count = mat[i - 2];
				mat[i - 2] = mat[j - 2];
				mat[j - 2] = count;
				count = mat[i - 1];
				mat[i - 1] = mat[j - 1];
				mat[j - 1] = count;
			}
		}
	}
	count = -4;
	for (int i = 1; i < 4 * totalCheckpoints; i += 4)
	{
		mazeCopy[mat[i]][mat[i + 1]] = count--;
	}
}
void orienteering::input()
{
	cout << "enter map size" << endl;
	cin >> R;
	cin >> C;
	cout << "enter the map" << endl;
	int count = 0;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> maze[i][j];
			mazeCopy[i][j] = converter(maze[i][j]);
			mazePath[i][j] = 0;
			if (maze[i][j] == '@')
			{
				combinationObjects[totalCheckpoints] = mazeCopy[i][j];
				totalCheckpoints++;
			}
		}
	}
	copyMaze(mazeCopy, mazeSave);
	mazeReorient();
	copyMaze(mazeCopy, mazeSave);
	checkmap();
}
int main()
{
	cout << "..................... enter y to run and n to exit................ " << endl;
	char t;
	cin >> t;
	while (t == 'y' || t == 'Y')
	{
		orienteering map;
		map.input();
		map.copyMaze(map.maze, map.mazeShow);
		map.copyMaze(map.mazePath, map.mazePathclean);
		int n = map.totalCheckpoints;
		if (n == 0 || n == 1)
		{
			map.sgRoute();
		}
		else
		{
			map.combination(n);
			map.distanceCal(n);
			map.bestRouteFinder(n);
		}
		cout << "..................... enter y to run and n to exit................ " << endl;
		cin >> t;
	}
	return 0;
}
