#include<iostream>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<chrono>
#include<iomanip>

using namespace std;

pair<int,int> func(vector<int> v){
    if(v.size() == 2) return {max(v[0],v[1]),min(v[0],v[1])};

    vector<int> b(floor((double)v.size()/2));
    vector<int> c(ceil((double)v.size()/2));

    copy(v.begin(), v.begin() + (floor(v.size()/2)), b.begin());    
    copy(v.begin() + (floor(v.size()/2)), v.end(), c.begin());

    pair<int,int> aux = func(b);
    pair<int,int> aux2 = func(c);

    pair<int,int> resp;

    if(aux.first > aux2.first) resp.first = aux.first;
    else resp.first = aux2.first;

    if(aux.second < aux2.second) resp.second = aux.second;
    else resp.second = aux2.second;

    return resp;
}

int main(){
    vector<int> v={100,-39,15,3,-62,32,8,110};

    pair<int,int> resp = func(v);
    cout << "maior:" <<resp.first << " \nmenor:" << resp.second << endl;
    return 0;
}