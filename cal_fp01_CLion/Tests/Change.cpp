/*
 * Change.cpp
 */

#include "Change.h"
#include "limits.h"
#include "algorithm"
#include "iostream"

/*
 *  Queremos calcular o troco usando primeiro as moedas maiores de maneira
 *  a minimizar o numero de moedas do troco.
 *
 *  Exemplo:
 *      Ao devolver o troco de 14cents, devemos ter 2 moedas de 5cents e 2 moedas de 2cents.
 *      assumindo que temos moedas de 5, 2 e 1 centimo.
 *
 *
 *      --- Programação Dinâmica ---
 *
 *  Para implementar programação dinâmica é essencial dividir o problema em subproblemas, neste problema
 *  podemos pensar que temos de escolher a melhor das seguintes opções:
 *
 *      - Selecionando a maior moeda: (quantia - valor da moeda que adicionamos);
 *      - Ignorando a maior moeda: neste caso queremos fazer o valor da quantia com todas as moedas exceto a maior.
 *
 *  Neste problema escolher a *melhor* opção significa escolher aquela que for menor. Se a maior moeda não exceder a soma
 *  que queremos, então escolhemos a menor das opções. Caso contrário, escolhemos a segunda opção e ignoramos a maior moeda,
 *  como se nunca tivesse existido.
 *
 *
 *      --- Solução Recursiva ---
 *
 *  O objetivo parte deste problema, usando DP, é implementar um array para guardar o estado das soluções para o subproblemas,
 *  desta forma não vamos estar a calcular algo que já foi calculado vezes sem conta.
 *  Cada elemento do array 2D diz-nos o numero minimo de moedas necessario para fazer a quantia j, considerando apenas as
 *  primeiras i moedas.
 *
 *  Vamos usar um array semelhante para guardar o valor da ultima moeda usada em cada iteração para ajudar a determinar a
 *  melhor solução para o nosso problema
 *
 */

/**
 * @brief Função para mostrar tabelas de arrays 2d (minCoins e lastCoin)
 * @param m
 * @param numCoins
 * @param coinValues
 * @param table
 */
void printTable(int m, int numCoins, int* coinValues, int** table) {
    cout << "i/j";
    for (int j = 1; j < m + 1; j++) {
        cout << "\t" << j;
    }
    cout << endl;
    for (int i = 1; i < numCoins + 1; i++) {
        cout << i << "\t";
        for (int j = 1; j < m + 1; j++) {
            cout << table[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}


string calcChange(int m, int numCoins, int* coinValues) {
    // criar um array 2D para guardar soluções para os subproblemas
    int** minCoins = new int*[numCoins + 1];
    int** lastCoin = new int*[numCoins + 1];

    for (int i = 0; i < numCoins + 1; i++) {
        minCoins[i] = new int[m + 1];
        lastCoin[i] = new int[m + 1];
    }

    // inicializar a primeira coluna a zero
    // uma vez que são necessarias zero moedas para fazer o total de 0
    for (int i = 0; i < numCoins + 1; i++) {
        minCoins[i][0] = 0;
    }

    // inicializar a primeira linha com INT_MAX (valor indefinido) ou 1000000 (valor grande)
    // uma vez que não conseguimos fazer nenhuma quantia com 0 moedas
    for (int j = 0; j < m + 1; j++) {
        minCoins[0][j] = 1000000;
    }

    // solução recursiva
    for (int i = 1; i < numCoins + 1; i++) {
        for (int j = 1; j < m + 1; ++j) {
            if (coinValues[i - 1] > j) {    // não é possivel escolher a maior moeda
                minCoins[i][j] = minCoins[i - 1][j];
                lastCoin[i][j] = lastCoin[i - 1][j]; // lastCoin toma o valor da linha anterior
            }
            else {
                // escolher a melhor opção:
                if (1 + minCoins[i][j - coinValues[i - 1]] <= minCoins[i - 1][j]) {
                    // lastCoin toma o valor da maior moeda
                    lastCoin[i][j] = coinValues[i - 1];
                }
                else {
                    // lastCoin toma o valor da linha anterior
                    lastCoin[i][j] = lastCoin[i - 1][j];
                }
                minCoins[i][j] = min(1 + minCoins[i][j - coinValues[i - 1]], minCoins[i - 1][j]);
            }
        }
    }

    // funçoes para mostrar as tabelas preenchidas de minCoins(i,j) e lastCoin(i,j):

    // printTable(m, numCoins, coinValues, minCoins);
    // printTable(m, numCoins, coinValues, lastCoin);

    string res = "";

    // podemos ir retirando a quantia total o valor da ultima moeda
    // e assim calcular novamente o lastCoin até que m seja zero.
    while ( m != 0) {
        int prev = m;

        res += to_string(lastCoin[numCoins][m]) + ";";
        m -= lastCoin[numCoins][m];

        // para quando não conseguimos dar troco com as moedas que temos
        if (prev == m) {
            return "-";
        }
    }

    return res;
}


