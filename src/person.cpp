#include "person.h"
#include <stdio.h>


person::person()
{
    //ctor
}

person::~person()
{
    //dtor
}

person::jump()
{
    printf("jumppp..");
    stateOptions::JUMP;
}

person::setState()
{
    state = stateOptions::WALKING;
}

int person::getState()
{
    return state;
}
