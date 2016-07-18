//#include "Graph.h"
//#include <windows.h>
//#include "MyMap.h"
//#include "Task1.h"
//#include "Task2.h"
//
//typedef Vertex<int,int> vertex;
//typedef Edge<vertex,int,int> edge;
//typedef Graph<vertex,edge> graph;
//
//void printPath(list<vertex*> s){
//	list<vertex*>::iterator i = s.begin();
//	for(; i != s.end(); ++i)
//		cout<<(*i)->GetName()<<' ';
//	cout<<endl;
//}
//
//void main(){
////	/*Graph<Vertex<int, int>, Edge<Vertex<int,int>, int, int>> g(10,false,false);
////	Vertex<int,int> *v1 = g.InsertV(); v1->SetName(10);
////	Vertex<int,int> *v2 = g.InsertV(); v2->SetName(11);
////	Vertex<int,int> *v3 = g.InsertV(); v3->SetName(12);
////	Vertex<int,int> *v4 = g.InsertV(); v4->SetName(13);
////	g.printVertexes();
////	Edge<Vertex<int,int>, int, int> *e1 = g.InsertE(v1,v2);
////	Edge<Vertex<int,int>, int, int> *e2 = g.InsertE(v1,v3);
////	Edge<Vertex<int,int>, int, int> *e3 = g.InsertE(v3,v2);
////	if(e1 == g.GetEdge(v2, v1))
////		cout<<"Done"<<endl;
////	if(g.InsertE(v1,v2) == NULL)
////		cout<<"correct"<<endl;
////	g.DeleteV(v1);
////	Vertex<int,int> *v5 = g.InsertV(); v5->SetName(14);
////	g.printVertexes();
////	cout<<g.GetEdge(v1,v2)<<endl;
////	cout<<g.GetEdge(v1,v3)<<endl;
////	cout<<g.GetEdge(v2,v3)<<' '<<e3<<endl;
////	cout<<g.DeleteE(v2,v1)<<endl;
////	g.printVertexes();
////	cout<<g.GetEdge(v2,v3)<<' '<<e3<<endl;
////	cout<<"Удаление ребра\n"<<g.DeleteE(v3,v2)<<endl;
////	cout<<g.GetEdge(v2,v3)<<' '<<e3<<endl;
////	graph g(5,100,false,true);
////	g.ToMatrixGraph();
////	cout<<"V: "<<g.V()<<endl;
////	cout<<"E: "<<g.E()<<endl;
////	graph::vertex_iterator it = g.beginV();
////	for(;it != g.endV(); ++it)
////		cout<<(*it)->GetName()<<endl;	 
////	
////	for(it = g.beginV(); it != g.endV(); ++it){
////		Vertex<int,int> *v = *it;
////		cout<<v->GetName()<<" : ";
////		graph::out_edge_iterator outedge_it = g.beginEout(v);
////		for(; outedge_it != g.endEout(v); ++outedge_it){
////			edge *e = *outedge_it;
////			int v1 = e->getV1()->GetName();
////			int v2 = e->getV2()->GetName();
////			cout<<'('<<v1<<','<<v2<<") ";
////		}
////		cout<<endl;
////	}
////
////	graph::edge_iterator edge_it = g.beginE();
////	for(;edge_it != g.endE(); ++edge_it){
////		edge *e = *edge_it;
////		int v1 = e->getV1()->GetName();
////		int v2 = e->getV2()->GetName();
////		cout<<v1<<' '<<v2<<endl;
////	}
////
////	for(it = g.beginV(); it != g.endV(); ++it){
////		Vertex<int,int> *v = *it;
////		cout<<v->GetName()<<" : ";
////		Graph<Vertex<int, int>, Edge<Vertex<int,int>, int, int>>::out_edge_iterator outedge_it = g.beginEout(v);
////		for(; outedge_it != g.endEout(v); ++outedge_it){
////			Edge<Vertex<int,int>, int, int> *e = *outedge_it;
////			int v1 = e->getV1()->GetName();
////			int v2 = e->getV2()->GetName();
////			cout<<'('<<v1<<','<<v2<<") ";
////		}
////		cout<<endl;
////	}*/
////
////	graph g(0,true,true);
////	/*vertex *v1 = g.InsertV(); v1->SetName(1);
////	vertex *v2 = g.InsertV(); v2->SetName(2);
////	vertex *v3 = g.InsertV(); v3->SetName(3);
////	vertex *v4 = g.InsertV(); v4->SetName(4);
////	g.InsertE(v1, v2);
////	g.InsertE(v1, v4);
////	g.InsertE(v2, v3);
////	g.InsertE(v3, v1);
////	g.InsertE(v3, v4);*/
//	//MyMap<int,vertex*> m;
//	//graph g(0,true,true);
//	//int N = 8;
//	//for(int i = 0; i < N; i++){
//	//	vertex *v = g.InsertV();
//	//	v->SetName(i);
//	//	m.put(i, v);
//	//}
////	vertex *v = m[1];
////	g.InsertE(m[0],m[1]);
////	g.InsertE(m[0],m[5]);
////	g.InsertE(m[0],m[6]);
////	g.InsertE(m[2],m[0]);
////	g.InsertE(m[2],m[3]);
////	g.InsertE(m[3],m[2]);
////	g.InsertE(m[3],m[5]);
////	g.InsertE(m[4],m[2]);
////	g.InsertE(m[4],m[11]);
////	g.InsertE(m[5],m[4]);
////	g.InsertE(m[6],m[4]);
////	g.InsertE(m[6],m[9]);
////	g.InsertE(m[7],m[6]);
////	g.InsertE(m[7],m[8]);
////	g.InsertE(m[8],m[7]);
////	g.InsertE(m[8],m[9]);
////	g.InsertE(m[9],m[10]);
////	g.InsertE(m[9],m[11]);
////	g.InsertE(m[10],m[12]);
////	g.InsertE(m[11],m[12]);
////	g.InsertE(m[12],m[9]);
////	/*g.InsertE(m[0],m[1]);
////	g.InsertE(m[1],m[2]);
////	g.InsertE(m[2],m[0]);
////	g.InsertE(m[1],m[3]);*/
////	Task1<vertex,edge> t(&g);
////	Graph<Task1<vertex,edge>::reduce_vertex,Task1<vertex,edge>::reduce_edge> *res = t.Result();
////	Graph<Task1<vertex,edge>::reduce_vertex,Task1<vertex,edge>::reduce_edge>::vertex_iterator iV = res->beginV();
////	
////	for(int k = 1; iV != res->endV(); ++iV, k++){
////		Task1<vertex,edge>::reduce_vertex *v = *iV;
////		list<vertex*> *l = v->GetData();
////		list<vertex*>::iterator iRV = l->begin();
////		cout<<"SCvertex"<<k<<": ";
////		for(; iRV != l->end(); ++iRV)
////			cout<<(*iRV)->GetName()<<' ';
////		cout<<endl;
////		cout<<"SCoutedge"<<k<<": ";
////		Graph<Task1<vertex,edge>::reduce_vertex,Task1<vertex,edge>::reduce_edge>::out_edge_iterator iOE = res->beginEout(*iV);
////		for(; iOE != res->endEout(*iV); ++iOE){
////			list<edge*> *l = (*iOE)->GetData();
////			list<edge*>::iterator iRE = l->begin();
////			for(; iRE != l->end(); ++iRE)
////				cout<<'('<<(*iRE)->getV1()->GetName()<<','<<(*iRE)->getV2()->GetName()<<") ";
////			
////		}
////		cout<<endl;
////	}
////
////
///*тестрование второй задачи*/
//	edge *e = NULL;
//	//e = g.InsertE(m[8],m[0]); e->SetW(1);
//	//e = g.InsertE(m[8],m[1]); e->SetW(1);
//	//e = g.InsertE(m[0],m[1]); e->SetW(1);
//	//e = g.InsertE(m[0],m[2]); e->SetW(100);
//	//e = g.InsertE(m[1],m[4]); e->SetW(1);
//	//e = g.InsertE(m[5],m[2]); e->SetW(1);
//	//e = g.InsertE(m[3],m[0]); e->SetW(1);
//	//e = g.InsertE(m[3],m[7]); e->SetW(1);
//	//e = g.InsertE(m[2],m[7]); e->SetW(1);
//	//e = g.InsertE(m[4],m[5]); e->SetW(1);
//	//e = g.InsertE(m[4],m[2]); e->SetW(1);
//	//e = g.InsertE(m[1],m[2]); e->SetW(1);
//	//e = g.InsertE(m[5],m[6]); e->SetW(1);
//	//e = g.InsertE(m[6],m[7]); e->SetW(1);
//	MyMap<int,vertex*> m;
//	graph g(0,true,true);
//	int N = 8;
//	for(int i = 0; i < N; i++){
//		vertex *v = g.InsertV();
//		v->SetName(i);
//		m.put(i, v);
//	}
//	e = g.InsertE(m[0],m[2]); e->SetW(10);
//	e = g.InsertE(m[1],m[2]); e->SetW(5);
//	e = g.InsertE(m[1],m[4]); e->SetW(7);
//	e = g.InsertE(m[2],m[6]); e->SetW(11);
//	e = g.InsertE(m[3],m[6]); e->SetW(20);
//	e = g.InsertE(m[4],m[1]); e->SetW(6);
//	e = g.InsertE(m[5],m[1]); e->SetW(1);
//	e = g.InsertE(m[5],m[3]); e->SetW(14);
//	e = g.InsertE(m[5],m[7]); e->SetW(3);
//	e = g.InsertE(m[6],m[0]); e->SetW(12);
//
//	//g.DeleteE(m[2],m[7]);
//	g.print();
//	Task2<vertex,edge> t2(&g,m[5],m[0]);
//	cout<<"Shortest path: ";
//	list<vertex*> shortest_path = t2.GetShortestPath();
//	printPath(shortest_path);
//	list<edge*> edges = t2.Result();
//	for(list<edge*>::iterator it = edges.begin(); it != edges.end(); ++it)
//		cout<<'('<<(*it)->getV1()->GetName()<<' '<<(*it)->getV2()->GetName()<<") ";
//	cout<<endl;
//	/*list<vertex*> l = t2.Result();
//	list<vertex*>::iterator it = l.begin();
//	for(; it != l.end(); ++it)
//		cout<<(*it)->GetName()<<' ';
//	cout<<endl;*/
//	cout<<t2.GetMaxShortestPathLength()<<endl;
//	map<edge*,list<vertex*>> vec = t2.GetMaxShortestPath();
//	map<edge*,list<vertex*>>::iterator i = vec.begin();
//	for(; i != vec.end(); ++i){
//		edge *e = i->first;
//		cout<<'('<<e->getV1()->GetName()<<' '<<e->getV2()->GetName()<<") ";
//		printPath(i->second);
//	}
//	//graph g2 = g;
//	//g.DeleteV(m[0]);
//	//g.print();
//	//g2.print();
//	system("pause");
//}