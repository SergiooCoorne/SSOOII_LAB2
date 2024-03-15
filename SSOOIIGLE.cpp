#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <queue>
#include <fstream>

using namespace std;

pair<string, string> palabrasAnteriorYPosterior(const string& linea, const string& palabraBuscada) {
    
    pair<string, string> palabras;

    // Encontrar la posición de la palabra buscada
    size_t pos = linea.find(palabraBuscada);
    if (pos == string::npos) {
        // Si la palabra no se encuentra, devolver un par de cadenas vacías
        return palabras;
    }

    // Encontrar la palabra anterior
    size_t posAnterior = linea.find(' ', pos);
    if (posAnterior != string::npos) {
        palabras.first = linea.substr(posAnterior + 1, pos - posAnterior - 1);
    }

    // Encontrar la palabra posterior
    size_t posPosterior = linea.find(' ', pos);
    if (posPosterior != string::npos) {
        palabras.second = linea.substr(posPosterior + 1, linea.find(' ', posPosterior + 1) - posPosterior - 1);
    }

    return palabras;
}

int main(){
    priority_queue <thread> pq;

    std::string linea;
    std::string palabraBuscada;

    std::cout << "Introduce una línea de texto: ";
    std::getline(std::cin, linea);

    std::cout << "Introduce la palabra buscada: ";
    std::cin >> palabraBuscada;

    auto palabras = palabrasAnteriorYPosterior(linea, palabraBuscada);
    std::cout << "Palabra anterior: " << palabras.first << std::endl;
    std::cout << "Palabra posterior: " << palabras.second << std::endl;

    return 0;

}