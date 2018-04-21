#pragma once

/*

�����

Approach_v1:

BFS ͨ�� 20% ��������

Approach_v2:

BFS + memo ���ڴ档��

Approach_v3:

Greedy

���ߣ�Leoric
���ӣ�https://www.nowcoder.com/discuss/73357
��Դ��ţ����

���ȼ�������������޵�״̬������������������Ҫ���ٲ��������ޣ��Ƚ���a�μӹ����������ٽ���b�ι�����������a+b��С��
�������ɱ����õ���������ʽֱ�Ӽ���Ҳ�У����������ͰѼӹ����͹������ֲ����ϲ��ˣ���Ϊɱ�ֲ������������������С����Ϊc�����Ӷ�O��100*100����

f(x) = attack_cnt + add_ap_cnt
add_ap_cnt = ceil(HM / (AP + add_ap_cnt * B))
f(x) = x + ceil(HM / (AP + B*x))
ע����f(x) = x + 1/x �ĺ������ʣ���֪�����ͨ������x���ܼ���f(x)�����ʱ��f(x)�Ѿ�����Сֵ��

���ſ������淽�棬ͬ�����ѻ�Ѫ�ͼ����ϲ�Ϊ������������Ȼ��������Ҫ�Ƚ��з���������ʹ���޵Ĺ��������������ֵ���������ǽ���c�ι���������
�ڷ��������У�����Ӧ�þ����ܵذѼ���������������ǰ�棬���������ս���л���Ҫ���м�������������ǰ������ֵ���ڹ��޹����������Ȼ���м���������
���⣬������������˼��������������d�λظ���ʹ���ܹ�����c��ɱ�ֲ�����������������
��ˣ����Դӳ�ʼ״̬��������step=0��Ȼ��ѭ��ʹstep++������������޹��������ڵ�ǰ����ֵ����ظ�����ֵ��������ٹ��޹�������
����ÿ��step��������O��1���ĸ��Ӷ�ֱ�Ӽ�����ظ�����d�����ܲ���Ϊstep+d+c����������õ�����ܲ�����ȡ��Сֵ�͵õ����ս�������Ӷ�O��100����

������

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


	// �޵�״̬��ɱ�ֲ������ӹ������������������С����
	// ��Ȼ��Ҫ�������С����Ϊk��ɱ�ֲ�������k = a + b����a�μӹ�����b�ι��������Ƚ���a�μӹ����������ٽ���b�ι�������������õ�ɱ�����档
	int min_kill_cnt = INT_MAX;
	int add_ap_cnt = 0;	// ��¼�ӹ����Ĵ���
	// ������100��ɱ�ֲ���
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
		// ���ͨ�����Ӽӹ����Ĵ������ܼ����ܵ�ɱ�ֲ����Ĵ�����������ӹ����Ѿ����棨����f(x) = x + 1/x �ĺ���ͼ��
		else
			break;
		++add_ap_cnt;
	}
	//cout << "min_kill_cnt = " << min_kill_cnt << endl;

	// ����״̬�����Ƚ����������﹥������������Ѫ��С�ڵ��ڹ��﹥������̽��������Ĺ�����ʱ�����лָ�Ѫ��������
	// ���ǰ���step�μ��������������ָ�Ѫ���������󣬼��㻹��Ҫ���ٴλָ�����ʹ�ý�ɫ�ܹ����� min_kill_cnt �ι�����
	// ����ǰѪ����Ҫ���� min_kill_cnt + recover_hp_cnt - 1 �ι�������� recover_hp_cnt ����
	int min_survive_cnt = INT_MAX;
	// ������200�μ��������������ظ�Ѫ��������
	for (int step = 0; step < 200; ++step)
	{
		int curr_hp = HP;
		int curr_am = AM;

		// ���� step �μ�������
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

		// ����Ҫ���ٴλָ�����ʹ�ý�ɫ�ܹ����� min_kill_cnt �ι�����ע�����һ�ι���ʱ�����ÿ����ٴ��ܵ���������Ϊ���ﱻɱ����
		int recover_hp_cnt = 0;
		int curr_kill_cnt = 0;
		// ���200�λظ�����
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
		// ���200�λظ��������޷��� curr_am ��Ϊ0����ǰstep�μ����޷��ɹ���������һ�ε���
		if (curr_hp <= 0 || curr_am > 0)
		{
			continue;
		}
		// ���� min_survive_cnt
		int curr_survive_cnt = step + recover_hp_cnt;
		if (min_survive_cnt >= curr_survive_cnt)
		{
			min_survive_cnt = curr_survive_cnt;
		}
		// ���ͨ�����Ӽ����Ĵ������ܼ����ܵ�ɱ�ֲ����Ĵ���������������Ѿ����棬��֤��������
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
	int HP;		// ��ɫѪ��
	int AP;		// ��ɫ������
	int HM;		// ����Ѫ��
	int AM;		// ���﹥����
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
		// ���Ӷ��е�ǰ����Ԫ��
		for (int i = 0; i < size; ++i)
		{
			Node curr = Q.front();
			Q.pop();

			// ������Ѫ����Ϊ0�����ʤ������Ϊ���ȹ�������ʹ���ʱ���˵�Ѫ��Ҳ��Ϊ0����Ȼ����ʤ����
			if (curr.HM <= 0)
			{
				cout << step << endl;
				return;
			}
			// ����ǰ�ڵ�HP�Ѿ���Ϊ0�����״̬ʧ�ܣ�����һ���ڵ�
			if (curr.HP <= 0)
				continue;

			// attack ��֧
			Node attack { curr.HP - curr.AM, curr.AP, curr.HM - curr.AP, curr.AM };
			// recover ��֧
			Node recover { HP - curr.AM, curr.AP, curr.HM, curr.AM };
			// enhance ��֧
			Node enhance { curr.HP - curr.AM, curr.AP + B, curr.HM, curr.AM };
			// weaken ��֧
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

	// ������¼�Ѿ����ʹ���״̬
	vector<vector<vector<vector<bool>>>> visited(101, vector<vector<vector<bool>>>(101, vector<vector<bool>>(101, vector<bool>(101, false))));

	queue<Node> Q;
	int step = 0;
	Q.push(curr);

	while (!Q.empty())
	{
		int size = Q.size();
		// ���Ӷ��е�ǰ����Ԫ��
		for (int i = 0; i < size; ++i)
		{
			Node curr = Q.front();
			Q.pop();
			visited[curr.HP][curr.AP][curr.HM][curr.AM] = true;

			// ������Ѫ����Ϊ0�����ʤ������Ϊ���ȹ�������ʹ���ʱ���˵�Ѫ��Ҳ��Ϊ0����Ȼ����ʤ����
			if (curr.HM <= 0)
			{
				cout << step << endl;
				return;
			}
			// ����ǰ�ڵ�HP�Ѿ���Ϊ0�����״̬ʧ�ܣ�����һ���ڵ�
			//if(curr.HP <= 0)
			//	continue;

			// attack ��֧
			Node attack { curr.HP - curr.AM, curr.AP, curr.HM - curr.AP, curr.AM };
			if (attack.HM <= 0)
			{
				cout << step + 1 << endl;
				return;
			}
			if (attack.HP > 0 && !visited[attack.HP][attack.AP][attack.HM][attack.AM])
				Q.push(attack);
			// recover ��֧
			Node recover { HP - curr.AM, curr.AP, curr.HM, curr.AM };
			if (recover.HP > 0 && !visited[recover.HP][recover.AP][recover.HM][recover.AM])
				Q.push(recover);
			// enhance ��֧
			if (B > 0)
			{
				Node enhance { curr.HP - curr.AM, curr.AP + B, curr.HM, curr.AM };
				if (enhance.HP > 0 && !visited[enhance.HP][enhance.AP][enhance.HM][enhance.AM])
					Q.push(enhance);
			}
			// weaken ��֧
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
	int HP = 0;		// ��ɫѪ��
	int AP = 0;		// ��ɫ������
	int HM = 0;		// ����Ѫ��
	int AM = 0;		// ���﹥����
	int B = 0;		// ��������ɫ����B�㹥����
	int D = 0;		// ���������޼���D�㹥��������౻������0��
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