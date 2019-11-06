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
        for (int j = 0; j < canal; ++j) {           //O(c)
            b.push_back(a[a.size() - canal * (i + 1) + j]); //O(1)
        }
    }
    return b;   //Entonces como para cada ejecucion del primer ciclo se ejecuta el segundo queda O((n/c)*c + k)
    // siendo k la suma de las operaciones O(1), y como se simplifica (n/c)*c queda entonces O(n).
}

void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos) {
    for (int i = 0; i < canal; ++i) {   // Sea canal = c, esto cicla canal veces, entonces es O(c)
        int max = 0; // O(1)
        int posMax = 0;  //O(1)
        for (int j = i; j < a.size(); j += canal) {  // Sea a.size() = n, esto cicla n/c veces
            if (abs(a[j]) > max) {
                max = a[j];     //O(1)
                posMax = j;     //O(1)
            }
        }
        maximos.push_back(max); //O(1)
        posicionesMaximos.push_back(posMax);  //O(1)
    }
}       // Luego como para cada ciclo de O(c) cicla un for de O(n/c), queda O((n/c)*c), quedando asi O(n)

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
            double b = as[i][j];
            b = floor(b / (pow(2, profundidad1 - profundidad2)));
            as[i][j] = (int) b;
        }
    }
}

void
audiosSoftYHard(vector<audio> as, int profundidad, int longitud, int umbral, vector<audio> &soft, vector<audio> &hard) {
    for (int i = 0; i < as.size(); ++i) {   //Sea as.size() = n, este for cicla
                                            //en peor caso n veces perteneciendo entonces a O(n)
        vector<audio> a = subAudiosDeLongitud(as[i], longitud); //Como se ve en auxiliares esto es O(n^2)
        int contador = 0; //O(1)
        for (int j = 0; j < a.size(); ++j) {  // Esto cicla as[i].size() - longitud + 1 veces, llamemos a esto O(M)
            int contador = 0;  //O(1)
            for (int k = 0; k < a[j].size(); ++k) { // Esto lo hace longitud veces, peor caso O(n)
                if (a[j][k] > umbral) { //O(1)
                    contador++;  //O(1)
                }
            }
            if (contador == a[j].size()) {
                hard.push_back(as[i]);  //O(1)
                j = a.size();  //O(1)
                as.erase(as.begin() + i);  //O(1)
            }
        }
    }
    soft = as; //O(1)
}
// Concluyendo como para cada ciclo del primer for hace los otros dos for, queda entonces O(n*M*n)
// y como estos numeros son arbitrariamente grande, queda O(n^3)




void reemplazarSubAudio(audio &a, audio a1, audio a2, int profundidad) {
    vector<audio> subAudios = subAudiosDeLongitud(a, a1.size()); // Como se ve en auxiliares, esto es O(n^2)
    int aparicion = 0;       //O(1)
    int indiceDeAparicion = 0;    //O(1)
    audio aux;      //O(1)
    for (int i = 0; i < subAudios.size(); ++i) {  // Esto cicla a.size() - longitud + 1 veces, tiempo de ejecucion
        if (subAudios[i] == a1) {  //O(1)           // en peor caso de O(n) siendo n = a.size()
            aparicion++;        //O(1)
            indiceDeAparicion = i;  //O(1)
        }
    }

    // Para cada uno de los ciclos que vienen, explicamos su tiempo de ejecucion en peor caso abajo
    if (aparicion > 0) {    //O(1)
        for (int i = 0; i < a.size() - (subAudios[indiceDeAparicion].size() + indiceDeAparicion); ++i) {  // 1)
            aux.push_back(a[a.size() - 1 - i]); // Lo pongo al reves en aux
        }
        for (int i = 0; i < aux.size(); ++i) {      // 2)
            a.pop_back();
        }
        for (int j = 0; j < a1.size(); ++j) {       // 3)
            a.pop_back();
        }
        for (int k = 0; k < a2.size(); ++k) {       // 4)
            a.push_back(a2[k]);
        }
        for (int l = 0; l < aux.size(); ++l) {      // 5)
            a.push_back(aux[aux.size() - 1 - l]); // Y aca lo meto al reves para recuperar el orden
        }
    }
}

// 1) Este for guarda lo que hay en el audio luego de la aparicion de a1, en peor caso O(n) (si a1 esta al comienzo)
// 2) Este for elimina esos elementos, tambien O(n)
// 3) Este for elimina a1, sea a1.size() = M esto es de O(M)
// 4) Este for pone a2, sea a2.size() = L esto es O(L)
// 5) Este for recompone el audio, siendo O(n) peor caso
// Concluyendo el orden quedaria de O(n^2 + k*n + c) siendo k la cantidad de O(n) que hay y c los O(1), por lo tanto
// reemplazarSubAudio es de O(n^2)



void maximosTemporales(audio a, int profundidad, vector<int> tiempos, vector<int> &maximos,
                       vector<pair<int, int> > &intervalos) {
    //Este ciclo calcula los intervalos
    for (int j = 0; j < tiempos.size(); ++j) {   //O(m) siendo m = tiempos.size()
        for (int i = 0; i < a.size(); i += tiempos[j]) {  // Este for cicla n/m veces es decir O(n) (peor caso)
            pair<int, int> intervalo = {i, i + tiempos[j] - 1}; //O(1)
            intervalos.push_back(intervalo); //O(1)
        }
    }
    // Entonces este primer ciclo quedaria de orden O(m*n) (para cada ciclo de m veces cicla n)

    //Y este ciclo calcula los maximos de esos intervalos
    for (int i = 0; i < intervalos.size(); ++i) {    // Este for cicla una cantidad de veces que es la suma de
        audio aux;                                  // (a.size)/t1 + (a.size)/t2 (a.size)/t3 ....
                                                    // siendo t1 hasta tn los tiempos de la lista de tiempos
        for (int j = intervalos[i].first; j <= intervalos[i].second; ++j) { // Y este for cicla t_i siendo esto cada
            if (j >= a.size()) {                                            // tiempo
                aux.push_back(a[a.size() - 1]);
            } else {
                aux.push_back(a[j]);
            }
        }
        int max = maximoDeUnAudio(aux);
        maximos.push_back(max);
    }
}
// Entonces como para es suma (a.size)/t1 + (a.size)/t2 (a.size)/t3 ... cicla esos tiempos
// quedaria ((a.size)/t1)*t1 + ((a.size)/t2)*t2 + ((a.size)/t3)*t3 ... quedando n*m veces
// Finalizando, quedaria O(n*m + n*m) = (2*n*m) siendo esto tiempo de ejecucion en peor caso de O(n*m)




void limpiarAudio(audio &a, int profundidad, vector<int> &outliers) {
    //Primero calculo los outliers
    if (a.size() > 1) {     //O(1)
        audio a0 = a;       //O(1)
        audio audioOrdenado = selectionSort(a0);   //O(n^2) siendo n = a.size()
        int percentil95 = audioOrdenado[(int) ((a.size() * 95) / 100) - 1];  //O(1)
        for (int i = 0; i < a.size(); ++i) {      //O(n) siendo n = a.size()
            if (a[i] > percentil95) {
                outliers.push_back(i);
            }
        }

        if (outliers.size() > 0) {  //O(1)
            for (int i = 0; i < outliers.size(); ++i) {   //O(M) siendo M = la cantidad de outliers
                int noOutlierDerecha = buscarNoOutlierDerecha(a, outliers[i], percentil95);  // O(n-i) n= a.size
                int noOutlierIzquierda = buscarNoOutlierIzquierda(a, outliers[i], percentil95);//O(i) siendo i la
                // Separo en los tres casos especificados                                     // posicion del outlier
                if ((noOutlierDerecha >= 0) && noOutlierIzquierda >= 0) {       //O(1)
                    double b = (a[noOutlierDerecha] + a[noOutlierIzquierda]);  //O(1)
                    b = floor(b / 2);       //O(1)
                    a[outliers[i]] = (int) b;   //O(1)
                }
                if ((noOutlierDerecha >= 0) && (noOutlierIzquierda == -1)) {   //O(1)
                    a[outliers[i]] = a[noOutlierDerecha];       //O(1)
                }
                if ((noOutlierDerecha == -1) && (noOutlierIzquierda >= 0)) {  //O(1)
                    a[outliers[i]] = a[noOutlierIzquierda];     //O(1)
                }
            }
        } // Entonves el tiempo de ejecucion en peor caso es de O(n^2 + n + m*((n-i) + i) + c) siendo c la suma de
        // las operaciones de O(1). Por lo tanto se puede acotar por un O(k*n^2) quedando asi O(n^2).
    }
}


