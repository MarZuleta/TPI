#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(revertirAudioValidoTEST, unCanal){
    audio a = {1,2,3,-5,-2,-10,0};
    int canal = 1;
    int profundidad = 6;
    audio esperado = {0,-10,-2,-5,3,2,1};

    ASSERT_VECTOR(revertirAudio(a, canal, profundidad), esperado);
}