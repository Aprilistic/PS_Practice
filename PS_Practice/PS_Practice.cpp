#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

inline int cell(int y, int x) { return 1 << (y * 5 + x); }


vector<int> moves; //push blocks by bitmasking to integer
void preCalc() {
	for(int y=0; y<4; ++y)
		for (int x = 0; x < 4; ++x) {
			vector<int> cells;
			for(int dy=0; dy<2; ++dy)
				for (int dx = 0; dx < 2; ++dx)
					cells.push_back(cell(y + dy, x + dx));
			int square = cells[0] + cells[1] + cells[2] + cells[3];
			for (int i = 0; i < 4; ++i)
				moves.push_back(square - cells[i]);
		}

	for(int i=0; i<5; ++i)
		for (int j = 0; j < 4; ++j) {
			moves.push_back(cell(i, j) + cell(i, j + 1));
			moves.push_back(cell(j, i) + cell(j + 1, i));
		}
}

char cache[1 << 25];
char play(int board) {
	char& ret = cache[board];
	if (ret != -1) return ret;

	ret = 0;
	for(int i=0; i<moves.size(); ++i)
		if((moves[i]&board)==0)
			if (!play(board | moves[i])) {
				ret = 1;
				break;
			}
	return ret;
}


int main()
{
	preCalc();
	int tCase;
	cin >> tCase;
	while (tCase--) {
		int board = 0;
		memset(cache, -1, sizeof(cache));

		for(int y=0; y<5; ++y)
			for (int x = 0; x < 5; ++x) {
				char tmp;
				cin >> tmp;

				if (tmp == '#') board += cell(y, x);
			}
		char result = play(board);

		if (result == 1)
			cout << "WINNING\n";
		else
			cout << "LOSING\n";

	}
}
