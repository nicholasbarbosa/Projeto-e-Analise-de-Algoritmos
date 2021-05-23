#include<iostream>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<chrono>
#include<iomanip>
using namespace std;

void bubbleSort(vector<int> & v){
    for(int i = 0; i < v.size(); i ++){
        for(int j = 0; j < v.size() - i - 1; j ++){
            if(v[j] > v[j + 1]) swap(v[j],v[j+1]);
        }
    }
}

void selectionSort(vector<int> & v){
    for(int i = 0; i < v.size(); i ++){
        int menor = i;
        for(int j = 1 + i; j < v.size(); j ++){
            if(v[j] < v[menor]) menor = j;
        }
        swap(v[i],v[menor]);
    }
}
void merge(vector<int> & B, vector<int> & C, vector<int> & A){  //junta os vetores ordenando eles (conquistar)
    int i = 0, j = 0, k = 0;
    int p = B.size(), q = C.size();

    while (i < p && j < q){
        if(B[i] <= C[j]) {
            A[k] = B[i]; 
            i ++;
        }
        else{
            A[k] = C[j];
            j ++;
        }
        k ++;
    }

    if(i == p){ //se ja terminou o de passar o vetor B, so gravar o resto do vetor b no v
        copy(C.begin() + j, C.end(), A.begin() + k);
    }
    else{
        copy(B.begin() + i, B.end(), A.begin() + k);
    }
}

void mergeSort(vector<int> & A){
    if(A.size() > 1){
        vector<int> B(floor((double)A.size()/2));
        vector<int> C(ceil((double)A.size()/2));

        copy(A.begin(), A.begin() + (floor(A.size()/2)), B.begin());    
        copy(A.begin() + (floor(A.size()/2)), A.end(), C.begin());

        //divide o vetor
        mergeSort(B);   
        mergeSort(C);
        merge(B,C,A);
    }
}

int partition(vector<int> & a, int l, int r){

    int p = a[l];   //pivô é sempre o primeiro elemento
    int i = l, j = r + 1;   

    while(true){
        while(true){
            i++;
            if(a[i] >= p) break;
        }
        while(true){
            j--;
            if(a[j] <= p) break;
        }
        swap(a[i],a[j]);
        
        if(i >= j) break;
    }

    swap(a[i],a[j]);
    swap(a[l],a[j]);

    return j;
}

void quickSort(vector<int> & v, int l, int r){
    if(l < r){
        int s = partition(v, l, r); //seleciona o pivo e deixa todos os numeros menores que o pivô no lado esquerdo
                                    //os numertos maiores no lado direito
        
        quickSort(v,l,s-1); //ordena o sub vetor dos valores menores que o pivo
        quickSort(v,s+1,r); //ordena o sub vetor dos valores mairoes que o pivo
    }
}

//vai inserindo o menor elemento no incio do vetor.
//começa comparando com um conjunto de 2 elementos do vetor, depois adiciona mais 1 elemento e insere ele no lugar correto
void insertionSort(vector<int> & a){
    int v;
    int j;
    for(int i = 1; i < a.size(); i ++){
        v = a[i];
        j = i - 1;

        while(j>=0 && a[j] > v){
            a[j+1] = a[j];
            j --;
        }
        a[j+1] = v;
    }   
}

void quickSort_insertionSort(vector<int> & v){
    if(v.size() >= 15) quickSort(v, 0, v.size() - 1);
    else insertionSort(v);
}

void execute(int n, vector<int> v1){
    cout << "-------------------------Para n = " << n << "------------------------- " << endl;
    
    chrono::time_point<chrono::high_resolution_clock> tp1, tp2;
    tp1 = chrono::high_resolution_clock::now();   //ponto inicial

    bubbleSort(v1);
    
    tp2 = chrono::high_resolution_clock::now();
    double tt = chrono::duration<double,ratio<1,1>> (tp2 - tp1).count(); 
    cout << "Bubble Sort " << fixed << setprecision(2) << tt << " segundos" << endl;
    
    tp1 = chrono::high_resolution_clock::now(); 
    
    selectionSort(v1);
    
    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1>> (tp2 - tp1).count(); 
    cout << "Selection Sort " << fixed << setprecision(2) << tt << " segundos" << endl;

    tp1 = chrono::high_resolution_clock::now(); 

    mergeSort(v1);
    
    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1>> (tp2 - tp1).count(); 
    cout << "Merge Sort " << fixed << setprecision(2) << tt << " segundos" << endl;

    tp1 = chrono::high_resolution_clock::now(); 

    quickSort(v1,0, v1.size() - 1);
    
    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1>> (tp2 - tp1).count(); 
    cout << "Quick Sort " << fixed << setprecision(2) << tt << " segundos" << endl;

  
    tp1 = chrono::high_resolution_clock::now(); 

    quickSort_insertionSort(v1);
    
    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1>> (tp2 - tp1).count(); 
    cout << "Quick_Insertion Sort " << fixed << setprecision(2) << tt << " segundos" << endl;


}

int main(){
    int n1 = 50000;
    int n2 = 100000;
    int n3 = 500000;
    int n4 = 1000000;
    
    vector<int> v1(n1);
    vector<int> v2(n2);
    vector<int> v3(n3);
    vector<int> v4(n4);

    chrono::time_point<chrono::high_resolution_clock> tp1,tp2;
    tp1 = chrono::high_resolution_clock::now();   //ponto inicial
      
    for(int i = 0; i < n1; i ++) v1[i] = rand()%200;
    for(int i = 0; i < n2; i ++) v2[i] = rand()%200;
    for(int i = 0; i < n3; i ++) v3[i] = rand()%200;
    for(int i = 0; i < n4; i ++) v4[i] = rand()%200;
    for(int i = 0; i < n4; i ++) v4[i] = rand()%200;

    tp2 = chrono::high_resolution_clock::now();
    double tt=chrono::duration<double,ratio<1,1>> (tp2-tp1).count(); 
    cout << "Tempo para criação dos vetores: " << fixed << setprecision(2) << tt << " segundos" << endl;
    
    execute(n1,v1);
    execute(n2,v2);
    execute(n3,v3);
    execute(n4,v4);

    return 0;
}