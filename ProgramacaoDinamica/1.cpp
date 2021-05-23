#include <iostream>
#include <vector>
#include <set>
using namespace std;

int coinRow(vector<int> coins){
    vector<int> F(coins.size() + 1);
    vector<set<int>> choice(coins.size());

    F[0] = 0; F[1] = coins[0];
    choice[0].insert(coins[0]);

    for(int i = 1; i < coins.size(); i ++){
        if(F[i - 1] + coins[i] > F[i]){
            F[i + 1] = F[i - 1] + coins[i];
            choice[i] = choice[i - 1];
            choice[i].insert(coins[i]);
        }
        else{
            F[i + 1] = F[i];
            choice[i] = choice[i - 1];
        }
    }

    for(auto it = choice[coins.size() - 1].begin(); it != choice[coins.size() - 1].end(); it ++)
        cout << (*it) << " ";
    cout << endl;
    
    return F[coins.size()];
}

int main(){
    vector<int> coins{10,2,4,20,12,1};

    cout << coinRow(coins) << endl;
    
    return 0;
}