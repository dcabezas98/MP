#include <iostream>
#include <fstream>

using namespace std;
   	
struct Valor {
	int fila;
	int columna;
	double valor;
};

int combinarSuma(const Valor *valores1, const int utiles1, const Valor *valores2, const int utiles2, Valor *resultado) {
	
	int k, i, fila, columna, utiles3 = 0;
	double valor;
	bool repetido;
	
	for(k = 0; k < utiles1; k++) {
	   resultado[utiles3].fila = valores1[k].fila;
	   resultado[utiles3].columna = valores1[k].columna;
	   resultado[utiles3].valor = valores1[k].valor;
	   utiles3++;
	}
		
	for(k = 0; k < utiles2; k++) {
		
		fila = valores2[k].fila;
		columna = valores2[k].columna;
		valor = valores2[k].valor;
		
	   for(i = 0, repetido = false; i < utiles3 && !repetido; i++) {
	      
			if(resultado[i].fila == fila && resultado[i].columna == columna) {
				resultado[i].valor += valor;   
				repetido = true;
			}
	   }
	   
	   if(!repetido) {
	   	resultado[utiles3].fila = fila;
	   	resultado[utiles3].columna = columna;
	   	resultado[utiles3].valor = valor;
	   	utiles3++;
	   }
	}
	
	return utiles3;
}

class MatrizDispersa {
	
public:

	int nfilas;
	int ncolumnas;
	Valor *valores;
	int numeroValores;
	
	MatrizDispersa() {
		
		nfilas = ncolumnas = numeroValores = 0;
		valores = NULL;
	}
	
	MatrizDispersa(int numero_filas, int numero_columnas, int *filas, int *columnas, double *val, int n) {
		
		nfilas = numero_filas;
		ncolumnas = numero_columnas;
		numeroValores = n;
		
		valores = new Valor[numeroValores];
		
		for(int i = 0; i < numeroValores; i++) {
		   
			valores[i].fila = filas[i];
			valores[i].columna = columnas[i];
			valores[i].valor = val[i];
		}
	}
	
	MatrizDispersa(const MatrizDispersa &matriz) {
		
		nfilas = matriz.nfilas;
		ncolumnas = matriz.ncolumnas;
		
		numeroValores = matriz.numeroValores;
		
		valores = new Valor[numeroValores];
		
		for(int i = 0; i < numeroValores; i++)				
			valores[i] = matriz.valores[i];
	}
	
	MatrizDispersa& operator=(const MatrizDispersa &matriz) {
		
		if(this != &matriz) {
			
			if(valores != NULL)
			   delete [] valores;
   
			nfilas = matriz.nfilas;
			ncolumnas = matriz.ncolumnas;
			numeroValores = matriz.numeroValores;
			
			valores = new Valor[numeroValores];
			
			for(int i = 0; i < numeroValores; i++)				
				valores[i] = matriz.valores[i];
	   }   
						
		return *this;
	}	
	
	~MatrizDispersa() {
		
		if(valores != NULL) {	
			delete [] valores;
		}
	}
	
	double obtenerValor(int f, int c) const {
		
		double valor = 0;
		int i;
		bool encontrado = false;
		
		for(i = 0; i < numeroValores && !encontrado; i++) {
			
			if(valores[i].fila == f && valores[i].columna == c) {
				valor = valores[i].valor;
				encontrado = true;
			}
		}
		
		return valor;
	}
	
	void asignarValor(int f, int c, double valor) {
	
		bool encontrado = false;
		
		for(int i = 0; i < numeroValores && !encontrado; i++) {
		   
			if(valores[i].fila == f && valores[i].columna == c) {
			   encontrado = true;
				
				if(valor != 0)
				   valores[i].valor = valor;
				   
	         else {
	         	
	         	numeroValores--;
	         	
	         	Valor *val = new Valor[numeroValores];
	         	int j;
	         	
	         	for(j = 0; j < i; j++)		         		
	               val[j] = valores[j];
	               
               for(j = i; j < numeroValores; j++)
                  val[j] = valores[j+1];
                  
               delete [] valores;
               
               valores = val; 	
	         }
	      }
	   }
	   
	   if(!encontrado && valor != 0) {
	   	valores[numeroValores] = {f, c, valor};
	   	numeroValores++;
	   }
	}
	
	MatrizDispersa operator+(const MatrizDispersa &matriz) const {
		
		MatrizDispersa suma;
		
		suma.nfilas = nfilas;
		suma.ncolumnas = ncolumnas;
		
		Valor *aux = new Valor[numeroValores + matriz.numeroValores];
		
		suma.numeroValores = combinarSuma(valores, numeroValores, matriz.valores, matriz.numeroValores, aux);
		
		suma.valores = new Valor[suma.numeroValores];
		
		for(int i = 0; i < suma.numeroValores; i++)
			suma.valores[i] = aux[i];
			
		delete [] aux;
		
		return suma;
	}		
};

ostream& operator<<(ostream &flujo, const MatrizDispersa &m) {
	
	flujo << m.nfilas << " " << m.ncolumnas << " " << m.numeroValores << endl;
	
	for(int i = 0; i < m.numeroValores; i++)
	   flujo << m.valores[i].fila << " " << m.valores[i].columna << " " << m.valores[i].valor << endl;
		
	return flujo;
}

istream& operator>>(istream &flujo, MatrizDispersa &m) {
	
	flujo >> m.nfilas >> m.ncolumnas >> m.numeroValores;
	
	if(m.valores != NULL)
      delete [] m.valores;
      
	m.valores = new Valor[m.numeroValores];
	
	for(int i = 0; i < m.numeroValores; i++)
		flujo >> m.valores[i].fila >> m.valores[i].columna >> m.valores[i].valor;
		
	return flujo;
}

bool cargar(char *archivo, MatrizDispersa &m) {
		
	ifstream f;
	
	f.open(archivo);
	
	string cadena;
	
	if(!f)
	   return false;
	   
	f >> cadena;
	
	if(cadena != "MP-MATRIZDISPERSA-1.0") {
		f.close();
		cerr << "La cadena no coincide" << endl;
		cout << cadena << endl;
		return false;
	}	      
	      	   
   f >> m;
   
   if(!f) {
   	f.close();
   	return false;
   }
   
   f.close();
   
   return true;
}

bool salvar(char *archivo, const MatrizDispersa &m) {
	
	ofstream f;
	
	char cadena[] = "MP-MATRIZDISPERSA-1.0";
	
	f.open(archivo);
	
	if(!f)
	   return false;
	
	f << cadena << endl;
	
	f << m;
	
	if(!f) {
		f.close();
		return false;
	}
	
	f.close();
	
	return true;
}
		   	
int main() {
	
	MatrizDispersa m1, m2, m3;
	char arch1[] = "arch1.txt";
	char arch2[] = "arch2.txt";
	char arch3[] = "hola.txt";
	
	cargar(arch1, m1);
	cargar(arch2, m2);
	
	m3 = m1 + m2;
		
	salvar(arch3, m3);
}
