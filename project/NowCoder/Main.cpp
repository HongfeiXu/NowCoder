/*

HDU - 1254 推箱子

Ref: http://acm.hdu.edu.cn/showproblem.php?pid=1254

推箱子是一个很经典的游戏.今天我们来玩一个简单版本.在一个M*N的房间里有一个箱子和一个搬运工,
搬运工的工作就是把箱子推到指定的位置,注意,搬运工只能推箱子而不能拉箱子,
因此如果箱子被推到一个角上(如图2)那么箱子就不能再被移动了,如果箱子被推到一面墙上,那么箱子只能沿着墙移动.

现在给定房间的结构,箱子的位置,搬运工的位置和箱子要被推去的位置,请你计算出搬运工至少要推动箱子多少格.

Input
输入数据的第一行是一个整数T(1<=T<=20),代表测试数据的数量.然后是T组测试数据,
每组测试数据的第一行是两个正整数M,N(2<=M,N<=7),代表房间的大小,
然后是一个M行N列的矩阵,代表房间的布局,其中0代表空的地板,1代表墙,2代表箱子的起始位置,3代表箱子要被推去的位置,4代表搬运工的起始位置.
Output
对于每组测试数据,输出搬运工最少需要推动箱子多少格才能帮箱子推到指定位置,如果不能推到指定位置则输出-1.
Sample Input
1
5 5
0 3 0 0 0
1 0 1 4 0
0 0 1 0 0
1 0 2 0 0
0 0 0 0 0
Sample Output
4

Approach:
注：不同于 PushBox 求人移动的最小步数（每一步人都会移动），这里求箱子移动的最小步数，
由于箱子不是每一步都会移动，所以后入队的状态可能具有更小的 step 值，
故需要使用优先级队列保存每一步移动的状态，每次取出箱子移动次数最少的状态进行访问。

BFS + 优先级队列

*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
	int playerX;
	int playerY;
	int boxX;
	int boxY;
	int step;		// 保存箱子移动的次数
	Node(int playerX_, int playerY_, int boxX_, int boxY_, int step_)
		: playerX(playerX_), playerY(playerY_), boxX(boxX_), boxY(boxY_), step(step_)
	{
	}
};

bool operator< (const Node& lhs, const Node& rhs)
{
	return lhs.step > rhs.step;
}

int N, M;

bool check(int x, int y, vector<vector<int>>& gameMap)
{
	return(x >= 0 && x < N && y >= 0 && y < M && gameMap[x][y] != 1);
}

void solver()
{
	cin >> N >> M;
	vector<vector<int>> gameMap(N, vector<int>(M, 0));
	int playerX, playerY;
	int boxX, boxY;
	int desX, desY;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> gameMap[i][j];
			if (gameMap[i][j] == 4)
				playerX = i, playerY = j;
			else if (gameMap[i][j] == 2)
				boxX = i, boxY = j;
			else if (gameMap[i][j] == 3)
				desX = i, desY = j;
		}
	}
	if (playerX == boxX && playerY == boxY)
	{
		cout << 0 << endl;
		return;
	}
	// 四个方向
	int dirsX[] = { -1,1,0,0 };
	int dirsY[] = { 0,0,-1,1 };
	// 用四维数组标记当前玩家和箱子的位置组合是否被访问过
	int visited[8][8][8][8] = { 0 };	// 置位0,（第一位置位0后，余下各位初始化为默认值0）
	priority_queue<Node> Q;
	visited[playerX][playerY][boxX][boxY] = 1;
	Q.push(Node(playerX, playerY, boxX, boxY, 0));
	while (!Q.empty())
	{
		Node curr = Q.top();
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
						return;
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
					Q.push(Node(playerNewX, playerNewY, curr.boxX, curr.boxY, curr.step));
					visited[playerNewX][playerNewY][curr.boxX][curr.boxY] = 1;
				}
			}
		}
	}
	cout << -1 << endl;
	return;
}
int main()
{
	int K;
	cin >> K;
	for (int i = 0; i < K; ++i)
	{
		solver();
	}
	return 0;
}
