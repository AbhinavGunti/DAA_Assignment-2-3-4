//NAME : ABHINAV GUNTI
//SRN : PES1UG20CS008
//SECTION : 4A
#include "header.h"
#include <limits.h>
// ANY STATIC FUNCTIONS ARE UP HERE

//2
static int DFS2(int n, int s, int d, int *visited, const connection_t connections[n][n], int count) {
    visited[s] = 1;
    if(s == d) return count;
    for(int i=0; i<n; i++) {
        if((connections[s][i].distance != INT_MAX && connections[s][i].distance != 0) && visited[i] == 0) {
            count++;
            return DFS2(n, i, d, visited, connections, count);
        }
    }
}
//3
void DFS3(int x,int d,int n,const connection_t connections[n][n],int visited[],int *visit){
    visited[x]=1;
    if(x==d){
        *visit=1;
        return;
    }
    int i=0;
    while(i<n){
        if(visited[i]==0 && connections[x][i].distance>0 && connections[x][i].distance<INT_MAX && i!=x){
            DFS3(i,d,n,connections,visited,visit);
        }
        i++;
    }
    visited[x]=0;
}
//4
static void swap(airport_t *x, airport_t *y)
{
    airport_t t = *y;
    *y = *x;
    *x = t;
}
static int split(int n,int l,int h,airport_t airport_list[n],int (*predicate_func)(const airport_t *, const airport_t *))
{
    int x;
    airport_t p;
    x= l-1;
    p= airport_list[h];
    int j=l;
    while(j<h){
        if (predicate_func(&airport_list[j], &p)){
            x++;
            swap(&airport_list[j], &airport_list[x]);
        }
        j++;
    }
    swap(&airport_list[h], &airport_list[x+1]);
    return (x+1);
}
static void QuickSort(int n,  int l, int h, airport_t airport_list[n],int (*predicate_func)(const airport_t *, const airport_t *))
{
    if (h>l)
    {
        int p = split(n,l,h,airport_list, predicate_func);
        QuickSort(n,l,p-1,airport_list,predicate_func);
        QuickSort(n,p + 1,h,airport_list,predicate_func);
    }
}
//5
static int length(airport_t airport1,airport_t airport2)
{
    int x=0;
    while(airport2.airport_name[x]!='\0' && airport1.airport_name[x]!='\0' &&  airport1.airport_name[x]==airport2.airport_name[x]){
        x++;
    }
    return x;
}
//7
void table_shift(const char *pat,int table[]){
    int i=0,j,m=0;
    while(*(pat+i)!='\0'){
        i++;
        m++;
    }
    for(i=0;i<500;i++){
        table[i]=m;
    }
    for(j=0;j<m-1;j++){
        table[pat[j]]=m-1-j;
    }
}

int horspool_algorithm(const char *str,const char *pat,int table[]) {
	int i=0,j,k,m=0,n=0;
	while(*(str+i)!='\0'){
        i++;
        n++;
	}
	i=0;
	while(*(pat+i)!='\0'){
        i++;
        m++;
	}
	i=m-1;
	while(i<n){
		k=0;
		while((pat[m-1-k]==str[i-k])&&(k<m)){
		   k++;
        }
		if(k==m){
		   return(i-m+1); 
        }
		else{
		   i=i+table[str[i]];
        }
	}
	return -1;
}
//8
typedef struct stack{
    int arr[100];
    int top;
}stack_t;

static void init(stack_t* s){
    s->top=-1;
}

static int full(stack_t* s)
{
    return s->top==100-1;
}

static void push(stack_t* s,int e){
    if(!full(s))
    {
        s->top=s->top+1;
        s->arr[s->top]=e;
    }
}

static int pop(stack_t* s){
    
    return s->arr[s->top--];
}

static int top(stack_t* s){ 
    return s->arr[s->top];
}

static void insert(int c[25][25],int v,int* cycle_no)
{
    int i=*cycle_no,in=-1;
    for(int j=0;j<25 && in==-1;j++){
        if(c[i][j]==-1){
            in=j;
        }
    }
    c[i][in]=v;
}
static void cycle(stack_t* s,int v,int cycles[25][25],int* cycle_no)
{
    stack_t s2;
    init(&s2);
    push(&s2,top(s));
    pop(s);
    while(top(&s2)!=v)
    {
        push(&s2,top(s));
        pop(s);
    }
    while(s2.top!=-1)
    {
        insert(cycles,top(&s2),cycle_no);
        push(s,top(&s2));
        pop(&s2);
    }
}
static void DFS_T(int n,const connection_t connections[n][n],stack_t* s,int visited[n],int cycles[25][25],int* cycle_no)
{
    int u=top(s);
    for(int i=0;i<n;i++)
    {
        if(connections[u][i].distance!=0 && connections[u][i].distance!=INT_MAX &&visited[i]==0)
        {
            *cycle_no=*cycle_no+1;
            cycle(s,i,cycles,cycle_no);
        }
        else if(connections[u][i].distance!=0 && connections[u][i].distance!=INT_MAX &&visited[i]==-1)
        {
            push(s,i);
            visited[i]=0;
            DFS_T(n,connections,s,visited,cycles,cycle_no);
        }
    }
    visited[top(s)]=1;
    pop(s);
}
static void find_cycles(int n,const connection_t connections[n][n],int v[n],int cycles[25][25],int* cycle_no)
{
    int i=0;
    while(i<n){
        if(v[i]==-1){
            stack_t s;
            init(&s);
            push(&s,i);
            v[i]=0;
            DFS_T(n,connections,&s,v,cycles,cycle_no);
        }
        i++;
    }
}
//9
static int minimum_key(int n,int keys[], int min_span_tree[])
{

    int min = INT_MAX, minim;
 
    for (int i = 0; i < n; i++)
        if (min_span_tree[i] == 0 && keys[i] < min)
            min = keys[i], minim = i;
 
    return minim;
}


static void mstf(int n,int p[], const connection_t connections[n][n],pair_t edges[n - 1])
{
    for (int i = 1; i < n; i++)
    {    
        edges[i-1].first = p[i];
        edges[i-1].second = i;
    }
}

static int calc_time(int n,pair_t edges[],const connection_t connections[n][n],int p[])
{
    int result = 0;
    for(int i=0;i<n-1;i++){
        result=result+connections[edges[i].first][edges[i].second].time;}
    return result;
}


//10
void dijkstra(int n,int k,const connection_t connections[n][n],int start,const int destinations[k],int costs_ans[k])
{
    int t[n][n],tt[n],p[n];
    int v[n],count,mintime,next,i,j;
    i=0;
    while(i<n){
        for(j=0;j<n;j++)
            if(connections[i][j].time==0)
                t[i][j]=INT_MAX;
            else
                t[i][j]=connections[i][j].time;
        i++;
    }
    i=0;
    while(i<n){
        tt[i]=t[start][i];
        p[i]=start;
        v[i]=0;
        i++;
    }
    tt[start]=0;
    v[start]=1;
    count=1;
    while(count<n-1)
    {
        mintime=INT_MAX;
        for(i=0;i<n;i++)
            if(tt[i]<mintime&&!v[i]){
                mintime=tt[i];
                next=i;
            }
        v[next]=1;
        for(i=0;i<n;i++)
            if(!v[i])
                if(mintime+t[next][i]<tt[i]){
                    tt[i]=mintime+t[next][i];
                    p[i]=next;
                }
            count++;
    }
    for(int i=0;i<k;i++){
        costs_ans[i]=tt[destinations[i]];
    }
}


// YOUR SOLUTIONS BELOW
//1
int q1(int n, const connection_t connections[n][n]){
    int m=0,k=0;
    while(m<n){
        while(k<n){
            if(connections[m][k].distance == INT_MAX && connections[m][k].time == INT_MAX)
                return 0;
            k++;
        }
        m++;
    }
    return 1;
}
//2


int q2(const airport_t *src, const airport_t *dest, int n, int k, const connection_t connections[n][n]) {
    int s,d,visited[n],num;
    s = src->num_id;
    d = dest->num_id;
    int i=0;
    while(i<n){
        visited[i] = 0;
        i++;
    }
    num = DFS2(n, s, d, visited, connections, 0);
    if(num <= k){return 1;}
    return 0;
}
//3
int q3(const airport_t *src, int n, const connection_t connections[n][n]){
    for(int i=0;i<n;i++){
        int visited[n];
        int j=0;
        while(j<n){
            visited[i] = 0;
            j++;
        }
        int visit=0;
        if(i!=src->num_id && connections[src->num_id][i].distance<INT_MAX && connections[src->num_id][i].distance>0){
            DFS3(i,src->num_id,n,connections,visited,&visit);
        }
        if(visit==1){
            return 1;
        }
    }
    return 0;
}

//4
void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),airport_t airport_list[n])
{
    QuickSort(n,0, n-1,airport_list,predicate_func);
}


//5
pair_t q5(int n, airport_t airports[n])
{
    pair_t t={-1, -1};
    int maximum=0,i=0,x,j=0;;
    while(i<n){
        j=i+1;
        while(j<n){
            x= length(airports[i],airports[j]);
            if(maximum<x){
                maximum=x;
                t.first=airports[i].num_id;
                t.second=airports[j].num_id;
            }
            j++;
        }
        i++;
    }
    return t;
}
//6
int q6(int n, int amount, const int entry_fee[n]){
    int l=0,h=n-1,m=(l+h)/2;
    if(amount>entry_fee[n-1]){
        return n;
    }
    else if(amount<entry_fee[0]){
        return 0;
    }
    while(l<=h && entry_fee[m]!=amount){
        m=(l+h)/2;
        if(entry_fee[m]>amount){
            h=m-1;
        }
        if(entry_fee[m]<amount){
            l=m+1;
        }
    }
    return (m+1);
}

//7
void q7(int n, const char *pat, int contains[n], const airport_t airports[n]){
    int t[500];
    table_shift(pat,t);
    int i=0;
    while(i<n){
        int check=horspool_algorithm(airports[i].airport_name,pat,t);
        if(check>=0){
            contains[i]=1;
        }
        i++;
    }

}


//Q8

int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    int visited[n],cycles[25][25],cycle_no=0,min_index,min=INT_MAX,cost=0,p,q;
    int i=0;
    while(i<n){
        visited[i]=-1;
        i++;
    }
    for(int x=0;x<25;x++)
    {
        for(int y=0;y<25;y++)
        {
            cycles[x][y]=-1;
        }
    }
    find_cycles(n,connections,visited,cycles,&cycle_no);
    int count[cycle_no+1];
    for(int i=0;i<cycle_no+1;i++){
        count[i]=0;
    }
    int res[cycle_no+1][n];
    int x=0,y=0,b=0;
    for(int a=0;a<cycle_no+1;a++)
    {
        for(int b=0;b<n;b++){
            res[a][b]=-1;
        }
    }
    for(int a=0;a<25;a++)
    {
        y=0;
        int flag=0;
        for(int b=0;b<25;b++)
        {
            if(cycles[a][b]!=-1)
            {
                if(!flag)
                {
                    x++;
                    flag=1;
                }
                res[x][y]=cycles[a][b];
                count[x]=count[x]+1;
                y++;
            }
        }
    }
    for(int a=1;a<cycle_no+1;a++)
    {
        if(count[a]==n-1)
        {
            cost=0;
            for(int b=0;b<n-1;b++)
            {
                if(res[a][b]!=-1 && res[a][b+1]!=-1)
                {
                    p=res[a][b];
                    q= res[a][b+1];
                    cost+= connections[p][q].distance;
                }
            }
            cost+=connections[q][res[a][0]].distance;
            if(cost<min)
            {
                min=cost;
                min_index=a;
            }
        }
    }
    if(min==INT_MAX)
    {
        return -1;
    }
    else
    {
        for(int i=0;i<n-1;i++)
        {
            trip_order[i]=cycles[min_index][i];
        }
        return min;
    }
}
//9

int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    int p[n],k[n],mst[n];
    int i=1;
    while(i<n){
        k[i] = INT_MAX, mst[i] = 0;
        i++;
    }
    k[0] = 0;
    p[0] = -1;
    for (int count=0; count<n-1;count++){
        int u = minimum_key(n,k, mst);
        mst[u] = 1;
        for (int v = 0; v < n; v++)
            if (connections[u][v].time && mst[v] == 0 && connections[u][v].time < k[v])
                p[v] = u, k[v] = connections[u][v].time;
    }
 
    mstf(n,p, connections ,edges);
    return calc_time(n,edges,connections,p);
}
//10

void q10(int n, int k, const airport_t *src, const connection_t connections[n][n], const int destinations[k], int costs[k]){
    dijkstra(n,k,connections,src->num_id,destinations,costs);
}


// END