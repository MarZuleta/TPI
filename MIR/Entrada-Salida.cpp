#include <iostream>
#include <fstream>
#include "definiciones.h"


void escribirAudio(audio a, string nombreArchivo, int c){

    ofstream fout;
    fout.open(nombreArchivo);
    fout << c ;
    fout << " ";
    for (int i = 0; i < a.size(); i++) {
        fout << a[i];
        fout << " ";
    }
    fout.close();
}

tuple<int,audio> leerAudio(string nombreArchivo){
    int c = 0;
    audio a ={};
    ifstream fin;
    fin.open(nombreArchivo);
    if (fin.fail()) {
        std::cout << "Error" << endl;
    } else {
        if(!fin.eof()){
            fin >> c;
            while (!fin.eof()){
                int x = 0;
                fin >> x;
                a.push_back(x);
            }
        }
    }
    fin.close();
    tuple<int,audio> t = make_tuple(c,a);
    return t;
};