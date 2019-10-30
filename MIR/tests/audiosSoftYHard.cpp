#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(audiosSoftYHardTEST, listaVacia){
    vector<audio> as = {};
    int profundidad = 8;
    int longitud = 2;
    int umbral = 2;
    vector<audio> soft = {};
    vector<audio> hard = {};

    vector<audio> esperadoSoft = {};
    vector<audio> esperadoHard = {};

    audiosSoftYHard(as, profundidad, longitud, umbral, soft, hard);

    ASSERT_MATRIX(soft, esperadoSoft);
    ASSERT_MATRIX(hard, esperadoHard);
}
