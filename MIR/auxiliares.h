#ifndef RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H
#define RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H

#include "definiciones.h"

//template<typename T>
bool vectoresOrdenadosIguales(vector<int> vector1, vector<int> vector2);
void revertirBloque(audio a, audio &b, int canal, int i);
void maximoDelCanal (audio a, int canal, int i, int &max, int &posMax);
void ajustarTope(audio &a, int canal, int profundidad, int i);
void ajustarAudio (vector<audio> &as, int i, int profundidad1, int profundidad2);
bool esHardOSoft(vector<audio> as, int longitud, int umbral, int contador, int i);
void buscoAparicion(audio a, audio a1, bool &pertenece, int &indiceDeAparicion);
void reemplazarAparicion (audio &a, audio a1, audio a2, int indiceDeAparicion, bool pertenece);
void conseguirIntervalos (audio a, vector<int> tiempos, vector<pair<int, int> > &intervalos);
void maximosDeLosIntervalos (audio a, vector<int> &maximos, vector<pair<int, int> > &intervalos);
void buscoOutliers (audio a, vector<int> &outliers, int &percentil95);
void reemplazoOutliers (audio &a, vector<int> &outliers, int &percentil95);
audio selectionSort(audio &a);
int buscarNoOutlierDerecha(audio a, int i, int percentil95);
int buscarNoOutlierIzquierda(audio a, int i, int percentil95);
bool tieneProfundidadValida(audio a, int profundidad);
//template<typename T>
void ASSERT_VECTOR(vector<int> vector1, vector<int> vector2);
void ASSERT_MATRIX(vector<audio> mat1, vector<audio> mat2);
bool vectoresDeDuplasOrdenadosIguales(vector<pair<int, int>> vector1, vector<pair<int, int>> vector2);
void ASSERT_VECTOR_DUPLA (vector<pair<int, int>> vector1, vector<pair<int, int>> vector2);


#endif //RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H
