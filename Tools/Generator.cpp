#include "Generator.h"


Generator::Generator():rd(),gen(rd()), dist(0, 100), distDouble(0.0,1.0)
{
}

int Generator::getNumber() {
    return dist(gen);
}
int Generator::getNumber(int min, int max) {
    dist.param(uniform_int_distribution<>::param_type(min,max));
    int valReturn = dist(gen);
    dist.param(uniform_int_distribution<>::param_type(0,INT32_MAX));
    return valReturn;
}
double Generator::randomZeroToOne() {
    return distDouble(gen);
}