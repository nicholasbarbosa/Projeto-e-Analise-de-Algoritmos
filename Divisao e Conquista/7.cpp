#include<iostream>
#include<vector>
#include<cmath>

using namespace std;
int Hoare(vector<int> & a, int l, int r){
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

int division(vector<int> & v, int l, int r){
    int s = Hoare(v, l, r); //seleciona o pivo e deixa todos os numeros menores que o pivô no lado esquerdo
                                //os numertos maiores no lado direito
    
    if (s == (int)(v.size()/2 + 0.5)) return s;
    if(s > (int)(v.size()/2 + 0.5)) s = division(v,l,s-1);
    else s = division(v,s+1, r);
        

    return s;
}

int main(){
    vector<int> v{1,2,3};
    
    //division(v,0,v.size()-1);
    cout << v[division(v,0,v.size()-1)] << endl;

    return 0;
}