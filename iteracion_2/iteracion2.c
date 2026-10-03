#include <stdio.h>
#include <stdlib.h>
int main(void){
    FILE *f = fopen("../iteracion_1/dato.txt", "r");
    float indice_gini;
    fscanf(f, "%f", &indice_gini);
    /*prueba para ver si se encotró el dato
    printf("%f", indice_gini);
    */
    
}
