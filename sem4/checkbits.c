#include "checkbits.h"

int checkbit(const int value, const int position){
    return (value & (1 << position)) >> position;
}