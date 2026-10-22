# TP2_SdC

## Descripción

El trabajo se dividió en dos iteraciones. En la primera se obtuvo el índice de Gini de Argentina mediante la API del Banco Mundial, utilizando un ejemplo de libcurl para realizar una petición HTTP. En la segunda se recuperó el dato almacenado y se procesó mediante una subrutina escrita en ensamblador x86-64, llamada desde C.

## Iteración 1 — Obtención del dato

Para realizar la petición HTTP se tomó como base el ejemplo `getinmemory` de libcurl, que permitió recibir la respuesta del servidor y almacenarla en memoria.

A partir de este ejemplo, se adaptó el programa para consultar el índice de Gini de Argentina correspondiente al período 2011–2020. La respuesta obtenida se guardó en el archivo `dato.txt`, ubicado en el directorio de esta iteración, para que pudiera utilizarse posteriormente.

## Iteración 2 — Procesamiento en C y Assembly

En esta iteración se leyó el valor almacenado en `../iteracion_1/dato.txt` mediante `fscanf`. El dato se guardó en una variable de tipo `float` y luego se convirtió a `int`, descartando su parte decimal.

A continuación, se llamó desde C a la subrutina `_sumar_uno`, implementada en ensamblador x86-64. La rutina utilizó la pila para guardar el valor recibido, incrementarlo en uno y devolver el resultado en `RAX`, que se utilizó como valor de retorno de la función.

Finalmente, el programa imprimió el resultado obtenido.

## Depuración

Durante el desarrollo se utilizó **GDB** para depurar el programa y analizar la ejecución de las instrucciones en ensamblador. Se emplearon herramientas de inspección de registros y ejecución paso a paso para observar el comportamiento de la rutina y verificar el funcionamiento de la pila.

## Tecnologías utilizadas

- C
- Assembly x86-64
- libcurl
- GCC
- GDB
- API REST del Banco Mundial

## Fuente de datos

[API del Banco Mundial — Índice de Gini de Argentina (2011–2020)](https://api.worldbank.org/v2/country/ARG/indicator/SI.POV.GINI?date=2011:2020&format=json)

