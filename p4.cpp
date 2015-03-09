#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;


class Maze
{
public:
	Maze();
	void read_in_puzzle(ifstream& input);	//need to test
	bool solve(char target);	//solves the maze, changing the array until 'target' is encountered	//need to test
	void setw(int w);	//sets width
	void seth(int h);	//sets height
	void print();		//outputs maze to cout	//need to test
	void clear_map();	//deletes all 'x' markers
	int get_moves();
	
	//move functions, alter position pair, place '.' where position is
	void moveup();
	void movedown();
	void moveleft();
	void moveright();
	
	//can move up,down,left,right:
	bool canup();
	bool candown();
	bool canleft();
	bool canright();
private:
	char puzzle[20][20];
	int moves;	//tracks number of moves to solve
	int width;
	int height;
	pair<int, int> position;	//keeps track of (x, y) coordinates
	enum direction {up, down, left, right} last_move;
};

int Maze::get_moves()
{
	return moves;
}

void Maze::clear_map()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (puzzle[x][y] == 'x')
			{
				puzzle[x][y] = ' ';
			}
		}
	}
	
}

bool Maze::canup()
{
	if ((puzzle[position.first][position.second + 1] != '*') && (puzzle[position.first][position.second + 1] != 'x'))
	{
		return true;
	}
	
	return false;
}

bool Maze::candown()
{
	if ((puzzle[position.first][position.second - 1] != '*') && (puzzle[position.first][position.second - 1] != 'x'))
	{
		return true;
	}
	
	return false;
}

bool Maze::canleft()
{
	if ((puzzle[position.first - 1][position.second] != '*') && (puzzle[position.first - 1][position.second] != 'x'))
	{
		return true;
	}
	
	return false;
}

bool Maze::canright()
{
	if ((puzzle[position.first + 1][position.second] != '*') && (puzzle[position.first + 1][position.second] != 'x'))
	{
		return true;
	}
	
	return false;
}


void Maze::moveup()
{
	position.second--;
	moves++;
	last_move = up;
}

void Maze::movedown()
{
	position.second++;
	moves++;
	last_move = down;
}

void Maze::moveleft()
{
	position.first--;
	moves++;
	last_move = left;
}

void Maze::moveright()
{
	position.first++;
	moves++;
	last_move = right;
}

void Maze::print()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cout << puzzle[x][y];
		}
		
		cout << endl;
	}
}

void Maze::seth(int h)
{
	height = h;
}

void Maze::setw(int w)
{
	width = w;
}

Maze::Maze(){
	moves = 0;
	width = 0;
	height = 0;
	position.first = 0;
	position.second = 0;
}

void Maze::read_in_puzzle(ifstream& input)
{
	char c;

	while (input.good())
	{
		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < height; x++)
			{
				input.get(c);
				
				switch (c)
				{
					case 'o':
					position.first = x;
					position.second = y;
					puzzle[x][y] = 'o';
					break;	
					
					
					default:
					puzzle[x][y] = 'c';
					break;
				}
		
			}
		}
	}
}

bool Maze::solve(char target)	//recursive solving function
{
//base case:
		if (puzzle[position.first][position.second] == target)
			{
				return true;
			}
		
//to ensure no back-tracking, keep track of last move direction

	if (canleft() && (last_move != right))
	{
		moveleft();
		solve(target);
	}
	
	if (canright() && (last_move != left))
	{
		moveright();
		solve(target);
	}
	
	if (candown() && (last_move != up))
	{
		movedown();
		solve(target);
	}
	
	if (canup() && (last_move != down))
	{
		moveup();
		solve(target);
	}
	
//if reach dead-end: need to back-track and place 'x' marker to show visited
	
	
	
	
	
	return false;
}








int main()
{
	string inputf;
	ifstream fin;
	do {
	cout << "Enter an input file" << endl;
	getline(cin, inputf);
	fin.open(inputf.c_str());
	if (!fin.good()) cerr << "Error opening file!" << endl << "Please try again" << endl;
} while (!fin.good());

	
	Maze maze = Maze();
	
	int width = 0;
	int height = 0;
	
	while (fin.good())
	{
		fin >> width;
		maze.setw(width);
		fin >> height;
		maze.seth(height);
		
		maze.read_in_puzzle(fin);
	}

	

	maze.solve('@');	//solves the maze for the item
	maze.clear_map();		//clears maze of 'x' markers
	maze.solve('!');	//solves maze for finish
	maze.clear_map();		//clears maze of 'x' markers
		
	maze.print();
	
	cout << "The number of moves was: " << maze.get_moves() << endl;
	
	//need to print out legend


	return 0;
}


