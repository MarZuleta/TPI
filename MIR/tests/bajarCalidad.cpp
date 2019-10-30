#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(bajarCalidadTEST, listaVacia){
    vector<audio> as = {};
    int profundidad1 = 4;
    int profundidad2 = 2;
    vector<audio> esperado = {};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_MATRIX(as, esperado);
}

