#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <fstream>
#include <sstream>

#include "SearchThread.cpp"

using namespace std;

int count_lines_file(string file_name);
void parse_argv(int argc, char *argv[]);
void solution();
bool fileExists(string& filename);

string file_name;
string word;
int n_threads;

struct CompareSearchThread {
    bool operator()(const SearchThread& st1, const SearchThread& st2) const {
        // Definir el orden de prioridad basado en el ID del hilo
        return st1.getID() > st2.getID();
    }
};

int main(int argc, char *argv[]) {
    parse_argv(argc,argv);
    solution();
    
    return 0;
}

void solution(){

    if(fileExists(file_name) == false){
        cout << "El archivo no existe...\nSaliendo..." << endl;
        exit(1);
    }

    int lines = count_lines_file(file_name);
    double lines_per_thread = lines / n_threads;
    int remaining_lines = lines % n_threads;
    int start_line = 1;

    /*Creamos una cola con prioridad pero cuya estrucctura interna es un vector, y usamos el comparador para ordenar los elementos que se estan metiendo en la cola*/
    priority_queue<SearchThread, vector<SearchThread>, CompareSearchThread> searchThreadsQueue;
    
    for (int i = 0; i < n_threads; i++) {
        int end_line = start_line + lines_per_thread - 1; // Asignar líneas según la división
        // Ajustar para las líneas restantes
        if (remaining_lines > 0) {
            end_line++;
            remaining_lines--;
        }
        searchThreadsQueue.push(SearchThread(i, start_line, end_line, word, file_name));
        start_line = end_line + 1;
    }

    vector<SearchThread> searchThreadsCopy; /*Creamos un vector para sacar los elementos de la cola con prioridad y manejarlos*/

    /*Sacamos los elementos de la cola con prioridad y los metemos en el vector que acabamos de crear para que sea mas simple manejarlos*/
    while (!searchThreadsQueue.empty()) {
        searchThreadsCopy.push_back(searchThreadsQueue.top());
        searchThreadsQueue.pop();
    }

    /*Creamos un vector donde iran todos los hilos*/
    vector<thread> threads;

    /*Inicializamos los hilos pasandole a cada hilo un objeto del tipo "SearchThread"*/
    for (auto& instance : searchThreadsCopy) {
        threads.emplace_back([&instance]() {
            instance();
        });
    }
    
    /*Esperar a que todos los hilos terminen*/
    for (auto& thread : threads) {
        thread.join();
    }

    /*Llamar al método toStringResults() de cada instancia de SearchThread*/
    for (auto& st : searchThreadsCopy) {
        st.toStringResults();
    }
}

void parse_argv(int argc, char *argv[]){
    if(argc != 4){
        cout << "Error en los argumentos...\nSaliendo..." << endl;
        exit(1);
    }

    file_name = argv[1];
    word = argv[2];
    n_threads = stoi(argv[3]);
}

int count_lines_file(string file_name) {
    ifstream file(file_name);
    string line;
    int n_line = 0;
    while (getline(file, line)) {
        n_line++;
    }
    return n_line;
}

bool fileExists(string& filename) {
    ifstream file(filename);
    return file.good(); /*Si no existe, devuelve FALSE*/
}