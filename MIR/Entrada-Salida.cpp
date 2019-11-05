#include <iostream>
#include <fstream>
#include "definiciones.h"



void escribirAudio(audio a, string nombreArchivo, int c) {

    ofstream fout;
    fout.open("audioTP.txt");
    fout << c << " ";
    for (int i = 0; i <= a.size() - 1; i++) {
        fout << a[i] << " ";
    }

}
tuple<int, audio> leerAudio(string nombreArchivo){
    int canal = 0;
    audio a;

}


