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


TEST(audiosSoftYHardTEST, listaNormal){
    vector<audio> as = {{10, 12, 5, 9, 35}, {12, 15, 11, 13, 10, 1, 10},{10, 12, 5, 9},{-5, 2, 10, 12, 3, 4}};
    int profundidad = 8;
    int longitud = 4;
    int umbral = 5;
    vector<audio> soft = {};
    vector<audio> hard = {};

    vector<audio> esperadoSoft = {{10, 12, 5, 9, 35},{10, 12, 5, 9},{-5, 2, 10, 12, 3, 4}};
    vector<audio> esperadoHard = {{12, 15, 11, 13, 10, 1, 10}};

    audiosSoftYHard(as, profundidad, longitud, umbral, soft, hard);

    ASSERT_MATRIX(soft, esperadoSoft);
    ASSERT_MATRIX(hard, esperadoHard);
}
