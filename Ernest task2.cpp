#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

// ==========================================
// Memory Stack Simulation
// ==========================================
void calculateWeight() {
    cout << "  [Stack Top] Executing calculateWeight()... done. Popping." << endl;
}

void loadTruck() {
    cout << " [Stack Mid] Executing loadTruck()... calling calculateWeight()." << endl;
    calculateWeight();
    cout << " [Stack Mid] loadTruck() done. Popping." << endl;
}

void simulateCallStack() {
    cout << "--- CALL STACK SIMULATION ---" << endl;
    cout << "[Stack Base] main() started... calling loadTruck()." << endl;
    loadTruck();
    cout << "[Stack Base] main() done." << endl;
    cout << "-----------------------------\n" << endl;
}

// ==========================================
//  Dijkstra's Algorithm for Truck Routing
// ==========================================
#define V 5 // Number of delivery hubs (Nodes A, B, C, D, E)

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    cout << " -> Hub " << j;
}

void dijkstra(int graph[V][V], int src, int dest) {
    int dist[V];     
    bool sptSet[V];  
    int parent[V];   

    for (int i = 0; i < V; i++) {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    cout << "--- TRUCK ROUTING ALGORITHM (DIJKSTRA) ---" << endl;
    cout << "Shortest Path from Hub " << src << " to Hub " << dest << ":" << endl;
    cout << "Total Distance: " << dist[dest] << " km" << endl;
    cout << "Route: Hub " << src;
    printPath(parent, dest);
    cout << "\n------------------------------------------\n" << endl;
}

// ==========================================
// Main Execution File
// ==========================================
int main() {
    // 1. Run Stack Simulation
    simulateCallStack();

    // 2. Run Dijkstra's Routing
    // Adjacency Matrix representing distances between 5 Hubs (2 to 0)
    // 0 means no direct road exists between those two hubs.
    int logisticsGraph[V][V] = {
        { 0, 10,  0, 30, 100 },
        { 10, 0, 50,  0,  0  },
        { 0, 50,  0, 20, 10  },
        { 30, 0, 20,  0, 60  },
        { 100,0, 10, 60,  0  }
    };

    // TODO: Change the source (src) and destination (dest) hubs for each group member!
    int srcHub = 2;  // Start at Hub 2
    int destHub = 0; // Deliver to Hub 0
    
    dijkstra(logisticsGraph, srcHub, destHub);

    return 0;
}
