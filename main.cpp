#include "NumberWithUnits.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace ariel;



int main(){

    ifstream file {"filename.txt"};
    NumberWithUnits::read_units(file);

    // cout << "hell";
    // NumberWithUnits num(7, "r_ILS");
    // cout << num << "\n";

    // istringstream iss("20 [r_sec]");
    // iss >> num;
    // cout << num << "\n";

    NumberWithUnits a(7, "r_ILS");
    NumberWithUnits b(7, "r_ILS");
    NumberWithUnits c(7, "r_ILS");
    istringstream iss3{" -16 [r_m]   -7 [r_hour ]  8.8 [r_min ]"};
    iss3 >> a >> b >> c;

    cout << a << b << c << endl;
    
    





    return 0;
}



//clang++-9 -c NumberWithUnits.cpp; clang++-9 -std=c++2a -o main main.cpp NumberWithUnits.o