#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

/*Clase que guardara objetos cuyos atributos son el numero de linea, la palabra anterior y posterior de la palabra que se esta buscando*/

class Result{
    private:
        int n_line;
        string w_before;
        string w_after;
        
    public:
        Result(int n_line, string w_before,string w_after){
            this->n_line = n_line;
            this->w_before = w_before;
            this->w_after = w_after;
        }

        int getN_line(){
            return n_line;
        }

        string getW_before(){
            return w_before;
        }

        string getW_after(){
            return w_after;
        }


        bool operator<(const Result& other) const {
            return n_line < other.n_line;
        }
          
};