#include<bits/stdc++.h>

using namespace std;
struct Edge {
    int src, dest, weight;
};
 
struct Graph {
    int V, E;
    struct Edge* edge;
};

void Bellman_Algorithm(struct Graph* G, int s, int d){
    int vertices = G->V;
    int edges = G->E;
    vector<int> cost(vertices,INT_MAX);
    vector<int> parent(vertices);
    cost[s] = 0;
    for(int c = 0; c<vertices-1; c++){
        for(int i = 0;i<edges;i++){
            int u = G->edge[i].src, v = G->edge[i].dest, w = G->edge[i].weight;
            if(cost[u]!=INT_MAX && (cost[v]>cost[u]+w)){
                cost[v] = cost[u]+w;
                parent[v] = u;
            }
        }
        
    }
    for(int i = 0;i<edges;i++){
            int u = G->edge[i].src, v = G->edge[i].dest, w = G->edge[i].weight;
            if(cost[u]!=INT_MAX && (cost[v]>cost[u]+w)){
                cout<< "Graph Contains A Negative Cycle"<<endl;
            }
        }
    // for(int i = 0;i<g_size;i++) cout<< cost[i]<<" "<<endl;
    if(cost[d]==INT_MAX) cout<< "No Path Exist";
    else{
        cout<< "Cost is: "<< cost[d] << endl;
        cout << char('A'+d) << endl;
        while(d!=s && cost[d]!=INT_MAX) {
            cout << char('A' + parent[d])<<endl;
            d = parent[d];
            }
    }

    return;
}

void insert_node(struct Graph *G, int u, int v, int d, int &count){
    G->edge[count].src = u;
    G->edge[count].dest = v;
    G->edge[count].weight = d;
    count++;
    G->edge[count].src = v;
    G->edge[count].dest = u;
    G->edge[count].weight = d;
    count++;

}

int main(){
    struct Graph* graph = new Graph;
    graph->V = 11;
    graph->E = 24;
    graph->edge = new Edge[24];
    int count = 0;
//A= 0, B =1 C = 2 D = 3 E = 4 F = 5 , G = 6, H = 7, I = 8, J = 9, k = 10
    insert_node(graph,0,1,1,count);
    insert_node(graph,0,4,1,count);
    insert_node(graph,1,2,1,count);
    insert_node(graph,2,6,1,count);
    insert_node(graph,2,5,3,count);
    insert_node(graph,2,9,4,count);
    insert_node(graph,3,4,5,count);
    insert_node(graph,3,7,1,count);
    insert_node(graph,3,10,1,count);
    insert_node(graph,3,9,2,count);
    insert_node(graph,4,6,1,count);
    insert_node(graph,5,10,1,count);
    char s,d;
    cin >> s >> d;

    Bellman_Algorithm(graph,s-'A',d-'A');

    return 0;
}