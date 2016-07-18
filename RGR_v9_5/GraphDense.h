#pragma once
#include "Edge.h"
#include "Vertex.h"
#include "MyMap.h"
//#include "Graph.h"
using namespace std;
template<class DVertex, class DEdge>
class GraphDense{
protected:
	bool directed;						//тип графа - ориентированный или неориентированный
	int Ecnt; //число ребер в графе
public:
	GraphDense(){Ecnt = 0;}
	int E(){return Ecnt;}
	//bool Directed(){return directed;}
	//virtual float K() = NULL;
	virtual ~GraphDense(){}
	virtual DVertex *InsertV() = NULL;
	virtual void InsertV(DVertex *v) = NULL;
	virtual bool DeleteV(DVertex *v) = NULL;
	virtual DEdge *InsertE(DVertex *v1, DVertex *v2) = NULL;
	virtual bool InsertE(DEdge *e) = NULL;
	virtual void DeleteE(DEdge *e) = NULL;
	virtual DEdge *GetEdge(DVertex *v1, DVertex *v2) = NULL;
	virtual void print(int *,int *, int) = NULL;
	bool Directed(){return directed;}
	class edge_iterator_dense{
	protected:
		GraphDense *g;
	public:
		virtual DEdge *getEdge() = NULL;
		virtual void next() = NULL;
		virtual bool equals(edge_iterator_dense *i) = NULL;
		virtual void set(edge_iterator_dense *i) = NULL;
	};
	virtual edge_iterator_dense *beginE(GraphDense *g) = NULL;
	virtual edge_iterator_dense *endE(GraphDense *g) = NULL;
	virtual edge_iterator_dense *beginEout(DVertex *v, GraphDense *g) = NULL;
	virtual edge_iterator_dense *endEout(DVertex *v, GraphDense *g) = NULL;
	/*class out_edge_iterator_dense{
	protected:
		GraphDense *g;
		DVertex *v;
	public:
		virtual DEdge *getEdge() = NULL;
		virtual void next() = NULL;
		virtual bool equals(edge_iterator_dense *i) = NULL;
		virtual void set(edge_iterator_dense *i) = NULL;
	};*/
};