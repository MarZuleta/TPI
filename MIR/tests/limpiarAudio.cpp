#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(limpiarAudioTEST, test){
    audio a = {1};
    audio outliers = {1};
    int profundidad = 6;
    audio audioEsperado = {1};
    audio outliersEsperado = {1};

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}