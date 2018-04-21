#pragma once

/*

打怪兽

Approach_v1:

BFS 通过 20% 测试用例

Approach_v2:

BFS + memo 爆内存。。

Approach_v3:

Greedy

作者：Leoric
链接：https://www.nowcoder.com/discuss/73357
来源：牛客网

首先计算出假设你是无敌状态（不会死亡）至少需要多少步打死怪兽，先进行a次加攻击操作，再进行b次攻击操作，且a+b最小。
这个结果可遍历得到（可能列式直接计算也行）。这样，就把加攻击和攻击两种操作合并了，称为杀怪操作，并设这个操作最小次数为c。复杂度O（100*100）。

f(x) = attack_cnt + add_ap_cnt
add_ap_cnt = ceil(HM / (AP + add_ap_cnt * B))
f(x) = x + ceil(HM / (AP + B*x))
注：由f(x) = x + 1/x 的函数性质，可知，如果通过增加x不能减少f(x)，则此时的f(x)已经是最小值。

接着考虑生存方面，同样，把回血和减攻合并为防御操作。显然，我们需要先进行防御操作，使怪兽的攻击和自身的生命值足以让我们进行c次攻击操作。
在防御操作中，我们应该尽可能地把减攻操作给安排在前面，即如果整个战略中还需要进行减攻操作且自身当前的生命值大于怪兽攻击力，则必然进行减攻操作。
另外，假设我们完成了减攻操作，则进行d次回复，使得能够进行c次杀怪操作且自身不会死亡。
因此，可以从初始状态出发，令step=0。然后循环使step++，并且如果怪兽攻击力大于当前生命值，则回复生命值，否则减少怪兽攻击力，
对于每个step，可以用O（1）的复杂度直接计算出回复次数d，则总步数为step+d+c。这样计算得到多个总步数，取最小值就得到最终结果。复杂度O（100）。

待测试

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <queue>
#include <cmath>
#include <chrono>

using namespace std;

#define MEASURE_TIME

void solver_v3(int HP, int AP, int HM, int AM, int B, int D)
{


	// 无敌状态，杀怪操作（加攻击，攻击）所需的最小次数
	// 显然，要想次数最小假设为k此杀怪操作，且k = a + b，即a次加攻击，b次攻击，则先进行a次加攻击操作，再进行b次攻击操作具有最好的杀怪收益。
	int min_kill_cnt = INT_MAX;
	int add_ap_cnt = 0;	// 记录加攻击的次数
	// 最多进行100次杀怪操作
	for(int i = 0; i < 100; ++i)
	{
		int attack_cnt = HM / (AP + add_ap_cnt * B);
		if (attack_cnt * (AP + add_ap_cnt * B) < HM)
			++attack_cnt;
		if (min_kill_cnt >= attack_cnt + add_ap_cnt)
		{
			//cout << "add_ap_cnt = " << add_ap_cnt << endl;
			//cout << "attack_cnt = " << attack_cnt << endl;
			min_kill_cnt = add_ap_cnt + attack_cnt;
		}
		// 如果通过增加加攻击的次数不能减少总的杀怪操作的次数，则继续加攻击已经无益（想象f(x) = x + 1/x 的函数图像）
		else
			break;
		++add_ap_cnt;
	}
	//cout << "min_kill_cnt = " << min_kill_cnt << endl;

	// 正常状态，优先进行削弱怪物攻击操作，仅当血量小于等于怪物攻击（试探性削弱后的攻击）时，进行恢复血量操作，
	// 完成前面的step次减功操作（包括恢复血量操作）后，计算还需要多少次恢复操作使得角色能够进行 min_kill_cnt 次攻击，
	// 即当前血量需要承受 min_kill_cnt + recover_hp_cnt - 1 次攻击所需的 recover_hp_cnt 次数
	int min_survive_cnt = INT_MAX;
	// 最多进行200次减功操作（包括回复血量操作）
	for (int step = 0; step < 200; ++step)
	{
		int curr_hp = HP;
		int curr_am = AM;

		// 进行 step 次减功操作
		for (int i = 0; i < step; ++i)
		{
			if (curr_hp <= curr_am - D)
			{
				curr_hp = HP - curr_am;
			}
			else
			{
				curr_am -= D;
				if (curr_am < 0)
					curr_am = 0;
				curr_hp -= curr_am;
			}
			if (curr_hp <= 0)
				break;
		}
		if (curr_hp <= 0)
		{
			continue;
		}

		// 还需要多少次恢复操作使得角色能够进行 min_kill_cnt 次攻击，注意最后一次攻击时，不用考虑再次受到攻击，因为怪物被杀死了
		int recover_hp_cnt = 0;
		int curr_kill_cnt = 0;
		// 最多200次回复操作
		for(int i = 0; i < 200; ++i)
		{
			//cout << "curr_kill_cnt = " << curr_kill_cnt <<endl;
			//cout << "recover_hp_cnt = " << recover_hp_cnt << endl;
			if (curr_kill_cnt == min_kill_cnt - 1)
			{
				curr_am = 0;
				break;
			}
			if (curr_hp <= curr_am)
			{
				curr_hp = HP - curr_am;
				++recover_hp_cnt;
			}
			else
			{
				curr_hp -= curr_am;
				++curr_kill_cnt;
			}
			if (curr_hp <= 0)
				break;
		}
		// 如果200次回复操作都无法让 curr_am 降为0，则当前step次减功无法成功，进入下一次迭代
		if (curr_hp <= 0 || curr_am > 0)
		{
			continue;
		}
		// 更新 min_survive_cnt
		int curr_survive_cnt = step + recover_hp_cnt;
		if (min_survive_cnt >= curr_survive_cnt)
		{
			min_survive_cnt = curr_survive_cnt;
		}
		// 如果通过增加减功的次数不能减少总的杀怪操作的次数，则继续减功已经无益，待证明。。。
		else
		{
			break;
		}
	}
	if (min_survive_cnt == INT_MAX)
	{
		cout << "IMPOSSIBLE" << endl;
	}
	else
	{
		cout << min_kill_cnt + min_survive_cnt << endl;
	}
}

struct Node {
	int HP;		// 角色血量
	int AP;		// 角色攻击力
	int HM;		// 怪物血量
	int AM;		// 怪物攻击力
};

void solver(int HP, int AP, int HM, int AM, int B, int D)
{
	Node curr { HP, AP, HM, AM };
	queue<Node> Q;
	int step = 0;
	Q.push(curr);

	while (!Q.empty())
	{
		int size = Q.size();
		// 出队队列当前所有元素
		for (int i = 0; i < size; ++i)
		{
			Node curr = Q.front();
			Q.pop();

			// 若怪兽血量降为0，则获胜，（因为人先攻击，即使这个时候人的血量也降为0，依然是人胜利）
			if (curr.HM <= 0)
			{
				cout << step << endl;
				return;
			}
			// 若当前节点HP已经降为0，则此状态失败，到下一个节点
			if (curr.HP <= 0)
				continue;

			// attack 分支
			Node attack { curr.HP - curr.AM, curr.AP, curr.HM - curr.AP, curr.AM };
			// recover 分支
			Node recover { HP - curr.AM, curr.AP, curr.HM, curr.AM };
			// enhance 分支
			Node enhance { curr.HP - curr.AM, curr.AP + B, curr.HM, curr.AM };
			// weaken 分支
			curr.AM = max(0, curr.AM - D);
			Node weaken { curr.HP - curr.AM, curr.AP, curr.HM, curr.AM };
			Q.push(attack);
			Q.push(recover);
			Q.push(enhance);
			Q.push(weaken);
		}
		++step;
	}
	cout << "IMPOSSIBLE" << endl;
}

void solver_v2(int HP, int AP, int HM, int AM, int B, int D)
{
	Node curr { HP, AP, HM, AM };

	// 用来记录已经访问过的状态
	vector<vector<vector<vector<bool>>>> visited(101, vector<vector<vector<bool>>>(101, vector<vector<bool>>(101, vector<bool>(101, false))));

	queue<Node> Q;
	int step = 0;
	Q.push(curr);

	while (!Q.empty())
	{
		int size = Q.size();
		// 出队队列当前所有元素
		for (int i = 0; i < size; ++i)
		{
			Node curr = Q.front();
			Q.pop();
			visited[curr.HP][curr.AP][curr.HM][curr.AM] = true;

			// 若怪兽血量降为0，则获胜，（因为人先攻击，即使这个时候人的血量也降为0，依然是人胜利）
			if (curr.HM <= 0)
			{
				cout << step << endl;
				return;
			}
			// 若当前节点HP已经降为0，则此状态失败，到下一个节点
			//if(curr.HP <= 0)
			//	continue;

			// attack 分支
			Node attack { curr.HP - curr.AM, curr.AP, curr.HM - curr.AP, curr.AM };
			if (attack.HM <= 0)
			{
				cout << step + 1 << endl;
				return;
			}
			if (attack.HP > 0 && !visited[attack.HP][attack.AP][attack.HM][attack.AM])
				Q.push(attack);
			// recover 分支
			Node recover { HP - curr.AM, curr.AP, curr.HM, curr.AM };
			if (recover.HP > 0 && !visited[recover.HP][recover.AP][recover.HM][recover.AM])
				Q.push(recover);
			// enhance 分支
			if (B > 0)
			{
				Node enhance { curr.HP - curr.AM, curr.AP + B, curr.HM, curr.AM };
				if (enhance.HP > 0 && !visited[enhance.HP][enhance.AP][enhance.HM][enhance.AM])
					Q.push(enhance);
			}
			// weaken 分支
			if (D > 0)
			{
				curr.AM = max(0, curr.AM - D);
				Node weaken { curr.HP - curr.AM, curr.AP, curr.HM, curr.AM };
				if (weaken.HP > 0 && !visited[weaken.HP][weaken.AP][weaken.HM][weaken.AM])
					Q.push(weaken);
			}
		}
		++step;
	}

	cout << "IMPOSSIBLE" << endl;
	return;
}

void driver()
{
	int HP = 0;		// 角色血量
	int AP = 0;		// 角色攻击力
	int HM = 0;		// 怪物血量
	int AM = 0;		// 怪物攻击力
	int B = 0;		// 修炼：角色增加B点攻击力
	int D = 0;		// 削弱：怪兽减少D点攻击力（最多被削弱到0）
	cin >> HP >> AP >> HM >> AM >> B >> D;

	// measure time
#ifdef MEASURE_TIME
	auto t0 = std::chrono::high_resolution_clock::now();
#endif // MEASURE_TIME

	solver_v3(HP, AP, HM, AM, B, D);

	// measure time
#ifdef MEASURE_TIME
	auto t1 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms\n";
#endif // MEASURE_TIME
}