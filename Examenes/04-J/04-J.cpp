#include <iostream>
#include <fstream>

using namespace std;

class Matriz {
	
	double * datos;	
	int filas, columnas;
	
public:
	
	Matriz() {
		datos = NULL;
		filas = columnas = 0;
	}
	
	~Matriz() {
		
		if(datos != NULL)
	      delete [] datos;
		
		datos = NULL;
		filas = columnas = 0;
	}
		 
	Matriz(const Matriz &m) {
		
		if(datos != NULL)
		   delete datos;
		   
		filas = m.filas;
		columnas = m.columnas;
		
		datos = new double[filas*columnas];
		
		for(int i = 0; i < filas*columnas; i++) 
			datos[i] = m.datos[i];
		
	}
	
	Matriz& operator = (const Matriz &m) {
		
		if(&m != this) {
			
			if(datos != NULL)
			   delete datos;
			
			filas = m.filas;
			columnas = m.columnas;
			
			datos = new double[filas*columnas];
			
			for(int i = 0; i < filas*columnas; i++)
	         datos[i] = m.datos[i];
		}
		return *this;
	}
	
	void Set(int f, int c, double d) {
		
		if(0 <= f && f < filas && 0 <= c && c < columnas) 
			datos[f*columnas+c] = d;
	}
	
	double Get(int f, int c) const {
		
		if(0 <= f && f < filas && 0 <= c && c < columnas)
		   return datos[f*columnas+c];
   }
   
   int Leer(const char * nombre) {
   	
   	if(datos != NULL) {
   	   delete datos;
   	}
   	   
   	ifstream f;
   	
   	f.open(nombre);
   	
   	if(!f) {
   		cerr << "Error en la apertura del fichero " << nombre << endl;
   		datos = NULL;
   		return 1;
   	}
   	
		f >> filas >> columnas;
		
		datos = new double[filas*columnas];
		
		int i;
		
		for(i = 0; i < filas*columnas; i++)				
			f >> datos[i];
		
		if(!f) {
			cerr << "Error en la lectura del fichero " << nombre << endl;
			f.close();
			return 1;
		}
		
		f.close();
			
		return 0;		
   }
	
 
 	int Escribir(const char * nombre) const {
		
		ofstream f;
		
		f.open(nombre);
		
		if(!f) {
			cerr << "Error de apertura del fichero " << nombre << endl;
			return 1;
		}
		
		f << filas << " " << columnas << "\n";
				
		int i, j;
		
		for(i = 0; i < filas; i++) {
			for(j = 0; j < columnas; j++) {
				f << Get(i,j) << " ";
			}
			f << "\n";
		}
		
	   if(!f) {
	   	cerr << "Error en la escritura en el fichero " << nombre << endl;
	   	f.close();
	   	return 1;
	   }
		f.close();
		
		return 0;  
	}
};
