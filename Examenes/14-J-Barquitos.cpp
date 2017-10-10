#include <iostream>
#include <fstream>

using namespace std;

class Barquitos {
	
	int filas;
	int columnas;
        int **tablero;
   
public:
	
    Barquitos(int f, int c) {
		
       if(0 < f && 0 < c) {
	   	
		filas = f;
		columnas = c;
			
		tablero = new *int[filas];
			
		int i, j;
			
		for(i = 0; i < filas; i++) {
				
			tablero[i] = new int[columnas];
		      
             	        for(j = 0; j < columnas; j++)
			        tablero[i][j] = 9;
	       }
   	}
   }
   
   ~Barquitos() {
   	
   	if(tablero != NULL) {
   		
   		for(int i = 0; i < filas; i++)
   		   delete [] tablero[i];
         
			delete [] tablero;
		}
   }
   
   Barquitos(const Barquitos &otro) {
   	
   	filas = otro.filas;
   	columnas = otro.columnas;
   	
   	tablero = new *int[filas];
			
		int i, j;
		
		for(i = 0; i < filas; i++) {
			
			tablero[i] = new int[columnas];
	      
	      for(j = 0; j < columnas; j++)
	         tablero[i][j] = otro.tablero[i][j];
      }
   }
   
   Barquitos& operator=(const Barquitos &otro) {
   	
   	if(this != &otro) {
   		
	   	if(tablero != NULL) {
	   		
	   		for(int i = 0; i < filas; i++)
	   		   delete [] tablero[i];
	         
				delete [] tablero;
			}
			
			filas = otro.filas;
			columnas = otro.columnas;
			
			tablero = new *int[filas];
			
			int i, j;
			
			for(i = 0; i < filas; i++) {
				
				tablero[i] = new int[columnas];
		      
		      for(j = 0; j < columnas; j++)
		         tablero[i][j] = otro.tablero[i][j];
	      }
		}
		return *this;
   }
};
