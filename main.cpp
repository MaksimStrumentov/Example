#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

struct edge{
    double l;
    int s;
    int e;
};

const double INF = 1000000000;
int COL = 1;
vector < vector <double> > data (1000, vector <double> (30, 0));
int n, m, d;
double length(int i, int j, int n);
void input();
void get_graph();
double ArrLen[1000][1000];
void output();
void get_ostov();
vector <bool> used (1000);
vector <int> min_e(1000, INF);
vector <int> sel_e(1000, -1);
vector < edge > result (1000);
void delete_edges();
vector < vector <int> > ostov(1000, vector<int> (0, 0));
bool comparator(edge a, edge b);
void dfs(int v);
void find_cl();
vector <int> comp;


int main()
{
    freopen("input.txt", "r", stdin);

    input();
    get_graph();
    get_ostov();
    delete_edges();
    find_cl();

    //output();
    return 0;
}

void input()
{
    scanf("%d%d", &n, &d);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            scanf("%lf", &data[i][j]);
    scanf("%d", &m);
    return;
}

double length(int i, int j, int d)
{
    double ans = .0;
    if (i != j)
        for (int tmp = 0; tmp < d; tmp++)
        {
            ans += (data[i][tmp] - data[j][tmp]) * (data[i][tmp] - data[j][tmp]);
        }
    else
        ans = INF + .0;
    //cout << sqrt(ans) << ' ';
    return sqrt(ans);
}

void get_graph()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ArrLen[i][j] = length(i, j, d);
        }
    }
    return;
}

void output()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (int)ostov[i].size(); j++)
        {
            printf("%d ", ostov[i][j]);
        }
        printf("\n");
    }
    return;
}

void get_ostov()
{
    min_e[0] = 0;
    for (int i = 0; i < n; i++)
    {
        int v = -1;
        for (int j = 0; j < n; j++)
            if(!used[j] && (v == -1 || (min_e[j] < min_e[v])))
                v = j;
        if(min_e[v] == INF)
        {
            cout << "error";
            exit(0);
        }

        used[v] = 1;
        if (sel_e[v] != -1)
        {
            result[v].l = ArrLen[sel_e[v]][v];
            result[v].s = v;
            result[v].e = sel_e[v];
            //cout << v << ' ' << sel_e[v] << endl;
        }

        for (int to = 0; to < n; to++)
        {
            if(ArrLen[v][to] < min_e[to])
            {
                min_e[to] = ArrLen[v][to];
                sel_e[to] = v;
            }
        }

    }
    return;
}

bool comparator(edge a, edge b)
{
    if(a.l >= b.l)
        return 0;
    else
        return 1;
}

void delete_edges()
{
    for (int i = n; i < 1000; i++)
        result[i].l = INF;
    sort(result.begin(), result.end(), comparator);
    for (int i = 1; i < n - m + 1; i++)
    {
        ostov[result[i].s].push_back(result[i].e);
        ostov[result[i].e].push_back(result[i].s);
    }
    for (int i = 0; i < 1000; i++)
        used[i] = 0;
}

void dfs(int v)
{
    used[v] = 1;
    comp.push_back(v);
    for (size_t i = 0; i < ostov[v].size(); i++)
    {
        int to = ostov[v][i];
        if(!used[to])
            dfs(to);
    }
}

void find_cl()
{
    for(int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < n; i++)
        if(!used[i])
        {
            comp.clear();
            dfs(i);
            printf("Claster %d is: \n", COL);
            sort(comp.begin(), comp.end());
            for (size_t j = 0; j < comp.size(); j++)
                printf("%d ", comp[j] + 1);
            printf("\n");
            COL++;
        }
}
