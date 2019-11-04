#ifndef RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H
#define RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H

#include "definiciones.h"

//template<typename T>
bool vectoresOrdenadosIguales(vector<int> vector1, vector<int> vector2);
vector<audio> subAudiosDeLongitud (audio a, int longitud);
int maximoDeUnAudio (audio a);
audio selectionSort(audio a);
int buscarNoOutlierDerecha(audio a, int i, int percentil95);
int buscarNoOutlierIzquierda(audio a, int i, int percentil95);
bool tieneProfundidadValida(audio a, int profundidad);
//template<typename T>
void ASSERT_VECTOR(vector<int> vector1, vector<int> vector2);
void ASSERT_MATRIX(vector<audio> mat1, vector<audio> mat2);


#endif //RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H
