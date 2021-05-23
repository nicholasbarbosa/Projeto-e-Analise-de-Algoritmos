#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int sum(vector<int> coins){
    int resp = 0;

    for(int a : coins){
        resp += a;
    }

    return resp;
}

int coin(vector<int> coins, int i){
    if(coins.size() == 1) return coins[0];
    if(coins.size() > 1 && coins.size()%2 == 1){
        i = coins[coins.size()-1];
        coins.erase(coins.begin() + coins.size()-1 );

        vector<int> b(floor((double)coins.size()/2));
        vector<int> c(ceil((double)coins.size()/2));

        copy(coins.begin(), coins.begin() + (floor(coins.size()/2)), b.begin());    
        copy(coins.begin() + (floor(coins.size()/2)), coins.end() , c.begin());
    
        int resp;
    
        int S1 = sum(b);
        int S2 = sum(c);

        if(S1 > S2){
            resp = coin(c,i);
        }
        else{
            resp = coin(b,i);
        }

        if(resp < i) return resp;
        else return i;
    }
    else{
        vector<int> b(floor((double)coins.size()/2));
        vector<int> c(ceil((double)coins.size()/2));

        copy(coins.begin(), coins.begin() + (floor(coins.size()/2)), b.begin());    
        copy(coins.begin() + (floor(coins.size()/2)), coins.end(), c.begin());

        int resp;
    
        int S1 = sum(b);
        int S2 = sum(c);

        if(S1 > S2){
            resp = coin(c,i);
        }
        else{
            resp = coin(b,i);
        }

        return resp;
    }
    
}

int main(){
    vector<int> a = {10,3,10,7,0};
    cout << coin(a, -1) << endl;
    return 0;
}