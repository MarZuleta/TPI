#include <iostream>
#include "gtest/gtest.h"
#include "solucion.h"
#include "auxiliares.h"
#include "Graficos.h"
#include <fstream>


int main(int argc, char **argv) {
    int n = 0; int hasta = 10000; int paso = 1000;
    ofstream fout;
    fout.open("datos.csv");

    fout << "n\t" << "tiempo" <<endl;
    while(n < hasta){
        audio v = construir_vector(n, "asc");

        double t0=clock();
        limpiarAudio(v);
        double t1 = clock();

        double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);

        fout << n << "\t" << tiempo << endl;

        n +=paso;
    }
    fout.close()





}


/*

std::cout << "Implementando TPI!!" << std::endl;

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TE*/STS();


*/