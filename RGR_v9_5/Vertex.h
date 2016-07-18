
template<class N, class T>
class Vertex{
	N name;
	int index;
	T data;
public:
	Vertex(){index = -1;}
	Vertex(const N &name, const T &data);
	N GetName();
	T GetData();
	void SetName(const N &name);
	void SetData(const T &data);

	int getIndex();
	void setIndex(int index);
};

/*template<class N, class T>
Vertex<N,T>::Vertex(){

}*/

template<class N, class T>
Vertex<N,T>::Vertex(const N &name, const T &data){
	this->name = name;
	this->data = data;
}

template<class N, class T>
T Vertex<N,T>::GetData(){
	return data;
}

template<class N, class T>
N Vertex<N,T>::GetName(){
	return name;
}

template<class N, class T>
void Vertex<N,T>::SetData(const T &data){
	this->data = data;
}

template<class N, class T>
void Vertex<N,T>::SetName(const N &name){
	this->name = name;
}

template<class N, class T>
int  Vertex<N,T>::getIndex(){
	return index;
}

template<class N, class T>
void Vertex<N,T>::setIndex(int index){
	this->index = index;
}