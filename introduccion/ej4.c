#include <stdio.h>
#include <stdlib.h>

float negativo(float x)
{
    return -x;
}

int main(int argc, char** argv) {

    double f, x;

    f=1.5E1.5;
    printf("x=");
    scanf("%f",&x);
    x=negativo(x);

    return (EXIT_SUCCESS);
}


