#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;

vector<int> scmbruta(vector<int> x){
    int somaMax = 0;
    int I, J;

    for(int i = 0; i < x.size(); i ++){
        int soma = 0;
        for(int j = i; j < x.size(); j ++){
            soma += x[j];
            if(soma > somaMax){
                somaMax = soma;
                I = i; J = j;
            }
        }
    }

    return {I,J,somaMax};
}

vector<int> scmdc(vector<int> x, int l, int r){
    if(x.empty()) return {0,0,0};
    else{
        if(l == r) return {x[l],l,l};

        int s1 = 0, s2 = 0;
        int mid = (l+r)/2;
        int somaMax1 = -99999, somaMax2 = -99999;

        vector<int> somal = scmdc(x,l,mid);         //valor da primeira metade
        vector<int> somar = scmdc(x,mid + 1, r);    //valor da segunda metade

        vector<int> aux(2);

        for(int i = mid; i >= l; i --){             //o maior valor no caso de começar na primeira metade
            s1 += x[i];                             //e terminar na segunda
            if(s1 > somaMax1){
                somaMax1 = s1;
                aux[0] = i;
            }
        }

        for(int i = mid + 1; i <= r; i ++){
            s2 += x[i];
            if(s2 > somaMax2){
                somaMax2 = s2;
                aux[1] = i;
            }
        }

        int somaMax = max(max(somal[0],somar[0]),somaMax1+somaMax2);    //escolhe o mair valor das 3 possibilidades

        int I,J;

        if(somaMax == somal[0]) {I = somal[1]; J = somal[2];}
        else if(somaMax == somar[0]) {I = somar[1]; J = somar[2];}
        else if(somaMax == somaMax1+somaMax2) {I = aux[0]; J = aux[1];}

        return {somaMax,I,J};
    }
}

int scmpd(vector<int> x){
    vector<int> F(x.size() + 1);
    F[0] = 0;

    for(int i = 0; i < x.size(); i ++)
        F[i + 1] = max(F[i] + x[i], x[i]); //a scm do vetor de 0 a i é igual à scm do vetor até i-1 mais o elemento i ou so o elemento i


    int resp = F[0];

    for(auto valor : F){
        if(valor > resp) resp = valor;
    }

    return resp;
}

vector<int> gerateste(int n){
    vector<int> v;

    for(int i = 0; i < n; i ++)
        v.push_back(rand()%200000 - 100000);

    return v;
}

void solve(int n){
    cout << "---------------------n = " << n << "---------------------\n";   
    chrono::time_point<chrono::high_resolution_clock> tp1,tp2;
    tp1 = chrono::high_resolution_clock::now(); 

    vector<int> v = gerateste(n);

    tp2 = chrono::high_resolution_clock::now();
    double tt = chrono::duration<double,ratio<1,1000>> (tp2-tp1).count(); 
    cout << "Tempo para criar o vetor: " << fixed << setprecision(2) << tt << " milissegundos" << endl << endl;

    tp1 = chrono::high_resolution_clock::now();
    
    cout << "Soma: " << scmbruta(v)[2] << "\n";

    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1000>> (tp2 - tp1).count(); 
    cout << "Tempo Bruta: " << fixed << setprecision(2) << tt << " milissegundos" << endl << endl;

    tp1 = chrono::high_resolution_clock::now();

    cout << "Soma: " << scmdc(v, 0, v.size() - 1)[0] << "\n";

    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1000>> (tp2 - tp1).count(); 
    cout << "Tempo divisao e conquista: " << fixed << setprecision(2) << tt << " milissegundos" << endl << endl;

    tp1 = chrono::high_resolution_clock::now();

    cout << "Soma: " << scmpd(v) << "\n";

    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1000>> (tp2 - tp1).count(); 
    cout << "Tempo programacao dinamica: " << fixed << setprecision(2) << tt << " milissegundos" << endl << endl;
}

int main(){

    solve(50000);
    solve(100000);
    solve(500000);
    solve(1000000);
    
    return 0;
}