#pragma once

/*

[�����]������

���ӣ�https://www.nowcoder.com/questionTerminal/d64d259ee34141378b62e1ea4be74030
��Դ��ţ����

���һ������������ӡ�����������Ϸ��������������һ��N*M�ĵ�ͼ�ϣ���1����ҡ�1�����ӡ�1��Ŀ�ĵ��Լ������ϰ��������ǿյء�
��ҿ�������������4�������ƶ������ǲ����ƶ�����ͼ�����ƶ����ϰ���ȥ���������������ƶ��Ƶ������ӣ�����Ҳ�ᰴ��������ƶ�һ��
��Ȼ������Ҳ���ܱ��Ƴ���ͼ���Ƶ��ϰ�������ӱ��Ƶ�Ŀ�ĵ��Ժ���ϷĿ���ɡ����ڸ�������Ϸ��ʼ�ǳ�ʼ�ĵ�ͼ���֣�
����������������Ҫ�ƶ����ٲ����ܹ�����ϷĿ���ɡ�

��������:
ÿ�������������1����������
��һ��������������N��M��ʾ��ͼ�Ĵ�С������0<N��M<=8��
��������N�У�ÿ�а���M���ַ���ʾ���е�ͼ������ . ��ʾ�յء�X��ʾ��ҡ�*��ʾ���ӡ�#��ʾ�ϰ���@��ʾĿ�ĵء�
ÿ����ͼ�ض�����1����ҡ�1�����ӡ�1��Ŀ�ĵء�

�������:
���һ�����ֱ�ʾ���������Ҫ�ƶ����ٲ����ܽ���ϷĿ���ɡ���������δ�ɲ��˵�ʱ�����-1��

ʾ��1

����
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

���
3
11

Approach:



����Ϊ��㿪ʼ bfs ,������ߵ���һ�����������ڵ����꣬˵���ҵ������ӣ�
��ʱ��Ҫ�������ӵ����꣬ʹ֮Ϊ��ǰ���ѷ������˵�����ǰ��һ�񣨾�����һ�����ӣ�����ǰ���ķ������ǰ���ķ�����һ�µģ���
�ж������Ƿ񵽴���Ŀ�ĵأ��������������ƶ������ٲ����������˾����-1��

��һ����ά�����ʾ�������ӵ�λ������Ƿ񱻷��ʹ���int visited[9][9][9][9];

ע�� HDU-1254 ����������ƶ�����С��������Ҫʹ�����ȼ�����
Ref: http://blog.csdn.net/zzcblogs/article/details/73368581
Ref: http://blog.csdn.net/unclejokerly/article/details/78935162

*/

#include <vector>
#include <utility>
#include <queue>
#include <iostream>

using namespace std;

// Node ���浱ǰ�˵�λ�ã����ӵ�λ�ã��Լ����ƶ��Ĳ���
struct Node {
	pair<int, int> playerPos;
	pair<int, int> boxPos;
	int step;
};

class Solution {
public:
	int visited[9][9][9][9] = { 0 };		//  ��¼��ǰ�������ӵ�λ������Ƿ���ֹ�
	vector<pair<int, int>> dirs { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };	// �ĸ�����
	int N, M;

	bool check(int x, int y, vector<vector<char>>& gameMap)
	{//����Ƿ�Խ��  
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
			Node curr = Q.front();		// ���Ӿ�����С�ƶ������� Node������ӵĿ϶����и��µ� step ֵ��
			Q.pop();
			for (auto dir : dirs)
			{
				pair<int, int> newPlayerPos = { curr.playerPos.first + dir.first, curr.playerPos.second + dir.second };
				// ���ƶ�һλ
				Node next = { newPlayerPos, curr.boxPos, curr.step + 1};
				// �����ߵ��������ϣ����ж����ӵ���λ���Ƿ�Ϸ�����
				if (next.playerPos == next.boxPos)	
				{
					next.boxPos.first += dir.first;
					next.boxPos.second += dir.second;
					// �����ӵ���λ�úϷ� ���� �������ӵ�λ�����δ�����ʹ�
					if (check(next.boxPos.first, next.boxPos.second, gameMap) 
						&& visited[next.playerPos.first][next.playerPos.second][next.boxPos.first][next.boxPos.second] == 0)
					{
						// ����ӵ�ʱ���ж������Ƿ��Ѿ��Ƶ�Ŀ��λ�ã����ƶ�������������
						if (next.boxPos == targetPos)
							return next.step;
						visited[next.playerPos.first][next.playerPos.second][next.boxPos.first][next.boxPos.second] = 1;
						Q.push(next);
					}
				}
				// ����δ�ߵ������ϣ����ж��˵�λ���Ƿ�Ϸ�����
				else
				{
					// ���˵���λ�úϷ� ���� �������ӵ�λ�����δ�����ʹ�
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
	// �ĸ�����
	int dirsX[] = { -1,1,0,0 };
	int dirsY[] = { 0,0,-1,1 };
	// ����ά�����ǵ�ǰ��Һ����ӵ�λ������Ƿ񱻷��ʹ�
	int visited[9][9][9][9] = { 0 };	// ��λ0,����һλ��λ0�����¸�λ��ʼ��ΪĬ��ֵ0��
	queue<Node> Q;
	visited[playerX][playerY][boxX][boxY] = 1;
	Q.push(Node(playerX, playerY, boxX, boxY, 0));
	while (!Q.empty())
	{
		Node curr = Q.front();
		Q.pop();
		for (int i = 0; i < 4; ++i)
		{
			// ��ҵ���λ��
			int playerNewX = curr.playerX + dirsX[i];
			int playerNewY = curr.playerY + dirsY[i];
			// �������ƶ���������
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
			// �����Ҳ�δ�ƶ���������
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