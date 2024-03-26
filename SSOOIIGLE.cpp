#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <queue>
#include <fstream>
#include <sstream>

#include "SearchThread.cpp"

using namespace std;

int count_lines_file(string file_name);

int main(int argc, char *argv[]){
    /*if(argc != 4){
        cout << "Error en los argumentos...\nSaliendo..." << endl;
        exit(1);
    }

    string file = argv[1];
    string word = argv[2];
    int n_threads = stoi(argv[3]);*/


    priority_queue <thread> pq;

    SearchThread st1(1, 1, 5, "esto");
    SearchThread st2(2, 6, 11, "esto");
    /*st1.search();
    st1.toStringResults();*/
    
    thread hilo1(st1);
    thread hilo2(st2);

    hilo1.join();
    hilo2.join();

    /*st1.toStringResults();
    st2.toStringResults();*/


    return 0;

}

int count_lines_file(string file_name){
    ifstream file(file_name);
    string line;
    int n_line = 0;
    while (getline(file, line)) {
        n_line++;
    }
    return n_line;
}