#include <string>

using namespace std;

class SearchResult{
    private:
        int n_line;
        string w_before;
        string w_after;
        
    public:
        SearchResult(int n_line, string w_before,string w_after){
            this->n_line = n_line;
            this->w_before = w_before;
            this->w_after = w_after;
        }  
};