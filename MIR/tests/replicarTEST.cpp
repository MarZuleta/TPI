#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(replicarTEST, unCanal){
    audio a = {1,2,3,-5,-2,-10,0};
    int canal = 1;
    int profundidad = 6;
    audio esperado = {1,2,3,-5,-2,-10,0};

    ASSERT_VECTOR(replicar(a, canal, profundidad), esperado);
}