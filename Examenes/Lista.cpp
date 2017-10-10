#iostream <iostream>

using namespace std;

struct Celda {
	
	double dato;
	Celda *sig;
};
	
int longitud(const Celda *lista) {
			
	Celda *p = lista;		
	int l = 0;
	
	while(p != 0) {
		l++;
		p = p->sig;
	}

   return l;	
}

/* Divide una lista en varias listas de longitud t.
 * Devolviendo un vector de punteros a cada una de
 * las sublistas.
 */
Celda** partirLista(Celda *lista, int t) {
	
	int l = longitud(lista);
	int n = (l-1)/t +1;
	
	Celda** punteros = new Celda*[n];
		
	int i, j;
	
	Celda* aux;
	
	for(i = 0; i < n; i++) {
		
		punteros[i] = lista;
		
		for(j = 1; j < t; j++) 
			lista = lista->sig;
		
		aux = lista->sig->sig;	
		lista->sig = NULL;
		lista = aux;
	}
}
	
/*
Celda** partirLista(Celda* &lista, int t, int &n) {
	
   int l = longitud(lista);
	
   // n = (l+t-1)/t ó n = (l-1)/t +1
	   
   Celda** v = new Celda*[n];
   
   v[0] = lista;
   lista = NULL;
   
   Celda *p = NULL;
   int i, j;
   
   for(i = 0; i < n-1; i++) {
			   
		p = v[i];
		
		for(j = 0; j < t-1, j++)
			p = p->sig;
			
		v[i+1] = p->sig;
		
		p->sig = NULL;
	}
	
	return v;
} */						    
		   
void imprimeInverso(const Celda *lista) {
	
	if(lista != 0)
	   return;
	   
   int l = longitud(lista);
   
   Celda **punteros = new Celda*[l];
   
   Celda *aux = lista;
   
   int i;
   
   for(i = 0; i < l; i++) {
	   aux = aux->sig;
	   punteros[i] = aux;		
   }
   
   for(i = l-1; i >= 0; i--) 
  	   cout << punteros[i]->dato << " ";
  	   
  	   cout << endl;
  	   
   delete [] punteros;
}

