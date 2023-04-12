//============================================================================
// Name        : DataStructure.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#ifndef ElemType
#define ElemType int
#endif

class binary_tree {
private:
	const int MAXSIZE = 10;
public:
	struct TreeNode {
		ElemType value;
		bool isEmpty;
	};

	typedef struct BiTNode {
		ElemType data;
		struct BiTNode *lchild, *rchild;
	} BiTNode, *BiTree;

	void InitBiTree(BiTree &root) {
		root = NULL;
		root = (BiTree) malloc(sizeof(BiTNode));
		root->data = 1;
		root->lchild = NULL;
		root->rchild = NULL;
	}

	bool InsertBiTNode(BiTree &root, ElemType val) {
		BiTNode *new_node = (BiTNode*) malloc(sizeof(BiTNode));
		if (root->lchild == NULL) {
			root->lchild = new_node;
			new_node->data = val;
			new_node->lchild = NULL;
			new_node->rchild = NULL;
		} else if (root->rchild == NULL) {
			root->rchild = new_node;
			new_node->lchild = NULL;
			new_node->rchild = NULL;
			new_node->data = val;
		} else {
			std::cout << "Invalid root!" << endl;
			return false;
		}

		return true;
	}
	void observe(BiTree T) {
		cout << T->data << endl;
	}

	void PreOrder(BiTree T) {
		if (T != NULL) {
			observe(T);
			PreOrder(T->lchild);
			PreOrder(T->rchild);
		}
	}

	void InOrder(BiTree T) {
		if (T != NULL) {
			InOrder(T->lchild);
			observe(T);
			InOrder(T->rchild);
		}
	}

	void PostOrder(BiTree T) {
		if (T != NULL) {
			PostOrder(T->lchild);
			PostOrder(T->rchild);
			observe(T);
		}
	}

	void LevelOrder(BiTree T);
};

template<typename T, int Size>
class Stack {
private:
	T data[Size];
	int top;
public:
	Stack() :
			top(-1) {

	}
	~Stack() {

	}

	bool push(T item) {
		if (top == Size - 1) {
			return false;
		}
		data[++top] = item;
		return true;
	}

	bool pop(T &topElem) {
		if (top == -1)
			return false;
		topElem = data[top--];
		return true;
	}

	bool getTop(T &topElem) {
		if (top == -1)
			return false;
		topElem = data[top];
		return true;
	}

	bool isEmpty() {
		return top == -1;
	}

	bool isFull() {
		return top == Size - 1;
	}
};

template<typename T, int Size>
class Queue {
private:
	T data[Size];
	int front, rear;
	int tag;
public:
	Queue() :
			front(0), rear(0), tag(0) {
	}

	~Queue() {
	}

	bool EnQueue(T item) {
		if (front == rear && tag == 1)
			return false;
		rear = (rear + 1) % Size;
		data[rear] = item;
		tag = 1;

		return true;
	}

	bool DeQueue(T &item) {
		if (front == rear && tag == 0)
			return false;
		item = data[front];
		front = (front + 1) % Size;
		tag = 0;
		return true;
	}

	bool isEmpty() {
		return front == rear && tag == 0;
	}

	bool isFull() {
		return front == rear && tag == 1;
	}
};

void binary_tree::LevelOrder(BiTree T) {
	Queue<BiTree, 20> queue;
	BiTree p = NULL;
	queue.EnQueue(T);

	while (!queue.isEmpty()) {
		queue.DeQueue(p);
		observe(p);
		if (p->lchild != NULL)
			queue.EnQueue(p->lchild);
		if (p->rchild != NULL)
			queue.EnQueue(p->rchild);
	}
}

class myString {
private:
	static const int MAXLEN = 255;
public:
	typedef struct {
		char ch[MAXLEN];
		int length;
	} SString;

	typedef struct {
		char *ch;
		int length;
	} HString;

	bool InitHString(HString &S) {
		S.ch = (char*) malloc(sizeof(MAXLEN * sizeof(char)));
		if (S.ch == NULL)
			return false;
		S.length = 0;
		return true;
	}

	typedef struct StringNode {
		char ch[4];
		struct StringNode *next;
	} StringNode, *String;

	bool SubString(SString &sub, SString S, int pos, int len) {
		if (pos + len - 1 > S.length)
			return false;
		for (int i = pos; i < pos + len; i++) {
			sub.ch[i - pos + 1] = S.ch[i];
		}
		sub.length = len;
		return true;
	}

	bool StrCompare(SString S, SString T) {
		for (int i = 1; i <= S.length && i <= T.length; i++) {
			if (S.ch[i] != T.ch[i])
				return S.ch[i] - T.ch[i];
		}

		return S.length - T.length;
	}

	int StrLength(SString S) {
		return S.length;
	}

	int Index(SString S, SString T) {
		int i = 1, j = 1;
		while (i <= S.length && j <= T.length) {
			if (S.ch[i] == T.ch[j]) {
				++i;
				++j;
			} else {
				i = i - j + 2;
				j = 1;
			}
		}
		if (j > T.length)
			return i - T.length;
		else
			return 0;
	}

	int Index_KMP(SString S, SString T, int next[]) {
		int i = 1, j = 1;
		while (i <= S.length && j <= T.length) {
			if (j == 0 || S.ch[i] == T.ch[j]) {
				++i;
				++j;
			} else
				j = next[j];
		}

		if (j > T.length)
			return i - T.length;
		else
			return 0;
	}

	int* next2nextval(SString T, int next[]) {
		int *nextval = (int*) malloc(T.length * sizeof(char));
		nextval[1] = 0;
		for (int j = 2; j <= T.length; j++) {
			if (T.ch[next[j]] == T.ch[j])
				nextval[j] = nextval[next[j]];
			else
				nextval[j] = next[j];
		}

		return nextval;
	}

};

class Thread_Tree {
private:
	typedef struct BiTNode {
		ElemType data;
		struct BiTNode *lchild, *rchild;
	} BiTNode, *BiTree;

	typedef struct ThreadNode {
		ElemType data;
		struct ThreadNode *lchild, *rchild;
		int ltag, rtag;
	} ThreadNode, *ThreadTree;
	/*tag == 0:point to child ;tag == 1:point to thread*/
public:
	ThreadNode *pre = NULL;

	void visit(ThreadNode *q) {
		if (q->lchild == NULL) {
			q->lchild = pre;
			q->ltag = 1;
		}
		if (pre != NULL && pre->rchild == NULL) {
			pre->rchild = q;
			pre->rtag = 1;
		}
		pre = q;
	}

	void InThread(ThreadTree p, ThreadTree &pre) {
		if (p != NULL) {
			InThread(p->lchild, pre);
			if (p->lchild == NULL) {
				p->lchild = pre;
				p->ltag = 1;
			}

			if (pre != NULL && pre->rchild == NULL) {
				pre->rchild = p;
				pre->rtag = 1;
			}
		}

		pre = p;
		InThread(p->rchild, pre);
	}

	void CreateInThread(ThreadTree T) {
		ThreadTree pre = NULL;
		if (T != NULL) {
			InThread(T, pre);
			pre->rchild = NULL;
			pre->rtag = 1;
		}
	}

	void PreThread(ThreadTree T) {
		//actually thread will destroy the original relationship between parent and lchild.
		//so we need the tag to determine whether we should activate the PreThread() function.
		if (T != NULL) {
			visit(T);
			if (T->ltag == 0)
				PreThread(T->lchild);
			PreThread(T->rchild);
		}
	}

	void CreatePreThread(ThreadTree T) {
		pre = NULL;
		if (T != NULL) {
			PreThread(T);
			if (pre->rchild == NULL)
				pre->rtag = 1;
		}
	}

	void PostThread(ThreadTree p, ThreadTree &pre) {
		if (p != NULL) {
			PostThread(p->lchild, pre);
			PostThread(p->rchild, pre);
			if (p->lchild == NULL) {
				p->lchild = pre;
				p->ltag = 1;
			}

			if (pre != NULL && pre->rchild == NULL) {
				pre->rchild = p;
				pre->rtag = 1;
			}

			pre = p;
		}
	}

	void CreatePostThread(ThreadTree T) {
		ThreadTree pre = NULL;
		if (T != NULL) {
			PostThread(T, pre);
			if (pre->rchild == NULL)
				pre->rtag = 1;
		}
	}

	ThreadNode* FirstNode(ThreadNode *p) {
		while (p->ltag == 0)
			p = p->lchild;
		return p;
	}

	ThreadNode* NextNode(ThreadNode *p) {
		if (p->rtag == 0)
			return FirstNode(p->rchild);
		else
			return p->rchild;
	}

	void InOreder(ThreadNode *T) {
		for (ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p))
			visit(p);
	}

	ThreadNode* LastNode(ThreadNode *p) {
		while (p->rtag == 0)
			p = p->rchild;
		return p;
	}

//	//reverse InOrder in in-order thread-tree
//	void RevInOrder(ThreadNode *T){
//		for(ThreadNode *p = LastNode(T);p != NULL;p = PreNode(p))
//			visit(p);
//	}
};

namespace Tree {
class Tree {
private:
	static const int MAX_TREE_SIZE = 100;

	typedef struct {
		ElemType data;
		int parent;
	} PTNode;

	typedef struct {
		PTNode nodes[MAX_TREE_SIZE];
		int n;						//the number of nodes
	} PTree;

	struct CTNode {
		ElemType child;
		struct CTNode *next;  		//the next sibling of the child
	};

	typedef struct {
		ElemType data;
		struct CTNode *firstchild;
	} CTBox;

	typedef struct {
		CTBox nodes[MAX_TREE_SIZE];
		int n, r;					//num of nodes and loc of root
	} CTree;

	typedef struct CSNode {
		ElemType data;
		struct CSNode *firstchild, *nextsibling; //第一个孩子指针，右兄弟指针
												 //指的是当前节点的兄弟，而不是第二个孩子
	} CSNode, *CSTree;

public:

};
}

namespace UFDS {
class Union_Find_Disjoint_Sets {
private:
	static const int MAX_TREE_SIZE = 100;
	typedef struct {
		ElemType data;
		int parent;
	} PTNode;

	typedef struct {
		PTNode nodes[MAX_TREE_SIZE];
		int n;									//节点数
	} PTree;
public:
	const int SIZE = 13;

	//初始化
	void Inital(int S[]) {
		for (int i = 0; i < SIZE; i++) {
			S[i] = -1;
		}
	}

	//
	int Find(int S[], int x) {
		while (S[x] >= 0) {
			x = S[x];
		}
		return x;
	}

	//
	void Union(int S[], int Root1, int Root2) {
		if (Root1 == Root2)
			return;
		if (S[Root1] < S[Root2]) {
			//S[Root1] < S[Root2] => |S[Root1]| > |S[Root2]|
			S[Root1] += S[Root2];
			S[Root2] = Root1;
		} else {
			S[Root2] += S[Root1];
			S[Root1] = Root2;
		}
	}

	int BetterFind(int S[], int x) {
		int root = x;
		while (S[root] > 0)
			root = S[root];
		while (x != root) {
			int temp = S[x];
			S[x] = root;
			x = temp;
		}
		return root;
	}

	//阿克曼函数。该函数的反函数描述了高度随着n的变化
	//AckFun(4,4) = 2^(2^(10^19729)),所以一般情况下\alpha(n) < 5
	int AckFun(int n, int m) {
		if (m == 0)
			return n + 1;
		else if (n == 0) {
			return AckFun(m - 1, 1);
		} else
			return AckFun(m - 1, AckFun(n, m - 1));
	}

};
}
class Graphic {
private:
	static const int MaxVertexNum = 100;
	static const int Infinity = 2147483647;

//	typedef struct{
//		char Vex[MaxVertexNum];					//顶点表
//		int Edge[MaxVertexNum][MaxVertexNum];	//边
//		int vexnum,arcnum;						//顶点数和弧数
//	}MGraph;

	typedef int VertexType;
	typedef int EdgeType;

	/*邻接矩阵存储图结构*/
	typedef struct {
		VertexType Vex[MaxVertexNum];
		EdgeType Edge[MaxVertexNum][MaxVertexNum];
		int vexnum, arcnum;
		bool tag[MaxVertexNum][MaxVertexNum];		//标记数据是否为空
	} MGraph;

	/*邻接表法存储图结构*/
	//definition of arc
	typedef struct ArcNode {
		int adjvex;						//该弧节点指向的顶点节点
		struct ArcNode *next;			//指向下一個共弧尾的弧节点
	} ArcNode;

	//definition of Node
	typedef struct VNode {
		VertexType data;				//数据域
		ArcNode *first;					//指向第一个邻接节点
	} VNode, AdjList[MaxVertexNum];

	typedef struct {
		AdjList vertices;
		int vexnum, arcnum;
	} ALGraph;

	/*十字链表法存储图结构*/
	typedef struct XArcNode {
		int tailvex, headvex;
		struct XArcNode *iLink, *jLink;	//指向依附于起点(i)的下一条边
										//指向依附于终点(j)的下一条边
		int info;						//权值
	} XArcNode, *XArcNodePtr;

	typedef struct XVexNode {
		VertexType data;				//数据域
		XArcNodePtr firstedge;			//与该顶点相连的第一条边
	} XVexNode;

	typedef struct {
		XVexNode xlist[MaxVertexNum];
		int vexnum, arcnum;				//顶点数，弧数
	} OLGraph;
public:
	bool Adjacent(MGraph G, VertexType x, VertexType y);

	//vector<VertexType> *Neighbors(MGraph G, VertexType x);

	bool InsertVertex(MGraph &G, VertexType x);

	bool DeleteVertex(MGraph &G, VertexType &x);

	bool AddEdge(MGraph &G, VertexType x, VertexType y);

	//图G中顶点X的第一个邻接点
	VertexType FirstNeighbor(MGraph G, VertexType x);

	//图G中顶点X的第一个邻接点为Y，求下一個邻接点
	VertexType NextNeighbor(MGraph G, VertexType x, VertexType y);

	int Get_edge_value(MGraph G, VertexType x, VertexType y);

	//设置G中<x,y>或者(x,y)的权值为v
	bool Set_edge_value(MGraph G, VertexType x, VertexType y, int v);

	bool visited[MaxVertexNum];

	void InitVisited() {
		for (int i = 0; i < MaxVertexNum; i++) {
			visited[MaxVertexNum] = false;
		}
	}

	void visit(VertexType v) {
		std::cout << v << endl;
	}

	//从顶点v开始进行广度优先遍历
	void BFS(MGraph G, VertexType v);

	void BFSTraverse(MGraph G) {
		InitVisited();
		//Queue<VertexType,MaxVertexNum>queue;
		for (int i = 0; i < G.vexnum; ++i) {
			//如果该图结构有多个连通分量，需要多次执行
			if (!visited[i]) {
				BFS(G, i);
			}
		}
	}

	void DFS(MGraph G, VertexType v);

	void DFSTraverse(MGraph G) {
		//visited[]bool数组的情况应该由总体的流程控制函数来决定。
		InitVisited();
		for (VertexType v = 0; v < G.vexnum; ++v) {
			if (!visited[v]) {
				DFS(G, v);
			}
		}
	}

};

void Graphic::BFS(MGraph G, VertexType v) {
	//InitVisited的权限应该交给BFSTraverse来管理，否则会反复清洗已经完成的数据
	visit(v);
	visited[v] = true;
	Queue<VertexType, MaxVertexNum> queue;
	queue.EnQueue(v);
	while (!queue.isEmpty()) {
		queue.DeQueue(v);
		for (VertexType w = FirstNeighbor(G, v); w >= 0;w = NextNeighbor(G, v, w)){
			if (!visited[w]) {
				visit(w);
				visited[w] = true;
				queue.EnQueue(w);
			}//if
		}//for
	}//while
}

void Graphic::DFS(MGraph G, VertexType v) {
	visit(v);
	visited[v] = true;
	for (VertexType w = FirstNeighbor(G, v); w >= 0;
			w = NextNeighbor(G, v, w)) {
		if (!visited[w]) {
			DFS(G, w);
		}				//if
	}				//for
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
    
    //this is a simple main() function to operate.
    //focus on the classes former and figure out these data structures

	//this comment was wroten on WSL2(Ubuntu-22.04 LTS).
	//the experience is : edit your personal file on Windows
	//and it will also work if you launch VS Code on WSL2.
	//PUSH IT on 2023.04.12
}