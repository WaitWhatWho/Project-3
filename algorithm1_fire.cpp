#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
 * Function: minDaysToBurn
 * ----------------------------------------
 * Simulates the spread of fire in a forest grid.
 * Uses Breadth-First Search (BFS) starting from all initially burned trees.
 *
 * forest: 2D grid representing the forest
 * returns: minimum number of days to burn all trees, or -1 if impossible
 */
int minDaysToBurn(vector<vector<int>>& forest) {
    int rows = forest.size();
    int cols = forest[0].size();

    queue<pair<int, int>> q;  // Queue to store positions of burning trees
    int healthy = 0;          // Count of healthy trees

    // Step 1: Initialize queue with all burned trees (multi-source BFS)
    // Also count total number of healthy trees
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (forest[i][j] == 2)
                q.push({i, j});     // Add burned tree to queue
            else if (forest[i][j] == 1)
                healthy++;          // Count healthy trees
        }
    }

    // If no healthy trees exist, no time is needed
    if (healthy == 0) return 0;

    // Possible directions: down, up, right, left
    vector<pair<int,int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};

    int days = 0;  // Tracks number of days required

    // Step 2: Perform BFS level by level
    while (!q.empty()) {
        int size = q.size();
        bool burnedToday = false; // Tracks if any tree burns this day

        // Process all currently burning trees (one "day")
        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();

            // Check all 4 adjacent cells
            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;

                // Check bounds and if the tree is healthy
                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && forest[nx][ny] == 1) {
                    forest[nx][ny] = 2;   // Mark tree as burned
                    q.push({nx, ny});     // Add to queue for next day
                    healthy--;            // Decrease healthy count
                    burnedToday = true;
                }
            }
        }

        // Only increment day if at least one tree burned
        if (burnedToday) days++;
    }

    // If there are still healthy trees left, return -1
    return (healthy == 0) ? days : -1;
}

int main() {
    int rows, cols;

    // Input grid size
    cout << "Enter rows and columns: ";
    cin >> rows >> cols;

    vector<vector<int>> forest(rows, vector<int>(cols));

    // Input grid values
    cout << "Enter grid values (0 = empty, 1 = healthy, 2 = burned):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> forest[i][j];
        }
    }

    // Call function and print result
    int result = minDaysToBurn(forest);
    cout << "Minimum days to burn all trees: " << result << endl;

    return 0;
}
