#include "std_lib_facilities.h"

int main(){
    int i = 0;
    while (true){
        double* doub = new double[10000];
        cout << "Loop " << i << '\n' << "doub[0] " << doub[0] << '\n';
        i++;
    }
    return 0;
}