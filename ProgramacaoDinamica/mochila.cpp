#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
using namespace std;    

int mochila2(int i, int j, vector<vector<int>> &F, vector<int> &w, vector<int> &v){
    int value; 

    if(F[i][j] < 0){
        if(j < w[i-1]){
            value = mochila2(i-1,j,F,w,v);
        }
        else {
            value = max(mochila2(i-1,j,F,w,v), v[i-1] + mochila2(i-1,j-w[i-1],F,w,v));
        }
        F[i][j] = value;
    }

    return F[i][j];
}

vector<vector<int>> genSubSets(int n){
    vector<vector<int>> subSets;
    for (int i=0;i<pow(2,n); i++){
        vector<int> temp;

        for (int j=0; j<n; j++){
            if (((1<<j) & i)){
                temp.push_back(j);
            }
        }
        subSets.push_back(temp);
    }

    return subSets;
}

//INÍCIO QUESTÃO 11C)
void ruckSackBrute(vector<int> &w, vector<int> &v, int W, int n){
    vector<vector<int>> subSets = genSubSets(n);
    vector<int> items;
    int maxValue = 0;

    for (int i=0; i<subSets.size(); i++){
        int tempValue=0;
        int tempWeight=0;
        for (int j=0; j<subSets[i].size(); j++){
            tempValue += v[subSets[i][j]]; tempWeight+=w[subSets[i][j]];
        }
        if (tempWeight<=W && tempValue>=maxValue){
            items=subSets[i];
            maxValue=tempValue;
        }
    }
    cout << "(BRUTE)Total value in the rucksack: " << maxValue << endl;
    cout << "Items in the rucksack:\n";
   
    for (int i=items.size()-1; i>=0; i--){
        cout << "Weight: " << w[items[i]] << " Value: " << v[items[i]] << endl;
    }
    cout << endl;
}


int main(){
    int n, W;

    cin >> n >> W;
    
    vector<int> w;
    vector<int> v;

    int aux1, aux2; 

    chrono::time_point<chrono::high_resolution_clock> tp1,tp2;
    tp1 = chrono::high_resolution_clock::now(); 

    for(int i = 0; i < n; i ++){
        cin >> aux1 >> aux2;

        w.push_back(aux1);
        v.push_back(aux2);
    }
    

    vector<vector<int>> F(n+1,vector<int>(W+1,-1));
    for(int i = 0; i < n+1; i ++) F[i][0] = 0;
    for(int j = 0; j < W+1; j ++) F[0][j] = 0;

    tp2 = chrono::high_resolution_clock::now();
    double tt = chrono::duration<double,ratio<1,1000>> (tp2-tp1).count(); 
    cout << "Leitura e criação da taneça " << fixed << setprecision(2) << tt << " milissegundos" << endl << endl;

    tp1 = chrono::high_resolution_clock::now();
    mochila2(n,W,F,w,v);

    int total = F[n][W];
    cout << "(PD)Total value in the rucksack: " << total << endl;
    int i=n; int j=W;
    cout << "Items in the rucksack:\n";
 
    while (i>0 && total>0){
        if (total==F[i-1][j]){
            i--;continue ;
        }
        else {
            cout << "Weight: " << w[i-1] << " Value: " << v[i-1] << endl;
            total -= v[i-1];
            j -= w[i-1];
            i--;
        }
    }

    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1000>> (tp2 - tp1).count(); 
    cout << "Tempo PD: " << fixed << setprecision(2) << tt << " milissegundos" << endl << endl;



    tp1 = chrono::high_resolution_clock::now();
    ruckSackBrute(w,v,W,n);
    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1000>> (tp2 - tp1).count(); 
    cout << "Tempo Bruta: " << fixed << setprecision(2) << tt << " milissegundos" << endl << endl;

    return 0;
}