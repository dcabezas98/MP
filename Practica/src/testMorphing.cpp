#include "lista.h"
#include "imagen.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

void ayuda(){
	cout << "Número de argumentos incorrecto. Uso:" << endl;
	cout << "testMorphing <imagen1> <imagen2> <npasos> <salida>" <<endl;
}

int main (int nArg, char * arg[]){
	if(nArg != 5){
		ayuda();
		return 1;
	}

	Lista lista;
	Imagen inicio, fin;
	
	if(inicio.leerImagen(arg[1])){
		cout << arg[1] << " leida correctamente." << endl;
	} else {
		cerr << "Error de lectura de " << arg[1] << "." << endl;
		return 1; 
	}

	if(fin.leerImagen(arg[2])){
		cout << arg[2] << " leida correctamente." << endl;
	} else {
		cerr << "Error de lectura de " << arg[2] << "." << endl;
		return 1; 
	}

	if(inicio.filas() != fin.filas() || inicio.columnas() != fin.columnas()){
		cerr<< "Error. Las imágenes tienen tamaños diferentes." << endl;
		return 1;
	}

	int k,i,j;
	int n = atoi(arg[3]);
	Byte pixel;
	Imagen aux(inicio.filas(), inicio.columnas());	

	lista.insertarPrincipio(inicio);
		
	for(k=1; k <= n; k++){
		for(i=0; i < inicio.filas(); i++){
			for(j=0; j < inicio.columnas(); j++){
				pixel = inicio.get(i,j) + k*(fin.get(i,j)-inicio.get(i,j))/n;
				aux.set(i,j,pixel);
			}
		}
		lista.insertarFinal(aux);
	}

	char nombre[100];
	bool estado = true;
	char numero[3];

	for(k=0; k < lista.longitud() && estado; k++){
		strcpy(nombre, arg[4]);
		sprintf(numero, "%d", k);
		strcat(nombre, numero);
		strcat(nombre, ".pgm");

		estado = lista.get(k)->escribirImagen(nombre, false);
	}

	if(!estado){
		cerr << "Error en la escritura de las imagenes." << endl;
		return 1;
	} else {
		cout << "Imagenes guardadas correctamente." << endl;
	}
}
