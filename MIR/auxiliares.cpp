#include <algorithm>
#include <gtest/gtest.h>
#include "auxiliares.h"


bool vectoresOrdenadosIguales(vector<int> vector1, vector<int> vector2){
    if(vector1.size() != vector2.size())
        return false;

    for (int i = 0; i < vector1.size(); ++i)
        if (vector1[i] != vector2[i]){return false;}

    return true;
}

bool tieneProfundidadValida(audio a, int profundidad) {
    int i = 0;
    while (i < a.size()) {
        if (((-2) ^ (profundidad - 1)) <= a[i] <= ((2 ^ (profundidad - 1)) - 1)) {
            i++;
        } else {
            return false;
        }
    }
    return true;
}



vector<audio> subAudiosDeLongitud (audio a, int longitud){
    vector<audio> b;
    if (longitud > a.size()){
        return b;
    }
    int max = longitud -1;
    int min= 0;
    audio v;
    int tamano = a.size()-longitud+1;
    vector<audio> subAudio (tamano, v);
    int j = 0;
    while (max<a.size()){
        for (int i = min; i <= max; ++i) {
            subAudio[j].push_back(a[i]);
        }
        min++;
        max++;
        j++;
    }
    return subAudio;
}


vector<pair<int, int>> intervalosDeTiempo (audio a, int tiempo){
    vector<pair<int, int>> res;
    for (int i = 0; i < a.size(); i+=tiempo) {
        pair<int, int> intervalo;
        intervalo.first = i;
        intervalo.second = i + tiempo -1;
        res.push_back(intervalo);
    }
    return res;
}

int maximoDeUnAudio (audio a){
    int max = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i]>max){
            max = a[i];
        }
    }
    return max;
}

audio selectionSort(audio a){
    audio res;
    for (int i = 0; i < a.size(); ++i) {
        int min = 0;
        int posMin = 0;
        for (int j = 0; j < a.size()-i; ++j) {
            if (a[j]< min){
                min = a[j];
                posMin = j;
            }
        }
        res.push_back(min);
        res.erase(res.begin() + posMin);
    }
    return res;
}


int buscarNoOutlierDerecha(audio a, int i, int percentil95){
    int noHayNoOutlier = -1;
    for (int j = i + 1; j < a.size(); ++j) {
        if (a[j]<percentil95){
            return j;
        }
    }
    return noHayNoOutlier;
}


int buscarNoOutlierIzquierda(audio a, int i, int percentil95){
    int noHayNoOutlier = -1;
    for (int j = i -1; j >= 0; j--) {
        if (a[j]<percentil95){
            return j;
        }
    }
    return noHayNoOutlier;
}



bool todasSusFilasEnLaOtraMatriz(vector<vector<int> > mat1, vector<vector<int> > mat2) {
    bool res;
    
    for (int i = 0; i < mat1.size(); ++i){
        res = false;
        for (int j = 0; j < mat2.size(); ++j) {
            if (vectoresOrdenadosIguales(mat1[i], mat2[j])) {
                res = true;
                break;
            }
        }
        if(!res)
            return false;
    }

    return true;
}

bool matricesIguales(vector<vector<int> > mat1, vector<vector<int> > mat2){
    if(mat1.size() != mat2.size())
        return false;

    for (int i = 0; i < mat1.size(); ++i) {
        sort(mat1[i].begin(), mat1[i].end());
        sort(mat2[i].begin(), mat2[i].end());
    }

    return todasSusFilasEnLaOtraMatriz(mat1,mat2) && todasSusFilasEnLaOtraMatriz(mat2,mat1);
}

void ASSERT_VECTOR(vector<int> vector1, vector<int> vector2) {
    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());

    ASSERT_TRUE(vectoresOrdenadosIguales(vector1, vector2));
}

void ASSERT_MATRIX(vector<audio> mat1, vector<audio> mat2) {
    ASSERT_TRUE(matricesIguales(mat1, mat2));
}