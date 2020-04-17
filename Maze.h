#ifndef MAZE_H

#define MAZE_H
#include <string>

class Maze {
private:
	int** maze;
	int** adj;
	const int row;
	const int col;
public:
	~Maze();
	Maze(int, int);
	void load(std::string &);
	void bonus(int);
	int getrow();
	int getcol();
	void print();
	void showroute();
};





#endif