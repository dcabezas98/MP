#include <iostream>
#include <fstream>

using namespace std;

double max(double a, double b) {
	if(a > b)
	   return a;
	   
   else
      return b;
}

int MezclarUnico(double *v1, int n1, double *v2, int n2, double *v3) {
	
	int i1, i2, n3;
	
	i1 = i2 = n3 = 0;
	
	while(i1 < n1 && i2 < n2) {
		
		if(v1[i1] <= v2[i2]) {
			
			v3[n3] = v1[i1];
			
			if(v1[i1] == v2[i2])
			   i2++;
			   
			n3++;
			i1++;
			
		} else {
		
		   v3[n3] = v2[i2];
			n3++;
			i2++;
		}
	}
	
	while(i1 < n1) {		
		v3[n3] = v1[i1];
		n3++;
		i1++;
	}
		
	while(i2 < n2) {
		v3[n3] = v2[i2];
		n3++;
		i2++;
	}
	
	return n3;
}

class SkyLine {
	
public:
	
	double *abscisas;
	double *alturas;
	int n;
	
	SkyLine() {
		
		abscisas = NULL;
		alturas = NULL;
		n = 0;
	}
	
	SkyLine(double x1, double x2, double h) {
		
		n = 2;
		
		abscisas = new double[n];
		alturas = new double[n];
		
		abscisas[0] = x1; 
		abscisas[1] = x2;
		
		alturas[0] = h;
		alturas[1] = 0;			
	}
	
	SkyLine(const SkyLine &skyline) {
		
		n = skyline.n;
		
		abscisas = new double[n];
		alturas = new double[n];
		
		for(int i = 0; i < n; i++) {
			abscisas[i] = skyline.abscisas[i];
			alturas[i] = skyline.alturas[i];
		}
	}
	
	SkyLine& operator=(const SkyLine &skyline) {
		
		if(this != &skyline) {
			
			if(n != 0) {
				delete [] abscisas;
				delete [] alturas;
			}
		
		   n = skyline.n;
		   
		   abscisas = new double[n];
		   alturas = new double[n];
		   
         for(int i = 0; i < n; i++) {
         	abscisas[i] = skyline.abscisas[i];
         	alturas[i] = skyline.alturas[i];
         }
	   }
		return *this;	
	}
		
	~SkyLine() {
		
		if(n != 0) {
			delete [] abscisas;
			delete [] alturas;
		}
	}
	
	double altura(double x) const {
	
	   double h = 0;
	   							   
		int i = 0;
		
		if(x < abscisas[0] || x >= abscisas[n-1])
		   return 0;
		   
		while(abscisas[i] <= x)
			i++;
					
		h = alturas[i-1];

		return h;	
	}
	
	SkyLine operator+(const SkyLine &s) {
		
		SkyLine suma;
				
		double *aux = new double[n+s.n];
		
		suma.n = MezclarUnico(abscisas, n, s.abscisas, s.n, aux);
		
		suma.abscisas = new double[suma.n];
		suma.alturas = new double[suma.n];
		
		int i;
				
		for(i = 0; i < suma.n; i++) {
			suma.abscisas[i] = aux[i];
			suma.alturas[i] = max(altura(suma.abscisas[i]), s.altura(suma.abscisas[i]));
	   }
		
		delete [] aux;
		
		return suma;
	}
};
		
ostream& operator<<(ostream &flujo, const SkyLine s) {
	
	flujo << s.n << endl;
	
	for(int i = 0; i < s.n; i++)
	   flujo << s.abscisas[i] << " " << s.alturas[i] << endl;
	   
   return flujo;
}

istream& operator>>(istream &flujo, SkyLine &s) {
	
	if(s.n != 0) {
	   delete [] s.abscisas;	
	   delete [] s.alturas;
	}
	
	flujo >> s.n;
		
	s.abscisas = new double[s.n];
	s.alturas = new double[s.n];
		
	for(int i = 0; i < s.n; i++)
	   flujo >> s.abscisas[i] >> s.alturas[i];
	   
   return flujo;
}

bool Cargar(const char *arch, SkyLine &s) {
	
	bool exito = true;
	ifstream f;
	
	string cadena;
	
	f.open(arch);
	
	if(!f)
	   return false;
	
	f >> cadena;
	
	if(cadena != "MP-SKYLINE-1.0") {
		f.close();
		return 0;
	}
	
   f >> s;
   
   if(!f) 
   	exito = false;
   	
  	f.close();
  	
  	return exito;
}
   
bool Salvar(const char *arch, const SkyLine &s) {
	
	bool exito = true;
	
	string cadena = "MP-SKYLINE-1.0";
	
	ofstream f;
	
	f.open(arch);
	
	if(!f)
	   return false;
	   
   f << cadena << endl;
	   
   f << s;
   
   if(!f)
      exito = false;
      
   f.close();
   
   return exito;
}   

int main() {
	
	char arch1[] = "arch1.txt";
	char arch2[] = "arch2.txt";
	
	SkyLine s1, s3;
		
	Cargar(arch1,s1);
			
	SkyLine s2(2,4.5,3);
	
	s3 = s1 + s2;
			
	Salvar(arch2,s3);	
}


