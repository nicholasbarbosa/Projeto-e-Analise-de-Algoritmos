#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

struct edge{
    int u = -1, v = -1;
    double peso = 0;
};

bool operator < (const edge &a,const edge &b) {
    return a.peso < b.peso;
}

bool operator > (const edge &a,const edge &b) {
    return a.peso > b.peso;
}

//Arrays a serem usados para na estrutura Union-Find
vector <int> raiz; //array de tamanho n, onde n é o número de vértices
vector <int> prox; //para fazer o encadeamento da lista
vector <int> size; //armazena o tamanho de cada lista

//=========================================================================
template <typename T>
void troca(T &a, T &b){
    T x = a;
    a = b;
    b = x;
}


void Make_Sets(int n){ //cria os n conjuntos
    for(int i = 0; i<n; i++){
        raiz[i] = i;
        prox[i] = i;
        size[i] = 1;
     }
}

int Find_Set(int i){
    return raiz[i];
}

void Union(int u, int v){
//A união é feita se u e v estão em conjuntos diferentes, ou seja se Find_Set(u) != Find_Set(v)

    int ru = raiz[u];
    int rv = raiz[v];
    if(size[ru] < size[rv] ){
        //lista de raiz rv recebe lista de raiz ru:
        size[rv] = size[rv] + size[ru];
        
        //altera a raiz dos elementos da lista de raiz ru:
        raiz[ru] = rv;
        for(int j = prox[ru]; j != ru; j=prox[j])
            raiz[j] = rv;
        
        troca(prox[ru], prox[rv]);
    }
    else{
        //lista de raiz ru recebe lista de raiz rv:
        size[ru] = size[ru] + size[rv];
        
        //altera a raiz dos elementos da lista de raiz rv:
        raiz[rv] = ru;
        for(int j = prox[rv]; j != rv; j = prox[j])
            raiz[j] = ru;
        troca(prox[ru], prox[rv]);
    }
}

int hoarePartition(vector<edge> &A, int l, int r){
    edge p = A[l];
    int i=l; int j=r+1;
    do{
        do{
            i++;
        } while(A[i]<p);
        do{
            j--;
        } while(A[j]>p);
        swap(A[i],A[j]);
    } while(!(i>=j));

    swap(A[i],A[j]);
    swap(A[l],A[j]);

    return j;
}

void quickSort(vector<edge> &A, int l, int r){
    if(l<r){
        int s = hoarePartition(A, l, r);
        quickSort(A,l,s-1);
        quickSort(A,s+1,r);
    }
}

int Kruskal(vector<edge> &arestas, vector<bool> &utilizadas,int nv,int ns){
    quickSort(arestas,0,arestas.size()-1);

    Make_Sets(nv);
    int k = 0;

   for(int i = 0; i < arestas.size(); i ++){
       if(Find_Set(arestas[i].u) != Find_Set(arestas[i].v)){
           utilizadas[i] = true;
           k ++;
           if(k == nv-ns) return k;
           Union(arestas[i].u,arestas[i].v);
       }
   }

    return k;
}

int main(){
    int nVertices, nEdges;

    cin >> nVertices >> nEdges;
    
    raiz.resize(nVertices);
    prox.resize(nVertices);
    size.resize(nVertices);
    
    int tmp1, tmp2, tmp3;
    
    vector<vector<double>> adj(nVertices,vector<double>(nVertices)); //Materiz de adj
    vector<edge> arestas; //Lista de arestas

    for(int i=0;i<nEdges;i++){
        cin >> tmp1 >> tmp2 >> tmp3;
        edge e;
        e.u = tmp1;
        e.v = tmp2;
        e.peso = tmp3;
        arestas.push_back(e);
        adj[tmp1][tmp2] = tmp3;
    }

    vector<bool> Autilizadas(arestas.size(),false);
    sort(arestas.begin(),arestas.end());
    int nAGM = Kruskal(arestas,Autilizadas,nVertices,nEdges);
    
    int total = 0;
    for(int i=0;i<Autilizadas.size();i++){
        if(Autilizadas[i]) {
            cout << arestas[i].u << " -> " << arestas[i].v << " peso: " << arestas[i].peso << endl;
            total += arestas[i].peso;
        }
    }
    cout << "Peso total: " << total << endl;
    
    return 0;
}