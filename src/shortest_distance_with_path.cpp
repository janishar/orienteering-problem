#include <iostream>
#include<iomanip>
const int N=100;
using namespace std;
int x1=0,y1=0,xx1,yy1,helper=0;
int C,R,m=0,k=0;
char maze[N][N];
int mazeCopy[N][N],mazeSave[N][N],mazePath[N][N],pathMemory[5*N][2];
void find(int x);
void print(int mat[N][N]);
void copyMaze(int maze1[N][N],int maze2[N][N])
{
 for(int i=0;i<R;i++)
    {
        for(int j=0;j<C;j++)
        {
            maze2[i][j]=maze1[i][j];
        }
    }
}

void looker(int i, int j)
{
    if(mazeCopy[i+1][j]==mazeCopy[i][j]+1)
    {
        xx1=i+1;
        yy1=j;
    }
    else if(mazeCopy[i-1][j]==mazeCopy[i][j]+1)
    {
        xx1=i-1;
        yy1=j;
    }
     else if(mazeCopy[i][j+1]==mazeCopy[i][j]+1)
    {
        xx1=i;
        yy1=j+1;
    }
     else if(mazeCopy[i][j-1]==mazeCopy[i][j]+1)
    {
        xx1=i;
        yy1=j-1;
    }
    else
    {
        helper=1;
    }
}
int pathFinder(int x,int y)
{
    looker(x,y);
    if(helper==0)
    {
        mazePath[xx1][yy1]=++k;
        if(maze[xx1][yy1]=='G')
            return 1;
        pathMemory[m][0]=x;
        pathMemory[m][1]=y;
        m++;
        int a = pathFinder(xx1,yy1);
    }
    else if(helper==1)
    {
        k--;
        mazeCopy[x][y]=0;
        mazePath[x][y]=0;
        if(maze[x][y]=='G')
            return 1;
        m--;
        helper=0;
        int a=pathFinder(pathMemory[m][0],pathMemory[m][1]);
    }
    return 0;
}
int converter(char x)
{
    if(x=='#')
        return -5;
    else if(x=='.')
        return -4;
    else if(x=='G')
        return -3;
    else if(x=='S')
        return -2;
    else if(x=='@')
        return -1;
    else
        return -10000;
}
void pathViewer()
{
    for(int i=0;i<R;i++)
    {
        for(int j=0;j<C;j++)
        {
            if(maze[i][j]=='.')
                maze[i][j]=' ';
            if(mazePath[i][j]!=0&&maze[i][j]!='G')
                maze[i][j]='.';
        }
    }
}
void print(int mat[N][N])
{
    cout<<endl;
    for(int i=0;i<R;i++)
    {
        for(int j=0;j<C;j++)
        {
            cout<<setw(5)<<mat[i][j]<<setw(5);
        }
        cout<<endl<<endl;;
    }
    cout<<endl<<endl;
}
void print(char mat[N][N])
{
    cout<<endl;
    for(int i=0;i<R;i++)
    {
        for(int j=0;j<C;j++)
        {
            cout<<setw(1)<<mat[i][j];
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}

void find(int x)
{
    int flag=0;
    for (int i = 0; i < R&&flag==0; i++)
	{
		for (int j = 0; j < C&&flag==0; j++)
		{
			if(mazeCopy[i][j]==x)
            {
                x1=i;
                y1=j;
                flag=1;
                break;
            }
		}
	}

}
void mover(int i,int j,int k)
{
    if(mazeCopy[i+1][j]!=-5&&mazeCopy[i+1][j]!=k&&mazeCopy[i+1][j]>=-5)
            mazeCopy[i+1][j]=(k+1);
    if(mazeCopy[i-1][j]!=-5&&mazeCopy[i-1][j]!=k&&mazeCopy[i-1][j]>=-5)
            mazeCopy[i-1][j]=(k+1);
    if(mazeCopy[i][j+1]!=-5&&mazeCopy[i][j+1]!=k&&mazeCopy[i][j+1]>=-5)
        mazeCopy[i][j+1]=(k+1);
    if(mazeCopy[i][j-1]!=-5&&mazeCopy[i][j-1]!=k&&mazeCopy[i][j-1]>=-5)
        mazeCopy[i][j-1]=(k+1);

}
bool goalReach(int i, int j)
{
    if(mazeCopy[i+1][j]==-3||mazeCopy[i-1][j]==-3||mazeCopy[i][j+1]==-3||mazeCopy[i][j-1]==-3)
        return true;
    else
        return false;
}
void convergenceHelper(int x,int y,int k,int val)
{
    if(mazeCopy[x+1][y]==k)
        mazeCopy[x+1][y]=val;
    if(mazeCopy[x-1][y]==k)
        mazeCopy[x-1][y]=val;
    if(mazeCopy[x][y+1]==k)
        mazeCopy[x][y+1]=val;
    if(mazeCopy[x][y-1]==k)
        mazeCopy[x][y-1]=val;
}
int shortestPathFinder()
{
    int count=0,pathMarker=-1000;

    find(-2);
    mazeCopy[x1][y1]=0;
    for(int k=0;k<1000;k++)
    {

        while(count<=4*k)
        {
            find(k);
            if(goalReach(x1,y1)==true)
            {
                mazeCopy[x1][y1]=pathMarker;
                find(-3);
                mazeCopy[x1][y1]=pathMarker+1;
                convergenceHelper(x1,y1,k,pathMarker);
                cout<<"goal reached"<<endl;
                return k+1;
            }
            else
            {
                mazeCopy[x1][y1]=pathMarker;
                mover(x1,y1,k);
                count++;
            }
        }
        pathMarker++;
        count=1;
    }
    return 0;

}
void input()
{
    cout << "enter map size" << endl;
	cin >> R;
	cin >>C;
	cout << "enter the map" << endl;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin>>maze[i][j];
			mazeCopy[i][j]=converter(maze[i][j]);
			mazePath[i][j]=0;
		}
	}
}
int main()
{
    cout<<"..................... enter y to run and n to exit................ "<<endl;
    char t;
    cin>>t;
    while(t=='y'||t=='Y')
    {
        input();
        int shortestDist=shortestPathFinder();
        cout<<"min distance = "<<shortestDist<<endl;
        copyMaze(mazeCopy,mazeSave);
        find(-1000);
        pathFinder(x1,y1);
        pathViewer();
        print(maze);
        print(mazePath);
        cout<<"..................... enter y to run and n to exit................ "<<endl;
        cin>>t;
        k=0;
    }
    return 0;
}
