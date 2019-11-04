#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(limpiarAudioTEST, audioSinOutliers) {
    audio a = {1};
    audio outliers;
    int profundidad = 6;
    audio audioEsperado = {1};
    audio outliersEsperado;

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}





TEST(limpiarAudioTEST, audioConOutlierAlFinal) {
    audio a = {1, 4, 3, 2, 30, -5, 50};
    audio outliers;
    int profundidad = 6;
    audio audioEsperado = {1, 4, 3, 2, 30, -5, -5};
    audio outliersEsperado = {6};

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}

TEST(limpiarAudioTEST, audioConOutlierAlPrincipio) {
    audio a = {50, 4, 3, 2, 30, -5, 1};
    audio outliers;
    int profundidad = 6;
    audio audioEsperado = {4, 4, 3, 2, 30, -5, 1};
    audio outliersEsperado = {0};

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}

TEST(limpiarAudioTEST, audioConOutlierYPromedio) {
    audio a = {1, 4, 50, 2, 30, -5, 3};
    audio outliers;
    int profundidad = 6;
    audio audioEsperado = {1, 4, 3, 2, 30, -5, 3};
    audio outliersEsperado = {2};

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}

