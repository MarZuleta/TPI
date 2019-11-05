#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(maximosTemporalesTEST, test){
    audio a = {33, 25, -1, 3, 1 };
    vector<int> tiempos = {2,3};
    vector<int> maximos;
    vector<pair<int, int>> intervalos;
    int profundidad = 5;
    maximosTemporales(a, profundidad, tiempos, maximos, intervalos);
    vector<pair<int, int>> IntervalosEsperados = { {0, 1},{2, 3},{4, 5},{0, 2},{3, 5}};
    vector<int> maximosEsperados = {33,3,1,33,3};
    ASSERT_VECTOR_DUPLA(intervalos, IntervalosEsperados);
    ASSERT_VECTOR(maximos, maximosEsperados);
}


