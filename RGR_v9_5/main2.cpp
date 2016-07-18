#include "Graph.h"
#include <windows.h>
#include "MyMap.h"
#include "Task1.h"
#include "Task2.h"
#include <time.h>
#include <locale.h>

typedef int name;
typedef int data_v;
typedef int data_e;
typedef int weight;
typedef Vertex<name,data_v> vertex;
typedef Edge<vertex,weight,data_e> edge;
typedef Graph<vertex,edge> graph;
typedef Task1<vertex,edge> task1;
typedef task1::reduce_edge r_edge;
typedef task1::reduce_vertex r_vertex;
//typedef Graph<r_vertex,r_edge>::vertex_iterator;
MyMap<name,vertex*> table;
void printmenu(){
	system("cls");
	cout<<"1) ������� ����\n2) �������� �������\n3) �������� �����\n4) ������� �������\n5) ������� �����\n6) �������� �����\n";
	cout<<"7) ����� ������\n8) ����� �����\n9) ��� �����\n10) ����� ������������ �����\n11) ����������� ������������\n";
	cout<<"12) ������������� � L-�����\n13) ������������� � �-�����\n14) �������� ������\n15) �������� �����\n";
	cout<<"16) �������� ��������� �����\n17) ������ ������ 1\n18) ������ ������ 2\n19) �������� ��������� �����\n\n";
}

void printmenuItV(){
	system("cls");
	cout<<"1) ������ ��� �������\n2) ���������� �� ������\n3) ��������� �������\n4) ��������� ��� � ������ �������\n";
	cout<<"5) �������� ���\n6) �������� ������\n\n";
}

void printmenuItE(){
	system("cls");
	cout<<"1) ������ ��� �����\n2) ���������� �� ������\n3) ��������� �����\n4) ��������� ��� � ������ �����\n";
	cout<<"5) �������� ������\n6) �������� ���\n\n";
}

void printmenuItEout(){
	system("cls");
	cout<<"1) ������ ��� ��������� ����� ��������� �������\n2) ������ ��������� ����� ���� ������\n3) ���������� �� ������\n";
	cout<<"4) ��������� �����\n5) ��������� ��� � ������ �����\n";
	cout<<"6) �������� ������\n7) �������� ���\n\n";
}

void printPath(list<vertex*> s){
	list<vertex*>::iterator i = s.begin();
	for(; i != s.end(); ++i)
		cout<<(*i)->GetName()<<' ';
	cout<<endl;
}

graph *createGraph(){
	int v,e;
	int dir,dense;
	cout<<"���������� ������: "; cin>>v;
	cout<<"���������� �����: "; cin>>e;
	cout<<"��������������� - 1, ����������������� - 0\n"; cin>>dir;
	cout<<"L-���� - 1, M-���� - 0\n"; cin>>dense;
	graph *g = new graph(v,e,dir,dense);
	table.clear();
	if(v > 0){
		graph::vertex_iterator i = g->beginV();
		for(; i != g->endV(); ++i){
			vertex *V = *i;
			table.put(V->GetName(), V);
		}
	}
	return g;
}

void insertV(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	name n; 
	data_v data;
	cout<<"������� ��� �������: "; cin>>n;
	if(table.contain(n)){
		int res;
		cout<<"������� � ����� ������ ���������� � �����";
		if(res == 0) return;
	}
	cout<<"������� ������: "; cin>>data;
	vertex *v = g->InsertV();
	v->SetName(n);
	v->SetData(data);
	table.put(n, v);
}

void insertE(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	vertex *v1,*v2;
	name n1,n2;
	cout<<"������� ����� ������\n������� 1: "; cin>>n1;
	cout<<"������� 2: "; cin>>n2;
	if(n1 == n2){
		cout<<"���� �� ������ ��������� ������\n";
		return;
	}
	if(table.contain(n1))
		if(table.contain(n2)){
			v1 = table[n1];
			v2 = table[n2];
			data_e data;
			weight w;
			cout<<"������� ������ �����: "; cin>>data;
			cout<<"������� ��� �����: "; cin>>w;
			edge *e = g->InsertE(v1,v2);
			if(e){
				e->SetData(data);
				e->SetW(w);
			}else
				cout<<"����� ����� ��� ���� � �����\n";
		}else
			cout<<"� ����� ��� ������� "<<n2<<endl;
	else
		cout<<"� ����� ��� ������� "<<n1<<endl;
}

void deleteV(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	name n;
	cout<<"������� ��� �������: "; cin>>n;
	if(table.contain(n)){
		g->DeleteV(table[n]);
		table.remove(n);
	}
	else
		cout<<"����� ������� ��� � �����\n";
}

void deleteE(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	vertex *v1,*v2;
	name n1,n2;
	cout<<"������� ����� ������\n������� 1: "; cin>>n1;
	cout<<"������� 2: "; cin>>n2;
	if(table.contain(n1))
		if(table.contain(n2)){
			v1 = table[n1];
			v2 = table[n2];
			if(g->DeleteE(v1, v2))
				cout<<"�����\n";
			else
				cout<<"����� ������� ��������� ��� �����\n";
		}else
			cout<<"� ����� ��� ������� "<<n2<<endl;
	else
		cout<<"� ����� ��� ������� "<<n1<<endl;
}

void getE(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	vertex *v1,*v2;
	name n1,n2;
	cout<<"������� ����� ������\n������� 1: "; cin>>n1;
	cout<<"������� 2: "; cin>>n2;
	if(table.contain(n1))
		if(table.contain(n2)){
			v1 = table[n1];
			v2 = table[n2];
			edge *e = g->GetEdge(v1, v2);
			if(e){
				cout<<"������: "<<e->GetData()<<endl;
				cout<<"���: "<<e->GetW()<<endl;
			}else
				cout<<"����� ������� ��������� ��� �����\n";
		}else
			cout<<"� ����� ��� ������� "<<n2<<endl;
	else
		cout<<"� ����� ��� ������� "<<n1<<endl;
}

void getVcnt(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	cout<<"����� ������: "<<g->V()<<endl;
}

void getEcnt(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	cout<<"����� �����: "<<g->E()<<endl;
}

void directed(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	bool d = g->Directed();
	if(d)
		cout<<"���� ���������������\n";
	else
		cout<<"���� ����������������\n";
}

void dense(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	bool d = g->Dense();
	if(d)
		cout<<"L-����\n";
	else
		cout<<"�-����\n";
}

void K(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	cout<<"����������� ������������: "<<g->K()<<endl;
}

void toLgraph(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	g->ToListGraph();
}

void toMgraph(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	g->ToMatrixGraph();
}

void iteratorV(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	printmenuItV();
	graph::vertex_iterator i = g->endV();
	int red;
	bool exec = true;
	while(exec){
		cin>>red;
		switch(red){
			case 1:{
				graph::vertex_iterator it = g->beginV();
				cout<<"Name\tData\n";
				for(; it != g->endV(); ++it){
					vertex *v = *it;
					cout<<v->GetName()<<"\t"<<v->GetData()<<endl;
				}
				break;
				   }
			case 2:{
				i = g->beginV();
				break;
				   }
			case 3:{
				try{
					++i;
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			case 4:{
				try{
					vertex *v = *i;
					cout<<"Name\tData\n";
					cout<<v->GetName()<<"\t"<<v->GetData()<<endl;
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			case 5:{
				try{
					vertex *v = *i;
					name old_name = v->GetName();
					name n;
					cout<<"����� ���: "; cin>>n;
					v->SetName(n);
					table.remove(old_name);
					table.put(n,v);
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			case 6:{
				try{
					vertex *v = *i;
					data_v data;
					cout<<"����� ������: "; cin>>data;
					v->SetData(data);
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			default:
				exec = false;
		}
	}
	printmenu();
}

void iteratorE(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	printmenuItE();
	graph::edge_iterator i = g->beginE();
	int red;
	bool exec = true;
	while(exec){
		cin>>red;
		switch(red){
			case 1:{
				graph::edge_iterator it = g->beginE();
				cout<<"Edge\tData\tWeight\n";
				for(; it != g->endE(); ++it){
					edge *e = *it;
					vertex *v1 = e->getV1(); name n1 = v1->GetName();
					vertex *v2 = e->getV2(); name n2 = v2->GetName();
					cout<<'('<<n1<<','<<n2<<")\t";
					cout<<e->GetData()<<"\t"<<e->GetW()<<endl;
				}
				break;
				   }
			case 2:{
				i = g->beginE();
				break;
				   }
			case 3:{
				try{
					++i;
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			case 4:{
				try{
					edge *e = *i;
					cout<<"Edge\tData\tWeight\n";
					vertex *v1 = e->getV1(); name n1 = v1->GetName();
					vertex *v2 = e->getV2(); name n2 = v2->GetName();
					cout<<'('<<n1<<','<<n2<<")\t";
					cout<<e->GetData()<<"\t"<<e->GetW()<<endl;
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			case 5:{
				try{
					edge *e = *i;
					data_e data;
					cout<<"����� ������: "; cin>>data;
					e->SetData(data);
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			case 6:{
				try{
					edge *e = *i;
					weight w;
					cout<<"����� ���: "; cin>>w;
					e->SetW(w);
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			default:
				exec = false;
		}
	}
	printmenu();
}

void iteratorEout(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	printmenuItEout();
	map<name,vertex*>::iterator q = table.begin();
	graph::out_edge_iterator i = g->endEout(q->second);
	int red;
	bool exec = true;
	while(exec){
		cin>>red;
		switch(red){
			case 1:{
				name n;
				cout<<"������� ��� �������: "; cin>>n;
				if(!table.contain(n)) {
					cout<<"������� � ����� ������ �� ����������\n";
					break;
				}
				graph::out_edge_iterator it = g->beginEout(table[n]);
				cout<<"Edge\tData\tWeight\n";
				for(; it != g->endEout(table[n]); ++it){
					edge *e = *it;
					vertex *v1 = e->getV1(); name n1 = v1->GetName();
					vertex *v2 = e->getV2(); name n2 = v2->GetName();
					cout<<'('<<n1<<','<<n2<<")\t";
					cout<<e->GetData()<<"\t"<<e->GetW()<<endl;
				}
				break;
				   }
			case 2:{
				graph::vertex_iterator i = g->beginV();
				graph::out_edge_iterator j = g->beginEout(*i);
				for(; i != g->endV(); ++i){
					vertex *v = *i;
					j = g->beginEout(v);
					cout<<v->GetName()<<": ";
					for(; j != g->endEout(v); ++j){
						edge *e = *j;
						name n1 = e->getV1()->GetName();
						name n2 = e->getV2()->GetName();
						cout<<'('<<n1<<','<<n2<<") ";
					}
					cout<<endl;
				}
				break;
				   }
			case 3:{
				name n;
				cout<<"������� ��� �������: "; cin>>n;
				if(!table.contain(n)) {
					cout<<"������� � ����� ������ �� ����������\n";
					break;
				}
				i = g->beginEout(table[n]);
				break;
				   }
			case 4:{
				try{
					++i;
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			case 5:{
				try{
					edge *e = *i;
					cout<<"Edge\tData\tWeight\n";
					vertex *v1 = e->getV1(); name n1 = v1->GetName();
					vertex *v2 = e->getV2(); name n2 = v2->GetName();
					cout<<'('<<n1<<','<<n2<<")\t";
					cout<<e->GetData()<<"\t"<<e->GetW()<<endl;
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			case 6:{
				try{
					edge *e = *i;
					data_e data;
					cout<<"����� ������: "; cin>>data;
					e->SetData(data);
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			case 7:{
				try{
					edge *e = *i;
					weight w;
					cout<<"����� ���: "; cin>>w;
					e->SetW(w);
				}catch(NoSuchElementException){
					cout<<"�������� �� ����������\n";
				}
				break;
				   }
			default:
				exec = false;
		}
	}
	printmenu();
	
}

void solveTask1(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	cout<<"******************������� ������ 1********************\n";
	try{
		task1 t(g);
		Graph<r_vertex,r_edge> *res = t.Result();
		Graph<r_vertex,r_edge>::vertex_iterator iV = res->beginV();
		cout<<"��������� ��������������� �����\n";
		res->print();
		
		cout<<"\n���������� ������ � �����\n";
		for(int k = 1; iV != res->endV(); ++iV, k++){
			task1::reduce_vertex *v = *iV;
			list<vertex*> *l = v->GetData();
			list<vertex*>::iterator iRV = l->begin();
			cout<<(*iV)->GetName()<<": ";
			for(; iRV != l->end(); ++iRV)
				cout<<(*iRV)->GetName()<<' ';
			cout<<endl;
		}
		cout<<endl<<endl;
		for(Graph<r_vertex,r_edge>::edge_iterator iE = res->beginE(); iE != res->endE(); ++iE){
			task1::reduce_edge *e = *iE;
			list<edge*> *l = e->GetData();
			list<edge*>::iterator i = l->begin(); 
			cout<<'('<<e->getV1()->GetName()<<' '<<e->getV2()->GetName()<<"): ";
			for(; i != l->end(); ++i){
				edge *E = *i;
				cout<<'('<<E->getV1()->GetName()<<','<<E->getV2()->GetName()<<") ";
			}
			cout<<endl;
		}
		//iteratorEout(res);
		cout<<"******************************************************\n\n";
	}catch(NotDirectedGraphException){
		cout<<"���� ������ ���� ���������������\n";
	}
}

void solveTask2(graph *g){
	if(!g){
		cout<<"�������� ����\n";
		return;
	}
	int v1,v2;
	cout<<"������� ����� ������\n";
	cout<<"������� 1: "; cin>>v1;
	cout<<"������� 2: "; cin>>v2;
	cout<<"******************������� ������ 2********************\n";
	try{
		Task2<vertex,edge> t2(g,table[v1],table[v2]);
		list<edge*> *edges = t2.Result();
		cout<<"�����: ";
		for(list<edge*>::iterator it = edges->begin(); it != edges->end(); ++it)
			cout<<'('<<(*it)->getV1()->GetName()<<' '<<(*it)->getV2()->GetName()<<") ";
		cout<<endl;
		cout<<"���������� ���� ����� ��� �������� ��������������� �����\n";
		cout<<t2.GetMaxShortestPathLength()<<endl;
		map<edge*,list<vertex*>> vec = t2.GetMaxShortestPath();
		map<edge*,list<vertex*>>::iterator i = vec.begin();
		for(; i != vec.end(); ++i){
			edge *e = i->first;
			cout<<'('<<e->getV1()->GetName()<<' '<<e->getV2()->GetName()<<"): ";
			printPath(i->second);
		}
		cout<<"���������� �� �������� �����\n����� ����������� ����: "<<t2.GetShortestPathLength()<<endl;
		cout<<"���������� ����: ";
		list<vertex*> shortest_path = t2.GetShortestPath();
		printPath(shortest_path);
		cout<<"******************************************************\n\n";
	}catch(VertexNotExistException){
		cout<<"������� 1 ��� 2 ��� � �����\n";
	}
}

void main(){
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	printmenu();
	graph *g = NULL;
	int red;
	while(1){
		cin>>red;
		switch(red){
			case 1: 
				if(!g) delete g;
				g = createGraph(); 
				break;
			case 2: 
				insertV(g); 
				break;
			case 3: 
				insertE(g); 
				break;
			case 4: 
				deleteV(g);
				break;
			case 5:
				deleteE(g);
				break;
			case 6:
				getE(g);
				break;
			case 7:
				getVcnt(g);
				break;
			case 8:
				getEcnt(g);
				break;
			case 9:
				directed(g);
				break;
			case 10:
				dense(g);
				break;
			case 11:
				K(g);
				break;
			case 12:
				toLgraph(g);
				break;
			case 13:
				toMgraph(g);
				break;
			case 14:
				iteratorV(g);
				break;
			case 15:
				iteratorE(g);
				break;
			case 16:
				iteratorEout(g);
				break;
			case 17:
				solveTask1(g);
				break;
			case 18:
				solveTask2(g);
				break;
			case 19:
				if(!g){cout<<"�������� ����\n"; break;}
				g->print();
				break;
			default:
				return;
		}
	}
	system("pause");
}