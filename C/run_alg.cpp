#include "algorithm.hpp"
using namespace std;
int main(int argc, char *argv[]) {
    //error checking 
    if(argc > 2) {
        cout << "too many input command arguments. Give filepath only\n";
        return -1;
    }
    if(argc < 2) {
        cout << "too little of input command arguments. Give filepath.\n";
        return -1;
    }
    mor_processing::Algorithm alg(15, 15, argv[1]); //argv[1] has the filepath name
    alg.run(); //run algorithm on the tiff image 
    return 0; //for successful execution
}
