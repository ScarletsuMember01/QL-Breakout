#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;

using qt = vector<vector<vector<vector<vector<vector<vector<double>>>>>>>;

struct reward {
	double movemalus;
	double losemalus;
	double blockmalus;
	double blockreward;
	double stillreward;
	double winreward;
};

struct state {
	int block;
	double px;
	double py;
	double bx;
	double by;
	double vx;
	double vy;
};

vector<vector<double>> init_grid(double size, double blocksize, double space);
bool isValidMove(double action, state st, double size);
bool hitWall(state& st, vector<vector<double>>& grid);
bool hitBlock(state& st, vector<vector<double>>& grid, reward rwd);
bool UpdateCollide(state &st, vector<vector<double>> &grid, reward rwd);
state makeAction(double action, state st, vector<vector<double>>& grid, reward rwd);
int train(qt& Qtable, state& st, vector<vector<double>>& grid, double exploration_rate, reward rwd, int cons);