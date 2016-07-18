#pragma once
#include <cstdlib>
#include <vector>
#include <list>
#include <iostream>
#include "GraphDenseL.h"
#include "GraphDenseM.h"
#include "Exceptions.h"

using namespace std;


template<class DVertex, class DEdge>
class Graph{
	list<DVertex *> vertexes;	//список вершин
	GraphDense<DVertex, DEdge> *dense;	//структура графа
	bool directed;				//тип графа - ориентированный или неориентированный
	bool dense_type;			//тип структуры графа - L-граф или M-граф
	void InsertRandE(int Vcnt, int Ecnt);
	void init(int Vcnt, bool directed, bool dense_type);
public:
	Graph();
	Graph(int Vcnt, bool directed, bool dense_type);
	Graph(int Vcnt, int Ecnt, bool directed, bool dense_type);
	Graph(const Graph &obj);
	~Graph();
	int V();
	int E();
	bool Directed();
	bool Dense();
	float K();
	void ToListGraph();
	void ToMatrixGraph();
	DVertex *InsertV();
	bool DeleteV(DVertex *v);
	DEdge *InsertE(DVertex *v1, DVertex *v2);
	bool DeleteE(DVertex *v1, DVertex *v2);
	DEdge *GetEdge(DVertex *v1, DVertex *v2);
	void print();
	void printVertexes();

	//итератор вершин
	class vertex_iterator{
		Graph<DVertex,DEdge> *g;
		typename list<DVertex*>::iterator i;
		vertex_iterator(typename Graph<DVertex,DEdge> *g, const typename list<DVertex*>::iterator iter);
	public:		
		//~vertex_iterator(){}
		DVertex* operator*();
		void operator++();
		bool operator ==(const vertex_iterator &iter);
		bool operator !=(const vertex_iterator &iter);
		vertex_iterator& operator=(const vertex_iterator &iter);
		friend Graph;
	};
	vertex_iterator beginV();
	vertex_iterator endV();
	friend typename Graph<DVertex, DEdge>::vertex_iterator;
	//итератор ребер
	class edge_iterator{
		bool dense_type;
		typename GraphDense<DVertex,DEdge>::edge_iterator_dense *i;
		edge_iterator(GraphDense<DVertex,DEdge> *g, bool begin);
	public:
		DEdge* operator*();
		void operator++();
		bool operator ==(const edge_iterator &iter);
		bool operator !=(const edge_iterator &iter);
		edge_iterator& operator=(const edge_iterator &iter);
		friend Graph;
	};
	friend typename GraphDense<DVertex,DEdge>::edge_iterator_dense;
	edge_iterator beginE();
	edge_iterator endE();
	//итератор исходящих ребер
	class out_edge_iterator{
		bool dense_type;
		typename GraphDense<DVertex,DEdge>::edge_iterator_dense *i;
		out_edge_iterator(DVertex *v, GraphDense<DVertex,DEdge> *g, bool begin);
	public:
		DEdge* operator*();
		void operator++();
		bool operator ==(const out_edge_iterator &iter);
		bool operator !=(const out_edge_iterator &iter);
		out_edge_iterator& operator=(const out_edge_iterator &iter);
		friend Graph;
	};
	out_edge_iterator beginEout(DVertex *v);
	out_edge_iterator endEout(DVertex *v);
};

template<class DVertex, class DEdge>
Graph<DVertex,DEdge>::Graph(){
	dense = new GraphDenseL<DVertex,DEdge>();
	directed = false;
	dense_type = true;
}

template<class DVertex, class DEdge>
Graph<DVertex,DEdge>::Graph(int Vcnt, bool directed, bool dense_type){
	init(Vcnt, directed, dense_type);
}

template<class DVertex, class DEdge>
Graph<DVertex,DEdge>::Graph(int Vcnt, int Ecnt, bool directed, bool dense_type){
	init(Vcnt, directed, dense_type);
	if(Vcnt > 1){
		this->InsertRandE(Vcnt, Ecnt);
	}
}

template<class DVertex, class DEdge>
Graph<DVertex,DEdge>::Graph(const Graph<DVertex,DEdge> &obj){
	this->dense_type = obj.dense_type;
	this->vertexes = obj.vertexes;
	this->directed = obj.directed;
	if(this->dense_type)
		this->dense = new GraphDenseL<DVertex,DEdge>(vertexes.size(), obj.directed);
	else
		this->dense = new GraphDenseM<DVertex,DEdge>(vertexes.size(), obj.directed);
	list<DVertex*>::iterator i = this->vertexes.begin();
	for(; i != this->vertexes.end(); ++i)
		this->dense->InsertV(*i);
	edge_iterator beg(obj.dense, true);
	edge_iterator end(obj.dense, false);
	for(; beg != end; ++beg){
		this->dense->InsertE(*beg);
	}
}

template<class DVertex, class DEdge>
Graph<DVertex,DEdge>::~Graph(){

}

template<class DVertex, class DEdge>
void Graph<DVertex,DEdge>::init(int Vcnt, bool directed, bool dense_type){
	this->dense_type = dense_type;
	this->directed = directed;
	//vertexes.assign(Vcnt, NULL);
	if(dense_type)
		dense = new GraphDenseL<DVertex,DEdge>(Vcnt, directed);
	else
		dense = new GraphDenseM<DVertex,DEdge>(Vcnt, directed);
	for(int i=0; i<Vcnt; i++){
		DVertex *v = dense->InsertV();
		v->SetName(i);
		vertexes.push_back(v);
	}
}

template<class DVertex, class DEdge>
void Graph<DVertex,DEdge>::InsertRandE(int Vcnt, int Ecnt){
	if(Ecnt <= 0) return;
	int Emax = Vcnt*(Vcnt - 1);
	if(!directed) Emax /= 2;
	vector<DVertex*> v1,v2;
	list<DVertex*>::iterator i = vertexes.begin();
	list<DVertex*>::iterator j = vertexes.begin();
	if(directed){
		double p = (double)Ecnt/(Vcnt*(Vcnt-1));
		for(++j; i != vertexes.end(); ++i){
			for(; j != vertexes.end(); ++j){
				if(j == i) continue;
				if(rand() < p * RAND_MAX){
					DEdge *e = dense->InsertE(*i, *j);
					e->SetW(rand()%30);
				}
				else{
					v1.push_back(*i);
					v2.push_back(*j);
				}
			}
			if(dense->E() == Ecnt || dense->E() == Emax) return;
			j = vertexes.begin();
		}
	}else{
		double p = (double)Ecnt/(Vcnt*(Vcnt-1));
		for(; i != vertexes.end(); ++i, j = i){
			for(++j; j != vertexes.end(); ++j){
				if(j == i) continue;
				if(rand() < p * RAND_MAX){
					DEdge *e = dense->InsertE(*i, *j);
					e->SetW(rand()%30);
				}
				else{
					v1.push_back(*i);
					v2.push_back(*j);
				}
			}
			if(dense->E() == Ecnt || dense->E() == Emax) return;
		}
	}
	while(dense->E() < Ecnt  && dense->E() < Emax){
		int index = int(v1.size()*rand()/(1.0 + RAND_MAX));
		DEdge *e = dense->InsertE(v1[index], v2[index]);
		e->SetW(rand()%30);
		v1.erase(v1.begin() + index);
		v2.erase(v2.begin() + index);
	}

}

template<class DVertex, class DEdge>
int Graph<DVertex,DEdge>::V(){
	return vertexes.size();
}

template<class DVertex, class DEdge>
int Graph<DVertex,DEdge>::E(){
	return dense->E();
}

template<class DVertex, class DEdge>
bool Graph<DVertex,DEdge>::Directed(){
	return directed;
}

template<class DVertex, class DEdge>
bool Graph<DVertex,DEdge>::Dense(){
	return dense_type;
}

template<class DVertex, class DEdge>
float Graph<DVertex,DEdge>::K(){
	int V = vertexes.size();
	if(V <= 1) return -1;
	float Emax;
	if(directed)
		Emax = V*(V-1);
	else
		Emax = (float)(V*(V-1))/2;
	int Ecnt = dense->E();
	float K = Ecnt/Emax;
	return K;
}

template<class DVertex, class DEdge>
void Graph<DVertex,DEdge>::ToListGraph(){
	if(dense_type == true) return; 
	GraphDense<DVertex,DEdge> *new_dense = new GraphDenseL<DVertex,DEdge>(vertexes.size(), directed);
	//вставка вершин
	list<DVertex*>::iterator v = vertexes.begin();
	for(; v != vertexes.end(); ++v)
		new_dense->InsertV(*v);
	//вставка ребер
	edge_iterator beg(this->dense, true);
	edge_iterator end(this->dense, false);
	for(; beg != end; ++beg){
		new_dense->InsertE(*beg);
	}
	delete dense;
	dense = new_dense;
	dense_type = true;
}

template<class DVertex, class DEdge>
void Graph<DVertex,DEdge>::ToMatrixGraph(){
	if(dense_type == false) return;
	GraphDense<DVertex,DEdge> *new_dense = new GraphDenseM<DVertex,DEdge>(vertexes.size(), directed);
	//индексация вершин и вставка вершин
	list<DVertex*>::iterator v = vertexes.begin();
	for(int i = 0; v != vertexes.end(); ++v, i++){
		(*v)->setIndex(i);
		new_dense->InsertV(*v);
	}
	//вставка ребер
	edge_iterator beg(this->dense, true);
	edge_iterator end(this->dense, false);
	for(; beg != end; ++beg){
		new_dense->InsertE(*beg);
	}
	delete dense;
	dense = new_dense;
	dense_type = false;
}

template<class DVertex, class DEdge>
DVertex *Graph<DVertex,DEdge>::InsertV(){
	DVertex *v = dense->InsertV();
	vertexes.push_back(v);
	return v;
}

template<class DVertex, class DEdge>
bool Graph<DVertex,DEdge>::DeleteV(DVertex *v){
	if(v == NULL) return false;
	vertexes.remove(v);
	return dense->DeleteV(v);
}

template<class DVertex, class DEdge>
DEdge *Graph<DVertex,DEdge>::InsertE(DVertex *v1, DVertex *v2){
	if(v1 == v2) return NULL;
	DEdge *e = dense->InsertE(v1,v2);
	return e;
}

template<class DVertex, class DEdge>
bool Graph<DVertex,DEdge>::DeleteE(DVertex *v1, DVertex *v2){
	DEdge *e = this->GetEdge(v1, v2);
	if(e == NULL) return false;
	dense->DeleteE(e);
	return true;
}

template<class DVertex, class DEdge>
DEdge *Graph<DVertex,DEdge>::GetEdge(DVertex *v1, DVertex *v2){
	return dense->GetEdge(v1, v2);
}

template<class DVertex, class DEdge>
void Graph<DVertex,DEdge>::printVertexes(){
	list<DVertex*>::iterator it = vertexes.begin();
	for(;it != vertexes.end(); ++it)
		cout<<(*it)->getIndex()<<' ';
	cout<<endl;
}

template<class DVertex, class DEdge>
void Graph<DVertex,DEdge>::print(){
	if(dense_type == false){
		int *arr = new int[vertexes.size()];
		int *name = new int[vertexes.size()];
		list<DVertex*>::iterator i = vertexes.begin();
		for(int k = 0; i != vertexes.end(); ++i, k++){
			DVertex *v = *i;
			arr[k] = v->getIndex();
			name[k] = v->GetName();
		}
		dense->print(arr,name, vertexes.size());
	}
	else
		dense->print(NULL,NULL,0);

}

template<class DVertex, class DEdge>
typename Graph<DVertex,DEdge>::vertex_iterator Graph<DVertex,DEdge>::beginV(){
	typename Graph<DVertex,DEdge>::vertex_iterator i(this, vertexes.begin());
	return i;
}

template<class DVertex, class DEdge>
typename Graph<DVertex,DEdge>::vertex_iterator Graph<DVertex,DEdge>::endV(){
	typename Graph<DVertex,DEdge>::vertex_iterator i(this, vertexes.end());
	return i;
}

template<class DVertex, class DEdge>
typename Graph<DVertex,DEdge>::edge_iterator Graph<DVertex,DEdge>::beginE(){
	typename Graph<DVertex,DEdge>::edge_iterator i(this->dense, true);
	return i;
}

template<class DVertex, class DEdge>
typename Graph<DVertex,DEdge>::edge_iterator Graph<DVertex,DEdge>::endE(){
	typename Graph<DVertex,DEdge>::edge_iterator i(this->dense, false);
	return i;
}

template<class DVertex, class DEdge>
typename Graph<DVertex,DEdge>::out_edge_iterator Graph<DVertex,DEdge>::beginEout(DVertex *v){
	typename Graph<DVertex,DEdge>::out_edge_iterator i(v, this->dense, true);
	return i;
}

template<class DVertex, class DEdge>
typename Graph<DVertex,DEdge>::out_edge_iterator Graph<DVertex,DEdge>::endEout(DVertex *v){
	typename Graph<DVertex,DEdge>::out_edge_iterator i(v, this->dense, false);
	return i;
}


//***************************************************************************
//***************************итератор вершин*********************************
//***************************************************************************

template<class DVertex, class DEdge>
Graph<DVertex,DEdge>::vertex_iterator::vertex_iterator(typename Graph<DVertex,DEdge> *g,const typename list<DVertex*>::iterator iter){
	this->g = g;
	this->i = iter;
}

template<class DVertex, class DEdge>
DVertex* Graph<DVertex,DEdge>::vertex_iterator::operator *(){
	if(this->i != (this->g->vertexes).end())
		return *i;
	throw NoSuchElementException();
}

template<class DVertex, class DEdge>
void Graph<DVertex,DEdge>::vertex_iterator::operator ++(){
	if(this->i == (this->g->vertexes).end())
		throw NoSuchElementException();
	++i;
}

template<class DVertex, class DEdge>
bool Graph<DVertex,DEdge>::vertex_iterator::operator !=(const typename Graph<DVertex,DEdge>::vertex_iterator &iter){
	if(/*this->g != iter.g || */this->i != iter.i)
		return true;
	else
		return false;
}

template<class DVertex, class DEdge>
bool Graph<DVertex,DEdge>::vertex_iterator::operator ==(const typename Graph<DVertex,DEdge>::vertex_iterator &iter){
	if(/*this->g == iter.g && */this->i == iter.i)
		return true;
	else
		return false;
}

template<class DVertex, class DEdge>
typename Graph<DVertex,DEdge>::vertex_iterator& Graph<DVertex,DEdge>::vertex_iterator::operator =(const typename Graph<DVertex,DEdge>::vertex_iterator &iter){
	if(this == &iter) return *this;
	//g = iter.g;
	this->i = iter.i;
	return *this;
}

//***************************************************************************
//***************************итератор ребер**********************************
//***************************************************************************
template<class DVertex, class DEdge>
Graph<DVertex,DEdge>::edge_iterator::edge_iterator(GraphDense<DVertex,DEdge> *g, bool begin){
	if(begin)
		this->i = g->beginE(g);
	else
		this->i = g->endE(g);
}

template<class DVertex, class DEdge>
DEdge *Graph<DVertex,DEdge>::edge_iterator::operator *(){
	try{
		return i->getEdge();
	}catch(NoSuchElementException){
		throw NoSuchElementException();
	}
}

template<class DVertex, class DEdge>
bool Graph<DVertex,DEdge>::edge_iterator::operator ==(const typename Graph<DVertex,DEdge>::edge_iterator &iter){
	return i->equals(iter.i);
}

template<class DVertex, class DEdge>
bool Graph<DVertex,DEdge>::edge_iterator::operator !=(const typename Graph<DVertex,DEdge>::edge_iterator &iter){
	return !i->equals(iter.i);
}

template<class DVertex, class DEdge>
typename Graph<DVertex,DEdge>::edge_iterator& Graph<DVertex,DEdge>::edge_iterator::operator =(const typename Graph<DVertex,DEdge>::edge_iterator &iter){
	if(this == &iter) return *this;
	i->set(iter.i);
	return *this;
}

template<class DVertex, class DEdge>
void Graph<DVertex,DEdge>::edge_iterator::operator ++(){
	i->next();
}

//***************************************************************************
//**********************итератор исходящих вершин****************************
//***************************************************************************
template<class DVertex, class DEdge>
Graph<DVertex,DEdge>::out_edge_iterator::out_edge_iterator(DVertex *v, GraphDense<DVertex,DEdge> *g, bool begin){
	if(begin)
		this->i = g->beginEout(v, g);
	else
		this->i = g->endEout(v, g);
}

template<class DVertex, class DEdge>
DEdge *Graph<DVertex,DEdge>::out_edge_iterator::operator *(){
	try{
		return i->getEdge();
	}catch(NoSuchElementException){
		throw NoSuchElementException();
	}
}

template<class DVertex, class DEdge>
bool Graph<DVertex,DEdge>::out_edge_iterator::operator ==(const typename Graph<DVertex,DEdge>::out_edge_iterator &iter){
	return i->equals(iter.i);
}

template<class DVertex, class DEdge>
bool Graph<DVertex,DEdge>::out_edge_iterator::operator !=(const typename Graph<DVertex,DEdge>::out_edge_iterator &iter){
	return !i->equals(iter.i);
}

template<class DVertex, class DEdge>
typename Graph<DVertex,DEdge>::out_edge_iterator& Graph<DVertex,DEdge>::out_edge_iterator::operator =(const typename Graph<DVertex,DEdge>::out_edge_iterator &iter){
	if(this == &iter) return *this;
	i->set(iter.i);
	return *this;
}

template<class DVertex, class DEdge>
void Graph<DVertex,DEdge>::out_edge_iterator::operator ++(){
	i->next();
}