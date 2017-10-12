/**
   @file testarteASCII.cpp
   @brief lee imagenes/gio.pgm y la convierte en ascii con los caracteres "@%#*+=-:. "
   @author MP-DGIM - Grupo A

**/
#include<iostream>
#include<imagen.h>
#include<fstream>

using namespace std;

void ayuda(){
	
	cout << "Número de parámetros incorrecto. Uso:" <<endl;
	cout << "testarteASCII <imagen> <grises> <salida>" <<endl;

}



int main(int narg, char *args[]){
	if(narg != 4){
		ayuda();
		return 1;
	}
	const int MAX=45000;
    char arteASCII[MAX+1]; // 4500 + el \0
	Imagen origen;
	char grises[200];
	bool estado=true;
	
	ifstream fentrada;
	ofstream fsalida;
	int n;   

   // Leer la imagen gio.pgm
    if (!origen.leerImagen(args[1])){
	    cerr << "error leyendo "<< args[1] << endl;
	   return 1;
    } else{
		cout << "Imagen " << args[1] << " leída correctamente" << endl;
	}

	fentrada.open(args[2]);
	if(fentrada){
		fentrada >> n;
	
		fsalida.open(args[3]);
		if(fsalida){
			for (int i=0; i<n; i++){
				fentrada >> grises;
				if(origen.aArteASCII(grises, arteASCII, MAX))
					fsalida << arteASCII << endl;
				else{
					cout << "La conversión no ha sido posible" << endl; 
					estado=false;
				}
			}
		
			if(!fentrada){
				cerr<< "Error de lectura del fichero." << endl;
			}
			if(!fsalida){
				cerr<< "Error de escritura del fichero." << endl;
			}
			if(fentrada && fsalida && estado){
				cerr<< "El proceso ha sido realizado de forma correcta" << endl;
			}
			fentrada.close();
			fsalida.close();
		}
	} else {
		cerr<< "Error de apertura del fichero." << endl;
	}
}
