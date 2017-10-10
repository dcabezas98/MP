
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

class Fecha {

private:
	
	int dia;
	int mes;
	int anio;

public:
	
	Fecha() :Fecha(0,0,0) {}
	
	Fecha(int d, int m, int a) {
		dia = d;
		mes = m;
		anio = a;
	}
	
	int getDia() const {
		return dia;
	}
	
	int getMes() const {
	   return mes;
	}
	
	int getAnio() const {
		return anio;
	}
};

class Hora {
	
private:
	
	int hora;
	int minuto;
	int segundo;
	
public:
	
	Hora() :Hora(0,0,0) {}
	
	Hora(int h, int m, int s) {
		hora = h;
		minuto = m;
		segundo = s;
	}
				
	int getHora() const {
		return hora;
	}
	
	int getMinuto() const {
		return minuto;
	}
	
	int getSegundo() const {
		return segundo;
	}
	
	void setHora(int h) {
		hora = h;
	}
	
	void setMinuto(int m) {
		minuto = m;
	}
		
	void setSegundo(int s) {
		segundo = s;
	}
};

class Instante {

private:
	
	Fecha fecha;
	Hora hora;
	
public:
	
	Instante() {
	
	   Fecha f(0,0,0);
		Hora h(0,0,0);
		
		fecha = f;
		hora = h;		
	}
	
	Instante(Fecha f, Hora h) :fecha(f), hora(h) {}

	Fecha getFecha() const {
		return fecha;
	}
	
	Hora getHora() const {
		return hora;
	}
	
	void setFecha(Fecha f) {
		fecha = f;
	}
	
	void setHora(Hora h) {
		hora = h;
	}
};

class Punto {
	
private:
	
	double latitud;
	double longitud;
	double altura;
	
public:
	
	Punto() :Punto(0,0,0) {}
	
	Punto(double lat, double lon, double alt) {
		latitud = lat;
		longitud = lon;
		altura = alt;
	}
	
   double getLatitud() const {
   	return latitud;
   }
   	
  	double getLongitud() const {
  		return longitud;
  	}
  	
  	double getAltura() const {
  		return altura;
  	}
  	
  	void setLatitud(double l) {
  		latitud = l;
  	}
  	
  	void setLongitud(double l) {
  		longitud = l;
  	}
  	
  	void setAltura(double a) {
  		altura = a;
  	}
};

class PuntoDeRecorrido {

private:	
	Punto punto;
	Instante instante;
	
public:
	
	PuntoDeRecorrido() {
	
	Punto p(0,0,0);
	Hora h(0,0,0);
	Fecha f(0,0,0);
	Instante i(f,h);
	
	punto = p;
	instante = i; 
	}
	
	PuntoDeRecorrido(Punto p, Instante i) :punto(p), instante(i) {}
	
	Punto getPunto() {
		return punto;
	}
	
	Instante getInstante() {
		return instante;
	}
};

Punto GetPosicion() {
	
	Punto p(1,2,3);
	
	return p;
}
	
Instante GetInstante() {
	
	Fecha f(12,6,2017);
	Hora h(15,10,30);
	
	Instante i(f,h);
	
	return i;
}

double Distancia(Punto p1, Punto p2) {
	
	double difLatitud = p1.getLatitud() - p2.getLatitud();
	double difLongitud = p1.getLongitud() - p2.getLongitud();
	double difAltura = p1.getAltura() - p2.getAltura();
	
	return sqrt(difLatitud*difLatitud + difLongitud*difLongitud + difAltura*difAltura);
}

long int DiferenciaInstantes(Instante t1, Instante t2) {
	
	int difAnio = t2.getFecha().getAnio() - t1.getFecha().getAnio();
   int difMes = t2.getFecha().getMes() - t1.getFecha().getMes();
	int difDia  = t2.getFecha().getDia() - t1.getFecha().getDia();
   int difHora = t2.getHora().getHora() - t1.getHora().getHora();
   int difMinuto = t2.getHora().getMinuto() - t1.getHora().getMinuto();
   int difSegundo = t2.getHora().getSegundo() - t1.getHora().getSegundo();
   
   return difAnio*356*24*3600 + difMes*30*24*3600 + difDia*24*3600 + difHora*3600 + difMinuto*60 + difSegundo; 
}
   
class Recorrido {

private: 
   
   PuntoDeRecorrido *puntos;
   int num_puntos;
   bool activo;
   
public:
	
	Recorrido(bool noNulo) {
		
		if(!noNulo) {
			puntos = NULL;
			num_puntos = 0;
			activo = true;
		}
		
		else {
			
			puntos = new PuntoDeRecorrido[1];
			PuntoDeRecorrido primerPunto(GetPosicion(), GetInstante());
			
			puntos[0] = primerPunto;
			num_puntos = 1;
			activo = false;			
		}
	}
   
	//Constructor copia: No necesario en las clases secundarias, ya que no trabajan con memoria dinámica
	Recorrido(const Recorrido &r) {
		
		activo = r.activo;
		num_puntos = r.num_puntos;
		
		puntos = new PuntoDeRecorrido[num_puntos];
		
		for(int i = 0; i < num_puntos; i++) 
		   puntos[i] = r.puntos[i];
   }
   
   // Tampoco necesario en clases secundarias
   Recorrido& operator=(const Recorrido &r) {
	
	   if(this != &r) {
	   	
	   	if(puntos != 0)
	   	   delete [] puntos;
	   	
	   	activo = r.activo;
	   	num_puntos = r.num_puntos;
	   	
	   	puntos = new PuntoDeRecorrido[num_puntos];
	   	
	   	for(int i = 0; i < num_puntos; i++)
	   	   puntos[i] = r.puntos[i];		
		}
		return *this;
   }
	
	~Recorrido() {
		
		if(puntos != NULL)
		   delete [] puntos;
   }
   
	void FinRecorrido() {
	   
		if(activo) {
		   
			PuntoDeRecorrido* aux = new PuntoDeRecorrido[num_puntos+1];
			
			for(int i = 0; i < num_puntos; i++)
				aux[i] = puntos[i];
							
			delete [] puntos;
			
			puntos = aux;
			
			PuntoDeRecorrido final(GetPosicion(), GetInstante());
			
			puntos[num_puntos] = final;
			num_puntos++;
		
		   activo = false;
		}
	}
	
	double DistanciaRecorrido() const {
	
	   double distancia = 0;		  
	   
	   for(int i = 1; i < num_puntos; i++)	   	
	   	distancia += Distancia(puntos[i].getPunto(), puntos[i-1].getPunto());
	   	
   	return distancia;
   }
   
   long int TiempoRecorrido() const {
   	
   	return DiferenciaInstantes(puntos[0].getInstante(), puntos[num_puntos-1].getInstante());
   }
   
   double VelocidadMedia() const {
   	
   	return DistanciaRecorrido()/TiempoRecorrido()*3.6;
   }
   
   bool LeerRecorrido(const char *archivo) {
   	
   	string cadena;
   	
   	int d_0, mes_0, a_0, h_0, min_0, s_0,
		    d_n, mes_n, a_n, h_n, min_n, s_n,  
		    d,   mes,   a,   h,   min,   s,
		    lat, lon, alt;
   	
   	ifstream f;
   	
   	f.open(archivo);
   	
   	if(!f)
   	   return false;
   	   
	   f >> cadena;
	   
	   if(cadena != "RECORRIDO_MP") {
	   	f.close();
	      return false;
	   }
	   
	   f >> d_0 >> mes_0 >> a_0;
		f >> h_0 >> min_0 >> s_0;
		f >> d_n >> mes_n >> a_n; 
		f >> h_n >> min_n >> s_n;
		
		f >> num_puntos;
		
		if(puntos != NULL)
		   delete [] puntos;
		   
		puntos = new PuntoDeRecorrido[num_puntos];
		
		for(int i = 0; i < num_puntos; i++) {
			
		   f >> lon >> lat >> alt >> d >> mes >> a >> h >> min >> s;
		   
		   Punto p(lat, lon, alt); 
		   Hora hora(h, min, s);
		   Fecha fecha(d, mes, a);
		   Instante inst(fecha, hora);
		   PuntoDeRecorrido puntor(p,inst);
		   
			puntos[i] = puntor;
		}
  		
		if(!f) {
		   f.close();
			return false;
		}
      f.close();
      return true;
	}
	
	bool EscribirRecorrido(char *archivo) const {  
	
	   ofstream f;
	   bool correcto = true;
	   string cadena = "RECORRIDO_MP";
	   
	   f.open(archivo);
	   
	   if(!f)
         return false;
      
      f << cadena << endl;
      f << puntos[0].getInstante().getFecha().getDia() << " " << puntos[0].getInstante().getFecha().getMes() << " " <<puntos[0].getInstante().getFecha().getAnio() << endl;
	   f << puntos[0].getInstante().getHora().getHora() << " " << puntos[0].getInstante().getHora().getMinuto() << " " << puntos[0].getInstante().getHora().getSegundo() << endl;
	   f << puntos[num_puntos-1].getInstante().getFecha().getDia() << " " << puntos[num_puntos-1].getInstante().getFecha().getMes() << " " << puntos[num_puntos-1].getInstante().getFecha().getAnio() << endl;
	   f << puntos[num_puntos-1].getInstante().getHora().getHora() << " " << puntos[num_puntos-1].getInstante().getHora().getMinuto() << " " << puntos[num_puntos-1].getInstante().getHora().getSegundo() << endl;
	   
	   f << num_puntos << endl;
	   
	   for(int i = 0; i < num_puntos; i++) {
	   	f << puntos[i].getPunto().getLongitud() << " " << puntos[i].getPunto().getLatitud() << " " <<  puntos[i].getPunto().getAltura() << " " 
 	        << puntos[i].getInstante().getFecha().getDia() << " " << puntos[i].getInstante().getFecha().getMes() << " " << puntos[i].getInstante().getFecha().getAnio() << " "
 	        << puntos[i].getInstante().getHora().getHora() << " " << puntos[i].getInstante().getHora().getMinuto() << " " << puntos[i].getInstante().getHora().getSegundo() << endl;		
		}
		
		if(!f) 
		   correcto = false;
		   
		f.close();
		
		return correcto;   
	}     	
	
	int getnum() {
		return num_puntos;
	}
};
	
int main(int nargs, char *args[]) {
	
	double vMax = 0;
	string archMax;
	
	Recorrido r(true);
	
	for(int i = 1; i < nargs; i++) {
	    
	   if(r.LeerRecorrido(args[i])) {
		   if(r.VelocidadMedia() > vMax) {
			   vMax = r.VelocidadMedia();
				archMax = args[i];
			}
		}
	}
	
	cout << "Recorrido con más velocidad: " << archMax << ", con " << vMax << " km/h" << endl;
}
