#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) { // 1이 들어있으면 실행되지 않음 이 함수는 선택되지 않은 것을 그냥 한개선택함
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) v = i; // distance에서 가장작은 가중치를 가진 정점을 반환함 선택된 것을 기반으로 가장작은 것을 찾음
	return (v);
}

void prim(GraphType* g, int s)
{
	int i, u, v; 

	for (u = 0; u < g->n; u++) // g->n은 그래프 정점의 개수
		distance[u] = INF;
	distance[s] = 0; //s는 0부터시작하는 것이라서 0으로 들어옴 distance[0] 에 0을 넣어줌.
	for (i = 0; i < g->n; i++) {// 정점의 개수 만큼 함수를 실행함 
		u = get_min_vertex(g->n); // 현재 distance에서 가장 작은 것을 u로 가져오고 밑에서 distance를 업데이트 한 후 다시 가장 작은 것을 선택함,  
		selected[u] = TRUE;
		if (distance[u] == INF) return; 
		printf("정점 %d 추가\n", u);
		for (v = 0; v < g->n; v++)  
 			if (g->weight[u][v] != INF)//여기 아래 라인은 리턴된 u의 정점에서의 각 거리를 distance배열에 저장함
				if (!selected[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v];
	}
}

int main(void)
{
	GraphType g = { 7, //정점의 개수
	{{ 0, 26, INF, INF, INF, 10, INF },
	{ 26,  0, 16, INF, INF, INF, 15 },
	{ INF, 16, 0, 12, INF, INF, INF },
	{ INF, INF, 12, 0, 22, INF, 18 },
	{ INF, INF, INF, 22, 0, 27, 25 },
	{ 10, INF, INF, INF, 27, 0, INF },
	{ INF, 15, INF, 18, 25, INF, 0 } }
	};
	prim(&g, 0);
	return 0;
}
