#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <algorithm>
#include <mutex>

#include "Result.cpp"

/*Colores para que cada hilo imprima sus linea de un color aleatorio*/
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

using namespace std;

/*Clase de la cual se crean los objetos que se le pasan a los hilos, para que cada hilo procese de manera independiente las lineas y los datos correspondientes*/

class SearchThread {
private:
    queue<Result> results; /*Cola de objetos de tipo "Result"*/
    int id;
    int index_first;
    int index_last;
    string word;
    string file_name;

public:
    SearchThread(int id, int index_first, int index_last, string word, string file_name) : id(id), index_first(index_first), index_last(index_last), word(word), file_name(file_name) {}

    void operator()() {
        search();
    }

     int getID() const {
        return id;
    }

    /*Metodo principal que se encarga de hacer la busqueda de las palabras y de sacar la informacion correspondiente a la misma*/
    void search() {
        ifstream file(file_name);
        string line;
        int n_line = 0;
        while (getline(file, line)) {
            n_line++;
            if (n_line >= index_first && n_line <= index_last) { /*Hacemos que se busquen solo las lineas comprendidas entre los indices*/
                size_t found = line.find(word);
                if (found != string::npos) { /*Comprobamos que la palabra que buscamos esta en la linea*/
                    /*Sacamos un vector de resultados por si aparece mas de una vez la palabra en la linea*/
                    vector<pair<string, string>> results_array = word_before_and_after(line, word);
                    int size_array = results_array.size();
                    for (int i = 0; i < size_array; i++) { /*Recorremos el vector sacando los resultados por linea e introduciendo los resultados en la cola de resultados*/
                        Result sr(n_line, results_array[i].first, results_array[i].second);
                        results.push(sr);
                    }
                }
            }
        }
    }


    /*Metodo que nos devuelve la palabra anterior y posterior de una linea pasandole la linea y la palabra que estamos buscando*/
    vector<pair<string, string>> word_before_and_after(const string& linea, const string& palabraBuscada) {
        vector<pair<string, string>> results_array; /*Vector donde iran los pares de palabras de resultados*/
        pair<string, string> result; /*Par de palabras que seran el resultado de la busqueda*/
        vector<string> line_words; /*Vector donde iran las palabras que hay en una linea*/
        istringstream iss(linea); /*Stream para recorrer la línea*/
        string word; /*Palabra que se iran incluyendo en el vector de palabras de cada lina*/

        /*Recorremos la línea y vamos metiendo las palabras en un vector*/
        while (iss >> word) {
            line_words.push_back(word);
        }
        int size_words = line_words.size(); /*Cogemos el tamaño para saber cuántas palabras hay en una línea*/

        /*Recorremos el vector de palabras para buscar la palabra que queremos*/
        for (int i = 0; i < size_words; i++) {
            if (line_words[i] == palabraBuscada) {
                if (i == 0) { /*Si la palabra buscada es la primera del vector*/
                    result.first = "NULL";
                    result.second = (size_words > 1) ? line_words[i + 1] : "NULL";
                } else if (i == size_words - 1) { /*Si la palabra buscada es la última del vector*/
                    result.first = (size_words > 1) ? line_words[i - 1] : "NULL";
                    result.second = "NULL";
                } else { /*Si la palabra buscada esta en mitad de la linea*/
                    result.first = line_words[i - 1];
                    result.second = line_words[i + 1];
                }
                results_array.push_back(result); /*Introducimos el resultado en el vector de resultados*/
            }
        }
        return results_array;
    }

    /*Metodo para mostrar toda la informacion correspondiente a la palabra que se esta buscando*/
    void toStringResults() {
        /*Vector de colores para que cada hilo imprima de un color diferente*/
        const string colors[] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
        srand(time(0) + id);
        string randomColor = colors[rand() % 7];

        while (!results.empty()) {
            Result sr = results.front();
            results.pop();
            cout << randomColor << "[Hilo " << id << " inicio: " << index_first << " - final: " << index_last << "] :: linea " << sr.getN_line() << " :: ... " << sr.getW_before() << " " << word << " " << sr.getW_after() << " ..." << RESET << endl;
        }
    }
};
