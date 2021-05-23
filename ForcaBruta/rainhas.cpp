#include<iostream>
#include<cmath>
#include<cstdio>
#include<vector>
using namespace std;

bool possivel(vector<int> rainhas, int r, int coluna){
    for(int i = 0; i < r; i ++){
        if(rainhas[i] == coluna) return false;
       
        if(abs(r - i) == abs(coluna - rainhas[i])) return false;
    }
    return true;
}

void backtracking(vector<int> & rainhas, int r, int n, int aux){
    if(r == n){
        cout << "Solucao " << aux << ": (x1, x2, x3, x4) = ";
        cout << "(";
        for(int i = 0; i < n; i ++){
            if(i == n - 1) cout << rainhas[i] + 1; 
            else cout << rainhas[i] + 1 << ",";
        }
        cout << ")" << endl;

        for(int i = 0; i < n; i ++){
            for(int j = 0; j < n; j ++){
                if(j == rainhas[i]) cout << i + 1 << " ";
                else cout << "-" << " ";
            }
            cout << endl;
        }
        aux ++;
        return;
    }
    
    else{
        for(int coluna = 0; coluna < n; coluna ++){
            if(possivel(rainhas, r, coluna)){
                rainhas[r] = coluna;
                backtracking(rainhas, r+1, n, aux ++);
            }
        }
    }
}

int main(){
    vector<int> rainhas(5);

    backtracking(rainhas, 0, 5,0);

    return 0;
}