#include "solucion.h"
#include "auxiliares.h"
#include <algorithm>

using namespace std;

bool tieneProfundidadValida (audio a, int profundidad){
    int i = 0;
    while (i < a.size()){
        if (((-2)^(profundidad -1))<= a[i] <= ((2^(profundidad -1)) -1)){
            i++;
        }
        else{
            return false;
        }
    }
    return true;
}

bool formatoValido(audio a, int canal, int profundidad) {
    if (canal>0 && profundidad>0 && a.size()>0 && (a.size() % canal == 0)){
        return tieneProfundidadValida(a, profundidad);
        }
        else{
            return false;

    }

}

audio replicar(audio a, int canal, int profundidad) {
    audio b;
    for(int i = 0; i<a.size(); i++){
        int j = 0;
        while (j< canal){
            b.push_back(a[i]);
            j++;
        }
    }
    return b;
}

audio revertirAudio(audio a, int canal, int profundidad) {
    audio b(a.size());
    for (int i = 0; i<a.size(); (i += canal)){

    }
    return a;
}

void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos) {

}

audio redirigir(audio a, int canal, int profundidad) {
    return a;
}

void bajarCalidad(vector<audio> & as, int profundidad1, int profundidad2) {

}

void audiosSoftYHard(vector<audio> as, int profundidad, int longitud, int umbral, vector<audio>& soft, vector<audio>& hard) {

}

void reemplazarSubAudio(audio& a, audio a1, audio a2, int profundidad) {

}

void maximosTemporales(audio a, int profundidad, vector<int> tiempos, vector<int>& maximos, vector<pair<int,int> > &intervalos ) {

}

void limpiarAudio(audio& a, int profundidad, vector<int>& outliers) {


}

