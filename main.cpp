#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void createMaze(int &, int &);
void showMaze(int, int);
bool robotMove(int &, int &);

const int SIZE = 10;
enum Values { Space, Wall, Exit };
Values maze[SIZE][SIZE];

int main()
{
    unsigned seed;
    seed = time(0);
    srand(seed);

    int robotRow, robotColumn;
    createMaze(robotRow, robotColumn);

    while (!robotMove(robotRow, robotColumn))
    {
        cout << "Done!" << endl;
    }
	cin.get();
	cout << "Press any key to continue..." << endl;
	cin.get();
    return 0;
}

void createMaze(int &robotRow, int &robotColumn)
{
    int i, j;
    // fill mazes with wall values
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            maze[i][j] = Wall;
        }
    }

    // carve out space values
    for (i = 1; i < SIZE-1; i++)
    {
        maze[1][i] = Space;
        maze[7][i] = Space;
    }
    for (j = 2; j < SIZE-6; j++)
    {
        maze[j][2] = Space;
    }
    for (i = 1; i < SIZE-2; i++)
    {
        maze[4][i] = Space;
    }
    for (j = 4; j < SIZE-2; j++)
    {
        maze[j][7] = Space;
    }
    for (i = 6; i < SIZE-1; i+=2)
    {
        maze[2][i] = Space;
    }
    maze[6][3] = Space;

    // add one or two exit values
    maze[1][0] = Exit;
    maze[7][9] = Exit;

    // robot starting location
    robotRow = 4;
    robotColumn = 6;

    return;
}

void showMaze(int robotRow, int robotColumn)
{
    system("cls");

    static int moves = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if ((i == robotRow) && (j == robotColumn))
            {
                cout << "X";
                moves++;
            }
            else if (maze[i][j] == Wall)
            {
                cout << "+";
            }
            else if (maze[i][j] == Space)
            {
                cout << " ";
            }
            else if (maze[i][j] == Exit)
            {
                cout << "E";
            }
        }
        cout << endl;
    }

    cout << "Move number " << moves << endl;
    cout << endl;
    return;
}

bool robotMove(int &robotRow, int &robotColumn)
{
    int dir = (rand() % 4) + 1;

    if ((dir == 1) && (maze[robotRow-1][robotColumn] != Wall))
    {
        robotRow = robotRow - 1;
        showMaze(robotRow, robotColumn);
    }
    if ((dir == 2) && (maze[robotRow+1][robotColumn] != Wall))
    {
        robotRow = robotRow + 1;
        showMaze(robotRow, robotColumn);
    }
    if ((dir == 3) && (maze[robotRow][robotColumn-1] != Wall))
    {
        robotColumn = robotColumn - 1;
        showMaze(robotRow, robotColumn);
    }
    if ((dir == 4) && (maze[robotRow][robotColumn+1] != Wall))
    {
        robotColumn = robotColumn + 1;
        showMaze(robotRow, robotColumn);
    }

    if (maze[robotRow][robotColumn] == Exit)
    {
        return true;
    }
    return false;
}


