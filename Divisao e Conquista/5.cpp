#include<iostream> 
#include<vector>
using namespace std;

int busca(vector<int> v, int elem){
    int l = 0, r = v.size() - 1;
    int m1, m2; 
    while (l <= r){
        cout << " a" << endl;
        m1 =  l+(r-l)/3, m2 = l+2*(r-l)/3; 
        
        if(elem == v[m1]) return m1;
        else if(elem < v[m1]) r = m1 - 1;   //verifica se esta no primeir 1/3
        else{
            l = m1 + 1; 
            
            if(elem == v[m2]) return m2;    //verifica se esta entre 1/3 e 2/3
            else if(elem < v[m2]) {r = m2 - 1;}
            else {
                l = m2 + 1;
            }
        }
    }
    return -1;
}

int main(){
    vector<int> L{1, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    cout << busca(L,2) << endl;
    return 0;
}