#include <iostream>
#include <stdint.h>

#include "linalg.h"

using float2 = linalg::aliases::float2;

class Person
{
private:   
    int16_t panic_degree;
    float2 position;
    float2 moving_direction;
    float moving_distance_last_few_seconds;  // A factor that affects panic_degree.
    bool dead;  // dead or not
}