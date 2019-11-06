//
// Created by Los Dudes on 11/6/2019.
//
#include "definiciones.h"
#include <iostream>
#include <fstream>

#ifndef RECUPERACIONINFORMACIONMUSICAL_ENTRADA_SALIDA_H
#define RECUPERACIONINFORMACIONMUSICAL_ENTRADA_SALIDA_H


void escribirAudio(audio a, string nombreArchivo, int c);
tuple<int,audio> leerAudio(string nombreArchivo);

#endif //RECUPERACIONINFORMACIONMUSICAL_ENTRADA_SALIDA_H
