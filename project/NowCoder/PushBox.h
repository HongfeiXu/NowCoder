#pragma once

/*

[编程题]推箱子

链接：https://www.nowcoder.com/questionTerminal/d64d259ee34141378b62e1ea4be74030
来源：牛客网

大家一定玩过“推箱子”这个经典的游戏。具体规则就是在一个N*M的地图上，有1个玩家、1个箱子、1个目的地以及若干障碍，其余是空地。
玩家可以往上下左右4个方向移动，但是不能移动出地图或者移动到障碍里去。如果往这个方向移动推到了箱子，箱子也会按这个方向移动一格，
当然，箱子也不能被推出地图或推到障碍里。当箱子被推到目的地以后，游戏目标达成。现在告诉你游戏开始是初始的地图布局，
请你求出玩家最少需要移动多少步才能够将游戏目标达成。

输入描述:
每个测试输入包含1个测试用例
第一行输入两个数字N，M表示地图的大小。其中0<N，M<=8。
接下来有N行，每行包含M个字符表示该行地图。其中 . 表示空地、X表示玩家、*表示箱子、#表示障碍、@表示目的地。
每个地图必定包含1个玩家、1个箱子、1个目的地。

输出描述:
输出一个数字表示玩家最少需要移动多少步才能将游戏目标达成。当无论如何达成不了的时候，输出-1。

示例1

输入
4 4
....
..*@
....
.X..
6 6
...#..
......
#*##..
..##.#
..X...
.@#...

输出
3
11

Approach:



从人为起点开始 bfs ,如果人走的下一步是箱子所在的坐标，说明找到了箱子，
此时需要更新箱子的坐标，使之为当前所搜方向上人的坐标前进一格（就是推一格箱子，箱子前进的方向和人前进的方向是一致的），
判断箱子是否到达了目的地，如果是则输出人移动的最少步数。到不了就输出-1。

用一个四维数组表示人与箱子的位置组合是否被访问过。int visited[9][9][9][9];

注： HDU-1254 求的是箱子移动的最小步数，需要使用优先级队列
Ref: http://blog.csdn.net/zzcblogs/article/details/73368581
Ref: http://blog.csdn.net/unclejokerly/article/details/78935162

*/

#include <vector>
#include <utility>
#include <queue>
#include <iostream>

using namespace std;

// Node 保存当前人的位置，箱子的位置，以及人移动的步数
struct Node {
	pair<int, int> playerPos;
	pair<int, int> boxPos;
	int step;
};

class Solution {
public:
	int visited[9][9][9][9] = { 0 };		//  记录当前人与箱子的位置组合是否出现过
	vector<pair<int, int>> dirs { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };	// 四个方向
	int N, M;

	bool check(int x, int y, vector<vector<char>>& gameMap)
	{//检查是否越界  
		if (x < 0 || x >= N || y >= M || y < 0 || gameMap[x][y] == '#')
			return false;
		return true;
	}

	int PushBox(vector<vector<char>>& gameMap, 
				pair<int, int>& playerPos, 
				pair<int, int>& boxPos, 
				pair<int, int>& targetPos)
	{
		N = gameMap.size();
		M = gameMap[0].size();

		if (boxPos == targetPos)
			return 0;

		queue<Node> Q;
		Node start = { playerPos, boxPos, 0 };
		Q.push(start);
		visited[start.playerPos.first][start.playerPos.second][start.boxPos.first][start.boxPos.second] = 1;
		while (!Q.empty())
		{
			Node curr = Q.front();		// 出队具有最小移动次数的 Node（先入队的肯定具有更下的 step 值）
			Q.pop();
			for (auto dir : dirs)
			{
				pair<int, int> newPlayerPos = { curr.playerPos.first + dir.first, curr.playerPos.second + dir.second };
				// 人移动一位
				Node next = { newPlayerPos, curr.boxPos, curr.step + 1};
				// 若人走到了箱子上，则判断箱子的新位置是否合法即可
				if (next.playerPos == next.boxPos)	
				{
					next.boxPos.first += dir.first;
					next.boxPos.second += dir.second;
					// 若箱子的新位置合法 并且 人与箱子的位置组合未被访问过
					if (check(next.boxPos.first, next.boxPos.second, gameMap) 
						&& visited[next.playerPos.first][next.playerPos.second][next.boxPos.first][next.boxPos.second] == 0)
					{
						// 在入队的时候判断箱子是否已经移到目标位置，若移动到，则输出结果
						if (next.boxPos == targetPos)
							return next.step;
						visited[next.playerPos.first][next.playerPos.second][next.boxPos.first][next.boxPos.second] = 1;
						Q.push(next);
					}
				}
				// 若人未走到箱子上，则判断人的位置是否合法即可
				else
				{
					// 如人的新位置合法 并且 人与箱子的位置组合未被访问过
					if (check(next.playerPos.first, next.playerPos.second, gameMap) 
						&& visited[next.playerPos.first][next.playerPos.second][next.boxPos.first][next.boxPos.second] == 0)
					{
						visited[next.playerPos.first][next.playerPos.second][next.boxPos.first][next.boxPos.second] = 1;
						Q.push(next);
					}
				}
			}
		}
		return -1;
	}
};

void driver()
{
	int N, M;
	cin >> N >> M;
	vector<vector<char>> gameMap(N, vector<char>(M, ' '));
	pair<int, int> playerPos;
	pair<int, int> boxPos;
	pair<int, int> targetPos;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
		{
			cin >> gameMap[i][j];
			if (gameMap[i][j] == 'X')
				playerPos = { i, j };
			else if (gameMap[i][j] == '*')
				boxPos = { i, j };
			else if (gameMap[i][j] == '@')
				targetPos = { i, j };
		}
	Solution solu;
	cout << solu.PushBox(gameMap, playerPos, boxPos, targetPos) << endl;
}

/*

// code v2

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
	int playerX;
	int playerY;
	int boxX;
	int boxY;
	int step;
	Node(int playerX_, int playerY_, int boxX_, int boxY_, int step_)
		: playerX(playerX_), playerY(playerY_), boxX(boxX_), boxY(boxY_), step(step_)
	{ }
};

bool operator< (const Node& lhs, const Node& rhs)
{
	return lhs.step > rhs.step;
}

int N, M;

bool check(int x, int y, vector<vector<char>>& gameMap)
{
	return(x >= 0 && x < N && y >= 0 && y < M && gameMap[x][y] != '#');
}

int main()
{
	cin >> N >> M;
	vector<vector<char>> gameMap(N, vector<char>(M, ' '));
	int playerX, playerY;
	int boxX, boxY;
	int desX, desY;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> gameMap[i][j];
			if (gameMap[i][j] == 'X')
				playerX = i, playerY = j;
			else if (gameMap[i][j] == '*')
				boxX = i, boxY = j;
			else if (gameMap[i][j] == '@')
				desX = i, desY = j;
		}
	}
	if (playerX == boxX && playerY == boxY)
		return 0;
	// 四个方向
	int dirsX[] = { -1,1,0,0 };
	int dirsY[] = { 0,0,-1,1 };
	// 用四维数组标记当前玩家和箱子的位置组合是否被访问过
	int visited[9][9][9][9] = { 0 };	// 置位0,（第一位置位0后，余下各位初始化为默认值0）
	queue<Node> Q;
	visited[playerX][playerY][boxX][boxY] = 1;
	Q.push(Node(playerX, playerY, boxX, boxY, 0));
	while (!Q.empty())
	{
		Node curr = Q.front();
		Q.pop();
		for (int i = 0; i < 4; ++i)
		{
			// 玩家的新位置
			int playerNewX = curr.playerX + dirsX[i];
			int playerNewY = curr.playerY + dirsY[i];
			// 如果玩家移动到箱子上
			if (playerNewX == curr.boxX && playerNewY == curr.boxY)
			{
				int boxNewX = curr.boxX + dirsX[i];
				int boxNewY = curr.boxY + dirsY[i];
				if (check(boxNewX, boxNewY, gameMap)
					&& visited[playerNewX][playerNewY][boxNewX][boxNewY] == 0)
				{
					if (boxNewX == desX && boxNewY == desY)
					{
						cout << curr.step + 1 << endl;
						return 0;
					}
					Q.push(Node(playerNewX, playerNewY, boxNewX, boxNewY, curr.step + 1));
					visited[playerNewX][playerNewY][boxNewX][boxNewY] = 1;
				}
			}
			// 如果玩家并未移动到箱子上
			else
			{
				if (check(playerNewX, playerNewY, gameMap)
					&& visited[playerNewX][playerNewY][curr.boxX][curr.boxY] == 0)
				{
					Q.push(Node(playerNewX, playerNewY, curr.boxX, curr.boxY, curr.step + 1));
					visited[playerNewX][playerNewY][curr.boxX][curr.boxY] = 1;
				}
			}
		}
	}
	cout << -1 << endl;
	return 0;
}

*/