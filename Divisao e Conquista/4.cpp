#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int max(vector<int> x){
    int resp = x[0];
    for(int i = 1; i < x.size(); i ++)
        if(resp < x[i]) resp = x[i];
    
    return resp;
}

int min(vector<int> x){
    int resp = x[0];
    for(int i = 1; i < x.size(); i ++){
        if(x[i] < resp) resp = x[i];
    }

    return resp;    
}

int maxlucro(vector<int> a){
    if(a.size() <= 1) return 0;

    vector<int> b(floor((double)a.size()/2));
    vector<int> c(ceil((double)a.size()/2));

    copy(a.begin(), a.begin() + (floor(a.size()/2)), b.begin());    
    copy(a.begin() + (floor(a.size()/2)), a.end() , c.begin());
    
    int respb;
    int respc;

    respb = maxlucro(b);
    respc = maxlucro(c);
    int over = max(c) - min(b);
    
    return max(max(respb, respc),over);
}

int main(){
    vector<int> a = {4,7,9,1,3,5,6,7};
    cout << maxlucro(a)  << endl;
    return 0;
}