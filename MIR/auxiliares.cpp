#include <algorithm>
#include <gtest/gtest.h>
#include "auxiliares.h"


bool vectoresOrdenadosIguales(vector<int> vector1, vector<int> vector2) {
    if (vector1.size() != vector2.size())
        return false;

    for (int i = 0; i < vector1.size(); i++)
        if (vector1[i] != vector2[i]) { return false; }

    return true;
}


bool tieneProfundidadValida(audio a, int profundidad) {
    int i = 0;
    while (i < a.size()) {
        if (-pow(2, profundidad - 1) <= a[i] && a[i] <= pow(2, profundidad - 1) - 1) {
            i++;
        } else {
            return false;
        }
    }
    return true;
}

void revertirBloque(audio a, audio &b, int canal, int i) {
    for (int j = 0; j < canal; ++j) {
        b.push_back(a[a.size() - canal * (i + 1) + j]);
    }
}

void maximoDelCanal(audio a, int canal, int i, int &max, int &posMax) {
    for (int j = i; j < a.size(); j += canal) {
        if (abs(a[j]) > max) {
            max = a[j];
            posMax = j;
        }
    }
}

void ajustarTope(audio &a, int canal, int profundidad, int i) {
    if (canal == 1) {
        if (a[i + 1] >= pow(2, (profundidad - 1))) {
            a[i + 1] = pow(2, profundidad - 1) - 1;
        }
        if (a[i + 1] < -pow(2, profundidad - 1)) {
            a[i + 1] = -pow(2, profundidad - 1);
        }
    } else {
        if (a[i] >= pow(2, (profundidad - 1))) {
            a[i] = pow(2, profundidad - 1) - 1;
        }
        if (a[i] < -pow(2, profundidad - 1)) {
            a[i] = -pow(2, profundidad - 1);
        }
    }

}

void ajustarAudio(vector<audio> &as, int i, int profundidad1, int profundidad2) {
    for (int j = 0; j < as[i].size(); ++j) {
        double b = as[i][j];
        b = floor(b / (pow(2, profundidad1 - profundidad2)));
        as[i][j] = (int) b;
    }
}


bool esHardOSoft(vector<audio> as, int longitud, int umbral, int contador, int i) {
    bool esHard = false;
    for (int j = 0; j < as[i].size(); ++j) {
        if (contador == longitud + 1) {
            esHard = true;
        }
        if (as[i][j] > umbral) {
            contador++;
        } else {
            contador = 0;
        }
    }
    return esHard;
}



void buscoAparicion(audio a, audio a1, bool &pertenece, int &indiceDeAparicion) {
    int contador = 0;
    for (int i = 0; i < a.size() && !pertenece; i++) {
        if (a[i] == a1[0]) {
            contador = 1;
            for (int j = 1; j < a1.size() && (a[j + i] == a1[j]); j++) {
                contador++;
            }
            if (contador == a1.size()) {
                pertenece = true;
                indiceDeAparicion = i;
            }
        }
    }
}


void reemplazarAparicion(audio &a, audio a1, audio a2, int indiceDeAparicion, bool pertenece) {
    audio b;
    if (pertenece==true) {
        for (int i = 0; i < indiceDeAparicion; ++i) {
            b.push_back(a[i]);
        }
        for (int j = 0; j < a2.size(); ++j) {
            b.push_back(a2[j]);
        }
        for (int k = indiceDeAparicion + a1.size(); k < a.size(); ++k) {
            b.push_back(a[k]);
        }
        a = b;
    }

}


void conseguirIntervalos(audio a, vector<int> tiempos, vector<pair<int, int> > &intervalos) {
    for (int j = 0; j < tiempos.size(); ++j) {
        for (int i = 0; i < a.size(); i += tiempos[j]) {
            pair<int, int> intervalo = {i, i + tiempos[j] - 1};
            intervalos.push_back(intervalo);
        }
    }
}


void maximosDeLosIntervalos(audio a, vector<int> &maximos, vector<pair<int, int> > &intervalos) {

    for (int i = 0; i < intervalos.size(); ++i) {
        int max = 0;
        for (int j = intervalos[i].first;
             j < a.size() && j <= intervalos[i].second; ++j) {
            if (a[j] > max) {
                max = a[j];

            }
        }
        maximos.push_back(max);
    }
}


void buscoOutliers (audio a, vector<int> &outliers, int &percentil95){
     audio a0 = a;
    audio audioOrdenado = selectionSort(a0);
    percentil95 = audioOrdenado[(int) (floor(((a.size() * 95) / 100) - 1))];
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] > percentil95) {
            outliers.push_back(i);
        }
    }

}

void reemplazoOutliers (audio &a, vector<int> &outliers, int &percentil95){
    for (int i = 0; i < outliers.size(); ++i) {
        int noOutlierDerecha = buscarNoOutlierDerecha(a, outliers[i], percentil95);
        int noOutlierIzquierda = buscarNoOutlierIzquierda(a, outliers[i], percentil95);
        if ((noOutlierDerecha >= 0) && noOutlierIzquierda >= 0) {
            double b = (a[noOutlierDerecha] + a[noOutlierIzquierda]);
            b = floor(b / 2);
            a[outliers[i]] = (int) b;
        }
        if ((noOutlierDerecha >= 0) && (noOutlierIzquierda == -1)) {
            a[outliers[i]] = a[noOutlierDerecha];
        }
        if ((noOutlierDerecha == -1) && (noOutlierIzquierda >= 0)) {
            a[outliers[i]] = a[noOutlierIzquierda];
        }
    }
}


audio selectionSort(audio &a) {
    int aux;
    for (int j = 0; j < a.size() - 1; ++j) {
        int min = a[j];
        aux = j;
        for (int i = j + 1; i < a.size(); ++i) {
            if (min > a[i]) {
                min = a[i];
                aux = i;
            }
        }
        swap(a[j], a[aux]);
    }
    return a;
}


int buscarNoOutlierDerecha(audio a, int i, int percentil95) {
    int noHayNoOutlier = -1; //O(1)
    for (int j = i + 1; j < a.size(); j++) { //O(a.size() - i)
        if (a[j] < percentil95) { //O(1)
            return j;//O(1)
        }
    }
    return noHayNoOutlier; //O(1)
}


int buscarNoOutlierIzquierda(audio a, int i, int percentil95) {
    int noHayNoOutlier = -1;//O(1)
    for (int j = i - 1; j >= 0; j--) {//O(a.size() - i)
        if (a[j] < percentil95) {//O(1)
            return j; //O(1)
        }
    }
    return noHayNoOutlier;//O(1)
}


bool todasSusFilasEnLaOtraMatriz(vector<vector<int> > mat1, vector<vector<int> > mat2) {
    bool res;

    for (int i = 0; i < mat1.size(); ++i) {
        res = false;
        for (int j = 0; j < mat2.size(); ++j) {
            if (vectoresOrdenadosIguales(mat1[i], mat2[j])) {
                res = true;
                break;
            }
        }
        if (!res)
            return false;
    }

    return true;
}

bool matricesIguales(vector<vector<int> > mat1, vector<vector<int> > mat2) {
    if (mat1.size() != mat2.size())
        return false;

    for (int i = 0; i < mat1.size(); ++i) {
        sort(mat1[i].begin(), mat1[i].end());
        sort(mat2[i].begin(), mat2[i].end());
    }

    return todasSusFilasEnLaOtraMatriz(mat1, mat2) && todasSusFilasEnLaOtraMatriz(mat2, mat1);
}

void ASSERT_VECTOR(vector<int> vector1, vector<int> vector2) {
    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());

    ASSERT_TRUE(vectoresOrdenadosIguales(vector1, vector2));
}

void ASSERT_MATRIX(vector<audio> mat1, vector<audio> mat2) {
    ASSERT_TRUE(matricesIguales(mat1, mat2));
}


bool vectoresDeDuplasOrdenadosIguales(vector<pair<int, int>> vector1, vector<pair<int, int>> vector2) {
    if (vector1.size() != vector2.size())
        return false;

    for (int i = 0; i < vector1.size(); i++)
        if (vector1[i] != vector2[i]) { return false; }

    return true;
}


void ASSERT_VECTOR_DUPLA(vector<pair<int, int>> vector1, vector<pair<int, int>> vector2) {
    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());

    ASSERT_TRUE(vectoresDeDuplasOrdenadosIguales(vector1, vector2));
}