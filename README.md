# Equipo
Joaquin Calderón 201973571-3 P-200

Daniel Martinez 201973508-k P-200

Tomás Nieto 201973529-2 P-200

## Archivos

El archivo "Strassen.cpp" contiene todo lo necesario para el funcionamiento del programa

## Compilación

Para compilar el programa se abre una consola en el directorio que contiene el archivo "Makefile" y se ejecuta el make de la siguiente forma:

```bash
make
```

Luego para ejecutarlo se ejecuta lo siguiente en la consola:

```bash
./Strassen
```

## Instrucciones generales de uso
Una vez ejecutado el programa pedira un "N" el cual es el tamaño de ambas matrices cuadradas.
Se asume que ese valor de "N" es una potencia de 2 de la forma 2^k.

Luego se ingresan N filas con N numeros enteros para la primera matriz y seguidamente otras N filas con N numeros enteros para la segunda matriz.

Despues el programa mostrará por pantalla ambas matrices junto con la multiplicacion usando el algoritmo tradicional y a continuación el resultado usando el algoritmo de Strassen. Estos acompañados del tiempo en segundos que se demoro la CPU en procesar esto y tambien el tiempo en mili segundos.

Para mas información ver el informe en el [repositorio Github](http://www.github.com/Joacaldo7965/Matrix-Multiplication-Algorithms)

## Extra

Esto fue probado en:

Sistema Operativo: Linux Mint 19.2 Cinnamon 4.2.4

Linux Kernel: 4.15.0-159-generic

Version compilador g++: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
