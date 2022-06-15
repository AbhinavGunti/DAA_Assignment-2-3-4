#include"header.h"

#include<limits.h>

//ques1


static void dfs_function(int a,int b,const connection_t connections[b][b],int vstd[]){

vstd[a]=1;
for(int i=0;i<b;i++){
if(connections[a][i].distance>0 && a!=i && connections[a][i].distance<INT_MAX && vstd[i]==0){
dfs_function(i,b,connections,vstd);
}
}
return;
}


int q1(int n, const connection_t connections[n][n]){

int vstd[n];

for(int j=0;j<n;j++){
for(int i=0;i<n;i++){
vstd[i]=0;
}

dfs_function(j,n,connections,vstd);
for(int i=0;i<n;i++){
if(vstd[i]==0){return 0;}
}
}
return 1;
}


//ques2



static void dfs_function_2(int source,int dest,int n,const connection_t connections[n][n],int vstd[],int *mininum_edges,int *count){

vstd[source]=1;
if(source==dest){
if(*count<*mininum_edges){
*mininum_edges=*count;
}
}

for(int i=0;i<n;i++){
if(vstd[i]==0 && connections[source][i].distance>0 && connections[source][i].distance<INT_MAX && i!=source){
*count=*count+1;
dfs_function_2(i,dest,n,connections,vstd,mininum_edges,count);
}
}

vstd[source]=0;
*count=*count-1;
}


int q2(const airport_t *source, const airport_t *dest, int n, int k,const connection_t connections[n][n]){

int vstd[n];
for(int i=0;i<n;i++){
vstd[i]=0;
}
int mininum_edges=INT_MAX;
int count=0;
dfs_function_2(source->num_id,dest->num_id,n,connections,vstd,&mininum_edges,&count);

if(count<=n){return 1;}

return 0;
}





static void dfs_function_3(int x,int dest,int y,const connection_t connections[y][y],int vstd[],int *reached){

vstd[x]=1;
if(x==dest){
*reached=1;
return;
}

for(int i=0;i<y;i++){
if(vstd[i]==0 && connections[x][i].distance>0 && connections[x][i].distance<INT_MAX && i!=x){
dfs_function_3(i,dest,y,connections,vstd,reached);
}
}

vstd[x]=0;
}


int q3(const airport_t *source, int n, const connection_t connections[n][n]){


for(int j=0;j<n;j++){
int vstd[n];
for(int i=0;i<n;i++){
vstd[i]=0;
}
int reached=0;
if(j!=source->num_id && connections[source->num_id][j].distance>0 && connections[source->num_id][j].distance<INT_MAX){
dfs_function_3(j,source->num_id,n,connections,vstd,&reached);}
if(reached==1){return 1;}
 }
return 0;
}


//ques4



static void swap_func(airport_t *a, airport_t *b)
{
    airport_t t = *a;
    *a = *b;
    *b = t;
}


static int partition_function(int n, airport_t airport_list[n], int l, int h, int (*predicate_func)(const airport_t *, const airport_t *))
{


    airport_t pivot = airport_list[h];

    int i = (l - 1);


    for (int j = l; j < h; j++)
    {
        if (predicate_func(&airport_list[j], &pivot))
        {

   
            i++;

  
            swap_func(&airport_list[i], &airport_list[j]);
        }
    }


    swap_func(&airport_list[i + 1], &airport_list[h]);


    return (i + 1);
}

static void quick_sort_function(int n, airport_t airport_list[n], int l, int h, int (*predicate_func)(const airport_t *, const airport_t *))
{
    if (l < h)
    {


        int partition = partition_function(n, airport_list, l, h, predicate_func);

        quick_sort_function(n, airport_list, l, partition - 1, predicate_func);


        quick_sort_function(n, airport_list, partition + 1, h, predicate_func);
    }
}





void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),airport_t airport_list[n])
{

    quick_sort_function( n, airport_list, 0, n-1, predicate_func);

    
}



//ques5


static int length(airport_t airport1,airport_t airport2)
{
    int i=0;
    while(airport1.airport_name[i]!='\0' && airport2.airport_name[i]!='\0' && airport1.airport_name[i] == airport2.airport_name[i])
    {
        i++;
    }
    return i;
}

pair_t q5(int n, airport_t airports[n])
{
    pair_t answer = {-1, -1};
    int maximum = 0;
    int x;
    for(int i=0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            x = length(airports[i],airports[j]);
            if(maximum < x)
            {
                maximum = x;
                answer.first = airports[i].num_id;
                answer.second = airports[j].num_id;
            }
        }
    }
    return answer;

}





//ques6


int q6(int n, int amount, const int entry_fee[n]){
if(amount<entry_fee[0]){return 0;}
if(amount>entry_fee[n-1]){return n;}

int l=0;
int h=n-1;
int mid=(l+h)/2;

while(l<=h && entry_fee[mid]!=amount){
mid=(l+h)/2;
if(entry_fee[mid]>amount){
h=mid-1;
}
if(entry_fee[mid]<amount){
l=mid+1;
}
}

return (mid+1);
}




//ques7


static void shift_table_st(const char *pat,int table[]) {
int a,b,c;
c=0;
a=0;

while(*(pat+a)!='\0'){
a++;
c++;
}



for(a=0;a<500;a++){
table[a]=c;
}

for(b=0;b<c-1;b++){
table[pat[b]]=c-1-b;
}

}

static int horspool_algo(const char *str,const char *pat,int table[]) {
	int a,b,c,m,n;
	a=0;
	n=0;	
	while(*(str+a)!='\0'){
	a++;
	n++;
	}
	a=0;
	m=0;
	while(*(pat+a)!='\0'){
	a++;
	m++;
	}


	a=m-1;
	while(a<n) {
		c=0;
		while((c<m)&&(pat[m-1-c]==str[a-c]))
		   c++;
		if(c==m)
		   return(a-m+1); 
		else
		   a=a+table[str[a]];
	}
	return -1;
}




void q7(int n, const char *pat, int contains[n], const airport_t airports[n]){

int table[500];
shift_table_st(pat,table);
for(int i=0;i<n;i++){
int check=horspool_algo(airports[i].airport_name,pat,table);
if(check>=0){
contains[i]=1;
}

}

}


//ques8


typedef struct stack
{
    int arr[100];
    int top;
}stack_t;

static void init(stack_t* s)
{
    s->top=-1;
}

static int full(stack_t* s)
{
    return s->top==100-1;
}

static void push(stack_t* s,int ele)
{
    if(!full(s))
    {
        s->top=s->top+1;
        s->arr[s->top]=ele;
    }
}

static int pop(stack_t* s)
{
    
    return s->arr[s->top--];
}

static int top(stack_t* s)
{
    
    return s->arr[s->top];
}

static void insert(int cycles[25][25],int v,int* cycle_no)
{
    int i=*cycle_no;
    int index=-1;
    for(int j=0;j<25 && index == -1;j++)
    {
        if(cycles[i][j]==-1)
        {
            index=j;
        }
    }
    cycles[i][index]=v;
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
static void DFS_tree(int n,const connection_t connections[n][n],stack_t* s,int visited[n],int cycles[25][25],int* cycle_no)
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
            DFS_tree(n,connections,s,visited,cycles,cycle_no);
        }
    }
    visited[top(s)]=1;
    pop(s);
}
static void find_cycles(int n,const connection_t connections[n][n],int visited[n],int cycles[25][25],int* cycle_no)
{
    for(int i=0;i<n;i++)
    {
        if(visited[i]==-1)
        {
            stack_t s;
            init(&s);
            push(&s,i);
            visited[i]=0;
            DFS_tree(n,connections,&s,visited,cycles,cycle_no);
        }
    }
}
int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    int visited[n];
    int cycles[25][25];
    int cycle_no = 0;
    int min_index;
    int min = INT_MAX;
    int cost=0;
    int p,q;
    for(int i=0;i<n;i++)
    {
        visited[i]=-1;
    }
    for(int a=0;a<25;a++)
    {
        for(int b=0;b<25;b++)
        {
            cycles[a][b]=-1;
        }
    }
    find_cycles(n,connections,visited,cycles,&cycle_no);
    int count[cycle_no+1];
    for(int i=0;i<cycle_no+1;i++)
    {
        count[i]=0;
    }
    int res[cycle_no+1][n];
    int x=0;
    int y=0;
    for(int a=0;a<cycle_no+1;a++)
    {
        for(int b=0;b<n;b++)
        {
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
            // last_index=n-1;
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


//ques9

static int find_min_key(int n,int keys[], int min_span_tree[])
{

    int min = INT_MAX, minim;
 
    for (int i = 0; i < n; i++)
        if (min_span_tree[i] == 0 && keys[i] < min)
            min = keys[i], minim = i;
 
    return minim;
}


static void min_span_tree_func(int n,int p[], const connection_t connections[n][n],pair_t edges[n - 1])
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



int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    int p[n];
    int keys[n];
    int min_span_tree[n];
 
    for (int i = 1; i < n; i++)
        keys[i] = INT_MAX, min_span_tree[i] = 0;
 
    keys[0] = 0;
    p[0] = -1;
 
    for (int count = 0; count < n - 1; count++) {
        int u = find_min_key(n,keys, min_span_tree);
        min_span_tree[u] = 1;
 
        for (int v = 0; v < n; v++)
 
            if (connections[u][v].time && min_span_tree[v] == 0 && connections[u][v].time < keys[v])
                p[v] = u, keys[v] = connections[u][v].time;
    }
 
    min_span_tree_func(n,p, connections ,edges);

    return calc_time(n,edges,connections,p);
}

//ques10


static void dijkstra_function(int n,int k,const connection_t connections[n][n],int start,const int destinations[k],int costs_ans[k])
{
 
int t[n][n],t_track[n],predec[n];
int vstd[n],count,minimum_time,next_airport,i,j;


for(i=0;i<n;i++)
for(j=0;j<n;j++)
if(connections[i][j].time==0)
t[i][j]=INT_MAX;
else
t[i][j]=connections[i][j].time;


for(i=0;i<n;i++)
{
t_track[i]=t[start][i];
predec[i]=start;
vstd[i]=0;
}
t_track[start]=0;
vstd[start]=1;
count=1;
while(count<n-1)
{
minimum_time=INT_MAX;

for(i=0;i<n;i++)
if(t_track[i]<minimum_time&&!vstd[i])
{
minimum_time=t_track[i];
next_airport=i;
}

vstd[next_airport]=1;
for(i=0;i<n;i++)
if(!vstd[i])
if(minimum_time+t[next_airport][i]<t_track[i])
{
t_track[i]=minimum_time+t[next_airport][i];
predec[i]=next_airport;
}
count++;
}
 

for(int i=0;i<k;i++){
costs_ans[i]=t_track[destinations[i]];
}



}


void q10(int n, int k, const airport_t *source, const connection_t connections[n][n], const int destinations[k], int costs[k]){

dijkstra_function(n,k,connections,source->num_id,destinations,costs);

}


