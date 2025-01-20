# Find-the-cost-of-the-shortest-path-in-DAG-using-one-pass-of-Bellman-Ford
BTL cho CTDL và GT
# Tìm đường đi ngắn nhất trong DAG bằng một lần duyệt Bellman–Ford

Giải thuật này được áp dụng cho đồ thị có hướng không chu trình (DAG) với mục tiêu tìm **chi phí đường đi ngắn nhất từ một đỉnh nguồn đến tất cả các đỉnh khác** trong đồ thị. Đặc điểm của đồ thị DAG là **không chứa chu trình**, điều này cho phép ta xử lý các đỉnh theo thứ tự tuyến tính (topological order) và thực hiện các bước thư giãn cạnh (edge relaxation) một cách hiệu quả.

## Ý tưởng của giải thuật

Giải thuật dựa trên hai bước chính:

1. **Sắp xếp topo (Topological Sort):**  
   Sắp xếp các đỉnh của đồ thị theo thứ tự topo để đảm bảo rằng khi xử lý một đỉnh `u`, tất cả các đỉnh `v` được nối từ `u` chỉ được xử lý sau `u`.

2. **Thư giãn cạnh (Edge Relaxation):**  
   Với mỗi đỉnh `u` trong thứ tự topo, xét tất cả các cạnh `(u, v)` nối từ `u` đến `v`. Nếu đường đi từ đỉnh nguồn qua `u` đến `v` có chi phí thấp hơn đường đi hiện tại đến `v`, ta cập nhật chi phí cho `v`.

---

## Chi tiết các bước của giải thuật

### Đầu vào (Input)

1. **Đồ thị DAG**: \( G = (V, E) \), gồm:
   - Tập đỉnh \( V \) (vertices).  
   - Tập cạnh \( E \) (edges), mỗi cạnh \( (u, v) \) có trọng số \( w(u, v) \).

2. **Đỉnh nguồn (source vertex)**: \( src \).

### Đầu ra (Output)

- Mảng `distance[]`, trong đó `distance[v]` là chi phí đường đi ngắn nhất từ \( src \) đến đỉnh \( v \).  
- Nếu \( v \) không thể đến được từ \( src \), thì `distance[v] = ∞` (vô cực).

---

### Bước 1: Sắp xếp topo các đỉnh trong DAG

**Mục đích:**  
Sắp xếp tất cả các đỉnh trong DAG thành thứ tự tuyến tính (topological order) sao cho mọi cạnh \( (u, v) \) đều thỏa mãn \( u \) xuất hiện trước \( v \).

**Cách thực hiện:**

1. **Dùng thuật toán DFS:**  
   - Thực hiện tìm kiếm theo chiều sâu (DFS) trên toàn bộ đồ thị.  
   - Khi kết thúc việc xử lý một đỉnh, thêm đỉnh đó vào danh sách topo.  
   - Kết quả là danh sách các đỉnh theo thứ tự ngược (reverse order).

2. **Dùng thuật toán Kahn’s:**  
   - Tính bậc vào (in-degree) của tất cả các đỉnh.  
   - Lần lượt đưa các đỉnh có bậc vào bằng 0 vào hàng đợi và xóa chúng khỏi đồ thị, cập nhật bậc vào của các đỉnh kề.

**Độ phức tạp:** \( O(V + E) \).

Kết quả của bước này là danh sách topo `topoOrder`.

---

### Bước 2: Khởi tạo mảng khoảng cách

1. Khởi tạo mảng `distance[]`:  
   - Với mọi đỉnh \( v \), gán `distance[v] = ∞`.  
   - Gán `distance[src] = 0`, vì chi phí từ nguồn đến chính nó bằng 0.

2. Biến `distance[]` này sẽ được cập nhật trong bước thư giãn cạnh.

---

### Bước 3: Duyệt qua các đỉnh theo thứ tự topo và thư giãn cạnh

**Thư giãn cạnh là gì?**  
Thư giãn cạnh là quá trình kiểm tra xem có thể giảm chi phí đi đến một đỉnh thông qua một đường đi khác ngắn hơn hay không. Nếu có, ta cập nhật chi phí ngắn nhất cho đỉnh đó.

- Với mỗi đỉnh `u` trong `topoOrder`:
  - Với mỗi cạnh `(u, v)` nối từ `u` đến `v`, nếu:
    \[
    distance[u] + w(u, v) < distance[v]
    \]
    thì:
    \[
    distance[v] = distance[u] + w(u, v)
    \]

**Độ phức tạp:**  
Duyệt qua các cạnh mất \( O(E) \).

---

### Bước 4: Trả về kết quả

- Sau khi duyệt xong, `distance[]` chứa chi phí đường đi ngắn nhất từ `src` đến tất cả các đỉnh.  
- Đỉnh nào không thể đến được từ `src` sẽ có giá trị `∞`.

---

## Ví dụ minh họa

### Đồ thị DAG:

- Tập đỉnh: \( V = \{0, 1, 2, 3, 4, 5, 6, 7\} \).  
- Tập cạnh (với trọng số):  
(7, 5, -4), (7, 3, 4), (7, 0, 6), (5, 1, -2), (5, 2, -1), (1, 4, 1), (1, 6, 8), (1, 2, -4)


### Thực hiện:

1. **Sắp xếp topo:**  
 - Kết quả topo: `topoOrder = [7, 5, 3, 0, 1, 2, 4, 6]`.

2. **Khởi tạo mảng `distance[]`:**  
distance = [∞, ∞, ∞, ∞, ∞, ∞, ∞, 0]


3. **Thư giãn cạnh:**  
- Xét đỉnh `7`:  
  ```
  distance[5] = min(∞, 0 + (-4)) = -4
  distance[3] = min(∞, 0 + 4) = 4
  distance[0] = min(∞, 0 + 6) = 6
  ```
- Xét đỉnh `5`:  
  ```
  distance[1] = min(∞, -4 + (-2)) = -6
  distance[2] = min(∞, -4 + (-1)) = -5
  ```
- Xét đỉnh `1`:  
  ```
  distance[4] = min(∞, -6 + 1) = -5
  distance[6] = min(∞, -6 + 8) = 2
  distance[2] = min(-5, -6 + (-4)) = -10
  ```

4. **Kết quả cuối cùng:**  
distance = [6, -6, -10, 4, -5, -4, 2, 0]


---

## Độ phức tạp

- **Sắp xếp topo:** \( O(V + E) \).  
- **Thư giãn cạnh:** \( O(E) \).  

Tổng độ phức tạp:  
\[
O(V + E)
\]

---

## Kết luận

Giải thuật tìm đường đi ngắn nhất trong DAG sử dụng sắp xếp topo và thư giãn cạnh là cách tiếp cận nhanh và hiệu quả. Đặc tính không có chu trình của DAG giúp đảm bảo tính đúng đắn và đơn giản hóa việc xử lý.


