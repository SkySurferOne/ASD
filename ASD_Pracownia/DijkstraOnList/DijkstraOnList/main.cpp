/*
	Solution for https://www.hackerrank.com/challenges/dijkstrashortreach
*/
#include <iostream>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <string>
using namespace std;

struct edge {
	int v;
	int w;
	edge * next;
};

struct vertex {
	int d;
	int parent;
	struct edge * edge;
	bool visited;
};

struct vertexId {
	int id;
	int d;
};

struct compare {
	bool operator()(const vertexId &l, const vertexId &r) {
		return l.d > r.d;
	}
};

void dijkstraOnList(vertex * graph, int n, int start) {
	start--;
	if (start < 0) return;

	for (int i = 0; i < n; i++) {
		graph[i].d = INT16_MAX;
		graph[i].parent = -1;
		graph[i].visited = false;
	}
	graph[start].d = 0;

	priority_queue<vertexId, vector< vertexId >, compare> queue;
	vertexId s = { start, graph[start].d };
	queue.push(s);

	while (!queue.empty()) {
		int u = queue.top().id; queue.pop();
		if (graph[u].visited) continue;
		graph[u].visited = true;

		struct edge * edge = graph[u].edge;
		while (edge != NULL) {
			int v = edge->v;
			if (graph[u].d + edge->w < graph[v].d) {
				graph[v].d = graph[u].d + edge->w;
				graph[v].parent = u;
				vertexId vid = { v, graph[v].d };
				queue.push(vid);
			}
			edge = edge->next;
		}
	}
}

void addEdge(int fromX, int toY, int r, edge ** last, vertex * ngraph) {
	if (ngraph[fromX].edge == NULL) {
		edge * ne = last[fromX] = new edge;
		ne->v = toY;
		ne->w = r;
		ne->next = ngraph[fromX].edge;
		ngraph[fromX].edge = ne;

	} else {
		edge * ne = new edge;
		ne->v = toY;
		ne->w = r;
		ne->next = NULL;
		last[fromX]->next = ne;
		last[fromX] = ne;
	}
}

vertex * makeGraphList(int v_num, int e_num) {
	vertex * ngraph = new vertex[v_num];
	for (int i = 0; i < v_num; i++)
		ngraph[i].edge = NULL;

	edge ** last = new edge *[v_num];
	int x, y, r;
	for (int i = 0; i < e_num; i++) {
		cin >> x >> y >> r;
		addEdge(x - 1, y - 1, r, last, ngraph);
		addEdge(y - 1, x - 1, r, last, ngraph);
	}

	delete[] last;

	return ngraph;
}

string genSmallestPathsDist(vertex * ngraph, int n, int start) {
	string str = "";
	for (int i = 0; i < n; i++) {
		if (i != start - 1) {
			if (ngraph[i].d == INT16_MAX)
				str += "-1 ";
			else
				str += to_string(ngraph[i].d) + " ";
		}
	}
	return str.substr(0, str.length() - 1);
}

int main() {
	int T, N, M, S;

	cin >> T;

	string * outputs = new string[T];
	for (int i = 0; i < T; i++) {
		cin >> N >> M;
		vertex * ngraph = makeGraphList(N, M);
		cin >> S;
		dijkstraOnList(ngraph, N, S);
		outputs[i] = genSmallestPathsDist(ngraph, N, S);
		delete[] ngraph;
	}

	for (int i = 0; i < T; i++)
		cout << outputs[i].c_str() << endl;

	return 0;
}