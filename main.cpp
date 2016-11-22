#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

const int chromeNum = 9*9;
const int unit_num = 100;
int ps = 10;//mutation possibility
const int genmax = 500;// iteration times

int rawInput[10][10] = {

	{ 0, 1, 1272, 2567, 1653, 2097, 1425, 1177, 3947, 1 },

	{ 1, 0, 1, 2511, 1633, 2077, 1369, 1157, 3961, 1518 },

	{ 1272, 1, 0, 1, 380, 1490, 821, 856, 3660, 385 },

	{ 2567, 2511, 1, 0, 1, 2335, 1562, 2165, 3995, 933 },

	{ 1653, 1633, 380, 1, 0, 1, 1041, 1135, 3870, 456 },

	{ 2097, 2077, 1490, 2335, 1, 0, 1, 920, 2170, 1920 },

	{ 1425, 1369, 821, 1562, 1041, 1, 0, 1, 4290, 626 },

	{ 1177, 1157, 856, 2165, 1135, 920, 1, 0, 1, 1290 },

	{ 3947, 3961, 3660, 3995, 3870, 2170, 4290, 1, 0, 1 },

	{ 1, 1518, 385, 993, 456, 1920, 626, 1290, 1, 0 }
};

class Unit
{
public:
	int chrome[chromeNum];
	int length;
	int val;
	bool operator < (const Unit & that) const
	{
		return this->val < that.val;
	}
};

class Group
{
private:
	void qfind(vector<Unit>& a, int l, int r, int k)
	{
		int i = l, j = r;
		auto t = a[rand() % (r - l + 1) + l];
		do
		{
			while (a[i] < t) i++;
			while (t < a[j]) j--;
			if (i <= j)
				swap(a[i++], a[j--]);
		} while (i <= j);
		if (k <= j - l)
			qfind(a, l, j, k);
		if (k >= i - l)
			qfind(a, i, r, k - i + l);
	}
public:
	vector<Unit> group;
	Unit best;
	int best_gen;

	Group()
	{
		group.resize(chromeNum);
		best.length = 0x3f3f3f3f;
		best_gen = 0;
		for (int i = 0; i < unit_num; i++)
		{
			bool flag[chromeNum] = {};

			for (int j = 0; j < chromeNum; j++)
			{
				int t_city = rand() % chromeNum;
				while (flag[t_city])
					t_city = rand() % chromeNum;
				flag[t_city] = true;
				group[i].chrome[j] = t_city;
			}
		}
	}

	void assess()
	{
	
	}

	void unit_sort()
	{
		for (int i = 0; i < unit_num; i++)
		{
			for (int j = i + 1; j < unit_num; j++)
			{
				if (group[i].length > group[j].length)
				{
					Unit temp;
					memcpy(&temp, &group[i], sizeof(Unit));
					memcpy(&group[i], &group[j], sizeof(Unit));
					memcpy(&group[j], &temp, sizeof(Unit));
				}
			}
		}
	}

	//cross
	Unit cross(Unit &father, Unit &mother)
	{
		Unit son;
		//...
		return son;
	}

	//mutation
	void mutation(Unit &t)
	{
		
	}

	//
	void print()
	{
	
	}

	//种群进化
	void evolve()
	{
		for (int i = 0; i < genmax; i++)
		{
			// Increase mutaion when generatin 
			if (i > 20)
				ps *= 3;

			assess();//assess

			sort(group.begin(), group.end());

			if (best.length > group[0].length)
			{
				memcpy(&best, &group[0], sizeof(group[0]));
				best_gen = i;
			}

			for (int j = 0; j + 2 < unit_num; j += 3)
				group[j + 2] = cross(group[j], group[j + 1]);

			for (int j = 0; j < chromeNum; j++)//mutation
				mutation(group[j]);
		}
	}

};

Unit group[unit_num];
Unit bestone;// record the best one
int generation_num;// recode the generation



int main()
{
	srand((int)time(0));

	for (int i = 0; i < 20; i++)
	{
		Group g;
		g.evolve();
		printf("Num", i + 1);
		for (int j = 0; j < chromeNum; j++)
			printf("%d ", g.best.chrome[j]);

		printf(";All Evaluation：%d; %dth;\n", g.best.length, g.best_gen);
	}
	system("pause");
	return 0;
}