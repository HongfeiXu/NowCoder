/*

HDU - 1254 ������

Ref: http://acm.hdu.edu.cn/showproblem.php?pid=1254

��������һ���ܾ������Ϸ.������������һ���򵥰汾.��һ��M*N�ķ�������һ�����Ӻ�һ�����˹�,
���˹��Ĺ������ǰ������Ƶ�ָ����λ��,ע��,���˹�ֻ�������Ӷ�����������,
���������ӱ��Ƶ�һ������(��ͼ2)��ô���ӾͲ����ٱ��ƶ���,������ӱ��Ƶ�һ��ǽ��,��ô����ֻ������ǽ�ƶ�.

���ڸ�������Ľṹ,���ӵ�λ��,���˹���λ�ú�����Ҫ����ȥ��λ��,�����������˹�����Ҫ�ƶ����Ӷ��ٸ�.

Input
�������ݵĵ�һ����һ������T(1<=T<=20),����������ݵ�����.Ȼ����T���������,
ÿ��������ݵĵ�һ��������������M,N(2<=M,N<=7),������Ĵ�С,
Ȼ����һ��M��N�еľ���,������Ĳ���,����0����յĵذ�,1����ǽ,2�������ӵ���ʼλ��,3��������Ҫ����ȥ��λ��,4������˹�����ʼλ��.
Output
����ÿ���������,������˹�������Ҫ�ƶ����Ӷ��ٸ���ܰ������Ƶ�ָ��λ��,��������Ƶ�ָ��λ�������-1.
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
ע����ͬ�� PushBox �����ƶ�����С������ÿһ���˶����ƶ����������������ƶ�����С������
�������Ӳ���ÿһ�������ƶ������Ժ���ӵ�״̬���ܾ��и�С�� step ֵ��
����Ҫʹ�����ȼ����б���ÿһ���ƶ���״̬��ÿ��ȡ�������ƶ��������ٵ�״̬���з��ʡ�

BFS + ���ȼ�����

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
	int step;		// ���������ƶ��Ĵ���
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
	// �ĸ�����
	int dirsX[] = { -1,1,0,0 };
	int dirsY[] = { 0,0,-1,1 };
	// ����ά�����ǵ�ǰ��Һ����ӵ�λ������Ƿ񱻷��ʹ�
	int visited[8][8][8][8] = { 0 };	// ��λ0,����һλ��λ0�����¸�λ��ʼ��ΪĬ��ֵ0��
	priority_queue<Node> Q;
	visited[playerX][playerY][boxX][boxY] = 1;
	Q.push(Node(playerX, playerY, boxX, boxY, 0));
	while (!Q.empty())
	{
		Node curr = Q.top();
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
						return;
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
