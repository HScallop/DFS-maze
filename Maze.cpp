#include "Maze.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct point {
	int x;
	int y;
};




//constructor
Maze::Maze(int row, int col)
	:row(row),
	col(col)

{
	maze = new int*[row + 1];
	for (int i = 0; i <= row; i++) {
		maze[i] = new int[col + 1];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			maze[i][j] = 1;
		}
	}
}

Maze::~Maze()
{	
	//delete 2D dynamic array
	for (int i = 0; i < row; i++) {
		delete[] maze[i];
	}

	delete[] maze;
}



void Maze::load(std::string & filename) {
	ifstream fin(filename);

	//check if the file was opened correctly
	if (!fin) {
		cerr << "File couldn't be opened.";
		system("pause");
	}


	//declare a char to ignore the commas in the file
	int a;
	char comma;
	fin >> a >> comma >> a;
	for (int i = 0; i < row; i++) {
		fin >> maze[i][0];
		for (int j = 1; j < col; j++) {
			fin >> comma >> maze[i][j];
		}
	}
	

}




void Maze::print() {
	//print maze
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (maze[i][j] == 1) {
				cout << "*" << setw(2);
			}
			else if (maze[i][j] == 0) {
				cout << "+" << setw(2);
			}
			else if (maze[i][j] == 200) {
				cout << "S" << setw(2);
			}
			else if (maze[i][j] == 201) {
				cout << "E" << setw(2);
			}
			else if (maze[i][j] >= 202) {
				cout << "$" << setw(2);
			}
		}
		cout << "\n";
	}
}



//get row
int Maze::getrow() {
	return row;
}
//get column
int Maze::getcol() {
	return col;
}



void Maze::showroute() {
	//first, find route
	point p;
	p.x = 1;
	p.y = 1;
	//use stack to realize DFS
	stack<point> visited;
	//decalre a two dimensional array to record
	int** record = new int*[row];
	for (int i = 0; i < row; i++) {
		record[i] = new int[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			record[i][j] = 0;
		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (maze[i][j] == 200) {
				p.x = i;
				p.y = j;
			}
		}
	}

	visited.push(p);
	//find route
	while (visited.size() >= 1) {
		//go down
		if (maze[p.x + 1][p.y] != 1 && record[p.x + 1][p.y] == 0) {
			p.x += 1;
			visited.push(p);
			record[p.x][p.y] = 1;
		}
		//go up
		else if (maze[p.x - 1][p.y] != 1 && record[p.x - 1][p.y] == 0) {
			p.x -= 1;
			visited.push(p);
			record[p.x][p.y] = 1;
		}
		//go right
		else if (maze[p.x][p.y + 1] != 1 && record[p.x][p.y + 1] == 0) {
			p.y += 1;
			visited.push(p);
			record[p.x][p.y] = 1;
		}
		//go left
		else if (maze[p.x][p.y - 1] != 1 && record[p.x][p.y - 1] == 0) {
			p.y -= 1;
			visited.push(p);
			record[p.x][p.y] = 1;
		}
		else if (maze[visited.top().x][visited.top().y] != 201) {
				p.x = visited.top().x;
				p.y = visited.top().y;
				visited.pop();
		}
		//store the route in the record array
		if (maze[visited.top().x][visited.top().y] == 201) {
			while (visited.size() >= 1) {
				record[visited.top().x][visited.top().y] = 99;
				visited.pop();
			}
		}
	}

	cout << "\n";


	
	//print maze
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			//use the same code as in print but judge if the position is on the route first
			if (record[i][j] == 99) {
				cout << "X" << setw(2);
			}
			else if (maze[i][j] == 1) {
				cout << "*" << setw(2);
			}
			else if (maze[i][j] == 0) {
				cout << "+" << setw(2);
			}
			else if (maze[i][j] == 200) {
				cout << "S" << setw(2);
			}
			else if (maze[i][j] == 201) {
				cout << "E" << setw(2);
			}
			else if (maze[i][j] >= 202) {
				cout << "$" << setw(2);
			}
		}
		cout << "\n";
	}



	//delete 2D dynamic array
	for (int i = 0; i < row; i++) {
		delete[] record[i];
	}
	delete [] record;


	return;
}

//add a bonus position to the maze
void Maze::bonus(int a) {
	int counter = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (maze[i][j] == 0) {
				counter++;
			}
		}
	}

	if (a >= counter) {
		cout << "Unvalid number for adding.\n";
		return;
	}
	srand(time(0));
	point p;
	cout << "Adding bonus positions.\n";
	for (int i = 0; i < a; i++) {
		while (true) {
			p.x = rand() % row;
			p.y = rand() % col;
			if (maze[p.x][p.y] == 0) {
				maze[p.x][p.y] = rand() % 10 + 1 + 200;
				break;
			}
		}
	}
}




