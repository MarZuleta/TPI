#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(redirigirTEST, canal1EnRango){
    audio a = {1,2,3,-5,-2,-10};
    int canal = 1;
    int profundidad = 6;
    audio esperado = {1,1,3,-8,-2,-8};

    ASSERT_VECTOR(redirigir(a, canal, profundidad), esperado);
}