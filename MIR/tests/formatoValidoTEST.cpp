#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(formatoValidoTEST, longitudErronea){
    audio a = {1,2,3,4,5};
    int canal = 3;
    int profundidad = 4;

    EXPECT_FALSE(formatoValido(a, canal, profundidad));
}



TEST(formatoValidoTEST, profundidadErronea_Test){
    audio a = {1,2,3,4,5,10};
    int canal = 3;
    int profundidad = 4;

    EXPECT_FALSE(formatoValido(a, canal, profundidad));
}


TEST(formatoValidoTEST, profundidadYcanalValidos_Test){
    audio a = {1,2,3,4,5,6};
    int canal = 3;
    int profundidad = 4;

    EXPECT_TRUE(formatoValido(a, canal, profundidad));
}

