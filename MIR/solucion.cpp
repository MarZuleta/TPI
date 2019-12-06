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
        for (int j = 0; j < canal; ++j) {
            b.push_back(a[i]);
        }
    }
    return b;
}

audio revertirAudio(audio a, int canal, int profundidad) {
    audio b;
    for (int i = 0; i < (a.size() / canal); i++) {
        revertirBloque(a, b, canal, i);
    }
    return b;
}





void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos) {
    for (int i = 0; i < canal; ++i) {
        int max = 0;
        int posMax = 0;
        maximoDelCanal(a, canal, i, max, posMax);
        maximos.push_back(max);
        posicionesMaximos.push_back(posMax);
    }
}


audio redirigir(audio a, int canal, int profundidad) {
    if (canal == 1) {
        for (int i = 0; i < a.size(); i += 2) {
            a[i + 1] = a[i + 1] - a[i];
            ajustarTope(a, canal, profundidad, i);
        }

    } else {
        for (int i = 0; i < a.size(); i += 2) {
            a[i] = a[i + 1] - a[i];
            ajustarTope(a, canal, profundidad, i);
        }
    }

    return a;
}


void bajarCalidad(vector<audio> &as, int profundidad1, int profundidad2) {
    for (int i = 0; i < as.size(); ++i) {
        ajustarAudio(as, i, profundidad1, profundidad2);
    }
}


void
audiosSoftYHard(vector<audio> as, int profundidad, int longitud, int umbral, vector<audio> &soft, vector<audio> &hard) {
    for (int i = 0; i < as.size(); ++i) {
        int contador = 0;
        bool esHard = esHardOSoft(as, longitud, umbral, contador, i);
        if (esHard == true) {
            hard.push_back(as[i]);
        } else {
            soft.push_back(as[i]);
        }
    }

}


void reemplazarSubAudio(audio &a, audio a1, audio a2, int profundidad) {
    int indiceDeAparicion = 0;
    bool pertenece = false;
    buscoAparicion(a, a1, pertenece, indiceDeAparicion);
    reemplazarAparicion(a, a1, a2, indiceDeAparicion, pertenece);
}


void maximosTemporales(audio a, int profundidad, vector<int> tiempos, vector<int> &maximos,
                       vector<pair<int, int> > &intervalos) {
    conseguirIntervalos(a, tiempos, intervalos);
    maximosDeLosIntervalos(a, maximos, intervalos);
}



void limpiarAudio(audio &a, int profundidad, vector<int> &outliers) {
    int percentil95 = 0;
    audio a0 = a;
    if (a.size() > 1) {
        buscoOutliers(a, outliers, percentil95);
    }
    if (outliers.size() > 0) {  //O(1)
        reemplazoOutliers(a0, outliers, percentil95);
    }
    a = a0;
}
