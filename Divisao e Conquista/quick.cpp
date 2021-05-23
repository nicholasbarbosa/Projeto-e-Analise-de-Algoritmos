#include<iostream>
#include<set>
#include<cmath>
#include<vector>
#include<chrono>
#include<iomanip>

using namespace std;

void convex(const set<pair<int,int>> &A){
    set<pair<int,int>> solucao;

    for (auto it=A.begin();it!=A.end();it++){
        for (auto it1=A.begin();it1!=A.end();it1++){
            pair<int,int> p1 = *it;
            pair<int,int> p2 = *it1;

            double a = p2.second - p1.second;
            double b = p1.first - p2.first;
            double c = (p1.first * p2.second) - (p1.second * p2.first);

            vector<pair<int,int>> plano1;
            vector<pair<int,int>> plano2;

            for (auto it2=A.begin();it2!=A.end();it2++){
                if(it2 != it && it2 != it1){
                    if((a*(*it2).first + b*(*it2).second - c) > 0){   //se um ponto for maior que zero, ele está no
                        plano1.push_back(*it2);                        //no plano de cima
                    }
                    if((a*(*it2).first + b*(*it2).second - c) < 0){   //menor que zero, plano de baixo
                        plano2.push_back(*it2);
                    } 

                    if(plano1.size() > 0 && plano2.size() > 0){ //se tiver pontos em 2 planos, não é a reta que queremos
                        plano2.resize(0); plano1.resize(0);
                        break;
                    }
                    if(plano2.size() > 0 && plano1.size() > 0){
                        plano2.resize(0); plano1.resize(0);
                        break;
                    }
                }  
            } 
            if(plano1.size() > 0 || plano2.size() > 0){ //adiciona a reta no conjunto solução
                solucao.insert(*it);
                solucao.insert(*it1);
            }
        }
    }
    cout << "{";
    for (auto it=solucao.begin(); it != solucao.end(); it++){
        cout << "(" << (*it).first << "," << (*it).second << ")";
    }
    cout << "}" << endl;
}

set<pair<int,int>> poligonoConvex(const pair<int,int> &p1, const pair<int,int> &p2, const set<pair<int,int>> &S){
    set<pair<int,int>> init;
    if(S.empty()) return init;

    else{
        double max=0;
        pair<int,int> pmax;

        for (auto it=S.begin(); it!=S.end(); it++){
            double b = p1.first - p2.first;
            double a = p2.second - p1.second;
            double c = (p1.second*p2.first - p1.first*p2.second);
            double dist = abs(a*(*it).first + b*(*it).second + c)/sqrt(a*a+b*b);
            
            if (dist > max){
                pmax = (*it);
                max = dist;
            }
        }
        set<pair<int,int>> S11, S22; 
        int x1, x2, x3, y1, y2, y3;

        x1 = p1.first;
        y1 = p1.second;
        x2 = pmax.first;
        y2 = pmax.second;

        //inserido os pontos em cada sub conjunto
        for(auto it = S.begin(); it != S.end(); it ++){
            x3 = (*it).first;
            y3 = (*it).second;

            if(x1*y2 + x3*y1 + x2*y3 - x3*y2 - x2*y1 - x1*y3 > 0) S11.insert((*it));
        }

        x1 = pmax.first;
        y1 = pmax.second;
        x2 = p2.first;
        y2 = p2.second;

        for (auto it=S.begin(); it!=S.end(); it++){
            x3 = (*it).first; 
            y3 = (*it).second;
            if (x1*y2 + x3*y1 + x2*y3 - x3*y2 - x2*y1 - x1*y3 > 0) S22.insert((*it));
        }

        set<pair<int,int>> solution11 = poligonoConvex(p1,pmax,S11);
        set<pair<int,int>> solution22 = poligonoConvex(pmax,p2,S22);
        
        init.insert(pmax);
        init.insert(solution11.begin(),solution11.end());
        init.insert(solution22.begin(),solution22.end());
        
        return init;
    }
}

void convex2(const set<pair<int,int>> &S){
    if(S.size() >= 2){
        set<pair<int,int>> ec;
        set<pair<int,int>>::iterator it1 = S.begin();
        set<pair<int,int>>::iterator it2 = S.end(); it2 --;

        pair<int,int> pa;
        pair<int,int> pb;

        pa = *it1;
        pb = *it2;

        ec.insert(pa); ec.insert(pb);

        set<pair<int,int>> S1, S2; 
        int x1, x2, x3, y1, y2, y3;

        x1 = pa.first;
        y1 = pa.second;
        x2 = pb.first;
        y2 = pb.second;

        //inserido os pontos em cada sub conjunto
        for(auto it = S.begin(); it != S.end(); it ++){
            if(*it == pa || *it == pb) continue;
            x3 = (*it).first;
            y3 = (*it).second;

            if(x1*y2 + x3*y1 + x2*y3 - x3*y2 - x2*y1 - x1*y3 > 0) S1.insert((*it));
            if(x1*y2 + x3*y1 + x2*y3 - x3*y2 - x2*y1 - x1*y3 < 0) S2.insert((*it));
        }

        set<pair<int,int>> solution1, solution2; 
        solution1 = poligonoConvex(pa,pb,S1);
        solution2 = poligonoConvex(pb,pa,S2);

        ec.insert(solution1.begin(), solution1.end());
        ec.insert(solution2.begin(), solution2.end());

        cout << "{";
        for (auto it=ec.begin(); it != ec.end(); it++){
            cout << "(" << (*it).first << "," << (*it).second << ")";
        }
        cout << "}" << endl;
    }
}

int main(){
    set<pair<int,int>> a;
    int n;

    int x;
    int y;

    cin >> n;

    chrono::time_point<chrono::high_resolution_clock> tp1,tp2;
    tp1 = chrono::high_resolution_clock::now();   //ponto inicial

    for(int i = 0; i < n; i ++){
        cin >> x;
        cin >> y;

        a.insert({x,y});
    }

    tp2 = chrono::high_resolution_clock::now();
    double tt=chrono::duration<double,ratio<1,1000>> (tp2-tp1).count(); 
    cout << "Tempo para ler os pontos: " << fixed << setprecision(2) << tt << " milissegundos" << endl << endl;

    tp1 = chrono::high_resolution_clock::now();   //ponto inicial

    convex(a);

    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1000>> (tp2 - tp1).count(); 
    cout << "Tempo Bruta: " << fixed << setprecision(2) << tt << " milissegundos" << endl << endl;
   
    tp1 = chrono::high_resolution_clock::now();   //ponto inicial

    convex2(a);

    tp2 = chrono::high_resolution_clock::now();
    tt = chrono::duration<double,ratio<1,1000>> (tp2 - tp1).count(); 
    cout << "Tempo Quick " << fixed << setprecision(2) << tt << " milisegundos"<< endl << endl;

    return 0;
}