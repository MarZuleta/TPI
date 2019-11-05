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

TEST(bajarCalidadTEST, listaNormal){
    vector<audio> as = {{0, -8, 0, 8, 14, 12, 6, 0}};
    int profundidad1 = 5;
    int profundidad2 = 4;
    vector<audio> esperado = {{0, -4, 0, 4, 7, 6,3, 0}};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_MATRIX(as, esperado);
}

TEST(bajarCalidadTEST, dosListasYNumerosNegativosParaRedondear){
    vector<audio> as = {{0, -8, 0, 8, 14, 12, 6, 0},{0, -8, 0, 8, -5}};
    int profundidad1 = 5;
    int profundidad2 = 4;
    vector<audio> esperado = {{0, -4, 0, 4, 7, 6,3, 0},{0, -4, 0, 4, -3}};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_MATRIX(as, esperado);
}
