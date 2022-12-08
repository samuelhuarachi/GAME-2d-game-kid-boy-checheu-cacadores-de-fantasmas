
#include<iostream>
#include "Helper.h"

using namespace std;

Helper::Helper()
{
    //ctor
}

Helper::~Helper()
{
    //dtor
}


void Helper::writeSomeTextInCmd(std::string text, bool DEBUG_ACTIVATED) {
    if (DEBUG_ACTIVATED == true) {
        cout << text << "\n";
    }
}


