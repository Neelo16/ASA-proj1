#include <stdio.h>
#include <stdlib.h>

#define MIN(A, B) (A < B ? A : B)
#define MAX(A, B) (A > B ? A : B)

typedef struct edge {
		int v;
		struct edge *next;
} Edge;

typedef struct vertex {
		Edge *first_edge;
		int depth;
		int low;
		struct vertex *parent;
} Vertex;

typedef struct {
		int m, M;
		int fundamental_count;
} fundamental_data;

void clear_graph(Vertex *graph, int size) {
		int i;
		for (i = 0; i < size; i++) {
				Edge *edge = graph[i].first_edge;
				while (edge != NULL) {
						Edge *aux = edge->next;
						free(edge);
						edge = aux;
				}
		}
		free(graph);
}

void find_fundamentals(Vertex *graph, int i, fundamental_data *data) {
		static int time = 0;
		int child_count = 0;
		int is_fundamental = 0;
		Edge *edge = NULL;
		Vertex *u = graph + i;
		u->depth = u->low = time++;
		for (edge = u->first_edge; edge != NULL; edge = edge->next) {
				Vertex *v = graph + edge->v;
				if (v->depth == -1) {
						v->parent = u;
						child_count++;
						find_fundamentals(graph, edge->v, data);
						if (v->low >= u->depth)
								is_fundamental = 1;
						u->low = MIN(u->low, v->low);
				}
				else if (v != u->parent)
						u->low = MIN(u->low, v->depth);
		}
		if ((u->parent != NULL && is_fundamental) ||
			(u->parent == NULL && child_count > 1)) {
				data->fundamental_count++;
				data->m = MIN(data->m, i);
				data->M = MAX(data->M, i);
		}
}

int main(int argc, char const *argv[]) {
		Vertex *graph = NULL;
		int vertices = 0, edges = 0;
		int i = 0;
		fundamental_data data;
		scanf("%d %d", &vertices, &edges);
		graph = malloc(sizeof(Vertex)*vertices);

		data.m = vertices;
		data.M = -1;
		data.fundamental_count = 0;

		for (i = 0; i < vertices; i++) {
				graph[i].parent = NULL;
				graph[i].first_edge = NULL;
				graph[i].depth = graph[i].low = -1;
		}

		while (edges--) {
				int u = 0, v = 0;
				Edge *edge = malloc(sizeof(Edge));
				scanf("%d %d", &u, &v);
				edge->v = v-1;
				edge->next = graph[u-1].first_edge;
				graph[u-1].first_edge = edge;
				edge = malloc(sizeof(Edge));
				edge->v = u-1;
				edge->next = graph[v-1].first_edge;
				graph[v-1].first_edge = edge;
		}
		find_fundamentals(graph, 0, &data);
		if (!data.fundamental_count)
				puts("0\n-1 -1");
		else
				printf("%d\n%d %d\n", data.fundamental_count, data.m + 1, data.M + 1);
		clear_graph(graph, vertices);
		return 0;
}
