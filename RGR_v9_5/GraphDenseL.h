#pragma once
#include "GraphDense.h"
#include <vector>
#include <list>

template<class DVertex, class DEdge>
class GraphDenseL: public GraphDense<DVertex,DEdge>{
	/*class Node{
		Node *next;
		DEdge *edge;
	public:
		Node(){
			next = NULL;
			edge = NULL;
		}	
		friend GraphDenseL;
	};*/
	MyMap<DVertex*,list<DEdge*>*> *maplists;
public:
	GraphDenseL();
	GraphDenseL(int Vcnt, bool directed);
	//GraphDenseL(int Vcnt, int Ecnt, bool directed);
	GraphDenseL(const GraphDense<DVertex, DEdge> &obj);
	~GraphDenseL();
	DVertex *InsertV();
	void InsertV(DVertex *v);
	bool DeleteV(DVertex *v);
	DEdge *InsertE(DVertex *v1,  DVertex *v2);
	bool InsertE(DEdge *e);
	void DeleteE(DEdge *e);
	DEdge *GetEdge(DVertex *v1, DVertex *v2);
	void print(int*, int*, int);
	//итератор ребер
	class edge_iterator_denseL: public GraphDense<DVertex,DEdge>::edge_iterator_dense{
		MyMap<DVertex*,list<DEdge*>*> *m;
		typename map<DVertex*,list<DEdge*>*>::iterator map_iterator;
		list<DEdge*> l;
		typename list<DEdge*>::iterator list_iterator;
		bool state;
	public:
		edge_iterator_denseL(GraphDense *g, MyMap<DVertex*,list<DEdge*>*> m);
		edge_iterator_denseL(GraphDense *g);
		//edge_iterator_denseL(const edge_iterator_denseL &obj);
		DEdge *getEdge();
		void next();
		bool equals(edge_iterator_dense *i);
		void set(edge_iterator_dense *i);
	};
	edge_iterator_dense *beginE(GraphDense *g);
	edge_iterator_dense *endE(GraphDense *g);
	//итератор исходящих ребер
	class out_edge_iterator_denseL: public GraphDense<DVertex,DEdge>::edge_iterator_dense{
		typename list<DEdge*>::iterator list_iterator;
		DVertex *v;
		list<DEdge*> *l;
	public:
		out_edge_iterator_denseL(DVertex *v, list<DEdge*> *l, GraphDense *g, typename list<DEdge*>::iterator iter);
		DEdge *getEdge();
		void next();
		bool equals(edge_iterator_dense *i);
		void set(edge_iterator_dense *i);
	};
	edge_iterator_dense *beginEout(DVertex *v, GraphDense *g);
	edge_iterator_dense *endEout(DVertex *v, GraphDense *g);
};

template<class DVertex, class DEdge>
GraphDenseL<DVertex,DEdge>::GraphDenseL(){
	maplists = new MyMap<DVertex*,list<DEdge*>*>();
	this->directed = false;
	this->Ecnt = 0;
}

template<class DVertex, class DEdge>
GraphDenseL<DVertex,DEdge>::GraphDenseL(int Vcnt, bool directed){
	maplists = new MyMap<DVertex*,list<DEdge*>*>();
	this->directed = directed;
	this->Ecnt = 0;
}

/*template<class DVertex, class DEdge>
GraphDenseL<DVertex,DEdge>::GraphDenseL(int Vcnt, int Ecnt, bool directed){
	
}*/

template<class DVertex, class DEdge>
GraphDenseL<DVertex,DEdge>::GraphDenseL(const GraphDense<DVertex, DEdge> &obj){

}

template<class DVertex, class DEdge>
GraphDenseL<DVertex,DEdge>::~GraphDenseL(){
	delete maplists;
}

template<class DVertex, class DEdge>
DVertex *GraphDenseL<DVertex,DEdge>::InsertV(){
	DVertex *v = new DVertex();
	this->InsertV(v);
	return v;
}

template<class DVertex, class DEdge>
void GraphDenseL<DVertex,DEdge>::InsertV(DVertex *v){
	list<DEdge*> *l = new list<DEdge*>();
	maplists->put(v, l);
}

template<class DVertex, class DEdge>
bool GraphDenseL<DVertex,DEdge>::DeleteV(DVertex *v){
	if(!maplists->contain(v)) return false;
	list<DEdge*> *l = (*maplists)[v];
	maplists->remove(v);
	if(directed){
		typename map<DVertex*,list<DEdge*>*>::iterator it_map = maplists->begin();
		while(it_map != maplists->end()){
			list<DEdge*> *l2 = it_map->second;
			for(list<DEdge*>::iterator jt = l2->begin(); jt != l2->end(); ){
				DEdge *e2 = *jt;
				if(v == e2->getV1() || v == e2->getV2()){
					jt = l2->erase(jt);
					Ecnt--;
					break;
				}else
					++jt;
			}
			++it_map;
		}
		Ecnt -= l->size();
	}else{
		for(list<DEdge*>::iterator it = l->begin(); it != l->end(); /*++it*/){
			DEdge *e = *it;
			it = l->erase(it);
			DVertex *v2 = NULL;
			if(v == e->getV1())
				v2 = e->getV2();
			else
				v2 = e->getV1();
			list<DEdge*> *l2 = (*maplists)[v2];
			l2->remove(e);
			Ecnt--;
			/*for(list<DEdge*>::iterator jt = l2->begin(); jt != l2->end(); ++jt){
				DEdge *e2 = *jt;
				if(v2 == e2->getV1() || v2 == e2->getV2()){
					l2->erase(jt);
					Ecnt--;
					break;
				}
			}*/
		}
	}
	delete l;
	return false;
}

template<class DVertex, class DEdge>
DEdge *GraphDenseL<DVertex,DEdge>::InsertE(DVertex *v1, DVertex *v2){
	//проверка на наличие такого ребра
	if(this->GetEdge(v1, v2) == NULL){
		DEdge *e = new DEdge(v1, v2);
		if(this->InsertE(e))
			return e;
		delete e;
	}
	return NULL;
}

template<class DVertex, class DEdge>
bool GraphDenseL<DVertex,DEdge>::InsertE(DEdge *e){
	DVertex *v1 = e->getV1();
	DVertex *v2 = e->getV2();
	list<DEdge*> *list1 = (*maplists)[v1];
	list<DEdge*> *list2 = (*maplists)[v2];
	if(list1 == NULL || list2 == NULL) return false;
	list1->push_back(e);
	if(!directed){
		list2->push_back(e);
	}
	Ecnt++;
	return true;
}

template<class DVertex, class DEdge>
void GraphDenseL<DVertex,DEdge>::DeleteE(DEdge *e){
	DVertex *v = e->getV1();
	list<DEdge*> *l = (*maplists)[v];
	l->remove(e);
	if(!directed){
		v = e->getV2();
		l = (*maplists)[v];
		l->remove(e);
	}
	Ecnt--;
}

template<class DVertex, class DEdge>
DEdge *GraphDenseL<DVertex,DEdge>::GetEdge(DVertex *v1, DVertex *v2){
	if(v1 == v2) return NULL;
	list<DEdge*> *list1 = (*maplists)[v1];
	list<DEdge*> *list2 = (*maplists)[v2];
	if(list1 == NULL || list2 == NULL) return NULL;
	for(list<DEdge*>::iterator it = list1->begin(); it != list1->end(); ++it)
		if((v1 == (*it)->getV1() || v1 == (*it)->getV2()) && (v2 == (*it)->getV1() || v2 == (*it)->getV2()))
			return *it;
	if(!directed){
		for(list<DEdge*>::iterator it = list2->begin(); it != list2->end(); ++it)
			if((v1 == (*it)->getV1() || v1 == (*it)->getV2()) && (v2 == (*it)->getV1() || v2 == (*it)->getV2()))
				return *it;
	}
	return NULL;
}

template<class DVertex, class DEdge>
void GraphDenseL<DVertex,DEdge>::print(int* a,int* b,int c){
	map<DVertex*,list<DEdge*>*>::iterator i = maplists->begin();
	for(; i != maplists->end(); ++i){
		DVertex *v = i->first;
		list<DEdge*> *l = i->second;
		list<DEdge*>::iterator j = l->begin();
		cout<<v->GetName()<<": ";
		for(; j != l->end(); ++j){
			DEdge *e = *j;
			DVertex *v1 = e->getV1();
			DVertex *v2 = e->getV2();
			if(v == v1)
				cout<<v2->GetName()<<' ';
			else
				cout<<v1->GetName()<<' ';
		}
		cout<<endl;
	}
}

template<class DVertex, class DEdge>
typename GraphDense<DVertex,DEdge>::edge_iterator_dense *GraphDenseL<DVertex,DEdge>::beginE(GraphDense *g){
	MyMap<DVertex*,list<DEdge*>*> m;
	map<DVertex*,list<DEdge*>*>::iterator it = this->maplists->begin();
	while(it != this->maplists->end()){
		DVertex* v = it->first;
		list<DEdge*> *l = it->second;
		list<DEdge*> *new_l = new list<DEdge*>(*l);
		m.put(v, new_l);
		++it;
	}
	return new GraphDenseL<DVertex,DEdge>::edge_iterator_denseL(g, m);
}

template<class DVertex, class DEdge>
typename GraphDense<DVertex,DEdge>::edge_iterator_dense *GraphDenseL<DVertex,DEdge>::endE(GraphDense *g){
	return new GraphDenseL<DVertex,DEdge>::edge_iterator_denseL(g);
}

template<class DVertex, class DEdge>
typename GraphDense<DVertex,DEdge>::edge_iterator_dense *GraphDenseL<DVertex,DEdge>::beginEout(DVertex *v, GraphDense *g){
	list<DEdge*> *l = (*this->maplists)[v];
	list<DEdge*>::iterator it;
	if(l->empty())
		it = l->end();
	else
		it = l->begin();
	return new GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL(v, l, g, it);
}

template<class DVertex, class DEdge>
typename GraphDense<DVertex,DEdge>::edge_iterator_dense *GraphDenseL<DVertex,DEdge>::endEout(DVertex *v, GraphDense *g){
	list<DEdge*> *l = (*this->maplists)[v];
	list<DEdge*>::iterator it = l->end();
	return new GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL(v, l, g, it);
}



//итератора ребер
template<class DVertex, class DEdge>
GraphDenseL<DVertex,DEdge>::edge_iterator_denseL::edge_iterator_denseL(GraphDense *g, MyMap<DVertex*,list<DEdge*>*> m){
	this->m = new MyMap<DVertex*,list<DEdge*>*>(m);
	this->g = g;
	this->state = false;
	if(!(this->m->empty())){
		this->map_iterator = (this->m)->begin();
		while(map_iterator != this->m->end()){
			l = *(map_iterator->second);
			if(!l.empty()){
				this->list_iterator = l.begin();
				this->state = true;
				break;
			}
			++map_iterator;
		}
		
	}else
		this->state = false;
}

template<class DVertex, class DEdge>
GraphDenseL<DVertex,DEdge>::edge_iterator_denseL::edge_iterator_denseL(GraphDense *g){
	this->g = g;
	this->state = false;
}

/*template<class DVertex, class DEdge>
GraphDenseL<DVertex,DEdge>::edge_iterator_denseL::edge_iterator_denseL(const typename GraphDenseL<DVertex,DEdge>::edge_iterator_denseL &obj){
	this->m = new MyMap<DVertex*,list<DEdge*>*>(obj.m);
	this->map_iterator = obj.map_iterator;
	this->list_iterator = obj.list_iterator;
}*/

template<class DVertex, class DEdge>
bool GraphDenseL<DVertex,DEdge>::edge_iterator_denseL::equals(typename GraphDense<DVertex,DEdge>::edge_iterator_dense *i){
	typename GraphDenseL<DVertex,DEdge>::edge_iterator_denseL *it = dynamic_cast<GraphDenseL<DVertex,DEdge>::edge_iterator_denseL*>(i);
	if(it->g == this->g){
		if(this->state == false && it->state == false ) return true;
		if(this->state == true && it->state == true){
			if(it->list_iterator == this->list_iterator && it->map_iterator == this->map_iterator)
				return true;
		}
	}
	return false;
}

template<class DVertex, class DEdge>
void GraphDenseL<DVertex,DEdge>::edge_iterator_denseL::set(typename GraphDense<DVertex,DEdge>::edge_iterator_dense *i){
	typename GraphDenseL<DVertex,DEdge>::edge_iterator_denseL *it = dynamic_cast<GraphDenseL<DVertex,DEdge>::edge_iterator_denseL*>(i);
	
	this->m = new MyMap<DVertex*,list<DEdge*>*>(*(it->m));
	this->map_iterator = m->begin();
	while(*map_iterator != (*it->map_iterator))
		++map_iterator;
	this->l = *(map_iterator->second);
	this->list_iterator = (this->l).begin();
	while(*list_iterator != *(it->list_iterator))
	this->g = it->g;
}

template<class DVertex, class DEdge>
DEdge *GraphDenseL<DVertex,DEdge>::edge_iterator_denseL::getEdge(){
	if(map_iterator != m->end())
		return *list_iterator;
	throw NoSuchElementException();
}

template<class DVertex, class DEdge>
void GraphDenseL<DVertex,DEdge>::edge_iterator_denseL::next(){
	if(this->state == false) return;
	if((this->g)->Directed() == false){
		DVertex *v = map_iterator->first;
		DEdge *e = *list_iterator;
		DVertex *v1 = e->getV1();
		DVertex *v2 = e->getV2();
		DVertex *real_v2 = NULL;
		if(v == v1)
			real_v2 = v2;
		else
			real_v2 = v1;
		list<DEdge*> *second_list = (*m)[real_v2];
		second_list->remove(e);
	}
	++list_iterator;
	//}
	if(list_iterator == l.end()){
		++map_iterator;
		state = false;
		while(map_iterator != m->end()){
			l = *(map_iterator->second);
			if(!l.empty()){
				this->list_iterator = l.begin();
				this->state = true;
				break;
			}
			++map_iterator;
		}
			
	}
}

//итератор исходящих ребер
template<class DVertex, class DEdge>
GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL::out_edge_iterator_denseL(DVertex *v, list<DEdge*> *l, GraphDense *g, typename list<DEdge*>::iterator iter){
	this->v = v;
	this->g = g;
	this->list_iterator = iter;
	this->l = l;
}

template<class DVertex, class DEdge>
bool GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL::equals(edge_iterator_dense *i){
	typename GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL *it = dynamic_cast<GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL*>(i);
	if(this->g == it->g && this->v == it->v && this->list_iterator == it->list_iterator)
		return true;
	return false;
}

template<class DVertex, class DEdge>
DEdge *GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL::getEdge(){
	if(this->list_iterator != (this->l)->end())
		return *list_iterator;
	throw NoSuchElementException();
}

template<class DVertex, class DEdge>
void GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL::next(){
	if(this->list_iterator == (this->l)->end())
		throw NoSuchElementException();
	++(this->list_iterator);
}

template<class DVertex, class DEdge>
void GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL::set(edge_iterator_dense *i){
	typename GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL *it = dynamic_cast<GraphDenseL<DVertex,DEdge>::out_edge_iterator_denseL*>(i);
	this->l = it->l;
	this->list_iterator = it->list_iterator;
	this->v = it->v;
	this->g = it->g;
}