#include <iostream>

using namespace std;

#ifndef ElemType
#define ElemType int
#endif

class List {
private:
    static const int MaxSize = 50;
    static const int InitSize = 10;
    //数据类型为ElemType, 长度为MaxSize的静态线性表
    typedef struct {
        ElemType data[MaxSize];
        //静态线性表长度
        int length;
    }SqList;
    
    typedef struct {
        ElemType *data;
        int MaxSize,length;
    }SeqList;

    //单链表
    typedef struct ListNode{
        ElemType data;//数据域
        struct ListNode *next;//下一结点的指针, 地址
    }ListNode,*LinkList;
public:
    bool InitList(SeqList &L){
        L.data = (ElemType *)malloc(sizeof(ElemType) * InitSize);
        if(L.data == NULL) return false;
        L.length = 0;
        return true;
    }

    //往静态顺序表L中的第i位插入元素e
    bool ListInset(SqList &L,int i, ElemType e){
        if(i < 1 || i > L.length + 1) return false;
        if(L.length >= MaxSize) return false;
        for(int j = L.length;j >= i;j--){
            L.data[j] = L.data[j - 1];
        }
        //结束循环时,j = i - 1;
        L.data[i - 1] = e;
        L.length++;
        return true;
    }

    //删除静态顺序表L中的第i位元素,并且保存该元素的值e
    bool ListDelete(SqList &L,int i,ElemType &e){
        if(i < 1 || i > L.length) return false;
        //在删除前保存待删除元素的值
        e = L.data[i - 1];

        for(int j = i;j < L.length;j++){
            L.data[j - 1] = L.data[j];
        }
        
        L.length--;
        return true;
    }

    //在静态顺序表L中查找第一个值为e的元素的位置(第i个)
    bool LocateElem(SqList L,ElemType e){
        int i;
        for(i = 0;i < L.length; i++){
            if(L.data[i] == e) return i + 1; 
        }
        return 0;//查找失败
    }

    //头插法建立单链表L
    LinkList List_HeadInsert(LinkList &L){
        ListNode *s;
        //输入9999即为结束插入
        int x;
        L = (LinkList)malloc(sizeof(ListNode));
        L -> next = NULL;
        scanf("%d", &x);
        while(x != 9999){
            s = (ListNode *)malloc(sizeof(ListNode));
            s -> data = x;
            s -> next = L -> next;
            L -> next = s;
            scanf("%d", &x);
        }
        return L;
    }

    //尾插法建立单链表L
    LinkList List_Tailnsert(LinkList &L){
        int x;
        L = (LinkList)malloc(sizeof(ListNode));
        ListNode *s,*r = L;//r为表尾指针
        scanf("%d", &x);
        while(x!= 9999){
            s = (ListNode *)malloc(sizeof(ListNode));
            s -> data = x;
            r -> next = s;
            r = s;
            scanf("%d", &x);
        }
        r -> next = NULL;//尾指针置空
        return L;
    }

    //按照序号查找结点
    ListNode *GetElem(LinkList L,int i){
        if(i < 1)return NULL;
        int j = 1;
        ListNode *p = L -> next;
        while(p != NULL && j < i){
            p = p -> next;
            j++;
        }
        return p;
    }

    //按照值查找表结点
    ListNode *LocateElem(LinkList L, ElemType e){
        ListNode *p = L -> next;
        while(p != NULL && p -> data != e){
            p = p -> next;
        }
        return p;
    }
};

class binary_tree {
private:
    static const int MAXSIZE = 10;

    //树节点
    struct TreeNode {
        ElemType value;
        bool isEmpty;
    };

    //二叉树结点
    typedef struct BiTNode {
        ElemType data;
        struct BiTNode *lchild, *rchild;
    }BiTNode, *BiTree;
public:

    //初始化二叉树root
    void InitBiTree(BiTree &root){
        //通过置空来清洗root所在的物理空间之前存放地址
        root = NULL;
        root = (BiTree)malloc(sizeof(BiTNode));
        root -> data = 1;
        root -> lchild = NULL;
        root -> rchild = NULL;
    }


    //向二叉树root插入值为val的结点
    bool InsertBiTNode(BiTree &root, ElemType val){
        BiTNode *new_node = (BiTNode *)malloc(sizeof(BiTNode));
        if(new_node == NULL)return false;
        if(root -> lchild == NULL){
            root -> lchild = new_node;
            new_node -> data = val;
            new_node -> lchild = NULL;
            new_node -> rchild = NULL;
        }else if(root -> rchild == NULL){
            root -> rchild = new_node;
            new_node -> data = val;
            new_node -> lchild = NULL;
            new_node -> rchild = NULL;
        }else{
            std::cout << "Invalid root! " << endl;
            return false;
        }
    }

    //定义访问二叉树结点的行为
    void observe(BiTree T){
        std::cout << T -> data << endl;
    }

    //前根遍历二叉树T
    void PreOrder(BiTree T){
        if(T != NULL){
            observe(T);
            PreOrder(T -> lchild);
            PreOrder(T -> rchild);
        }
    }

    //中根遍历二叉树T
    void InOrder(BiTree T){
        if(T != NULL){
            InOrder(T -> lchild);
            observe(T);
            InOrder(T -> rchild);
        }
    }

    //后根遍历二叉树T
    void PostOrder(BiTree T){
        if(T != NULL){
            PostOrder(T -> lchild);
            PostOrder(T -> rchild);
            observe(T);
        }
    }

    //层次遍历二叉树T
    void LevelOrder(BiTree T);
};

//定义模板栈类
template<typename T,int Size>
class Stack {
private:
    T data[Size];
    int top;//记录栈顶元素位置
public:
    Stack():top(-1){

    }
    //析构函数
    ~Stack(){

    }

    //进栈元素 item
    bool push(T item){
        if(top == Size - 1)return false;
        data[++top] = item;
        return true;
    }

    //出栈元素topElem
    bool pop(T &topElem){
        if(top == -1)return false;
        topElem = data[top--];
        return true;
    }

    //读取栈顶元素
    bool getTop(T &topElem){
        if(top == -1)return false;
        topElem = data[top];
        return true;
    }

    //判断是否栈空
    bool isEmpty(){
        return top == -1;
    }

    //判断是否栈满
    bool isFull(){
        return top == Size - 1;
    }
};

//定义模板队列类
template<typename T, int Size>
class Queue{
private:
    T data[Size];
    int front, rear;
    int tag;
public:
    Queue():front(0), rear(0), tag(0){

    }

    //析构函数
    ~Queue(){

    }

    //元素item入队
    bool EnQueue(T item){
        if(front == rear && tag == 1)return false;
        rear = (rear + 1) % Size;
        data[rear] = item;
        tag = 1;
        return true;
    }

    //队列出队并记录元素item
    bool DeQueue(T &item){
        if(front == rear && tag == 0)return false;
        front = (front + 1) % Size;
        tag = 0;
        return true;
    }

    //判断队列是否为空
    bool isEmpty(){
        return front == rear && tag == 0;
    }

    //判断队列是否为满
    bool isFull(){
        return front == rear && tag == 1;
    }
};

void binary_tree::LevelOrder(BiTree T){
    Queue<BiTree,20>queue;
    BiTree p = NULL;
    queue.EnQueue(T);

    while(!queue.isEmpty()){
        queue.DeQueue(p);
        observe(p);
        if(p -> lchild != NULL){
            queue.EnQueue(p -> lchild);
        }
        if(p -> rchild != NULL){
            queue.EnQueue(p -> rchild);
        }
    }
}

//定义字符串
class myString{
private:
    //定义字符最长长度
    static const int MAXLEN = 255;

    //定义静态字符串结构体
    typedef struct {
        char ch[MAXLEN];
        int length;
    }SString;

    //定义动态字符串结构体
    typedef struct{
        char *ch;
        int length;
    }HString;

    //定义字符串结点
    typedef struct StringNode{
        char ch[4];
        struct StringNode *next;
    }StringNode, *String;

public:
    //初始化动态字符串
    bool InitHString(HString &S){
        S.ch = (char *)malloc(MAXLEN* sizeof(char));
        if(S.ch == NULL)return false;
        S.length = 0;
        return true;
    }

    //求静态字符串S中以pos为起点,长为len的子串sub
    bool SubString(SString &sub, SString S, int pos, int len){
        //子串末尾溢出原串的长度
        if(pos + len - 1 > S.length) return false;
        for(int i = pos; i < pos + len;i++){
            sub.ch[i - pos + 1] = S.ch[i];
        }
        sub.length = len;
        return true;
    }

    //比较两个串的大小
    bool StrCompare(SString S, SString T){
        for(int i = 1;i <= S.length && i <= T.length;i++){
            //首次出现差异时,进行对应位上字符的减法
            if(S.ch[i] != T.ch[i])
                return S.ch[i] - T.ch[i];
        }
        //呈现包含关系,直接用长度进行比较
        return S.length - T.length;
    }

    //查询字符串长度
    int StrLength(SString S){
        return S.length;
    }

    //使用朴素遍历方法查询子串T首次出现在S中时的位置
    int Index(SString S, SString T){
        int i = 1, j = 1;
        while(i <= S.length && j <= T.length){
            if(S.ch[i] == T.ch[i]){
                //匹配成功, i,j同步后移
                ++i;
                ++j;
            }else{
                //匹配失败, i回到原起点的下一位
                i = i - j + 2;
                j = 1;
            }
        }
        if(j > T.length) return i - T.length;
        else return 0;
    }

    //使用KMP算法,借助next[]查询子串T首次出现在S中时的位置
    int Index_KMP(SString S, SString T, int next[]){
        int i = 1, j = 1;
        while(i <= S.length && j <= T.length){
            if(j == 0 || S.ch[i] == T.ch[j]){
                ++i;
                ++j;
            }else{
                j = next[j];
            }
        }
        if(j > T.length)return i - T.length;//遍历溢出模式串长度, 说明匹配完全成功, 可以返回位置
        else return 0;
    }

    //根据next[]数组生成nextval[]数组, 从而优化KMP算法
    int *next2nextval(SString T, int next[]){
        int *nextval = (int *)malloc(T.length * sizeof(char));
        nextval[1] = 0;
        for(int j = 2; j <= T.length; j++){
            if(T.ch[next[j]] == T.ch[j]) nextval[j] = nextval[next[j]];
            else nextval[j] = next[j];
        }
        return nextval;
    }
};

//定义线索二叉树
class Thread_Tree{
private:
    //定义二叉树结点
    typedef struct BiTNode{
        ElemType data;
        struct BiTNode *lchild, *rchild;
    }BiTNode, *BiTree;

    //定义线索二叉树节点
    typedef struct ThreadNode{
        ElemType data;
        struct ThreadNode *lchild, *rchild;
        int ltag, rtag;//标记lchild,rchild是否为线索, 1为true, 0为false
    }ThreadNode, *ThreadTree;

public:
    //全局变量pre用以指定前驱结点
    ThreadNode *pre = NULL;

    //定义访问行为visit()
    void visit(ThreadNode *nodeptr){
        //没有左孩子, 空链域可存储前驱结点地址
        if(nodeptr -> lchild == NULL){
            nodeptr -> lchild = pre;
            nodeptr -> ltag = 1;
        }
        //没有右孩子,空链域可存储后继结点地址
        if(pre != NULL && pre -> rchild == NULL){
            pre -> rchild = nodeptr;
            pre -> rtag = 1;
        }
        pre = nodeptr;
    }

    //将线索二叉树形式的二叉树中序线索化
    void InThread(ThreadTree p, ThreadTree &pre){
        if(p != NULL){
            InThread(p -> lchild, pre);
            if(p -> lchild == NULL){
                p -> lchild = pre;
                p -> ltag = 1;
            }
            if(pre != NULL && pre -> rchild == NULL){
                pre -> rchild = p;
                pre -> rtag = 1;
            }
        }
        pre = p;
        InThread(p -> rchild, pre);
    }

    //创建中序二叉树
    void CreateInThread(ThreadTree &T){
        ThreadTree pre = NULL;
        if(T != NULL){
            InThread(T, pre);
            pre -> rchild = NULL;
            pre -> rtag = 1;
        }
    }

    //将线索二叉树形式的二叉树前序线索化
    void PreThread(ThreadTree &T){
    //实际上前序线索化会导致原先父子结点之间的关系遭到破坏.
    //因此需要使用tag标记来判断是否需要真正执行PreThread()函数
        if(T != NULL){
            visit(T);
            if(T -> ltag == 0){
                //只有在左孩子指针的确指向的是左子树的情况下才进行前序线索化
                PreThread(T -> lchild);
            }
            PreThread(T -> rchild);
        }
    }

    //创建前序线索二叉树T
    void CreatePreThread(ThreadTree &T){
        pre = NULL;
        if(T != NULL){
            PreThread(T);
            if(pre -> rchild == NULL){
                //pre的右子树为空, 则将其标记为后继结点的地址
                pre -> rtag = 1;
            }
        }
    }

    //将线索二叉树形式的二叉树后序线索化
    void PostThread(ThreadTree p, ThreadTree &pre){
        if(p != NULL){
            PostThread(p -> lchild, pre);
            PostThread(p -> rchild, pre);
            if(p -> rchild == NULL){
                //注意到pre实际上是可以等于NULL的,这代表着线索化循环刚从起点开始
                p -> lchild = pre;
                p -> ltag = 1;
            }
            if(pre != NULL && pre -> rchild == NULL){
                pre -> rchild = p;
                pre -> rtag = 1;
            }
            //更新pre的位置
            pre = p;
        }
    }

    //创建后序线索二叉树
    void CreatePostThread(ThreadTree &T){
        //通过空置清洗之前pre的物理空间所存储的地址
        ThreadTree pre = NULL;
        if(T != NULL){
            PostThread(T,pre);
            if(pre -> rchild == NULL){
                pre -> rtag = 1;
            }
        }
    }

    //寻找以T为根的树的最左下结点
    ThreadNode *FirstNode(ThreadNode *p){
        while(p -> ltag == 0){
            p = p -> lchild;
        }
        return p;
    }

    ////寻找中序线索二叉树的后继结点
    ThreadNode *NextNode(ThreadNode *p){
        if(p -> rtag == 0){
            return FirstNode(p -> rchild);
        }
        else{
            return p -> rchild;
        }
    }

    //利用FirstNode()和NextNode()对以T为根节点的树进行中序遍历
    void InOrder(ThreadNode *T){
        for(ThreadNode *p = FirstNode(T);p != NULL; p = NextNode(p)){
            visit(p);
        }
    }

    //寻找以p为根节点的子树中最右下的结点地址
    //可用来寻找先序前驱结点(原结点身为右孩子,其左兄弟非空)
    ThreadNode *LastNode(ThreadNode *p){
        while(p -> rtag == 0){
            p = p -> rchild;
        }
        return p;
    }

};

class Tree{
private:
    //定义树最多存储结点数
    static const int MAX_TREE_SIZE = 100;
    
    //使用双亲表示法定义树结点
    typedef struct {
        ElemType data;
        int parent;
    }PTNode;

    //用双亲表示法定义树
    typedef struct {
        PTNode nodes[MAX_TREE_SIZE];
        int n;//记录当前树中结点数
    }PTree;

    //用孩子表示法定义树结点.每个结点的孩子结点被单链表链接起来
    struct CTNode{
        ElemType child;
        struct CTNode *next;
    };

    //用孩子表示法定义
    typedef struct{
        ElemType data;
        struct CTNode *firstchild;
    }CTBox;

    //用孩子表示法定义树
    typedef struct {
        CTBox nodes[MAX_TREE_SIZE];
        int n;//目前树中结点数
        int r;//根节点位置
    }CTree;

    //用孩子-兄弟表示法表示树结点和树
    typedef struct CSNode{
        ElemType data;//数据域
        struct CSNode *firstchild;//第一个孩子指针
        struct CSNode *nextsibling;//当前结点第一个兄弟的地址
    }CSNode, *CSTree;

public:
};

//基于森林和树结构定义并查集
class Union_Find_Disjoint_Sets{
private:
    //定义树的最多储存结点数
    static const int MAX_TREE_SIZE = 100;
    
    //使用双亲表示法定义树结点, 方便溯源找到根结点
    typedef struct{
        ElemType data;
        int parent;
    }PTNode;
    
    //使用双亲表示法定义树
    typedef struct{
        PTNode nodes[MAX_TREE_SIZE];//线性表存储PTNode类型的数据
        int n;//目前树中存储的结点数
    }PTree;

    //
    static const int SIZE = 13;

public:
    //初始化并查集结构
    void Init(int S[]){
        for(int i = 0; i < SIZE; i++){
            S[i] = -1;
        }
    }

    //寻找第x个结点所对应的根节点的位序
    int Find(int S[], int x){
        while(S[x] >= 0){
            x = S[x];
        }
        return x;
    }

    //将Root1和Root2对应的树进行合并, 要求结点数少的成为多的一部分
    void Union(int S[], int Root1, int Root2){
        if(Root1 == Root2) return ;//同一结点无法合并
        if(S[Root1] < S[Root2]){
            //S[Root1] < S[Root2] 相当于|S[Root1]| > |S[Root2]|,即Root1对应的子树结点数量大于Root2
            S[Root1] += S[Root2];
            S[Root2] = Root1;
        }
        else{
            S[Root2] += S[Root1];
            S[Root1] = Root2;
        }
    }

    //优化后的寻找根节点的方法;
    //每完成一次寻找都将所查找的对象挂载到根节点下, 从而减少搜索长度
    int BetterFind(int S[],int x){
        int root = x;
        while(S[root] > 0){
            root = S[root];
        }
        while(x != root){
            int temp = S[x];
            S[x] = root;
            x = temp;
        }
        return root;
    }

    //阿克曼函数, 其反函数描述了最坏情况下的树高随着n的变化
    //AckFun(4,4)=2^(2^(10^19729)), 所以一般情况下\alpha(n)<5
    int AckFun(int n, int m){
        if(m == 0) return n + 1;
        else if (n == 0) return AckFun(m - 1, 1);
        else return AckFun(m - 1, AckFun(n, m - 1));
    }
};

class Graphic{
private:
    //最大结点数
    static const int MaxVertexNum = 100;
    //整型变量的无穷大.
    //在邻接矩阵中, 描述两个顶点之间没有边(弧)进行链接, 即用该量进行描述
    static const int Infinity = 2147483647;

#ifndef VertexType
#define VertexType int
#endif

#ifndef EdgeType
#define EdgeType int
#endif

    //邻接矩阵法存储的图结构
    typedef struct {
        VertexType Vex[MaxVertexNum];               //结点列表
        EdgeType Edge[MaxVertexNum][MaxVertexNum];  //边矩阵.元素既可以用0/1表示是否存在该边也可以用具体数值表示权值, 0/Inf表示不存在
        int vexnum;                                 //结点数
        int arcnum;                                 //边数
        bool tag[MaxVertexNum][MaxVertexNum];       //标记数据是否为空
    }MGraph;

    //邻接表法存储图结构.
    //弧
    typedef struct ArcNode{
        int adjvex;                 //弧指向的顶点结点(Vertex Node)
        struct ArcNode *next;       //下一个共弧尾(出发点)的弧的地址
    }ArcNode;

    //邻接表法存储图结构.
    //VNode为顶点表中单个顶点结点, AdjList为顶点表
    typedef struct VNode{
        VertexType data;    //数据域
        ArcNode *first;     //第一个弧的地址(弧的adjvex给出所指向的顶点的编号)
    }VNode, AdjList[MaxVertexNum];

    //邻接表法存储图结构.
    //图
    typedef struct{
        AdjList vertices;   //顶点表
        int vexnum;         //顶点数
        int arcnum;         //边(弧)数
    }ALGraph;

    //十字链表法存储图结构,该方法适用于描述有向图
    //弧结点
    typedef struct XArcNode{
        int tailvex;            //弧尾结点(起点)tail的编号
        int headvex;            //弧头结点(终点)head的编号
        struct XArcNode *tlink; //依附于相同弧尾(起点)tail的下一条边的地址
        struct XArcNode *hLink; //依附于相同弧头(终点)head的下一条边的地址
        int info;               //权值
    }XArcNode, *XArcNodePtr;

    //十字链表法存储图结构,该方法适用于描述有向图
    //顶点结点和顶点表
    typedef struct XVexNode{
        int data;               //数据域
        XArcNodePtr firstin;    //以当前节点为弧头(终点)tail的第一条弧(边)的结点位置
        XArcNodePtr firstout;   //以当前节点为弧尾(起点)head的第一条弧(边)的结点位置
    }XVexNode,XVexList[MaxVertexNum];

    //邻接多重表法存储图结构,该方法适用于描述无向图
    //MAT=Multi-Adjacency Table
    //弧(边)结点
    //为了淡化方向概念, 使用了更具有平等意味的i,j指标而非head,tail指标
    typedef struct MATArcNode{
        int ivex;                   //该弧(边)所连接的结点i的编号
        int jvex;                   //该弧(边)所连接的结点j的编号
        struct MATArcNode *ilink;   //下一条依附于结点i的地址
        struct MATArcNode *jlink;   //下一条依附于结点j的地址
        int info;                   //权值
    }MATArcNode;

    //邻接多重表法存储图结构,该方法适用于描述无向图
    //MAT=Multi-Adjacency Table
    //顶点结点, 顶点结点表
    typedef struct MATVexNode{
        int data;                           //数据域
        MATArcNode *firstedge;       //第一条依附于该顶点的边
    }MATVexNode, MATVexList[MaxVertexNum];

    //邻接多重表法存储图结构,该方法适用于描述无向图
    //MAT=Multi-Adjacency Table
    //图结构
    typedef struct MATGraph{
        MATVexList vertices;                //顶点结点表
        int vexnum;                         //顶点数
        int arcnum;                         //边数
    }MATGraph;
public:
    //查看在图G中, 顶点x 和 顶点y 是否相邻, 返回检查结果
    bool Adjacent(MGraph G, VertexType x, VertexType y);

    //向图G中插入 顶点x, 并返回是否成功
    bool InsertVertex(MGraph &G, VertexType x);

    //在图G中删除 顶点x, 并返回是否成功
    bool DeleteVertex(MGraph &G, VertexType &x);

    //在图G中,给 顶点x 和 顶点y 之间新增一条边, 并返回是否成功
    bool AddEdge(MGraph &G, VertexType x, VertexType y);

    //查询图G中, 顶点x的第一个邻接点
    VertexType FirstNeighbor(MGraph G, VertexType x);

    //查询邻接表法存储的图G中, 顶点x的第一个邻接点
    VertexType ALG_FirstNeighbor(ALGraph G, VertexType x){
        ArcNode *Arcptr = G.vertices[x].first;
        return Arcptr -> adjvex;
    }

    //已知图G中 顶点x 的第一个邻接点为 顶点y, 求下一个邻接点
    VertexType NextNeighbor(MGraph G, VertexType x, VertexType y);

    //已知邻接表法存储的图G中, 顶点x 的第一个邻接点为 顶点y, 求下一个邻接点
    VertexType ALG_NextNeighbor(ALGraph G, VertexType x, VertexType y){
        ArcNode *Arcptr = G.vertices[x].first;
        while(Arcptr -> adjvex != y){
            Arcptr = Arcptr -> next;
        }
        //如果 顶点y 并没有和 顶点x 相连, 则Arcptr停在NULL的位置
        if(Arcptr == NULL) return -1;
        //如果 顶点y 合法, 则Arcptr停在 弧头为y 的弧上
        if(Arcptr -> next == NULL)return -1;
        else return Arcptr -> next -> adjvex;
    }

    //查询邻接表法存储的图G中第i顶点的出度
    int ALG_Outdegree(ALGraph G, int i){
        ArcNode *Arcptr = G.vertices[i].first;
        int j = 0;
        while(Arcptr != NULL){
            Arcptr = Arcptr -> next;
            j++;
        }
        return j;
    }

    //查询邻接表法存储的图G中第i顶点的入度
    //对邻接表法存储的AOV网进行拓扑排序, 时间复杂度:
    //(1)需要对n个顶点进行出入栈/队列:O(n)
    //(2)检查所有e个边结点:O(e)
    //即有总时间复杂度T(n,e) = O(n + e)
    int ALG_Indegree(ALGraph G, int i){
        int j = 0;
        for(int k = 0; k < G.vexnum; k++){
            ArcNode *Arcptr = G.vertices[k].first;
            while(Arcptr != NULL){
                if(Arcptr -> adjvex == i){
                    //指针查到含有第i结点, 则计数器++, 退出本次while循环
                    j++;break;
                }
                else{
                    //没有查到, 则继续查看下一弧结点
                    Arcptr = Arcptr -> next;
                }
            }
        }
        return j;
    }

    //查询图G中 顶点x 和 顶点y 之间的边的权值
    int Get_edge_value(MGraph G, VertexType x, VertexType y);

    //设置图G中边(弧)的权值为v, 并返回是否成功
    bool Set_edge_value(MGraph G, VertexType x, VertexType y, int v);

    //bool数组, 标记顶点是否已经被访问过
    bool visited[MaxVertexNum];

    //初始化visited[]数组, 令所有结点均为被访问
    void InitVisited(){
        for(int i = 0; i < MaxVertexNum; i++){
            visited[i] = false;
        }
    }
    //访问结点v
    void visit(VertexType v){
        std::cout << v << std::endl;
    }

    //从 顶点v 出发对邻接表法存储的图G进行广度优先遍历
    void BFS(ALGraph G, VertexType v);

    //寻找邻接表法存储的非带权图G中的从点u出发到各点的最短路径长度
    void BFS_MIN_Distance(ALGraph G, int u){
        int d[G.vexnum];//距离列表d[], 表示从 点u 到 点i 的最短路径长度
        //初始化距离列表d[]
        for(int i = 0; i < G.vexnum; ++i){
            d[i] = Infinity;
        }
        visited[u] = true;
        d[u] = 0;
        Queue<int,20>queue;
        queue.EnQueue(u);
        while(!queue.isEmpty()){
            queue.DeQueue(u);
            for(int w = ALG_FirstNeighbor(G, u); w >= 0; w = ALG_NextNeighbor(G, u, w)){
                if(!visited[w]){
                    visited[w] = true;
                    d[w] = d[u] + 1;
                    queue.EnQueue(w);
                }
            }
        }
    }

    //对邻接表法存储的图G进行广度优先遍历
    void BFSTraverse(ALGraph G){
        //visited[]数组为类里全局变量, 应该交由遍历管理函数BFSTraverse()执行初始化
        InitVisited();
        for(int i = 0; i < G.vexnum; ++i){
            if(!visited[i]){
                //如果仍然存在未访问的结点i, 则从该点出发进行广度优先遍历
                //这种情况通常意味着图G中存在着多个连通分量, 所以需要多次执行
                BFS(G,i);
            }
        }
    }

    //从 顶点v 对邻接表存储的图G进行深度优先遍历
    //使用递归定义
    void DFS(ALGraph G, VertexType v);

    int **FloydMINpath(MGraph G){
        int Len = G.vexnum;
        //int A[Len][Len];    //A[i][j]表示从i到j的最短路径长度
        int **A = new int*[Len];
        for(int i = 0; i < Len; i++){
            A[i] = new int[Len];
        }
        int path[Len][Len]; //path[i][j]表示从i到j的最短路径上的第一个中间点
        //初始化A[][], path[][]
        for(int i = 0; i < Len; i++){
            for(int j = 0; j < Len; j++){
                A[i][j] = G.Edge[i][j];
                path[i][j] = -1;
            }
        }
        //第k轮新加入可用于中转的结点, 重新计算最短路径长度, 并且更新到轮次上的path[][]矩阵
        for(int k = 0; k < Len; k++){
            for(int i = 0; i < Len; i++){
                for(int j = 0; j < Len; j++){
                    if(A[i][j] > A[i][k] + A[k][j]){    //以k结点为中转点的路径更短
                        A[i][j] = A[i][k] + A[k][j];    //更新最短路径长度
                        path[i][j] = k;                 //更新中转点
                    }
                }
            }
        }
        return A;
    }

    //对有向无环图(DAG)存储的AOV网(Activity on Vertex Network)进行拓扑排序
    //拓扑排序: 每个顶点只出现一次;若A排在B前,则不存在从B到A的路径
    bool TopologicalSort(ALGraph G){
        //获取存储度为0的顶点.因为对输出顺序没有要求, 所以也可以用队列做到
        Stack<int, MaxVertexNum>stack;
        //Queue<int, MaxVertexNum>queue;

        int print[G.vexnum];//记录第i个输出的元素, 即拓扑排序中的第i位
        int i;
        for(i = 0;i < G.vexnum;i++){
            //若该结点没有前驱(即入度为0), 则令其进入输出区
            if(ALG_Indegree(G,i) == 0){
                stack.push(i);
                ArcNode *Arcptr = G.vertices[i].first;
                //清除依附于该点的所有边
                while(Arcptr != NULL){
                    ArcNode *s = Arcptr;
                    Arcptr = Arcptr -> next;
                    free(s);
                }
                G.vertices[i].first = NULL;//将其置空, 方便后续重新计算入度
            }
        }
        int count = 0;//入度计数器
        while(!stack.isEmpty()){
            stack.pop(i);
            print[count++] = i;
            for(ArcNode *p = G.vertices[i].first; p ; p -> next){
                int v = p -> adjvex;
                int indegree = ALG_Indegree(G, v);
                if(!(--indegree))stack.push(v);
            }
        }

        //检查是否存在回路
        return count < G.vexnum ? false : true;
    }

    //对有向无环图(DAG)存储的AOV网(Activity on Vertex Network)进行逆拓扑排序;
    //借助DFS算法实现
    void Anti_TopologicalSort(ALGraph G,int v){
        InitVisited();
        visited[v] = true;
        for(VertexType w = ALG_FirstNeighbor(G,v); w >= 0; w = ALG_NextNeighbor(G,v,w)){
            if(!visited[w]) DFS(G,w);
        }
        //所有后继结点均已被访问, 
        //则在该子函数在退出函数调用栈前, 输出该结点
        visit(v);
    }
};

void Graphic::BFS(ALGraph G, VertexType v){
    visit(v);
    visited[v] = true;
    Queue<VertexType, MaxVertexNum>queue;
    queue.EnQueue(v);
    while(!queue.isEmpty()){
        queue.DeQueue(v);//通过该函数来获取v
        for(VertexType w = ALG_FirstNeighbor(G,v);w>=0;w = ALG_NextNeighbor(G,v,w)){
            if((!visited[w])){
                //如果未被访问过, 标记其为已被访问, 并且将该节点入队
                visit(w);
                visited[w] = true;
                queue.EnQueue(w);
            }
        }
    }
};

void Graphic::DFS(ALGraph G, VertexType v){
    visit(v);
    visited[v] = true;
    for(VertexType w = ALG_FirstNeighbor(G,v);w>=0;w = ALG_NextNeighbor(G,v,w)){
        if(!visited[w]){
            DFS(G,w);
        }
    }
};

//定义查找类
class Find{
private:
    //查找表
    typedef struct{
        ElemType *elem; //表的地址
        int TableLen;   //表长
    }SSTable;

    // //分块查找
    // //Index为单一的分块区间索引, IndexList为分块索引表的地址
    // //(因为索引表可以用链表方式存储, 所以统一用指针代替)
    // typedef struct{
    //     ElemType maxValue;      //当前分块中元素最大值
    //     ElemType *leftEdge;     //当前分块最左边元素地址
    //     ElemType *rightEdge;    //当前分块最右边元素地址
    // }Index, *IndexList;

    //元素结点
    //即用链表方式对元素进行存储
    typedef struct ElemNode{
        ElemType value;         //数据域
        struct ElemNode *next;  //下一元素结点的地址
    }ElemNode;

    //索引区块结点
    //存储当前分块的最大值和该区块第一个元素结点的地址
    typedef struct IndexBlock{
        ElemType maxvalue;              //当前索引的分块中元素的最大值
        struct IndexBlock *nextBlock;   //下一个索引分块的结点地址
        ElemNode *firstNode;            //当前索引的分块中第一个元素的地址(即分块链表的地址)
    }IndexBlock, *IndexList;

    //二分查找
    //使用二叉树实现. 
    typedef struct BSTNode{
        ElemType key;           //当前结点比较的值
        struct BSTNode *lchild; //小于结点的关键字, 则继续往当前结点的左子树寻找
        struct BSTNode *rchild; //大于结点的关键字, 则继续往当前结点的右子树寻找
    }BSTNode, *BSTree;

    //二分查找, 使用平衡二叉树(Balanced Binary Tree), 或者AVL树实现
    typedef struct AVLNode{
        int key;                //数据域
        int balance;            //平衡因子, 为左子树高-右子树高
        struct AVLNode *lchild; //平衡二叉树结点的左子树根节点
        struct AVLNode *rchild; //平衡二叉树结点的右子树根节点
    }AVLNode, *AVLTree;

    //红黑树结构
    //AVL树需要频繁调整树的形态, 计算平衡因子, 非常耗时
    //而红黑树的插入/删除操作无需频繁更改形态.
    //红黑树的叶结点不包含实际的数据, 它代表的是"查找失败"
    //(1)"左根右":红黑树仍然是二叉排序树;
    //(2)"根叶黑":根结点和叶结点一定为黑;
    //(3)"不红红":红结点必不相邻;
    //(4)"黑路通":对任意结点, 到叶结点的路径所含黑结点数相同
    typedef struct RBNode{
        int key;                //数据域
        struct RBNode *parent;  //父节点指针
        struct RBNode *lchild;  //左子树指针
        struct RBNode *rchild;  //右子树指针
        int color;              //颜色
    }RBNode, *RBTree;

    //B树(m阶B树)B = Balance
    //(1)结点含有至多(m-1)个关键字,至多m个子树
    //(2)非叶结点至少有[m/2](向上取整)棵子树, 至少[m/2]-1(向上取整)个关键字
    //5叉B树的结点构造
    //和分块查找的比较:分块查找是使用的索引块, 里面的关键字并不是实际的数据;B树里面的关键字都是实际存储的数据
    typedef struct mBT_Node{
        ElemType keys[4];           //关键字列表, 非根叶结点最少[5/2]-1=2个关键字, 最多5-1=4个关键字
        struct mBT_Node *child[5];  //分叉指针列表, 非根叶结点最少3个分叉, 最多5个分叉
        int num;                    //当前结点的关键字数量
    }mBT_IndexNode;

public:
    //顺序查找
    int Search_Seq(SSTable ST, ElemType key){
        int i;
        for(i = 0; i < ST.TableLen && ST.elem[i] != key;++i){
            //等待循环完成.循环停止时, 或者i等于表长, 或者找到了值的索引
        }
        //如果i等于表长,说明查找失败
        return i == ST.TableLen ? -1 : i;
    }

    //使用哨兵'Sentinel'实现顺序查找
    int Search_Seq_Sentinel(SSTable ST, ElemType key){
        ST.elem[0] = key;//将关键字的值存放在查找表的最开始的位置
        int i;
        for(i = ST.TableLen; ST.elem[i] != key; --i){
            //从后往前查找
            //等待循环完成.循环停止时, 或者i = 0, 或者找到了值的索引
        }
        //如果i = 0,则说明查找失败
        return i;
    }

    //对于有序表进行二叉排序.
    //假设数组为升序排列.
    int Binary_Search(SSTable L, ElemType key){
        int low = 0;                //低位指针
        int high = L.TableLen - 1;  //高位指针
        int mid;                    //中位指针
        while(low <= high){
            mid = (low + high) / 2;
            if(L.elem[mid] == key){
                //最好的情况:中位指针所指元素即为待找元素
                return mid;
            }
            else if(L.elem[mid] > key){
                //中位指针所指元素大于待找元素, 说明待找元素可能在中位指针的左边
                high = mid - 1;//重新赋值高位指针
            }
            else{
                //中位指针所指元素小于待找元素, 说明待找元素可能在中位指针的右边
                low = mid + 1;
            }
        }
        //只有循环没有正常返回时才会结束, 此时low > high
        return -1;
    }

    //链表方式存储的最大值索引分块查找实现
    ElemNode *IndexList_Search(IndexList indexlist, ElemType key){
        IndexBlock *blockptr = indexlist;
        while(key < blockptr -> maxvalue && blockptr != NULL){
            blockptr = blockptr -> nextBlock;
        }

        //key大于所有索引分块的maxvalue值, 或者indexlist本身传参不合法, 查找失败
        if(blockptr == NULL) return NULL;

        //查找成功, 则此时blockptr 停在刚好大于上一个maxvalue而小于当前maxvalue的IndexBlock

        ElemNode *elemptr = blockptr -> firstNode;
        while(elemptr != NULL && elemptr -> value != key){
            elemptr = elemptr -> next;
        }

        //跳出while循环时, 或这elemptr == NULL, 或者 elemptr -> value == key
        if(elemptr == NULL)return NULL;
        else return elemptr;
    }

    //二叉排序树查找
    //该树的效率实际上和数据的插入顺序有关, 因此为了优化这个弱点开发了平衡二叉树
    BSTNode *BST_Search(BSTree T, int key){
        while(T != NULL && key != T -> key){
            if(key < T -> key){
                T = T -> lchild;
            }
            else{
                T = T -> rchild;
            }
        }
        //退出while循环时, 或者T -> key == key, 或者
        return T;
    }

    //递归实现二叉树查找
    //递归深度, 即空间复杂度S(n) = O(h) = O([log_2(n+1)]), 向上取整
    BSTNode *BST_Search_Recursion(BSTree T, int key){
        if(T == NULL) return T;
        if(key == T -> key) return T;
        else if(key < T -> key) return BST_Search_Recursion(T -> lchild, key);
        else if(key < T -> key) return BST_Search_Recursion(T -> rchild, key);
    }

    //向二叉排序树插入新元素, 返回插入是否成功
    //使用递归方法实现
    bool BST_Insert(BSTree &T, int k){
        if(T == NULL){
            //如果树空, 则申请内存空间以创建新树
            T = (BSTree)malloc(sizeof(BSTNode));
            T -> key = k;
            T -> lchild = T -> rchild = NULL;
            return true;
        }
        else if(k == T -> key) return false;//树中存在相同元素, 则插入失败
        else if(k <  T -> key) return BST_Insert(T -> lchild, k);
        else                   return BST_Insert(T -> rchild, k);
    }

    //构造二叉排序树
    void Create_BST(BSTree &T, int str[], int n){
        T = NULL;//置空, 清洗T数据
        int i = 0;
        while(i < n){
            BST_Insert(T,str[i]);
            i++;
        }
    }

    //计算AVL树某结点的平衡因子
    int AVL_Balance_factor(AVLNode* node){
        if(node == NULL) return 0;
        //若左右子树根节点非空, 则读取子树高为各自的平衡因子
        int h_left  = node -> lchild ? node -> lchild -> balance : 0;
        int h_right = node -> rchild ? node -> rchild -> balance : 0;
        //平衡因子做差得到根节点平衡因子
        return h_left - h_right;
    }

    //从插入点往根结点寻找, 找到第一个不平衡节点(|balance|>1), 调整该节点为根的树(最小不平衡子树)
    //LL: 第一个不平衡结点的左孩子(L)的左子树(L)插入导致的
    //RR: 第一个不平衡结点的右孩子(R)的右子树(R)插入导致的
    //LR: 第一个不平衡结点的左孩子(L)的右子树(R)插入导致的
    //RL: 第一个不平衡结点的右孩子(R)的左子树(L)插入导致的

    //要求对平衡二叉树进行构造, 插入, 删除等操作时, 必须保持AVL树的两个特性:
    //(1)恢复平衡
    //(2)保持二叉排序树的特性

    //LL类型, 进行"右旋"操作
    //简记为"'儿子'右上旋", 这里的儿子是指的B
    //'node'为第一不平衡结点, 即笔记中的'A'
    void AVL_Right_Rotate(AVLNode* &node){
        AVLNode* lchild = node -> lchild;//即笔记中的'B'
        node -> lchild = lchild -> rchild;//A的左子树指针接管B的右子树
        lchild -> rchild = node;//B的右子树指针接管A
        //自下而上依次更新结点的平衡因子
        node -> balance = AVL_Balance_factor(node);
        lchild -> balance = AVL_Balance_factor(lchild);
        node = lchild;//新的根节点从A转到B
    }

    //RR类型, 进行"左旋"操作
    //简记为"'儿子'左上旋", 这里的儿子是指的'B'
    //'node'为第一不平衡结点, 即笔记中的'A'
    void AVL_Left_Rotate(AVLNode* &node){
        AVLNode* rchild = node -> rchild;//即笔记中的'B'
        node -> rchild = rchild -> lchild;//A的右子树指针接管B的左子树
        rchild  -> lchild = node;//B的左子树指针接管A
        //自下而上依次更新结点的平衡因子
        node -> balance = AVL_Balance_factor(node);
        rchild -> balance = AVL_Balance_factor(rchild);
        node = rchild;//新的根结点从A转到B
    }

    //LR类型, 进行左上-右上旋操作
    //简记为"'孙子'先左上旋再右上旋"
    //'node'为第一不平衡结点, 即笔记中的'A'
    //其实就是node左子树的右孩子成为根节点;
    //新根节点以B为左子树, 以A为右子树;
    //A的左子树指针改为指向C的右子树;
    //B的右子树指针改为指向C的左子树.
    void AVL_Left_Right_Rotate(AVLNode* &node){
        AVL_Left_Rotate(node -> lchild);
        AVL_Right_Rotate(node);
    }

    //RL类型, 进行右上-左上旋操作
    //简记为"'孙子'先右上旋再左上旋"
    //'node'为第一不平衡结点, 即笔记中的'A'
    //其实就是node右子树的左孩子成为根节点;
    //新根节点以A为左子树, 以B为右子树;
    //A的右子树指针改为指向C的左子树;
    //B的左子树指针改为指向C的右子树.
    void AVL_Right_Left_Rotate(AVLNode* &node){
        AVL_Right_Rotate(node -> rchild);
        AVL_Right_Rotate(node);
    }

    //构造新平衡二叉树(AVL树)
    void Build_AVL_Tree(AVLTree &root, int key){
        AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
        node -> key = key;
        node -> balance = 0;
        node -> lchild = node -> rchild = NULL;
        root = node;
    }
    
    //向AVL树中插入关键字为key的新结点
    //使用递归定义实现
    void Insert_AVL_Tree(AVLTree &root, int key){
        //如果树空, 则创建新树
        if(root == NULL){
            Build_AVL_Tree(root, key);
            return ;
        }

        if(key < root -> key){
            Insert_AVL_Tree(root -> lchild, key);
            if(root -> balance == 2){
                if(AVL_Balance_factor(root -> lchild) == 1){
                    //如果属于LL型,即balance从上到下为(2,1)
                    //则应该进行"'儿子'右上旋"
                    AVL_Right_Rotate(root);
                }
                else if(AVL_Balance_factor(root-> lchild) == -1){
                    //如果属于LR型,即balance从上到下为(2,-1)
                    //则应该进行"'孙子'先左上旋再右上旋"
                    AVL_Left_Right_Rotate(root);
                }
            }
        }
        else if(key > root -> key){
            Insert_AVL_Tree(root -> rchild, key);
            if(root -> balance == -2){
                if(AVL_Balance_factor(root -> rchild) == -1){
                    //如果属于RR型,即balance从上到下为(-2,-1)
                    //则应该进行"'儿子'左上旋"
                    AVL_Left_Rotate(root);
                }
                else if(AVL_Balance_factor(root -> rchild) == 1){
                    //如果属于RL型,即balance从上到下为(2, 1)
                    //则应该进行"'孙子'先右上旋再左上旋"
                    AVL_Right_Left_Rotate(root);
                }
            }
        }
        else{
            //未能正常从上述条件语句中结束, 说明该关键字已经存在于该AVL树中
            cout << "Key already exists." << endl;
            return ;
        }
    }

    //使用递归方法求解深度为h的平衡二叉树所含有的最少结点数
    int AVL_Least_Num_of_Nodes(int h){
        if(h == 0)return 0;
        else if(h == 1) return 1;
        else if(h == 2) return 2;
        else return AVL_Least_Num_of_Nodes(h-2) + AVL_Least_Num_of_Nodes(h-1) + 1;
        //依次为左子树, 右子树, 根结点
    }

    //红黑树的插入
    //(1)新结点是否为根结点?
    //(1.1)是根结点->染黑
    //(1.2)是非根结点->染红(保持"黑路同"特性)
    //
    //(2)是否满足红黑树的特性?->是否破坏"不红红"?
    //所以只需要重点关注是否有相邻红节点
    //(2.1)满足->结束
    //(2.2)不满足->进入第(3)步
    //
    //(3)叔叔是黑色还是红色?
    //(3.1)叔叔是黑色
    //(3.1.1)LL型:右旋,self和self.儿染色
    //(3.1.2)RR型:左旋,self和self.儿染色
    //(3.1.3)LR型:先左旋再右旋,self和self.孙染色
    //(3.1.4)RL型:先右旋再左旋,self和self.孙染色
    //(3.2)叔叔是红色
    //(3.2.1)叔父爷染色, 爷变新结点(即对其判断是否为根,是否满足特性...)->"不平衡"向上传递的过程
    //
    //
    //红黑树对于旋转的处理是和AVL树一样的



    //向B树插入新结点
};

int main(){
    Find find;
    int n3 = find.AVL_Least_Num_of_Nodes(3);
    cout << n3 << endl;
}