#include "Graph.h"
#include <stack>


template<class DVertex, class DEdge>
class Task1{
public:
	typedef Vertex<int,list<DVertex*>*> reduce_vertex;
	typedef Edge<reduce_vertex,int,list<DEdge*>*> reduce_edge;
private:
	Graph<DVertex,DEdge> *g;
	stack<DVertex*> S, path;
	int cnt, scnt;
	map<DVertex*,int> pre, id;
	void scR(DVertex *w);
	DVertex *otherVertex(DEdge *e, DVertex *v);
	void init();
	bool found;
	list<DEdge*> undefined_edge;
	Graph<reduce_vertex,reduce_edge> *result;
	map<int,reduce_vertex*> map_vertex;
	void push_edge_to_graph(DEdge *e);
public:
	Task1(Graph<DVertex,DEdge> *g);
	Task1(const Task1 &obj);
	~Task1();
	void Set(Graph<DVertex,DEdge> *g);
	void Restart();
	Graph<reduce_vertex, reduce_edge> *Result();
};

template<class DVertex, class DEdge>
Task1<DVertex,DEdge>::Task1(Graph<DVertex,DEdge> *g){
	if(!g->Directed()) throw NotDirectedGraphException();
	Set(g);
}

template<class DVertex, class DEdge>
Task1<DVertex,DEdge>::Task1(const Task1<DVertex,DEdge> &obj){
	this->g = obj.g;
	this->cnt = obj.cnt;
	this->scnt = obj.scnt;
	this->id = obj.id;
	this->pre = obj.pre;
	this->S = obj.S;
	this->path = obj.path;
}

template<class DVertex, class DEdge>
Task1<DVertex,DEdge>::~Task1(){}

template<class DVertex, class DEdge>
void Task1<DVertex,DEdge>::Set(Graph<DVertex,DEdge> *g){
	if(!g->Directed()) throw NotDirectedGraphException();
	this->g = g;
	Restart();
}

template<class DVertex, class DEdge>
void Task1<DVertex,DEdge>::Restart(){
	this->init();
	Graph<DVertex,DEdge>::vertex_iterator i = this->g->beginV();
	for(; i != this->g->endV(); ++i){
		if(pre[*i] == -1) 
			scR(*i);
		found = false;
	}
	list<DEdge*>::iterator j = undefined_edge.begin();
	for(; j != undefined_edge.end(); ++j)
		this->push_edge_to_graph(*j);
}

template<class DVertex, class DEdge>
Graph<typename Task1<DVertex,DEdge>::reduce_vertex, typename Task1<DVertex,DEdge>::reduce_edge> *Task1<DVertex,DEdge>::Result(){
	return result;
}

template<class DVertex, class DEdge>
void Task1<DVertex,DEdge>::scR(DVertex *w){
	DVertex *v = NULL;
	pre[w] = cnt++;
	S.push(w); path.push(w);
	typename Graph<DVertex,DEdge>::out_edge_iterator i = g->beginEout(w);
	for(; i != g->endEout(w); ++i){
		DVertex *t = otherVertex(*i, w);
		if(pre[t] == -1){
			scR(t);
			if(found){
				undefined_edge.push_back(*i);
				found = false;
			}else{
				
			}
		}
		else if(id[t] == -1)
			while(pre[path.top()] > pre[t])
				path.pop();
		else
			if(id[w] != id[t])
				undefined_edge.push_back(*i);
	}
	if(path.top() == w)
		path.pop();
	else
		return;
	found = true;
	list<DVertex*> *l = new list<DVertex*>();
	do{
		v = S.top(); S.pop();
		id[v] = scnt;
		l->push_back(v);
	}while(v != w);
	Task1<DVertex,DEdge>::reduce_vertex *V = result->InsertV();
	V->SetName(scnt);
	V->SetData(l);
	map_vertex[scnt] = V;
	scnt++;
}

template<class DVertex, class DEdge>
void Task1<DVertex,DEdge>::init(){
	Graph<DVertex,DEdge>::vertex_iterator i = this->g->beginV();
	for(; i != this->g->endV(); ++i){
		DVertex *v = *i;
		pre[v] = -1;
		id[v] = -1;
	}
	cnt = scnt = 0;
	found = false;
	result = new Graph<Task1<DVertex,DEdge>::reduce_vertex,Task1<DVertex,DEdge>::reduce_edge>(0,true,true);
	//S.clear();
	//path.clear();
}

template<class DVertex, class DEdge>
DVertex *Task1<DVertex,DEdge>::otherVertex(DEdge *e, DVertex *v){
	DVertex *v1 = e->getV1();
	DVertex *v2 = e->getV2();
	if(v == v1)
		return v2;
	else
		return v1;
}

template<class DVertex, class DEdge>
void Task1<DVertex,DEdge>::push_edge_to_graph(DEdge *e){
	int id1 = id[e->getV1()];
	int id2 = id[e->getV2()];
	Task1<DVertex,DEdge>::reduce_vertex *v1 = map_vertex[id1];
	Task1<DVertex,DEdge>::reduce_vertex *v2 = map_vertex[id2];
	Task1<DVertex,DEdge>::reduce_edge *E = result->GetEdge(v1,v2);
	if(E == NULL){
		E = result->InsertE(v1, v2);
		list<DEdge*> *l = new list<DEdge*>();
		l->push_back(e);
		E->SetData(l);
		return;
	}
	list<DEdge*> *l = E->GetData();
	l->push_back(e);
}