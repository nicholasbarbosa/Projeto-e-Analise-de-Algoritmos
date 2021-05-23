#include <iostream>
#include <vector>
#include <set>
using namespace std;

int changeMaking(vector<int> coins, int troco){
    vector<int> F(troco + 1);
    vector<vector<int>> moedas(troco + 1);
    F[0] = 0; moedas[0].push_back(0);

    for(int i = 1; i <= troco; i ++){
        int temp = 99999;
        moedas[i] = moedas[i - 1];

        for(int j = 0; j < coins.size(); j ++){
            if(i < coins[j]) break;
        
            if(F[i - coins[j]] < temp){
                temp = F[i - coins[j]];

                moedas[i] = moedas[i - coins[j]];
                moedas[i].push_back(coins[j]);
            }
        }

        F[i] = temp + 1;
    }

    for(auto it = moedas[troco].begin(); it != moedas[troco].end(); it ++)
        if((*it) == 0) continue;
        else cout << (*it) << " ";
    cout << endl;

    return F[troco]; 
}

int main(){
    vector<int> v{1, 3, 4, 5};

    cout << changeMaking(v,8) << "\n";

    return 0;
}