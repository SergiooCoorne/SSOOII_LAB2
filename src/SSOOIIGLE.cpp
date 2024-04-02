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
        /*Definimos el orden de prioridad basado en el ID del hilo*/
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
    /*Creamos unas variables las cuales usaremos para el desarrollo del programa*/
    int lines = count_lines_file(file_name); /*Numero de lineas del archivo que se le pase*/
    double lines_per_thread = lines / n_threads; /*Numero de lineas que tiene que procesar cada hilo*/
    int remaining_lines = lines % n_threads; /*Lineas que quedan "sueltas" en el caso de que las lineas no sean multiplo del numero de hilos*/
    int start_line = 1; /*Linea de comienzo*/

    /*Creamos una cola con prioridad pero cuya estrucctura interna es un vector, y usamos el comparador para ordenar los elementos que se estan metiendo en la cola*/
    priority_queue<SearchThread, vector<SearchThread>, CompareSearchThread> searchThreadsQueue;
    
    for (int i = 0; i < n_threads; i++) {
        int end_line = start_line + lines_per_thread - 1; /*Asignamos las líneas según la división que hemos hecho antes*/
        /*Ajustamos las líneas restantes*/
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
    
    /*Esperamos a que todos los hilos terminen*/
    for (auto& thread : threads) {
        thread.join();
    }

    /*Llamar al método toStringResults() de cada instancia de SearchThread*/
    for (auto& st : searchThreadsCopy) {
        st.toStringResults();
    }
}

/*Funcion usada para procesar los argumentos que se les pasa al programa*/
void parse_argv(int argc, char *argv[]){
    if(argc != 4){
        cout << "Error en los argumentos...\nSaliendo..." << endl;
        exit(1);
    }

    file_name = argv[1];
    word = argv[2];
    n_threads = stoi(argv[3]);
}

/*Funcion usada para contar las lineas que tiene el archivo .txt que se le pase*/
int count_lines_file(string file_name) {
    ifstream file(file_name);
    string line;
    int n_line = 0;
    while (getline(file, line)) {
        n_line++;
    }
    return n_line;
}

/*Funcion usada para comprobar si el archivo existe*/
bool fileExists(string& filename) {
    ifstream file(filename);
    return file.good(); /*Si no existe, devuelve FALSE*/
}