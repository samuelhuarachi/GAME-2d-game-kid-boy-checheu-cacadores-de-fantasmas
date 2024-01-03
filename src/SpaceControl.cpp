#include <iostream>
#include "SpaceControl.h"

using namespace std;

SpaceControl::SpaceControl()
{
    //ctor
    pristine = true;
    variationCount = 0;
    variation = 0;
}

SpaceControl::~SpaceControl()
{
    //dtor
}

void SpaceControl::teste() {
    cout << "Teste... \n";
}

void SpaceControl::setInitialSpace(double value) {
    cout << "O espaço inicial eh: " << value << "\n";
    initialSpace = value;
    return;
}

void SpaceControl::setFinalSpace(double value) {
    cout << "O espaço final eh: " << value << "\n";
    finalSpace = value;
    return;
}

void SpaceControl::setPristine(bool value) {
    pristine = value;
}

bool SpaceControl::getPristine() {
    return pristine;
}

void SpaceControl::setVariation(double value) {
    variation = value;
}

double SpaceControl::getVariation() {
    return variation;
}

double SpaceControl::getVariationCount() {
    return variationCount;
}

void SpaceControl::setVariationCount(double value) {
    variationCount = value;
}

void SpaceControl::handle() {
    variationCount++;
}

bool SpaceControl::isHandleble() {
    double absVariation = std::abs(variation);

    if (absVariation > variationCount) {
        return true;
    }
    return false;
}

