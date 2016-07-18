#pragma once
#include "GraphDense.h"
#include <vector>

template<class DVertex, class DEdge>
class GraphDenseM: public GraphDense<DVertex,DEdge>{
	vector<vector<DEdge*>*> matrix;
public:
	GraphDenseM();
	GraphDenseM(int Vcnt, bool directed);
	//GraphDenseM(int Vcnt, int Ecnt, bool directed);
	GraphDenseM(const GraphDense<DVertex, DEdge> &obj);
	~GraphDenseM();
	DVertex *InsertV();
	void InsertV(DVertex *v);
	bool DeleteV(DVertex *v);
	DEdge *InsertE(DVertex *v1, DVertex *v2);
	bool InsertE(DEdge *e);
	void DeleteE(DEdge *e);
	DEdge *GetEdge(DVertex *v1, DVertex *v2);
	void print(int*,int*,int);
	edge_iterator_dense *beginE(GraphDense *g);
	edge_iterator_dense *endE(GraphDense *g);
	edge_iterator_dense *beginEout(DVertex *v, GraphDense *g);
	edge_iterator_dense *endEout(DVertex *v, GraphDense *g);
	//итератор ребер
	class edge_iterator_denseM: public GraphDense<DVertex,DEdge>::edge_iterator_dense{
		vector<vector<DEdge*>*> *matrix;
		int i,j;
		bool state;
	public:
		edge_iterator_denseM(GraphDense *g, vector<vector<DEdge*>*> &matrix);
		edge_iterator_denseM(GraphDense *g);
		DEdge *getEdge();
		void next();
		bool equals(edge_iterator_dense *i);
		void set(edge_iterator_dense *i);
	};
	//итератор исходящих ребер
	class out_edge_iterator_denseM: public GraphDense<DVertex,DEdge>::edge_iterator_dense{
		typename vector<DEdge*>::iterator i;
		DVertex *v;
		vector<DEdge*> *vec;
	public:
		out_edge_iterator_denseM(DVertex *v, typename vector<DEdge*> *vec, GraphDense *g, typename vector<DEdge*>::iterator iter);
		DEdge *getEdge();
		void next();
		bool equals(edge_iterator_dense *i);
		void set(edge_iterator_dense *i);
	};
};

template<class DVertex, class DEdge>
GraphDenseM<DVertex,DEdge>::GraphDenseM(){

}

template<class DVertex, class DEdge>
GraphDenseM<DVertex,DEdge>::GraphDenseM(int Vcnt, bool directed){
	this->directed = directed;
	this->matrix.assign(Vcnt, NULL);
	/*for(int i = 0; i < Vcnt; i++){
		matrix[i] = new vector<DEdge*>(Vcnt, NULL);
	}*/
}

/*template<class DVertex, class DEdge>
GraphDenseM<DVertex,DEdge>::GraphDenseM(int Vcnt, int Ecnt, bool directed){

}*/

template<class DVertex, class DEdge>
GraphDenseM<DVertex,DEdge>::GraphDenseM(const GraphDense<DVertex, DEdge> &obj){

}

template<class DVertex, class DEdge>
GraphDenseM<DVertex,DEdge>::~GraphDenseM(){

}

template<class DVertex, class DEdge>
DVertex *GraphDenseM<DVertex,DEdge>::InsertV(){
	DVertex *v = new DVertex();
	this->InsertV(v);
	return v;
}

template<class DVertex, class DEdge>
void GraphDenseM<DVertex,DEdge>::InsertV(DVertex *v){
	for(int i = 0; i < matrix.size(); i++){
		if(matrix[i] == NULL){
			matrix[i] = new vector<DEdge*>(matrix.size());
			v->setIndex(i);
			return;
		}
	}
	matrix.push_back(new vector<DEdge*>(matrix.size()+1));
	v->setIndex(matrix.size()-1);
	for(int i = 0; i < matrix.size()-1; i++)
		matrix[i]->push_back(NULL);
}

template<class DVertex, class DEdge>
bool GraphDenseM<DVertex,DEdge>::DeleteV(DVertex *v){
	int index = v->getIndex();
	matrix[index] = NULL;
	for(int i = 0; i < matrix.size(); i++){
		if(i == index) continue;
		if(matrix[i] == NULL) continue;
		/*if((*matrix[index])[i] != NULL){
			Ecnt--;
			(*matrix[index])[i] = NULL;
		}*/
		if((*matrix[i])[index] != NULL){
			Ecnt--;
			(*matrix[i])[index] = NULL;
		}
	}
	//matrix[index] = NULL;
	return true;
}

template<class DVertex, class DEdge>
DEdge *GraphDenseM<DVertex,DEdge>::InsertE(DVertex *v1, DVertex *v2){
	//проверка на наличие такого ребра
	if(this->GetEdge(v1, v2) == NULL){
		DEdge *e = new DEdge(v1, v2);
		this->InsertE(e);
		return e;
	}
	return NULL;
}

template<class DVertex, class DEdge>
bool GraphDenseM<DVertex,DEdge>::InsertE(DEdge *e){
	int i1 = e->getV1()->getIndex();
	int i2 = e->getV2()->getIndex();
	if(directed){
		(*matrix[i1])[i2] = e;
	}else{
		(*matrix[i1])[i2] = e;
		(*matrix[i2])[i1] = e;
	}
	Ecnt++;
	return true;
}

template<class DVertex, class DEdge>
void GraphDenseM<DVertex,DEdge>::DeleteE(DEdge *e){
	int i1 = e->getV1()->getIndex();
	int i2 = e->getV2()->getIndex();
	if(directed){
			(*matrix[i1])[i2] = NULL;
		}else{
			if(i1 < i2)
				(*matrix[i1])[i2] = NULL;
			else
				(*matrix[i2])[i1] = NULL;
		}
	Ecnt--;
}

template<class DVertex, class DEdge>
DEdge *GraphDenseM<DVertex,DEdge>::GetEdge(DVertex *v1, DVertex *v2){
	if(v1 == v2) return NULL;
	int i1 = v1->getIndex();
	int i2 = v2->getIndex();
	if(matrix[i1] == NULL || matrix[i2] == NULL) return NULL;
	if(directed)
		return (*matrix[i1])[i2];
	else{
		if(i1 < i2)
			return (*matrix[i1])[i2];
		else
			return (*matrix[i2])[i1];
	}
	return NULL;
}

template<class DVertex, class DEdge>
void GraphDenseM<DVertex,DEdge>::print(int *index, int *name, int N){
	//MyMap<int,int> index;
	cout<<"Name\t|";
	for(int i = 0; i < N; i++)
		cout<<name[i]<<'\t';
	cout<<"\n__________________________________________________\n";
	for(int i = 0; i < N; i++){
		//if(matrix[i] == NULL) continue;
		cout<<name[i]<<"\t|";
		for(int j = 0; j < N; j++){
			DEdge *e = (*matrix[index[i]])[index[j]];
			if(e == NULL) {
				cout<<"-\t";
				continue;
			}
			cout<<e->GetW()<<"\t";
		}
		cout<<endl;
	}
}

template<class DVertex, class DEdge>
typename GraphDense<DVertex,DEdge>::edge_iterator_dense *GraphDenseM<DVertex,DEdge>::beginE(GraphDense *g){
	return new GraphDenseM<DVertex,DEdge>::edge_iterator_denseM(g, this->matrix);
}

template<class DVertex, class DEdge>
typename GraphDense<DVertex,DEdge>::edge_iterator_dense *GraphDenseM<DVertex,DEdge>::endE(GraphDense *g){
	return new GraphDenseM<DVertex,DEdge>::edge_iterator_denseM(g);
}

template<class DVertex, class DEdge>
typename GraphDense<DVertex,DEdge>::edge_iterator_dense *GraphDenseM<DVertex,DEdge>::beginEout(DVertex *v, GraphDense *g){
	int index = v->getIndex();
	vector<DEdge*> *vec = matrix[index];
	return new GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM(v, vec, g, vec->begin());
}

template<class DVertex, class DEdge>
typename GraphDense<DVertex,DEdge>::edge_iterator_dense *GraphDenseM<DVertex,DEdge>::endEout(DVertex *v, GraphDense *g){
	int index = v->getIndex();
	vector<DEdge*> *vec = matrix[index];
	return new GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM(v, vec, g, vec->end());
}


//Итератор ребер
template<class DVertex, class DEdge>
GraphDenseM<DVertex,DEdge>::edge_iterator_denseM::edge_iterator_denseM(GraphDense *g, std::vector<vector<DEdge*>*> &matrix){
	this->g = g;
	this->matrix = &matrix;
	i = 0; j = 1;
	state = false;
	int n =this->matrix->size();
	while(i < n){
		if(matrix[i] == NULL){
			i++;
			continue;
		}
		while(j < n){
			
			if((*matrix[i])[j] != NULL){
				state = true;
				break;
			}
			j++;
		}
		if(state) break;
		i++;
		if(!g->Directed()) j = i + 1;
		else j = 0;
	}
}

template<class DVertex, class DEdge>
GraphDenseM<DVertex,DEdge>::edge_iterator_denseM::edge_iterator_denseM(GraphDense *g){
	this->g = g;
	this->state = false;
}

template<class DVertex, class DEdge>
bool GraphDenseM<DVertex,DEdge>::edge_iterator_denseM::equals(edge_iterator_dense *i){
	typename GraphDenseM<DVertex,DEdge>::edge_iterator_denseM *it = dynamic_cast<GraphDenseM<DVertex,DEdge>::edge_iterator_denseM*>(i);
	if(it->g == this->g){
		if(this->state == false && it->state == false) return true;
		if(this->state == true && it->state == true){
			if(it->i == this->i && it->j == this->j)
				return true;
		}
	}
	return false;
}

template<class DVertex, class DEdge>
DEdge* GraphDenseM<DVertex,DEdge>::edge_iterator_denseM::getEdge(){
	if(state == false) throw NoSuchElementException();
	return matrix->at(i)->at(j);
}

template<class DVertex, class DEdge>
void GraphDenseM<DVertex,DEdge>::edge_iterator_denseM::next(){
	if(state == false) throw NoSuchElementException();
	int n =this->matrix->size();
	state = false;
	j++;
	while(i < n){
		if((*matrix)[i] == NULL){
			i++;
			continue;
		}
		while(j < n){
			if((*(*matrix)[i])[j] != NULL){
				state = true;
				break;
			}
			j++;
		}
		if(state) break;
		i++;
		if(!g->Directed()) j = i + 1;
		else j = 0;
	}
}

template<class DVertex, class DEdge>
void GraphDenseM<DVertex,DEdge>::edge_iterator_denseM::set(edge_iterator_dense *i){
	typename GraphDenseM<DVertex,DEdge>::edge_iterator_denseM *it = dynamic_cast<GraphDenseM<DVertex,DEdge>::edge_iterator_denseM*>(i);
	this->g = it->g;
	this->i = it->i;
	this->j = it->j;
	this->state = it->state;
}

//итератор исходящих ребер
template<class DVertex, class DEdge>
GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM::out_edge_iterator_denseM(DVertex *v, typename vector<DEdge*> *vec, GraphDense *g, typename std::vector<DEdge*>::iterator iter){
	this->v = v;
	this->g = g;
	this->i = iter;
	this->vec = vec;
	while(this->i != this->vec->end()){
		if(*(this->i) != NULL)
			break;
		++(this->i);
	}
}

template<class DVertex, class DEdge>
bool GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM::equals(edge_iterator_dense *i){
	typename GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM *it = dynamic_cast<GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM*>(i);
	if(this->g == it->g && this->v == it->v && this->i == it->i)
		return true;
	return false;
}

template<class DVertex, class DEdge>
DEdge *GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM::getEdge(){
	if(this->i != vec->end())
		return *i;
	throw NoSuchElementException();
}

template<class DVertex, class DEdge>
void GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM::next(){
	if(i == vec->end()) return;
	++i;
	while(i != vec->end()){
		if(*i != NULL)
			break;
		++i;
	}
}

template<class DVertex, class DEdge>
void GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM::set(edge_iterator_dense *i){
	typename GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM *it = dynamic_cast<GraphDenseM<DVertex,DEdge>::out_edge_iterator_denseM*>(i);
	this->g = it->g;
	this->i = it->i;
	this->v = it->v;
	this->vec = it->vec;
}