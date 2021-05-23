#include<iostream> 
#include<vector>
#include<cmath>

using namespace std;

int buscaBinaria(int elem, vector<int> & L){
    int l = 0, r = L.size() - 1, m;
    while (l <= r){
        m = (l+r)/2;
        if(elem == L[m]) return m;
        else if(L[m] > elem) r = m - 1;
        else l = m + 1;
    }
    return -1;
}

bool func(vector<int> & L, int elem){
    for(int i = 0; i < L.size(); i ++){
        if(buscaBinaria(elem - L[i], L) != -1 && buscaBinaria(elem - 3, L) != i) return true;
    }
    return false;
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

    for(auto a: A) cout << a << " ";
    cout << endl;
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

int main(){
    vector<int> L{1,3,10,17,20};
    int x = 20;
    vector<int> af{310,285,179,652,351,423,861,254,450,520};
    mergeSort(af);
    if(func(L,x)) cout << "existem 2 elementos pertecentes 'a L que a soma resulta em " << x << endl;
    else cout << "nao existe 2 elementos pertecentes 'a L que a soma resulta em " << x << endl;
    
    return 0;
}