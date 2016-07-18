template<class DVertex>
class node;

template<class DVertex>
class orderlist{
	node<DVertex> *begin;
	int n;
public:
	orderlist();
	void push(int w, DVertex *v);
	node<DVertex> *pop();
	bool empty();
};
template<class DVertex>
class node{
	node *next;
public:
	node(int w, DVertex *v){ this->w = w; this->v = v; next = NULL;}
	int w;
	DVertex *v;
	friend orderlist<DVertex>;
};

template<class DVertex>
orderlist<DVertex>::orderlist(){
	begin = NULL;
	n = 0;
}

template<class DVertex>
bool orderlist<DVertex>::empty(){
	if(n == 0) return true;
	return false;
}

template<class DVertex>
void orderlist<DVertex>::push(int w, DVertex *v){
	if(!begin){
		begin = new node<DVertex>(w, v);
		n++;
		return;
	}
	if(w <= begin->w){
		node<DVertex> *elem = new node<DVertex>(w,v);
		elem->next = begin;
		begin = elem;
		n++;
		return;
	}
	if(begin->next == NULL){
		begin->next = new node<DVertex>(w,v);
		n++;
		return;
	}
	node<DVertex> *p = begin->next;
	node<DVertex> *pre = begin;
	while(p != NULL){
		if(w <= p->w){
			node<DVertex> *elem = new node<DVertex>(w,v);
			elem->next = p->next;
			pre->next = elem;
			n++;
			return;
		}
		pre = p;
		p = p->next;
	}
}

template<class DVertex>
node<DVertex> *orderlist<DVertex>::pop(){
	if(n == 0) return NULL;
	node<DVertex> *res = begin;
	begin = begin->next;
	n--;
	return res;
}