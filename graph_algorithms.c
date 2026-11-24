#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXV 100
#define INF (INT_MAX / 4)

typedef struct Edge {
    int to, weight;
    struct Edge *next;
} Edge;

typedef struct {
    int n;
    Edge *adj[MAXV];
} Graph;

void init_graph(Graph *g, int n) {
    g->n = n;
    for (int i=0; i<n; i++) g->adj[i] = NULL;
}

int add_directed(Graph *g, int u, int v, int w) {
    if (u<0 || u>=g->n || v<0 || v>=g->n || w<0) return 0;
    Edge *e = malloc(sizeof *e);
    if (!e) return 0;
    e->to=v; e->weight=w; e->next=g->adj[u]; g->adj[u]=e;
    return 1;
}

int add_undirected(Graph *g, int u, int v, int w) {
    return add_directed(g,u,v,w) && add_directed(g,v,u,w);
}

void free_graph(Graph *g) {
    for (int i=0; i<g->n; i++) {
        Edge *e=g->adj[i];
        while (e) { Edge *next=e->next; free(e); e=next; }
        g->adj[i]=NULL;
    }
}

void bfs(const Graph *g, int start) {
    int seen[MAXV]={0}, q[MAXV], front=0, rear=0;
    if (start<0 || start>=g->n) return;
    seen[start]=1; q[rear++]=start;
    printf("BFS depuis %d : ",start);
    while (front<rear) {
        int u=q[front++]; printf("%d ",u);
        for (Edge *e=g->adj[u]; e; e=e->next)
            if (!seen[e->to]) { seen[e->to]=1; q[rear++]=e->to; }
    }
    puts("");
}

void dfs_visit(const Graph *g, int u, int seen[]) {
    seen[u]=1; printf("%d ",u);
    for (Edge *e=g->adj[u]; e; e=e->next)
        if (!seen[e->to]) dfs_visit(g,e->to,seen);
}

void dfs(const Graph *g, int start) {
    int seen[MAXV]={0};
    if (start<0 || start>=g->n) return;
    printf("DFS depuis %d : ",start); dfs_visit(g,start,seen); puts("");
}

void print_path(int parent[], int v) {
    if (v==-1) return;
    print_path(parent,parent[v]); printf("%d ",v);
}

/* Dijkstra avec sélection linéaire : O(V^2 + E), poids non négatifs. */
void dijkstra(const Graph *g, int start) {
    int dist[MAXV], parent[MAXV], seen[MAXV]={0};
    for (int i=0; i<g->n; i++) { dist[i]=INF; parent[i]=-1; }
    dist[start]=0;
    for (int step=0; step<g->n; step++) {
        int u=-1, best=INF;
        for (int i=0; i<g->n; i++)
            if (!seen[i] && dist[i]<best) { best=dist[i]; u=i; }
        if (u==-1) break;
        seen[u]=1;
        for (Edge *e=g->adj[u]; e; e=e->next) {
            int v=e->to;
            if (!seen[v] && dist[u]+e->weight<dist[v]) {
                dist[v]=dist[u]+e->weight; parent[v]=u;
            }
        }
    }
    puts("Plus courts chemins depuis la source :");
    for (int i=0; i<g->n; i++) {
        if (dist[i]==INF) printf("Vers %d : inaccessible\n",i);
        else {
            printf("Vers %d : distance %d, chemin ",i,dist[i]);
            print_path(parent,i); puts("");
        }
    }
}

int main(void) {
    Graph g; init_graph(&g,6);
    int ok =
        add_undirected(&g,0,1,7) && add_undirected(&g,0,2,9) &&
        add_undirected(&g,0,5,14) && add_undirected(&g,1,2,10) &&
        add_undirected(&g,1,3,15) && add_undirected(&g,2,3,11) &&
        add_undirected(&g,2,5,2) && add_undirected(&g,3,4,6) &&
        add_undirected(&g,4,5,9);
    if (!ok) { fprintf(stderr,"Erreur de construction/allocation.\n"); free_graph(&g); return EXIT_FAILURE; }
    puts("Graphe non orienté pondéré à 6 sommets.");
    bfs(&g,0); dfs(&g,0); dijkstra(&g,0);
    free_graph(&g);
    return EXIT_SUCCESS;
}
