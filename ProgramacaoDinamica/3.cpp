#include <iostream>
using namespace std;

def caminho(matriz[1..n][1..m], i, j, coin):
    if i == 1 && j == 1 then return matriz[i][j]

    coin += matriz[i][j]

    resp1 = caminho(matriz, i, j --, coin)
    resp2 = caminho(matri, i --, j, coin)

    coin = max{resp1, resp2}

    return coin

T(m,n) = T(n, m - 1) + T(n - 1, m) + 1; T(1,1) = 0;

T(m,n) = [T(n, m - 2) + T(n - 1, m - 1) + 1] + [T(n - 1, m - 1) + T(n - 2, m) + 1] + 1
T(m,n) = T(n, m - 2) + 2T(n - 1, m - 1) + T(n - 2, m) + 3
T(m,n) = [T(n, m - 3) + T(n - 1, m - 2) + 1] + 2[[T(n - 1, m - 2) + T(n - 2, m - 1) + 1] + [T(n - 2, m - 1) + T(n - 3, m) + 1] + 3
T(m,n) = T(n, m - 3) + 2T(n - 1, m - 2) + 2T(n - 2, m - 1) + T(n - 3, m) + 6