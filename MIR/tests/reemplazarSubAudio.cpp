#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(reemplazarSubAudioTEST, unElementoYPresente){
    audio a = {1};
    audio a1 = {1};
    audio a2 = {3};
    int profundidad = 5;
    audio esperado = {3};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_VECTOR(a, esperado);
}

TEST(reemplazarSubAudioTEST, variosElementosYPresente){
    audio a = {1,2,3,4,5,6};
    audio a1 = {3,4};
    audio a2 = {7,8,9};
    int profundidad = 5;
    audio esperado = {1,2,7,8,9,5,6};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_VECTOR(a, esperado);
}

