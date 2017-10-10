#include <iostream>
#include <fstream>
using namespace std;

struct Pareja {
	int dato;
	int nveces;
};

class Frecuencias {
	
public:
		
	Pareja *parejas;
	int npares;
	
	Frecuencias() {
		
		npares = 0;
		parejas = 0;
	}
	
	Frecuencias(const Frecuencias &frec) {
		
		npares = frec.npares;
		
		parejas = new Pareja[npares];
		
		for(int i = 0; i < npares; i++) 
		   parejas[i] = frec.parejas[i];
   }
   
   ~Frecuencias() {
   	
   	if(parejas != 0) 
   	   delete [] parejas;
	}
	
	Frecuencias& operator=(const Frecuencias &frec) {
		
		if(this != &frec) {
			
			if(parejas != 0)
            delete [] parejas;
            
         npares = frec.npares;
         
         parejas = new Pareja[npares];
         
         for(int i = 0; i < npares; i++) 
            parejas[i] = frec.parejas[i];
      }
      return *this;
   }
   
   void Add(int num) {
   	
   	int i, pos = -1;
  	   bool sigue = true;
   	
   	for(i = 0; i < npares && sigue; i++) {
   		if(parejas[i].dato >= num) {
   			sigue = false;
   			if(parejas[i].dato == num)
   			   parejas[i].nveces++;
			   else
			      pos = i;
			}
		}
		
		if(sigue)
		   pos = npares;
		   
		if(pos != -1) {
			Pareja *aux = parejas;
				
			npares++;
			
	      if(parejas != 0)
			   delete [] parejas;
				
			parejas = new Pareja[npares];
			
			for(i = 0; i < pos; i++)
			   parejas[i] = aux[i];
			   
	      parejas[pos].dato = num;
	      parejas[pos].nveces = 1;
	      
	      for(i = pos+1; i < npares; i++) 
	         parejas[i] = aux[i-1];
      }
   }
   
   void operator+=(int num) {
   	
   	this->Add(num);
   }
   
   int& getNpares() {
   	return npares;
   }
      
   Pareja& getPareja(int i) {
   	if(0 <= i && i < npares)
   	   return parejas[i];
  	}
   
   void reserva(int n) {
   	if(parejas != 0)
   	   delete parejas;
   	   
	   parejas = new Pareja[n];
	}
	
	void aniade(Pareja p, int i) {
      if(i <= 0 && i <= npares) 
	   	parejas[i] = p;
	}
	
	void setNpares(int n) {
		npares = n;
	}
};

ostream& operator<<(ostream &flujo, Frecuencias &frec) {

   flujo << frec.getNpares() << endl;
	
	for(int i = 0; i < frec.getNpares(); i++) 
	   flujo << frec.getPareja(i).dato << " " << frec.getPareja(i).nveces << endl;
   
   return flujo;
}

istream& operator>>(istream &flujo, Frecuencias &frec) {
	
	flujo >> frec.getNpares();
	
	frec.reserva(frec.npares);

   for(int i = 0; i < frec.npares; i++) 
      flujo >> frec.parejas[i].dato >> frec.parejas[i].nveces;
   
   return flujo;
}
   	   
bool Leer(const char *archivo, Frecuencias &frec) {
	
	ifstream f;
	bool correcto = true;
	
	f.open(archivo);
	
	if(!f)
	   return false;
	   
   f >> frec;
   
   if(!f)
      correcto = false;
      
   f.close();
   return correcto;
}

bool Escribir(const char *archivo, Frecuencias &frec) {

   ofstream f;
	bool correcto = true;
	
	f.open(archivo);

	if(!f)
	   return false;
	   
	f << frec;
	
	if(!f){
	   correcto = false;
		cout << "despues" << endl;
	}
	f.close();
	return correcto;
}

int main() { 

   char arch1[] = "archivo1.txt";
   char arch2[] = "archivo2.txt";

   Frecuencias f1;
   
   cout << Leer(arch1, f1) << endl;
   
   f1.Add(6);
   f1.Add(11);
   
   Frecuencias f2(f1);
   
   cout << Escribir(arch2, f2);
}
