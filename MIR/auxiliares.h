#ifndef RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H
#define RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H

#include "definiciones.h"

//template<typename T>
bool vectoresOrdenadosIguales(vector<int> vector1, vector<int> vector2);
vector<audio> subAudiosDeLongitud (audio a, int longitud);
vector<pair<int, int>> intervalosDeTiempo (audio a, int tiempo);
int maximoDeUnAudio (audio a);
//template<typename T>
void ASSERT_VECTOR(vector<int> vector1, vector<int> vector2);
void ASSERT_MATRIX(vector<audio> mat1, vector<audio> mat2);


#endif //RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H
