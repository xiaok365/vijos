#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int left, up;
};

int max(int a, int b) {
    return a > b ? a : b;
}


int min(int a, int b, int c) {
    return a < b ? a < c ? a : c : b < c ? b : c;
}

int main() {

    freopen("../a.in", "r", stdin);

    vector<vector<int>> f(1000, vector<int>(1000, 0));
    vector<vector<int>> map(1000, vector<int>(1000, 0));
    Node initNode{0, 0};
    vector<vector<Node>> node(1000, vector<Node>(1000, initNode));

    int n, m, i, j, maxSquare = 0;

    cin >> n >> m;
    //input
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            cin >> map[i][j];

    //init left
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) {
            if (j == 0) {
                if (map[i][j] == 1) {
                    node[i][j].left = 1;
                } else { node[i][j].left = 0; }
            } else {
                if (map[i][j] == 1) {
                    node[i][j].left = node[i][j - 1].left + 1;
                } else {
                    node[i][j].left = 0;
                }
            }
        }

    //init up
    for (j = 0; j < m; j++)
        for (i = 0; i < n; i++) {
            if (i == 0) {
                if (map[i][j] == 1) {
                    node[i][j].up = 1;
                } else { node[i][j].up = 0; }
            } else {
                if (map[i][j] == 1) {
                    node[i][j].up = node[i - 1][j].up + 1;
                } else {
                    node[i][j].up = 0;
                }
            }
        }

    //dynamic programming
    for (i = 0; i < n; i++) {
        if (map[i][0] == 1) {
            f[i][0] = 1;
            maxSquare = 1;
        } else f[i][0] = 0;
    }

    for (j = 1; j < m; j++) {
        if (map[0][j] == 1) {
            f[0][j] = 1;
            maxSquare = 1;
        } else f[0][j] = 0;
    }

    for (i = 1; i < n; i++)
        for (j = 1; j < m; j++) {
            f[i][j] = min(node[i][j].left, node[i][j].up, f[i - 1][j - 1] + 1);
            maxSquare = max(f[i][j], maxSquare);
        }

    cout << maxSquare;
    return 0;
}