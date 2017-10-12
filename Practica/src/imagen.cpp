#include "byte.h"
#include "imagen.h"
#include "pgm.h"
#include <cmath>
#include <cstring>

using namespace std;

	Imagen::Imagen(){
		nfilas=0;
		ncolumnas=0;
		datos=NULL;
	}

	Imagen::Imagen(int filas, int columnas){
		datos=NULL;
		crear(filas, columnas);
	}

	Imagen::Imagen(const Imagen &imagen1) {

		nfilas = imagen1.filas();
		ncolumnas = imagen1.columnas();
	
		datos = new Byte*[nfilas];

		datos[0] = new Byte[nfilas*ncolumnas];

		int i, j;

		for(i = 1; i < nfilas; i++)      
		  datos[i] = datos[i-1] + ncolumnas;

		for(i = 0; i < nfilas; i++) {
			for(j = 0; j < ncolumnas; j++) 
				set(i,j,imagen1.get(i,j));
		}
	}

	Imagen& Imagen::operator=(const Imagen &imagen1) {
		if(this!= &imagen1){
			if(datos != NULL) {
				delete [] datos[0];
				delete [] datos;
			}

			nfilas = imagen1.filas();
			ncolumnas = imagen1.columnas();
	
			datos = new Byte*[nfilas];

			datos[0] = new Byte[nfilas*ncolumnas];

			int i, j;

			for(i = 1; i < nfilas; i++)      
			  datos[i] = datos[i-1] + ncolumnas;

			for(i = 0; i < nfilas; i++) {
				for(j = 0; j < ncolumnas; j++) 
					set(i,j,imagen1.get(i,j));
			}
		}
		return *this;
	}

	Imagen:: ~Imagen(){
	
			if(datos != NULL){
				delete [] datos[0];
				delete [] datos;
				datos=NULL;
			}	
			nfilas=ncolumnas=0;

	}
   
   	void Imagen:: crear(int filas, int columnas){
				
		if(datos != NULL){
			delete [] datos[0];
			delete [] datos;
			datos=NULL;
		}

		if(filas*columnas >= 0){
			nfilas=abs(filas);
			ncolumnas=abs(columnas);
			
			datos= new Byte*[nfilas];
			datos[0]= new Byte[filas*columnas];

			int j,i;

			for (i=1; i < nfilas; i++){
				datos[i]=datos[i-1]+ncolumnas;
			}
	
			for (i=0; i< nfilas; i++){
				for (j=0; j< ncolumnas; j++){
					datos[i][j]=0x0;
				}
			}

		} else {
			nfilas = ncolumnas = 0;
		}
	}


	int Imagen:: filas() const{
		return nfilas;
	} 


	int Imagen:: columnas() const{
		return ncolumnas;
	}
   

	void Imagen:: set(int y, int x, Byte v){
		
		if(y>=0 && y<nfilas && x>=0 && x<ncolumnas){
			datos[y][x]=v;
		}
	}
   
   
	Byte Imagen:: get(int y, int x) const{
		if(y>=0 && y<nfilas && x>=0 && x<ncolumnas){
			return datos[y][x];
		} else {
			return 0x0;
		}
	}
   

	void Imagen:: setPos(int i, Byte v){
		if (i >=0 && i < nfilas*ncolumnas){		
			datos[i/ncolumnas][i%ncolumnas]=v;
		}
	}
   
 
	Byte Imagen:: getPos(int i) const{
		if (i >=0 && i < nfilas*ncolumnas){	
			return datos[i/ncolumnas][i%ncolumnas];
		}else{
			return 0x0;
		}
	}



	bool Imagen:: leerImagen(const char nombreFichero[]){
		bool correcto;
		
		if(infoPGM(nombreFichero, nfilas, ncolumnas) == IMG_PGM_BINARIO){
			crear(nfilas, ncolumnas);
			correcto = leerPGMBinario(nombreFichero, datos[0], nfilas, ncolumnas);			
		}else if(infoPGM(nombreFichero, nfilas, ncolumnas) == IMG_PGM_TEXTO){
			crear(nfilas, ncolumnas);
			correcto = leerPGMTexto(nombreFichero, datos[0], nfilas, ncolumnas);			
		}
		
		
		return correcto;
	}
   

	bool Imagen:: escribirImagen(const char nombreFichero[], bool esBinario) const{
		int fila=nfilas, columna=ncolumnas;
		bool correcto;
		
		if(esBinario){
			correcto = escribirPGMBinario(nombreFichero, datos[0], fila, columna);
		}else{
			correcto = escribirPGMTexto(nombreFichero, datos[0], fila, columna);
		}
		
		return correcto;
	}
  
	Imagen Imagen:: plano (int k) const{
		Imagen plano(nfilas, ncolumnas);
		Byte mask;

		if(0 <=k && k <= 7){
			for(int i=0; i<nfilas*ncolumnas; i++){
				if (getBit(getPos(i), k)){
					mask=0xff;		
				} else{
					mask=0x0;
				}
				plano.setPos(i,mask);
			}
		}
		
		return plano;
	}

	bool Imagen:: aArteASCII(const char grises[], char arteASCII[], int maxlong) const{
		
		if(maxlong > nfilas*(ncolumnas + 1)){
			
			int i, j, cardinal;

			cardinal=strlen(grises);

			for(i=0; i<nfilas; i++){
				for(j=0; j<ncolumnas; j++){
					arteASCII[i*ncolumnas+(i+j)]=grises[(getPos(i*ncolumnas+j)*cardinal)/256];
				}
				arteASCII[i*ncolumnas+(i+j)]='\n';
			}
			
			arteASCII[i*ncolumnas+i]='\0';
			return true;			
			
		}else{
			return false;
		}

	}

