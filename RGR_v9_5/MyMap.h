#pragma once
#include <map>

using namespace std;

template<class key, class value>
class MyMap{
	map<key,value> m;
public:
	MyMap(){}
	MyMap(const MyMap &obj);
	~MyMap(){}
	void put(const key &k, const value &v);
	bool contain(const key &k);
	value& operator[](key k);
	void remove(const key &k);
	bool empty();
	void clear();
	typename map<key,value>::iterator begin();
	typename map<key,value>::iterator end();
};

template<class key, class value>
MyMap<key,value>::MyMap(const MyMap<key,value> &obj){
	this->m = obj.m;
	//cout<<"Constructor copy MyMap\n";
}

template<class key, class value>
bool MyMap<key,value>::contain(const key &k){
	if(m.count(k) > 0)
		return true;
	else
		return false;
}

template<class key, class value>
value& MyMap<key,value>::operator [](key k){
	return m[k];
}
template<class key, class value>
void MyMap<key,value>::put(const key &k, const value &v){
	m[k] = v;
}

template<class key, class value>
void MyMap<key,value>::remove(const key &k){
	m.erase(k);
}

template<class key, class value>
bool MyMap<key,value>::empty(){
	return m.empty();
}

template<class key, class value>
void MyMap<key,value>::clear(){
	m.clear();
}

template<class key, class value>
typename map<key,value>::iterator MyMap<key,value>::begin(){
	return m.begin();
}

template<class key, class value>
typename map<key,value>::iterator MyMap<key,value>::end(){
	return m.end();
}