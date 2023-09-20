#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifndef GENERACIONIMG_H
#define GENERACIONIMG_H

//Prototipos de funciones
void generacionImg(string, string);

void generacionImg(string nombreEstructura, string cadena){
    try{
        ofstream file;
        file.open(nombreEstructura + ".dot", std::ios::out);
        if(file.fail()){
            exit(1);
        }
        file << cadena;
        file.close();
        string command = "dot -Tpng " + nombreEstructura + ".dot -o " + nombreEstructura + ".png";
        system(command.c_str()); 
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
}

#endif