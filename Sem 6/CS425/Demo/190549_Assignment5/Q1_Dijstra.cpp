/*
Instructions:
compile using : "g++ Q1_Dijstra.cpp -0 Dijstra.out"
run the binary file : "./Dijstra.out"
Input:
Give two characters as input

*/


#include<bits/stdc++.h>

using namespace std;


void Dijkstra_Algorithm(vector<vector<int>> &G, int s, int d){
    int g_size = G.size();
    vector<bool> visited(g_size,0);
    vector<int> cost(g_size,INT_MAX);
    vector<int> parent(g_size);
    cost[s] = 0;
    for(int c = 0; c<g_size-1; c++){
        int min_distance = INT_MAX, node;
        for(int i = 0;i<g_size;i++){
            if(visited[i]==0 && cost[i]<=min_distance) {
                node = i;
                min_distance = cost[i]; 
            }
        }
        visited[node] = 1;
        for(int i = 0;i<g_size;i++){
            if(visited[i]==0 && G[node][i]!= 0 && cost[node]!=INT_MAX && (cost[i]>cost[node] + G[node][i])){
                cost[i] = cost[node] + G[node][i];
                parent[i] = node;
            }
        }
        
    }
    // for(int i = 0;i<g_size;i++) cout<< cost[i]<<" "<<endl;
    if(cost[d]==INT_MAX) cout<< "No Path Exist";
    else{
        cout<< "Cost is: "<< cost[d] << endl;
        cout << "Path is :"  << char('A'+d);
        while(d!=s && cost[d]!=INT_MAX) {
            cout << " <-- " << char('A' + parent[d]);
            d = parent[d];
            }
            cout << endl;
    }

    return;
}

void insert_node(vector<vector<int>> &G, int u, int v, int d){
    G[u][v] = d;
    G[v][u] = d;

}

int main(){
    vector<vector<int>> graph(11,vector<int>(11,0));
//A= 0, B =1 C = 2 D = 3 E = 4 F = 5 , G = 6, H = 7, I = 8, J = 9, k = 10
    insert_node(graph,0,1,1);
    insert_node(graph,0,4,1);
    insert_node(graph,1,2,1);
    insert_node(graph,2,6,1);
    insert_node(graph,2,5,3);
    insert_node(graph,2,9,4);
    insert_node(graph,3,4,5);
    insert_node(graph,3,7,1);
    insert_node(graph,3,10,1);
    insert_node(graph,3,9,2);
    insert_node(graph,4,6,1);
    insert_node(graph,5,10,1);
    insert_node(graph,6,7,1);
    char s,d;
    cout << "Start Vertex: ";
    cin >> s;
    cout << "End Vertex: ";
    cin >> d;

    Dijkstra_Algorithm(graph,s-'A',d-'A');

    return 0;
}