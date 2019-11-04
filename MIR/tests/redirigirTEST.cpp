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



TEST(redirigirTEST, OtroCanal1EnRango){
    audio a = {50,2,-50,-5,-2,-10};
    int canal = 1;
    int profundidad = 6;
    audio esperado = {50,-32,-50,31,-2,-8};

    ASSERT_VECTOR(redirigir(a, canal, profundidad), esperado);
}


TEST(redirigirTEST, canal2EnRango){
    audio a = {1,40,3,-40,-2,-10};
    int canal = 2;
    int profundidad = 6;
    audio esperado = {-32,40,31,-40,8,-10};

    ASSERT_VECTOR(redirigir(a, canal, profundidad), esperado);
}