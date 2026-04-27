#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

/*
 * Function: cheapestRoute
 * ----------------------------------------
 * Finds the minimum cost to travel from src to dst
 * with at most k stops using a BFS-based approach.
 *
 * n: number of nodes (distribution centers)
 * routes: list of edges (from, to, cost)
 * src: starting node
 * dst: destination node
 * k: maximum number of stops allowed
 *
 * returns: minimum cost or -1 if no valid route exists
 */
int cheapestRoute(int n, vector<vector<int>>& routes, int src, int dst, int k) {

    // Step 1: Build adjacency list for graph representation
    vector<vector<pair<int,int>>> graph(n);

    for (auto& r : routes) {
        int from = r[0];
        int to = r[1];
        int cost = r[2];
        graph[from].push_back({to, cost});
    }

    // Queue stores: (current node, total cost so far, stops used)
    queue<tuple<int,int,int>> q;
    q.push({src, 0, 0});

    // Track minimum cost to reach each node
    vector<int> minCost(n, INT_MAX);
    minCost[src] = 0;

    // Step 2: BFS traversal with stop constraint
    while (!q.empty()) {
        auto [node, cost, stops] = q.front();
        q.pop();

        // If stops exceed allowed limit, skip this path
        if (stops > k) continue;

        // Explore neighbors
        for (auto& [neighbor, price] : graph[node]) {
            int newCost = cost + price;

            // Only continue if we found a cheaper path
            if (newCost < minCost[neighbor]) {
                minCost[neighbor] = newCost;
                q.push({neighbor, newCost, stops + 1});
            }
        }
    }

    // If destination is unreachable, return -1
    return (minCost[dst] == INT_MAX) ? -1 : minCost[dst];
}

int main() {
    int n, m;

    // Input number of nodes and routes
    cout << "Enter number of distribution centers (nodes): ";
    cin >> n;

    cout << "Enter number of routes: ";
    cin >> m;

    vector<vector<int>> routes(m, vector<int>(3));

    // Input routes
    cout << "Enter routes (from to cost):\n";
    for (int i = 0; i < m; i++) {
        cin >> routes[i][0] >> routes[i][1] >> routes[i][2];
    }

    int src, dst, k;

    // Input source, destination, and max stops
    cout << "Enter source, destination, and max stops (k): ";
    cin >> src >> dst >> k;

    // Call function and print result
    int result = cheapestRoute(n, routes, src, dst, k);
    cout << "Cheapest route cost: " << result << endl;

    return 0;
}
