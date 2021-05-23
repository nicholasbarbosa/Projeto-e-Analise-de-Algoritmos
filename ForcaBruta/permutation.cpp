#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

long long int possivel(vector<vector<int>> m, vector<int> resp){
    int aux = 0;
    for(int i = 0; i < m.size(); i ++){
            if (m[resp[i] - 1][resp[i + 1] - 1] == 0) return 100000000000000;
            else aux += m[resp[i] - 1][resp[i + 1] - 1];
    }
    return aux;
}

void per(int n, vector<int> resp, vector<int> conjunto, vector<vector<int>> m, long long int & menor, vector<int> & perm){
    
    if(conjunto.size() == 0 ){  //se o conjunto for zero, quer dizer que ja usamos todos os elementos
        resp.push_back(resp[0]); //adiciona o primeiro elemento no final do vetor para mostrar que é um ciclo
        
        int comp = 0;
        
        comp = possivel(m,resp);    //retorna a soma dos caminhos. se nao for um ciclo hamiltoniano, retorna um numero 
                                    //muito grande
        if(comp < menor){           //resposta final
            menor = comp;
            perm = resp;
        }

        return;
    }
    else{
        for(int i = 0; i < conjunto.size(); i ++){
            vector<int> a = resp;       //vetores auxiliares
            vector<int> b = conjunto;

            a.push_back(conjunto[i]);   //adiciona um elemento do conjunto à resposta
            b.erase(b.begin() + i);     //retira o elemento para nao repetir

            per(n,a,b,m, menor, perm);
        }
    }
}

int main(){
    int n;
    cin >> n;
    
    vector<int> conjunto(n);
    vector<int> resp;
    vector<vector<int>> m(n, vector<int>(n)); 
    long long int menor = 100000000000000;
    vector<int> perm;


    for(int i = 0; i < n; i ++){
        conjunto[i] = i+1;
        for(int j = 0; j < n; j ++){
            cin >> m[i][j];

        }
    }
    per(n, resp, conjunto,m, menor, perm);

    for(int i = 0; i < perm.size(); i ++){
        if(i + 1 < perm.size()) cout << perm[i] << " --> ";
        else cout << perm[i] << endl;
    }
    
    cout << menor << endl;

    return 0;
}