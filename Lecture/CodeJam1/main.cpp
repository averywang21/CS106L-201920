#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <stdlib.h>

using namespace std;


bool searchH(size_t r, size_t c, size_t remain,
             vector<vector<int>>& grid, vector<pair<int, int>>& path) {
    if (remain == 0) {
        // path.push_back(make_pair(r, c));
        return true;
    }
    if (grid[r][c] == 1) return false;
    grid[r][c] = 1;
    path.push_back(make_pair(r, c));
    for (size_t nextR = 0; nextR < grid.size(); nextR++) {
        for (size_t nextC = 0; nextC < grid[0].size(); nextC++) {
            if (nextR == r || nextC == c ||
                    nextR - nextC == r - c || nextR + nextC == r + c) continue;

            if (searchH(nextR, nextC, remain-1, grid, path)) return true;
        }
    }
    path.pop_back();
    grid[r][c] = 0;
    return false;
}
vector<pair<int, int>> search(size_t r, size_t c) {
    vector<vector<int>> grid;
    for (size_t i = 0; i < r; i++) {
        grid.emplace_back(c);
    }

    for (int i = 0; i < 15; i++) {
        size_t startR = rand() % r;
        size_t startC = rand() % c;
        vector<pair<int, int>> path;
        if (searchH(startR, startC, r*c, grid, path)) return path;
    }

    return {};
}

int main() {
    int cases;
    cin >> cases;
    vector<pair<int, int>> tests;
    for (int i = 1; i <= cases; i++) {
        size_t r, c;
        cin >> r >> c;
        tests.push_back(make_pair(r, c));
    }

    for (int i = 1; i <= cases; i++) {
        auto curr = tests[i-1];
        cout << "Case #" << i << ": ";
        vector<pair<int, int>> result = search(curr.first, curr.second);
        if (result.empty()) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << "POSSIBLE" << endl;
            for (pair<int, int> loc : result) {
                cout << loc.first+1 << " " << loc.second+1 << endl;
            }
        }
    }
}


