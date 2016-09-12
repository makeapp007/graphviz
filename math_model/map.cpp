/*
地图生成器
随机生成一个城市的地图（第二新北京市）
城市中只存在东西向和南北向的道路，分为干路、次干路、支路三种
三种路的通行速度从高到低依次减小
输出格式为：
首行三个数v1, v2, v3，分别表示干路、次干路、支路上的速度
后一行两个数max_X, max_Y，表示图的范围
后一行一个整数N，表示该城市有N条道路
之后N行，每行表示一条道路的信息，具体格式为
[0|1] [x|y] [0|1|2] [-1|0|1]
表示横坐标为x/纵坐标为y有一条干路/次干路/支路，这条路为由北向南或由西向东/双行道/由南向北或由东向西
之后一个整数P，表示该城市有P个路口存在红绿灯
之后P行，每行三个数x, y, k，表示在该坐标处存在一个红绿灯，对周边道路产生的缓慢影响因子为k
之后一行一个整数M，表示该城市有M个可开放的小区
之后M行，每行五个数x, y, d1, d2, v，表示每个小区的坐标，西北-东南/东北-西南方向穿过小区时的距离和该道路的速度
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

double rand(double x1, double x2){
	int y1 = x1 * 1000;
	int y2 = x2 * 1000;
	int y = (rand() % (y2 - y1) + y1);
	double ans = y / 1000.0;
	return ans;
}
int find(double a[], double x){
	int i = 1;
	while (a[i + 1] < x) i++;
	return i;
}
int N, M, P;
double a[5000], b[5000];
bool f[5000][5000];
bool occx[5000], occy[5000];
int main(){
	srand((unsigned)time(NULL));
	//随机生成三种路上的速度，并输出
	double v1 = 70, v2 = 50, v3 = 40;
	cout << v1 << " " << v2 << " " << v3 << endl;

	//随机生成地图大小,取5.5km - 17km，范围大致为北京二环到四环边长，并输出
	double max_X, max_Y; 
	max_X = rand(5.5, 17);
	max_Y = rand(5.5, 17);
	cout << max_X << " " << max_Y << endl;
	double area = max_X * max_Y;

	//随机生成干路、次干路、支路条数，密度分别为0.8-1.2km/km2、1.2-1.4km/km2、3-5km/km2
	int primary, secondary, branch;
	primary = area * rand(0.8, 1.2) / (max_X + max_Y) * 2 + 0.5;
	secondary = area * rand(1.2, 1.4) / (max_X + max_Y) * 2 + 0.5;
	branch = area * rand(3, 5) / (max_X + max_Y) * 2 + 0.5;
	N = primary + secondary + branch;

	//随机生成各条路的情况，并输出
	cout << N << endl;
	memset(occx, 1, sizeof(occx));
	memset(occy, 1, sizeof(occy));
	int t1 = 0, t2 = 0; //记录坐标
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	for (int i = 1; i <= primary; i++){
		int direction = rand() % 2; //方向
		double coor; //坐标
		if (direction == 0){
			coor = rand(0, max_X);
			while (!occx[(int)(coor*2)]) coor = rand(0, max_X);
			a[++t1] = coor;
			occx[(int)(coor*2)] = false;
		}
		else{
			coor = rand(0, max_Y);
			while (!occy[(int)(coor*2)]) coor = rand(0, max_Y);
			b[++t2] = coor;
			occy[(int)(coor*2)] = false;
		}
		int width = 0; //类别
		int single = rand() % 50 - 1; //单行
		if (single >= 2) single = 0;
		cout << direction << " " << coor << " " << width << " " << single << endl;
	}
	for (int i = 1; i <= secondary; i++){
		int direction = rand() % 2; //方向
		double coor; //坐标
		if (direction == 0){
			coor = rand(0, max_X);
			while (!occx[(int)(coor * 4)]) coor = rand(0, max_X);
			a[++t1] = coor;
			occx[(int)(coor * 4)] = false;
		}
		else{
			coor = rand(0, max_Y);
			while (!occy[(int)(coor * 4)]) coor = rand(0, max_Y);
			b[++t2] = coor;
			occy[(int)(coor * 4)] = false;
		}
		int width = 1; //类别
		int single = rand() % 50 - 1; //单行
		if (single >= 2) single = 0;
		cout << direction << " " << coor << " " << width << " " << single << endl;
	}
	for (int i = 1; i <= branch; i++){
		int direction = rand() % 2; //方向
		double coor; //坐标
		if (direction == 0){
			coor = rand(0, max_X);
			while (!occx[(int)(coor * 10)]) coor = rand(0, max_X);
			a[++t1] = coor;
			occx[(int)(coor * 10)] = false;
		}
		else{
			coor = rand(0, max_Y);
			while (!occy[(int)(coor * 10)]) coor = rand(0, max_Y);
			b[++t2] = coor;
			occy[(int)(coor * 10)] = false;
		}
		int width = 2; //类别
		int single = rand() % 50 - 1; //单行
		if (single >= 2) single = 0;
		cout << direction << " " << coor << " " << width << " " << single << endl;
	}
	a[t1 + 1] = max_X; b[t2 + 1] = max_Y;

	//随机生成红绿灯数目和具体信息，并输出
	sort(a + 1, a + 1 + t1);
	sort(b + 1, b + 1 + t2);
	for (int i = 1; i <= t1; i++)
		for (int j = 1; j <= t2; j++)
			f[i][j] = true;
	int P = t1 * t2 * rand(0.2, 0.6); //考虑到很多路段都有红绿灯
	cout << P << endl;
	int i = 0;
	while ((++i) <= P){
		int x, y;
		while (1){
			x = rand() % t1 + 1;
			y = rand() % t2 + 1;
			if (f[x][y]) break;
		}
		f[x][y] = false;
		double k = rand(0.6, 1);
		cout << a[x] << " " << b[y] << " " << k << endl;
	}

	//随机生成小区数目和具体信息，并输出
	//参考密度为北京东城区+西城区面积为90km2，共有460个小区，为5.11个/km2
	int M = area * 5.11;
	cout << M << endl;
	for (int i = 1; i <= M; i++){
		double x = rand(0, a[t1]);
		double y = rand(0, b[t2]);
		int p1 = find(a, x);
		int p2 = find(b, y);
		double dist = sqrt((a[p1] - a[p1 + 1]) * (a[p1] - a[p1 + 1]) + (b[p2] - b[p2 + 1]) * (b[p2] - b[p2 + 1]));
		double d1 = rand(dist, (a[p1 + 1] + b[p2 + 1] - a[p1] - b[p2]) * 0.7); //经过小区的路段长度
		double d2 = rand(dist, (a[p1 + 1] + b[p2 + 1] - a[p1] - b[p2]) * 0.8);
		double v = rand(55, 65); //随机小区内道路平均速度
		cout << x << " " << y << " " << d1 << " " << d2 << " " << v << endl;
	}

	return 0;
}