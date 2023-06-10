#include "breakout.h"

bool changed = false;
int counter = 0;
double totalreward = 0;
int timer = 0;
int finished = 0;


void print_state(state st) {
	cout << "player X" << st.px << " ballCoords(" << st.bx << ";" << st.by << ") " << st.vx << st.vy << endl;
}

vector<vector<double>> init_grid(double size, double blocksize, double space) {
	timer = 0;
	counter = 0;
	finished = 0;
	vector<vector<double>> grid;
	for (auto i = 0; i < size; i++) {
		vector<double> row;
		for (auto j = 0; j < size; j++) {
			if (i < space)
				row.push_back(0);
			else if (i == 3 && j == 10)
				row.push_back(2);
			else if (i == 6 && j == 4)
				row.push_back(4);
			else if (i == 5 && j == 15)
				row.push_back(1);
			else
				row.push_back(0);
		}
		grid.push_back(row);
	}
	return grid;
}

bool isValidMove(double action, state st, double size) {
	if ((st.px == 0) && (action == 0))
		return false;
	if (st.px+4 == size-1 && (action == 1))
		return false;
	return true;
}

bool hitWall(state& st, vector<vector<double>>& grid) {
	// WHEN HITTING A WALL

	bool changed = false;
	if ((st.by + st.vy) < 0) {
		st.vy *= -1;
		changed = true;
	}
	if (st.by + st.vy >= grid.size())
		return false;
	if (st.vx == 2 || st.vx == -2) {
		if (st.bx == 0 || st.bx == 19) {
			st.vx *= -1;
			st.bx += st.vx;
			if ((st.by + st.vy) >= 0 && (st.by + st.vy) < grid.size())
				st.by += st.vy;
			changed = true;
		}
		else if ((st.bx + st.vx) < 0) {
			st.bx = 0;
			if ((st.by + st.vy) >= 0 && (st.by + st.vy) < grid.size())
				st.by += st.vy;
			changed = true;
		}
		else if ((st.bx + st.vx) > 19) {
			st.bx = 19;
			if ((st.by + st.vy) >= 0 && (st.by + st.vy) < grid.size())
				st.by += st.vy;
			changed = true;
		}
	}
	else if ((st.bx + st.vx) < 0 || (st.bx + st.vx) >= grid.size()) {
		st.vx *= -1;
		if ((st.by + st.vy) >= 0 && (st.by + st.vy) < grid.size())
		changed = true;
	}
	return changed;
}

bool hitBlock(state& st, vector<vector<double>>& grid, reward rwd) {
	int negatif = 0;
	if (st.vx > 0)
		negatif = 1;
	if (st.vx < 0)
		negatif = -1;
	bool touchedx = false;
	bool touchedy = false;
	if (st.vx == 2 * negatif && st.vx != 0)
	{
		if (grid[st.by + st.vy][st.bx + st.vx] > 0)
		{
			st.by += st.vy;
			st.bx += negatif;
			return false;
		}
	}
	if (grid[st.by][st.bx + negatif] > 0)
	{
		if (grid[st.by][st.bx + negatif] == 2) {
			totalreward += rwd.blockmalus;
			finished = -1;
		}
		else
			totalreward += rwd.blockreward;
		st.block -= grid[st.by][st.bx + negatif];
		grid[st.by][st.bx + negatif] = 0;
		st.vx *= -1;
		touchedx = true;
	}
	if (grid[st.by + st.vy][st.bx] > 0)
	{
		if (grid[st.by + st.vy][st.bx] == 2) {
			totalreward += rwd.blockmalus;
			finished = -1;
		}
		else
			totalreward += rwd.blockreward;
		st.block -= grid[st.by + st.vy][st.bx];
		grid[st.by + st.vy][st.bx] = 0;
		st.vy *= -1;
		touchedy = true;
	}
	if (grid[st.by + st.vy][st.bx + negatif] > 0 && touchedx == false && touchedy == false) {

		if (grid[st.by + st.vy][st.bx + negatif] == 2) {
			totalreward += rwd.blockmalus;
			finished = -1;
		}
		else
			totalreward += rwd.blockreward;
		st.block -= grid[st.by + st.vy][st.bx + negatif];
		grid[st.by + st.vy][st.bx + negatif] = 0;
		st.vx *= -1;
		st.vy *= -1;
		touchedx = true;
		touchedy = true;
	}
	return true;
}

bool UpdateCollide(state &st, vector<vector<double>> &grid, reward rwd) {
	// WHEN TOUCH GROUND

	if (st.by + st.vy >= grid.size()) {
		totalreward += rwd.losemalus;
		finished = -1;
		return false;
	}
	if (hitBlock(st, grid, rwd) == false)
		return false;
	
	// WHEN HITTING THE PLAYER
	if (st.by + st.vy >= st.py)
	{
		if ((st.bx) == st.px) {
			st.vx = -2;
			st.vy *= -1;
		}
		else if ((st.bx) == st.px + 1) {
			st.vx = -1;
			st.vy *= -1;
		}
		else if ((st.bx) == st.px + 2) {
			st.vx = 0;
			st.vy *= -1;
		}
		
		else if ((st.bx) == st.px + 3) {
			st.vx = 1;
			st.vy *= -1;
		}
		else if ((st.bx) == st.px + 4) {
			st.vx = 2;
			st.vy *= -1;
		}
		st.bx += st.vx;
		st.by += st.vy;
	}
	if (st.by + st.vy >= grid.size()) {
		totalreward += rwd.losemalus;
		finished = -1;
		return false;
	}
	return true;
}

state makeAction(double action, state st, vector<vector<double>> &grid, reward rwd) {

	if (hitWall(st, grid)) {
		return st;
	}
	if (!UpdateCollide(st, grid, rwd)) {
		return st;
	}

	if (hitWall(st, grid)) {
		return st;
	}
	st.bx += st.vx;
	st.by += st.vy;
	if (isValidMove(action, st, grid.size())) {
		if (action == 2)
			totalreward += rwd.stillreward;
		else
		{
			if (action == 0)
				st.px -= 1;
			else if (action == 1)
				st.px += 1;
			totalreward += rwd.movemalus;
		}
	}

	return st;
}


int train(qt& Qtable, state &st, vector<vector<double>>& grid, double exploration_rate, reward rwd, int cons) {
	totalreward = 0;
	double gamma = 0.99;
	double action = 0;
	double lr = 0.2;
	state nst{0,0,0,0,0,0};
	double vx = st.vx + 2;
	double vy = st.vy;
	if (st.vy == -1)
		vy = 0;

	double r = (float)rand() / RAND_MAX;
	if (r < exploration_rate) 
		action = floor(((double)rand() / (RAND_MAX + 1)) * 3);
	else 
		action = max_element(Qtable[st.block][st.px][st.by][st.bx][vy][vx].begin(), Qtable[st.block][st.px][st.by][st.bx][vy][vx].end()) - Qtable[st.block][st.px][st.by][st.bx][vy][vx].begin();

	nst = makeAction(action,st, grid, rwd);
	double nvx = nst.vx + 2;
	double nvy = nst.vy;
	if (nst.vy == -1)
		nvy = 0;

	if (nst.block == 2)
	{
		totalreward += rwd.winreward;
		finished = 1;
	}

	if (cons == 499 && finished == 0) {
		totalreward += rwd.losemalus;
		finished = -1;
	}
	//print_state(nst);
	double new_action = max_element(Qtable[nst.block][nst.px][nst.by][nst.bx][nvy][nvx].begin(), Qtable[nst.block][nst.px][nst.by][nst.bx][nvy][nvx].end()) - Qtable[nst.block][nst.px][nst.by][nst.bx][nvy][nvx].begin();
	Qtable[st.block][st.px][st.by][st.bx][vy][vx][action] = Qtable[st.block][st.px][st.by][st.bx][vy][vx][action] + lr * (totalreward + gamma * Qtable[nst.block][nst.px][nst.by][nst.bx][nvy][nvx][new_action] - Qtable[st.block][st.px][st.by][st.bx][vy][vx][action]);
	st = nst;
	
	return finished;
}