#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <algorithm>

using namespace std;

class SearchThread
{
private:
    priority_queue <SearchResult> pq;
    int id;
    int index_first;
    int index_last;
    string word;

    void search()
    {
        ifstream file("file.txt");
        string line;
        int n_line = 0;
        while (getline(file, line))
        {
            n_line++;
            size_t found = line.find(word);
            if (found != string::npos)
            {
                string w_before = line.substr(found - 10, 10);
                string w_after = line.substr(found + word.size(), 10);
                SearchResult sr(n_line, w_before, w_after);
                pq.push(sr);
            }
        }
    }

    pair<string, string> palabrasAnteriorYPosterior(const string& linea, const string& palabraBuscada) {
    
    pair<string, string> palabras;

    // Encontrar la posición de la palabra buscada
    size_t pos = linea.find(palabraBuscada);
    if (pos == string::npos) {
        // Si la palabra no se encuentra, devolver un par de cadenas vacías
        return palabras;
    }

    // Encontrar la palabra anterior
    size_t posAnterior = linea.rfind(' ', pos);
    if (posAnterior != string::npos) {
        palabras.first = linea.substr(posAnterior + 1, lin pos - posAnterior - 1);
    }

    // Encontrar la palabra posterior
    size_t posPosterior = linea.find(' ', pos);
    if (posPosterior != string::npos) {
        palabras.second = linea.substr(posPosterior + 1, linea.find(' ', posPosterior + 1) - posPosterior - 1);
    }

    return palabras;
}

public:
    SearchThread(int id, int index_first, int index_last, string word)
    {
        this->id = id;
        this->index_first = index_first;
        this->index_last = index_last;
        this->word = word;
    }
};