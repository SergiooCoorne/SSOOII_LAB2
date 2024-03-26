#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <algorithm>

#include "Result.cpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

using namespace std;

class SearchThread {
    private:
        priority_queue <Result> pq;
        int id;
        int index_first;
        int index_last;
        string word;

    public:
        SearchThread(int id, int index_first, int index_last, string word){
            this->id = id;
            this->index_first = index_first;
            this->index_last = index_last;
            this->word = word;
        }
        
        void operator()(){
            search();
            toStringResults();
        }

        void search() {
            ifstream file("text.txt");
            string line;
            int n_line = 0;
            while (getline(file, line)) {
                n_line++;
                if (n_line >= index_first && n_line <= index_last) { /*Hacemos que se busquen solo las lineas comprendidas entre los indices*/
                    size_t found = line.find(word);
                    if (found != string::npos) { /*Comprobamos que la palabra que buscamos esta en la linea*/
                        /*Sacamos un vector de resultados por si aparece mas de una vez la palabra en la linea*/
                        vector<pair<string, string>> results_array = word_before_and_after(line, word);
                        for (int i = 0; i < results_array.size(); i++) { /*Recorremos el vectro sacando los resultados por linea e introduciendo los resultados en la cola de resultados*/
                            /*cout << "Thread " << id << " found word " << word << " in line " << n_line << " with word before and after: " << results_array[i].first << " " << results_array[i].second << endl;*/
                            Result sr(n_line, results_array[i].first, results_array[i].second);
                            pq.push(sr);
                        }
                    }
                }
            }
        }
    
        vector <pair<string, string>> word_before_and_after(const string& linea, const string& palabraBuscada) {
            vector <pair<string, string>> results_array; /*Vector donde iran los pares de palabras de resultados*/
            pair<string, string> result; /*Par de palabras que seran el resultado de la busqueda*/
            vector<string> line_words; /*Vector donde iran las palabras que hay en una linea*/
            istringstream iss(linea); /*Stream para recorrer la línea*/
            string word; /*Palabra que se iran incluyendo en el vector de palabras de cada lina*/

            /*Recorremos la línea y vamos metiendo las palabras en un vector*/
            while(iss >> word){
                line_words.push_back(word);
            }
            int size_words = line_words.size(); /*Cogemos el tamaño para saber cuántas palabras hay en una línea*/

            /*Recorremos el vector de palabras para buscar la palabra que queremos*/
            for(int i = 0; i < size_words; i++){
                if(line_words[i] == palabraBuscada){
                    if(i == 0){ /*Si la palabra buscada es la primera del vector*/
                        result.first = "NULL";
                        result.second = line_words[i + 1];
                    }else if(i == size_words - 1){ /*Si la palabra buscada es la última del vector*/
                        result.first = line_words[i - 1];
                        result.second = "NULL";
                    }else{ /*Si la palabra buscada esta en mitad de la linea*/
                        result.first = line_words[i - 1]; 
                        result.second = line_words[i + 1];
                    }
                    results_array.push_back(result); /*Introducimos el resultado en el vector de resultados*/
                }
            }
            return results_array;
        }

        void toStringResults(){
            /*Vector de colores para que cada hilo imprima de un color diferente*/
            const string colors[] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
            srand(time(0) + id);
            string randomColor = colors[rand() % 7];

            /*Vamos a hacer uso de una pila auxiliar para que se impriman los resultados en el mismo orden en el que se introdujeron*/
            stack <Result> resultsAux;
            while (!pq.empty())
            {
                Result sr = pq.top();
                resultsAux.push(sr);
                pq.pop();
            }
            while (!resultsAux.empty())
            {
                Result sr = resultsAux.top();
                cout << randomColor << "[Hilo " << id << " inicio: " << index_first << " - final: " << index_last << "] :: linea " << sr.getN_line() << " :: ... " << sr.getW_before() << " " << word << " " << sr.getW_after() << " ..." << RESET <<endl;
                resultsAux.pop();
            }
        }
};