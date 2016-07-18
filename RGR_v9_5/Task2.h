#include "Graph.h"
#include "orderlist.h"
#include <stack>
#include <queue>
#include <limits.h>
#define INF INT_MAX



template<class DVertex>
class compareWeight{
public:
	bool operator()(pair<int,DVertex*> p1, pair<int,DVertex*> p2){
		return p1.first > p2.first;
	}
};

template<class DVertex, class DEdge>
class Task2{
	Graph<DVertex,DEdge> *initial_graph;
	Graph<DVertex,DEdge> *current_graph;
	int max_short_path;
	int shortest_path_length;
	DVertex *u,*v;
	void solve(DVertex *a);
	void init();
	map<DVertex*,int> indexes;
	vector<int> dist;
	vector<bool> visited;
	vector<stack<DVertex*>> path;
	map<DEdge*, list<DVertex*>> max_shortest_paths_vertex;
	list<DVertex*> short_path_vertex;
	list<DEdge*> *max_short_path_edges;
	void Restart(DVertex *u, DVertex *v);
	list<DVertex*> stack_path_to_list_vertex_path(stack<DVertex*>&);
public:
	Task2(Graph<DVertex,DEdge> *g, DVertex* u, DVertex *v);
	Task2(const Task2 &obj);
	~Task2();
	void Set(Graph<DVertex,DEdge> *g);
	void SetU(DVertex *u);
	void SetV(DVertex *v);
	void Restart();
	int GetMaxShortestPathLength();
	map<DEdge*,list<DVertex*>> GetMaxShortestPath();
	list<DEdge*>* Result();
	list<DVertex*> GetShortestPath();
	int GetShortestPathLength();
};

template<class DVertex, class DEdge>
Task2<DVertex,DEdge>::Task2(Graph<DVertex,DEdge> *g, DVertex *u, DVertex *v){
	this->initial_graph = g;
	max_short_path_edges = new list<DEdge*>();
	Graph<DVertex,DEdge>::vertex_iterator i = g->beginV();
	bool V1 = true, V2 = true;
	for(; i != g->endV(); ++i){
		DVertex *vertex = *i;
		if(u == vertex) V1 = false;
		if(v == vertex) V2 = false;
	}
	if(V1 && V2) throw VertexNotExistException();
	this->u = u;
	this->v = v;
	max_short_path = 0;
	current_graph = initial_graph;
	Restart(u,v);
}

template<class DVertex, class DEdge>
Task2<DVertex,DEdge>::Task2(const Task2 &obj){
	initial_graph = obj.initial_graph;
	current_graph = obj.current_graph;
	u = obj.u;
	v = obj.v;
	indexes = obj.indexes;
	dist = obj.dist;
	visited = obj.visited;
	path = obj.path;
}

template<class DVertex, class DEdge>
Task2<DVertex,DEdge>::~Task2(){}

template<class DVertex, class DEdge>
void Task2<DVertex,DEdge>::init(){
	indexes.clear();
	Graph<DVertex,DEdge>::vertex_iterator it = current_graph->beginV();
	for(int j = 0; it != current_graph->endV(); j++, ++it)
		indexes[*it] = j;
	dist.assign(indexes.size(), INF);
	stack<DVertex*> s;
	path.assign(indexes.size(),s);
	visited.assign(indexes.size(), false);
	int i = indexes[u];
	/*for(int j = 0; j < indexes.size(); j++){
		if(i == j) 
			continue;
		else
			dist[j] = 2147483647;
		while(!path[j].empty())
			path[j].pop();
	}*/
	dist[i] = 0; 
	path[i].push(u);
}

template<class DVertex, class DEdge>
void Task2<DVertex,DEdge>::Restart(){
	this->Restart(u,v);
}

template<class DVertex, class DEdge>
void Task2<DVertex,DEdge>::Restart(DVertex *u, DVertex *v){
	init();
	solve(u);
	int i = indexes[v];
	shortest_path_length = dist[i];
	short_path_vertex = stack_path_to_list_vertex_path(path[i]);
	if(shortest_path_length < INF){
		//stack<DVertex*> shortest_path_vertex = path[i];
		current_graph = new Graph<DVertex,DEdge>(*initial_graph);
		max_short_path = shortest_path_length;
		list<DVertex*>::iterator it = short_path_vertex.begin();
		list<DVertex*>::iterator jt = ++short_path_vertex.begin();
		for(; jt != short_path_vertex.end(); ++it, ++jt){
			DVertex *v1 = *it;
			DVertex *v2 = *jt;
			DEdge *e = initial_graph->GetEdge(v1,v2);
			current_graph->DeleteE(v1,v2);
			init();
			solve(u);
			int new_path_length = dist[indexes[v]];
			if(new_path_length > max_short_path){
				max_short_path_edges->clear();
				max_short_path_edges->push_back(e);
				max_shortest_paths_vertex.clear();
				max_shortest_paths_vertex[e] = stack_path_to_list_vertex_path(path[indexes[v]]);
				max_short_path = new_path_length;
			}else if(new_path_length == max_short_path){
				max_shortest_paths_vertex[e] = stack_path_to_list_vertex_path(path[indexes[v]]);
				max_short_path_edges->push_back(e);
			}
			DEdge *new_edge = current_graph->InsertE(v1,v2);
			new_edge->SetW(e->GetW());
			new_edge->SetData(e->GetData());
		}
		delete current_graph;
	}	
}

template<class DVertex, class DEdge>
list<DEdge*> *Task2<DVertex,DEdge>::Result(){
	return max_short_path_edges;
}

template<class DVertex, class DEdge>
void Task2<DVertex,DEdge>::Set(Graph<DVertex,DEdge> *g){
	this->initial_graph = g;
	this->current_graph = g;
	Restart(u,v);
}

template<class DVertex, class DEdge>
void Task2<DVertex,DEdge>::SetU(DVertex *u){
	Graph<DVertex,DEdge>::vertex_iterator i = g->beginV();
	bool V1 = false;
	for(; i != g->endV(); ++i){
		DVertex *vertex = *i;
		if(u == vertex) V1 = false;
	}
	if(!V1) throw VertexNotExistException();
	this->u = u;
}

template<class DVertex, class DEdge>
void Task2<DVertex,DEdge>::SetV(DVertex *v){
	Graph<DVertex,DEdge>::vertex_iterator i = g->beginV();
	bool V2 = false;
	for(; i != g->endV(); ++i){
		DVertex *vertex = *i;
		if(v == vertex) V2 = false;
	}
	if(!V2) throw VertexNotExistException();
	this->v = v;
}

template<class DVertex, class DEdge>
void Task2<DVertex,DEdge>::solve(DVertex *a){
	int i = indexes[a];
	if(visited[i]) return;
	visited[i] = true;
	priority_queue<pair<int,DVertex*>,vector<pair<int,DVertex*>>,compareWeight<DVertex>> edges;
	Graph<DVertex,DEdge>::out_edge_iterator it = current_graph->beginEout(a);
	for(; it != current_graph->endEout(a); ++it){
		DEdge *e = (*it);
		DVertex *v2 = e->getV2();
		
		//if(visited[indexes[v2]]) continue;
		pair<int,DVertex*> p(e->GetW(), v2);
		edges.push(p);
	}
	priority_queue<pair<int,DVertex*>,vector<pair<int,DVertex*>>,compareWeight<DVertex>> vertexes;
	while(!edges.empty()){
		pair<int,DVertex*> V = edges.top(); edges.pop();
		int w = V.first;
		DVertex *v = V.second;
		int k = indexes[v];
		if(dist[k] > dist[i] + w){
			dist[k] = dist[i] + w;
			path[k] = path[i];
			path[k].push(v);
			visited[k] = false;
			//cout<<dist[k]<<endl;
		}
		pair<int,DVertex*> p(dist[k], v);
		vertexes.push(p);
	}

	while(!vertexes.empty()){
		solve(vertexes.top().second);
		vertexes.pop();
	}
}

template<class DVertex, class DEdge>
map<DEdge*, list<DVertex*>> Task2<DVertex,DEdge>::GetMaxShortestPath(){
	return max_shortest_paths_vertex;
}

template<class DVertex, class DEdge>
int Task2<DVertex,DEdge>::GetMaxShortestPathLength(){
	return max_short_path;
}

template<class DVertex, class DEdge>
list<DVertex*> Task2<DVertex,DEdge>::stack_path_to_list_vertex_path(stack<DVertex *> &s){
	list<DVertex*> res;
	while(!s.empty()){
		res.push_front(s.top());
		s.pop();
	}
	return res;
}

template<class DVertex, class DEdge>
list<DVertex*> Task2<DVertex,DEdge>::GetShortestPath(){
	return short_path_vertex;
}

template<class DVertex, class DEdge>
int Task2<DVertex,DEdge>::GetShortestPathLength(){
	return shortest_path_length;
}