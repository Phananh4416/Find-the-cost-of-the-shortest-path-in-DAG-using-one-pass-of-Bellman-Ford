#include <stdio.h>
#include <stdbool.h>

#define INF 1000000 // Giá trị đại diện cho "vô cực"

// Cấu trúc để lưu trữ thông tin một cạnh của đồ thị
struct Edge {
    int src, dest, weight;
};

// Hàm thực hiện duyệt DFS và ghi nhận thời gian kết thúc của từng đỉnh
void DFS(int v, int n, struct Edge adjList[][n], int adjCount[], bool discovered[], int departure[], int *time) {
    // Đánh dấu đỉnh hiện tại là đã được khám phá
    discovered[v] = true;

    // Duyệt qua tất cả các đỉnh kề của đỉnh hiện tại
    for (int i = 0; i < adjCount[v]; i++) {
        int u = adjList[v][i].dest;
        if (!discovered[u]) {
            DFS(u, n, adjList, adjCount, discovered, departure, time);
        }
    }

    // Ghi nhận thời gian kết thúc của đỉnh v
    departure[(*time)++] = v;
}

// Hàm tìm khoảng cách ngắn nhất từ một đỉnh nguồn đến các đỉnh khác trong DAG
void findShortestDistance(int n, struct Edge edges[], int edgeCount, int source) {
    // Danh sách kề (adjacency list) để lưu các cạnh
    struct Edge adjList[n][n];
    int adjCount[n];

    // Khởi tạo danh sách kề
    for (int i = 0; i < n; i++) {
        adjCount[i] = 0;
    }

    // Thêm các cạnh vào danh sách kề
    for (int i = 0; i < edgeCount; i++) {
        struct Edge edge = edges[i];
        adjList[edge.src][adjCount[edge.src]++] = edge;
    }

    // Mảng lưu thời gian kết thúc của các đỉnh sau DFS
    int departure[n];
    bool discovered[n];

    // Khởi tạo mảng discovered và thời gian
    for (int i = 0; i < n; i++) {
        discovered[i] = false;
    }

    int time = 0;

    // Thực hiện DFS trên tất cả các đỉnh chưa được khám phá
    for (int i = 0; i < n; i++) {
        if (!discovered[i]) {
            DFS(i, n, adjList, adjCount, discovered, departure, &time);
        }
    }

    // Mảng lưu chi phí từ nguồn đến các đỉnh khác
    int cost[n];
    for (int i = 0; i < n; i++) {
        cost[i] = INF; // Khởi tạo khoảng cách ban đầu là vô cực
    }
    cost[source] = 0; // Khoảng cách đến chính nó là 0

    // Xử lý các đỉnh theo thứ tự topo (thứ tự ngược của thời gian kết thúc)
    for (int i = n - 1; i >= 0; i--) {
        int v = departure[i];

        // Thư giãn các cạnh của đỉnh v
        for (int j = 0; j < adjCount[v]; j++) {
            int u = adjList[v][j].dest;
            int w = adjList[v][j].weight;

            // Cập nhật khoảng cách nếu tìm được đường ngắn hơn
            if (cost[v] != INF && cost[v] + w < cost[u]) {
                cost[u] = cost[v] + w;
            }
        }
    }

    // In kết quả
    for (int i = 0; i < n; i++) {
        if (cost[i] == INF) {
            printf("dist(%d, %d) = INF\n", source, i);
        } else {
            printf("dist(%d, %d) = %d\n", source, i, cost[i]);
        }
    }
}

int main() {
    // Các cạnh của đồ thị
    struct Edge edges[] = {
        {0, 6, 2}, {1, 2, -4}, {1, 4, 1}, {1, 6, 8}, {3, 0, 3}, {3, 4, 5},
        {5, 1, 2}, {7, 0, 6}, {7, 1, -1}, {7, 3, 4}, {7, 5, -4}
    };

    // Tổng số đỉnh và cạnh
    int n = 8; // Số đỉnh
    int edgeCount = sizeof(edges) / sizeof(edges[0]);

    // Đỉnh nguồn
    int source = 7;

    // Tìm khoảng cách ngắn nhất từ đỉnh nguồn
    findShortestDistance(n, edges, edgeCount, source);

    return 0;
}