#include "solucion.h"
#include "auxiliares.h"
#include <algorithm>


using namespace std;


//Para justificar y calcular los tiempos de ejecucion en peor caso
//Comentare al lado de cada linea el costo de ejecucion donde corresponda



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
    audio b;        // O(1)
    for (int i = 0; i < (a.size() / canal); i++) {  //O(n/c) siendo n = a.size() y c = canal
        revertirBloque(a, b, canal, i); // O(c)
    }
    return b;
}
//Sea k la suma de las operaciones O(1), entonces como para cada ejecucion del primer ciclo se ejecuta el segundo, queda O((n/c)*c + k),
// y como se simplifica (n/c)*c queda entonces O(n).






void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos) {
    for (int i = 0; i < canal; ++i) {   // Sea canal = c, esto cicla canal veces, entonces es O(c)
        int max = 0; // O(1)
        int posMax = 0;  //O(1)
        maximoDelCanal(a, canal, i, max, posMax);//O(n/c)
        maximos.push_back(max); //O(1)
        posicionesMaximos.push_back(posMax);  //O(1)
    }
}       // Luego como para cada ciclo de O(c) cicla un for de O(n/c), queda O((n/c)*c), quedando asi O(n)



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
        int contador = 0; //O(1)
        bool esHard = esHardOSoft(as, longitud, umbral, contador, i); // O(L)
        if (esHard == true) { //O(1)
            hard.push_back(as[i]); //O(1)
        } else {
            soft.push_back(as[i]); //O(1)
        }
    }

}
// Sea n = as.size(), el primer ciclo es O(n), y esHardOSoft es O(L) como se puede ver en auxiliares.
// Sea k la cantidad de operaciones O(1), como para cada ciclo del primer for, se ejecuta esHardOSoft, esto es O(n*L +k)




void reemplazarSubAudio(audio &a, audio a1, audio a2, int profundidad) {
    int indiceDeAparicion = 0;//O(1)
    bool pertenece = false;//O(1)
    buscoAparicion(a, a1, pertenece, indiceDeAparicion);
    reemplazarAparicion(a, a1, a2, indiceDeAparicion, pertenece);
}


void maximosTemporales(audio a, int profundidad, vector<int> tiempos, vector<int> &maximos,
                       vector<pair<int, int> > &intervalos) {
    //Este ciclo calcula los intervalos
    conseguirIntervalos(a, tiempos, intervalos);
    // Entonces este primer ciclo quedaria de orden O(m*n) (para cada ciclo de m veces cicla n)
    maximosDeLosIntervalos(a, maximos, intervalos);
}
// Entonces como para es suma (a.size)/t1 + (a.size)/t2 (a.size)/t3 ... cicla esos tiempos
// quedaria ((a.size)/t1)*t1 + ((a.size)/t2)*t2 + ((a.size)/t3)*t3 ... quedando n*m veces
// Finalizando, quedaria O(n*m + n*m) = (2*n*m) siendo esto tiempo de ejecucion en peor caso de O(n*m)




void limpiarAudio(audio &a, int profundidad, vector<int> &outliers) {
    int percentil95 = 0; //O(1)
    audio a0 = a; //O(1)
    if (a.size() > 1) {     //O(1)
        buscoOutliers(a, outliers, percentil95);
    }
    if (outliers.size() > 0) {  //O(1)
        reemplazoOutliers(a0, outliers, percentil95);
    }
    a = a0;
}
// Entonces el tiempo de ejecucion en peor caso es de O(n^2 + n + m*((n-i) + i) + c) siendo c la suma de
// las operaciones de O(1). Por lo tanto se puede acotar por un O(k*n^2) quedando asi O(n^2).

