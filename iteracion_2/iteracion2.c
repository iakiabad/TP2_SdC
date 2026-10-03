#include <stdio.h>
#include <stdlib.h>

extern int _sumar_uno(int indice);

int main(void){
    FILE *f = fopen("../iteracion_1/dato.txt", "r");
    float indice_gini;
    fscanf(f, "%f", &indice_gini);
    /*prueba para ver si se encotró el dato
    printf("%f", indice_gini);
    */
    fclose(f);
    int indice_gini_entero = (int)indice_gini;

    int resultado_final = _sumar_uno(indice_gini_entero);
    printf("\n El resultado final de la iteracion 2 es: %d", resultado_final);
}


