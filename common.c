#include "common.h"
#include <stdlib.h>

int random_bit(double probability)
{
    double res = (double)rand() / (double)RAND_MAX;
    return (res <= probability);
}
