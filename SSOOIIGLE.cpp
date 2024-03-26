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

struct CompareSearchThread {
    bool operator()(const SearchThread& st1, const SearchThread& st2) const {
        // Definir el orden de prioridad basado en el ID del hilo
        return st1.getID() > st2.getID();
    }
};

int main(int argc, char *argv[]) {
    /*if(argc != 4){
        cout << "Error en los argumentos...\nSaliendo..." << endl;
        exit(1);
    }

    string file = argv[1];
    string word = argv[2];
    int n_threads = stoi(argv[3]);*/

    priority_queue<SearchThread, vector<SearchThread>, CompareSearchThread> searchThreadsQueue;
    searchThreadsQueue.push(SearchThread(2, 6, 11, "esto"));
    searchThreadsQueue.push(SearchThread(1, 1, 5, "esto"));
    

    vector<SearchThread> searchThreadsCopy; // Mantenemos una copia de los objetos SearchThread

    // Copiar los objetos SearchThread desde la cola
    while (!searchThreadsQueue.empty()) {
        searchThreadsCopy.push_back(searchThreadsQueue.top());
        searchThreadsQueue.pop();
    }

    vector<thread> threads;

    // Iniciar los hilos y agregarlos al vector
    for (auto& searchThread : searchThreadsCopy) {
        threads.emplace_back([&searchThread]() {
            searchThread();
        });
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    // Llamar al método toStringResults() de cada instancia de SearchThread desde el hilo principal
    for (auto& st : searchThreadsCopy) {
        st.toStringResults();
    }

    return 0;
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
