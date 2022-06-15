#include"header.h"

#include<limits.h>

//ques1


void DFS_func(int u,int n,const connection_t connections[n][n],int visited[]){

visited[u]=1;
for(int i=0;i<n;i++){
if(connections[u][i].distance>0 && u!=i && connections[u][i].distance<INT_MAX && visited[i]==0){
DFS_func(i,n,connections,visited);
}
}
return;
}


int q1(int n, const connection_t connections[n][n]){

int visited[n];

for(int j=0;j<n;j++){
for(int i=0;i<n;i++){
visited[i]=0;
}

DFS_func(j,n,connections,visited);
for(int i=0;i<n;i++){
if(visited[i]==0){return 0;}
}
}
return 1;
}


//ques2



void DFS_func_2(int src,int des,int n,const connection_t connections[n][n],int visited[],int *min_edges,int *count){

visited[src]=1;
if(src==des){
if(*count<*min_edges){
*min_edges=*count;
}
}

for(int i=0;i<n;i++){
if(visited[i]==0 && connections[src][i].distance>0 && connections[src][i].distance<INT_MAX && i!=src){
*count=*count+1;
DFS_func_2(i,des,n,connections,visited,min_edges,count);
}
}

visited[src]=0;
*count=*count-1;
}


int q2(const airport_t *src, const airport_t *dest, int n, int k,const connection_t connections[n][n]){

int visited[n];
for(int i=0;i<n;i++){
visited[i]=0;
}
int min_edges=INT_MAX;
int count=0;
DFS_func_2(src->num_id,dest->num_id,n,connections,visited,&min_edges,&count);

if(count<=k){return 1;}

return 0;
}


//ques3


void DFS_func_3(int u,int des,int n,const connection_t connections[n][n],int visited[],int *reached){

visited[u]=1;
if(u==des){
*reached=1;
return;
}

for(int i=0;i<n;i++){
if(visited[i]==0 && connections[u][i].distance>0 && connections[u][i].distance<INT_MAX && i!=u){
DFS_func_3(i,des,n,connections,visited,reached);
}
}

visited[u]=0;
}


int q3(const airport_t *src, int n, const connection_t connections[n][n]){


for(int j=0;j<n;j++){
int visited[n];
for(int i=0;i<n;i++){
visited[i]=0;
}
int reached=0;
if(j!=src->num_id && connections[src->num_id][j].distance>0 && connections[src->num_id][j].distance<INT_MAX){
DFS_func_3(j,src->num_id,n,connections,visited,&reached);}
if(reached==1){return 1;}
 }
return 0;
}


//ques4



static void swap(airport_t *a, airport_t *b)
{
    airport_t t = *a;
    *a = *b;
    *b = t;
}


static int partition_func(int n, airport_t airport_list[n], int low, int high, int (*predicate_func)(const airport_t *, const airport_t *))
{


    airport_t pivot = airport_list[high];

    int i = (low - 1);


    for (int j = low; j < high; j++)
    {
        if (predicate_func(&airport_list[j], &pivot))
        {

   
            i++;

  
            swap(&airport_list[i], &airport_list[j]);
        }
    }


    swap(&airport_list[i + 1], &airport_list[high]);


    return (i + 1);
}

static void quick_sort_func(int n, airport_t airport_list[n], int low, int high, int (*predicate_func)(const airport_t *, const airport_t *))
{
    if (low < high)
    {


        int parti = partition_func(n, airport_list, low, high, predicate_func);

        quick_sort_func(n, airport_list, low, parti - 1, predicate_func);


        quick_sort_func(n, airport_list, parti + 1, high, predicate_func);
    }
}





void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),airport_t airport_list[n])
{
    quick_sort_func( n, airport_list, 0, n-1, predicate_func);
}



//ques5


static int len(airport_t airport1,airport_t airport2)
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
    pair_t ans = {-1, -1};
    int max = 0;
    int a;
    for(int i=0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            a = len(airports[i],airports[j]);
            if(max < a)
            {
                max = a;
                ans.first = airports[i].num_id;
                ans.second = airports[j].num_id;
            }
        }
    }
    return ans;

}





//ques6


int q6(int n, int amount, const int entry_fee[n]){
if(amount<entry_fee[0]){return 0;}
if(amount>entry_fee[n-1]){return n;}

int low=0;
int high=n-1;
int mid=(low+high)/2;

while(low<=high && entry_fee[mid]!=amount){
mid=(low+high)/2;
if(entry_fee[mid]>amount){
high=mid-1;
}
if(entry_fee[mid]<amount){
low=mid+1;
}
}

return (mid+1);
}




//ques7


void shift_table(const char *pat,int table[]) {
int i,j,m;
m=0;
i=0;

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
	int i,j,k,m,n;
	i=0;
	n=0;	
	while(*(str+i)!='\0'){
	i++;
	n++;
	}
	i=0;
	m=0;
	while(*(pat+i)!='\0'){
	i++;
	m++;
	}


	i=m-1;
	while(i<n) {
		k=0;
		while((k<m)&&(pat[m-1-k]==str[i-k]))
		   k++;
		if(k==m)
		   return(i-m+1); 
		else
		   i=i+table[str[i]];
	}
	return -1;
}




void q7(int n, const char *pat, int contains[n], const airport_t airports[n]){

int table[500];
shift_table(pat,table);
for(int i=0;i<n;i++){
int check=horspool_algorithm(airports[i].airport_name,pat,table);
if(check>=0){
contains[i]=1;
}

}

}


//ques8


void DFS_func_8(int u,int des,int n,const connection_t connections[n][n],int visited[],int *reached,int trip_order[n - 1],int *k,int *min_cost){

visited[u]=1;
trip_order[*k]=u;
*k=*k+1;
if(u==des && *k<n){
*reached=1;
return;
}


for(int i=0;i<n;i++){
if(visited[i]==0 && connections[u][i].distance>0 && connections[u][i].distance<INT_MAX && i!=u){
*min_cost=*min_cost+connections[u][i].distance;
DFS_func_8(i,des,n,connections,visited,reached,trip_order,k,min_cost);
}
}

visited[u]=0;
trip_order[*k]=-1;
*k=*k-1;

}


int q8(int n, int trip_order[n - 1], const connection_t connections[n][n]){

for(int des=0;des<n;des++){

for(int j=0;j<n;j++){
int visited[n];
int k=0;
int min_cost=0;
for(int i=0;i<n;i++){
visited[i]=0;
}
int reached=0;

if(j!=des && connections[des][j].distance>0 && connections[des][j].distance<INT_MAX){
min_cost=min_cost+connections[des][j].distance;
DFS_func_8(j,des,n,connections,visited,&reached,trip_order,&k,&min_cost);

}
if(reached==0){
for(int x=0;x<n-1;x++){
trip_order[x]=-1;
}
}




if(reached==1){return min_cost;}
 }


}
return -1;
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


void dijkstra(int n,int k,const connection_t connections[n][n],int start,const int destinations[k],int costs_ans[k])
{
 
int time[n][n],time_track[n],predecessor[n];
int visited[n],count,mintime,next_airport,i,j;


for(i=0;i<n;i++)
for(j=0;j<n;j++)
if(connections[i][j].time==0)
time[i][j]=INT_MAX;
else
time[i][j]=connections[i][j].time;


for(i=0;i<n;i++)
{
time_track[i]=time[start][i];
predecessor[i]=start;
visited[i]=0;
}
time_track[start]=0;
visited[start]=1;
count=1;
while(count<n-1)
{
mintime=INT_MAX;

for(i=0;i<n;i++)
if(time_track[i]<mintime&&!visited[i])
{
mintime=time_track[i];
next_airport=i;
}

visited[next_airport]=1;
for(i=0;i<n;i++)
if(!visited[i])
if(mintime+time[next_airport][i]<time_track[i])
{
time_track[i]=mintime+time[next_airport][i];
predecessor[i]=next_airport;
}
count++;
}
 

for(int i=0;i<k;i++){
costs_ans[i]=time_track[destinations[i]];
}



}


void q10(int n, int k, const airport_t *src, const connection_t connections[n][n], const int destinations[k], int costs[k]){

dijkstra(n,k,connections,src->num_id,destinations,costs);

}


