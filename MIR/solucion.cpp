#include "solucion.h"
#include "auxiliares.h"
#include <algorithm>


using namespace std;


bool formatoValido(audio a, int canal, int profundidad) {
    if (canal > 0 && profundidad > 0 && a.size() > 0 && (a.size() % canal == 0)) {
        return tieneProfundidadValida(a, profundidad);
    } else {
        return false;

    }

}

audio replicar(audio a, int canal, int profundidad) {
    audio b;
    for (int i = 0; i < a.size(); i++) {
        int j = 0;
        while (j < canal) {
            b.push_back(a[i]);
            j++;
        }
    }
    return b;
}

audio revertirAudio(audio a, int canal, int profundidad) {
    audio b;
    for (int i = 0; i < (a.size() / canal); i++) {
        for (int j = 0; j < canal; ++j) {
            b.push_back(a[a.size() - canal * (i + 1) + j]);
        }
    }
    return b;
}

void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos) {
    for (int i = 0; i < canal; ++i) {
        int max = 0;
        int posMax = 0;
        for (int j = i; j < a.size(); j += canal) {
            if (abs(a[j]) > max) {
                max = a[j];
                posMax = j;
            }
        }
        maximos.push_back(max);
        posicionesMaximos.push_back(posMax);
    }
}

audio redirigir(audio a, int canal, int profundidad) {
    if (canal == 1) {
        for (int i = 0; i < a.size(); i += 2) {
            a[i + 1] = a[i + 1] - a[i];
            if (a[i + 1] >= pow(2, (profundidad - 1))) {
                a[i + 1] = pow(2, profundidad - 1) - 1;
            }
            if (a[i + 1] < -pow(2, profundidad - 1)) {
                a[i + 1] = -pow(2, profundidad - 1);
            }
        }

    } else {
        for (int i = 0; i < a.size(); i += 2) {
            a[i] = a[i] - a[i + 1];
            if (a[i] >= pow(2, (profundidad - 1))) {
                a[i] = pow(2, profundidad - 1) - 1;
            }
            if (a[i] < -pow(2, profundidad - 1)) {
                a[i] = -pow(2, profundidad - 1);
            }
        }
    }

    return a;
}


void bajarCalidad(vector<audio> &as, int profundidad1, int profundidad2) {
    for (int i = 0; i < as.size(); ++i) {
        for (int j = 0; j < as[i].size(); ++j) {
            as[i][j] = (as[i][j]) / (pow(2, profundidad1 - profundidad2));
        }
    }
}

void
audiosSoftYHard(vector<audio> as, int profundidad, int longitud, int umbral, vector<audio> &soft, vector<audio> &hard) {
    for (int i = 0; i < as.size(); ++i) {
        vector<audio> a = subAudiosDeLongitud(as[i], longitud);
        int contador = 0;
        for (int j = 0; j < a.size(); ++j) {
            int contador = 0;
            for (int k = 0; k < a[j].size(); ++k) {
                if (a[j][k] > umbral) {
                    contador++;
                }
            }
            if (contador == a[j].size()) {
                hard.push_back(as[i]);
                j = a.size();
                as.erase(as.begin() + i);
            }
        }
    }
    soft = as;
}

void reemplazarSubAudio(audio &a, audio a1, audio a2, int profundidad) {
    vector<audio> subAudios = subAudiosDeLongitud(a, a1.size());
    int aparicion = 0;
    int indiceDeAparicion = 0;
    audio aux;
    for (int i = 0; i < subAudios.size(); ++i) {
        if (subAudios[i] == a1) {
            aparicion++;
            indiceDeAparicion = i;
        }
    }
    if (aparicion > 0) {
        for (int i = 0; i < a.size() - (subAudios[indiceDeAparicion].size() + indiceDeAparicion); ++i) {
            aux.push_back(a[a.size() - 1 - i]); // Lo pongo al reves en aux
        }
        for (int i = 0; i < aux.size(); ++i) {
            a.pop_back();
        }
        for (int j = 0; j < a1.size(); ++j) {
            a.pop_back();
        }
        for (int k = 0; k < a2.size(); ++k) {
            a.push_back(a2[k]);
        }
        for (int l = 0; l < aux.size(); ++l) {
            a.push_back(aux[aux.size() - 1 - l]); // Y aca lo meto al reves para recuperar el orden
        }
    }
}

void maximosTemporales(audio a, int profundidad, vector<int> tiempos, vector<int> &maximos,
                       vector<pair<int, int> > &intervalos) {
    //Primero calculo los intervalos
    for (int j = 0; j < tiempos.size(); ++j) {
        for (int i = 0; i < a.size(); i += tiempos[j]) {
            pair<int, int> intervalo = {i, i + tiempos[i] - 1};
            intervalos.push_back(intervalo);
        }
    }


    //Y ahora calculo los maximos de esos intervalos
    for (int i = 0; i < intervalos.size(); ++i) {
        audio aux;
        for (int j = intervalos[i].first; j <= intervalos[i].second; ++j) {
            if (j >= a.size()) {
                aux.push_back(a[a.size() - 1]);
            } else {
                aux.push_back(a[j]);
            }
        }
        int max = maximoDeUnAudio(aux);
        maximos.push_back(max);
    }
}

void limpiarAudio(audio &a, int profundidad, vector<int> &outliers) {
    //Primero calculo los outliers

    if (a.size() != 1) {
        audio audioOrdenado = selectionSort(a);
        int percentil95 = audioOrdenado[(int) ((a.size() * 95) / 100)];
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] > percentil95) {
                outliers.push_back(i);
            }
        }
        if (outliers.size() > 0) {
            for (int i = 0; i < outliers.size(); ++i) {
                int noOutlierDerecha = buscarNoOutlierDerecha(a, outliers[i], percentil95);
                int noOutlierIzquierda = buscarNoOutlierIzquierda(a, outliers[i], percentil95);
                // Separo en los tres casos especificados
                if ((noOutlierDerecha >= 0) && noOutlierIzquierda >= 0) {
                    a[outliers[i]] = (a[noOutlierDerecha] + a[noOutlierIzquierda]) / 2;
                }
                if ((noOutlierDerecha >= 0) && (noOutlierIzquierda == -1)) {
                    a[outliers[i]] = a[noOutlierDerecha];
                }
                if ((noOutlierDerecha == -1) && (noOutlierIzquierda >= 0)) {
                    a[outliers[i]] = a[noOutlierIzquierda];
                }
            }
        }
    }
}


