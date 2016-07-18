#pragma once
#include "GraphDense.h"
using namespace std;

template<class DVertex, class Weight, class T>
class Edge{
	DVertex *v1;
	DVertex *v2;
	Weight w;
	T data;
public:
	Edge(DVertex *v1, DVertex *v2);
	Edge(DVertex *v1, DVertex *v2, const Weight &w);
	Edge(DVertex *v1, DVertex *v2, const Weight &w, const T &data);
	Weight GetW();
	void SetW(const Weight &w);
	T GetData();
	void SetData(const T &data);
	DVertex *getV1(){return v1;}
	DVertex *getV2(){return v2;}
};

template<class DVertex, class Weight, class T>
Edge<DVertex,Weight,T>::Edge(DVertex *v1, DVertex *v2){
	this->v1 = v1;
	this->v2 = v2;
}

template<class DVertex, class Weight, class T>
Edge<DVertex,Weight,T>::Edge(DVertex *v1, DVertex *v2, const Weight &w, const T &data){
	this->v1 = v1;
	this->v2 = v2;
	this->w = w;
	this->data = data;
}

template<class DVertex, class Weight, class T>
Edge<DVertex,Weight,T>::Edge(DVertex *v1, DVertex *v2, const Weight &w){
	this->v1 = v1;
	this->v2 = v2;
	this->w = w;
}

template<class DVertex, class Weight, class T>
T Edge<DVertex,Weight,T>::GetData(){
	return data;
}

template<class DVertex, class Weight, class T>
void Edge<DVertex,Weight,T>::SetData(const T &data){
	this->data = data;
}

template<class DVertex, class Weight, class T>
Weight Edge<DVertex,Weight,T>::GetW(){
	return w;
}

template<class DVertex, class Weight, class T>
void Edge<DVertex,Weight,T>::SetW(const Weight &w){
	this->w = w;
}