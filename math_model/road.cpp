#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;

int N, M, P;
int t1, t2;
double g[5000][5000];
double dist[5000];
int v[3];
double max_X, max_Y;
struct mymap{
	double coor;
	int direction, width, single;
} a[5000], b[5000];

typedef pair<int, int> pii;
priority_queue< pii, vector<pii>, greater<pii> > q;

bool cmp(mymap x, mymap y){
	return x.coor < y.coor;
}
int find(mymap a[], double x){
	int i = 1;
	while (a[i + 1].coor <= x) i++;
	return i;
}
void dijkstra(){
	bool f[8000];
	memset(f, 0, sizeof(f));
	for (int i = 2; i <= t1 * t2; i++) dist[i] = 0x7fffffff;
	dist[1] = 0;
	q.push(make_pair(dist[1], 1));
	while (!q.empty()){
		pii u = q.top();
		q.pop();
		int i = u.second;
		if (f[i]) continue;
		else f[i] = true;
		for (int j = 1; j <= t1 * t2; j++){
			if ((!f[j]) && (g[i][j] < 0x7fffffff) && (dist[i] + g[i][j] < dist[j])){
				dist[j] = dist[i] + g[i][j];
				q.push(make_pair(dist[j], j));
			}
		}
	}
	cout << dist[t1 * t2] << "\t";
}
int main(){
	srand((unsigned)time(NULL));
	cin >> v[0] >> v[1] >> v[2];
	cin >> max_X >> max_Y;
	cin >> N;

	t1 = 0, t2 = 0;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));

	for (int i = 1; i <= N; i++){
		int direction, width, single;
		double coor;
		cin >> direction >> coor >> width >> single;
		if (direction == 0){
			a[++t1].coor = coor;
			a[t1].width = width;
			a[t1].single = single;
		}
		else{
			b[++t2].coor = coor;
			b[t2].width = width;
			b[t2].single = single;
		}
	}

	for (int i = 1; i <= t1 * t2; i++)
		for (int j = 1; j <= t1 * t2; j++)
			if (i == j) g[i][j] = 0;
			else g[i][j] = 0x7fffffff;

	sort(a + 1, a + t1 + 1, cmp);
	sort(b + 1, b + t2 + 1, cmp);
	a[t1 + 1].coor = max_X;
	b[t2 + 1].coor = max_Y;

	int t = 0;
	for (int i = 1; i <= t1; i++)
		for (int j = 1; j <= t2; j++){
			t++;
			if (i != t1){
				double time = (a[i + 1].coor - a[i].coor) / v[b[j].width];
				if (b[j].single <= 0) g[t][t + t2] = time;
				if (b[j].single >= 0) g[t + t2][t] = time;
			}
			if (j != t2){
				double time = (b[j + 1].coor - b[j].coor) / v[a[i].width];
				if (a[i].single >= 0) g[t][t + 1] = time;
				if (a[i].single <= 0) g[t + 1][t] = time;
			}
		}
//	dijkstra();
	cin >> P;
	for (int i = 1; i <= P; i++){
		double x, y, k;
		cin >> x >> y >> k;
		int p1 = find(a, x);
		int p2 = find(b, y);
		int t = (p1 - 1) * t2 + p2;
		if (t - 1 >= 1) {if (g[t][t - 1] != 0x7fffffff) g[t][t - 1] /= k;}
		if (t - 1 >= 1) {if (g[t - 1][t] != 0x7fffffff) g[t - 1][t] /= k;}
		if (t - t2 >= 1) {if (g[t][t - t2] != 0x7fffffff) g[t][t - t2] /= k;}
		if (t - t2 >= 1) {if (g[t - t2][t] != 0x7fffffff) g[t - t2][t] /= k;}
		if (t + 1 <= t1 * t2) {if (g[t][t + 1] != 0x7fffffff) g[t][t + 1] /= k;}
		if (t + 1 <= t1 * t2) {if (g[t + 1][t] != 0x7fffffff) g[t + 1][t] /= k;}
		if (t + t2 <= t1 * t2) {if (g[t][t + t2] != 0x7fffffff) g[t][t + t2] /= k;}
		if (t + t2 <= t1 * t2) {if (g[t + t2][t] != 0x7fffffff) g[t + t2][t] /= k;}
	}
	dijkstra();

	cin >> M;
	for (int i = 1; i <= M; i++){
		double x, y, d1, d2, v;
		cin >> x >> y >> d1 >> d2 >> v;
		int p1 = find(a, x);
		int p2 = find(b, y);
		int t = (p1 - 1) * t2 + p2;
		g[t][t + 1 + t2] = min(min(g[t][t + 1] + g[t + 1][t + 1 + t2], g[t][t + t2] + g[t + t2][t + 1 + t2]), d1 / v);
		g[t + 1 + t2][t] = min(min(g[t + 1 + t2][t + 1] + g[t + 1][t], g[t + 1 + t2][t + t2] + g[t + t2][t]), d1 / v);
		g[t + 1][t + t2] = min(min(g[t][t + 1] + g[t + 1][t + 1 + t2], g[t][t + t2] + g[t + t2][t + 1 + t2]), d2 / v);
		g[t + t2][t + 1] = min(min(g[t + 1 + t2][t + 1] + g[t + 1][t], g[t + 1 + t2][t + t2] + g[t + t2][t]), d2 / v);
	}

	dijkstra();

	return 0;
}
