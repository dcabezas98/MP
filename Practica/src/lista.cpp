#include "imagen.h"
#include "lista.h"
#include <cstring>

using namespace std;

////////////////////////////////////////////////////////////////// CELDA

	Celda::Celda(){
		img=NULL;
		sig=NULL;
	}

	Celda::~Celda(){
		if(img!=NULL){
			delete img;
		}
	}
	

	void Celda::setImagen(const Imagen &img){
		if(this->img == NULL){
			this->img= new Imagen;
		}

		*this->img = img;
	}

	Imagen * Celda::getImagen() const{
		return img;
	}


	void Celda::setSiguiente(Celda *next){
		if(sig!=NULL){
			delete sig;
		}		

		sig=next;
	}

	Celda * Celda::getSiguiente() const{
		return sig;
	}

////////////////////////////////////////////////////////////////// LISTA

	Lista::Lista(){
		lista=NULL;
	}
	Lista::~Lista(){
		destruir();
	}

	void Lista::destruir(){
		while (lista!=NULL){
			Celda* aux = lista;
			lista = aux->getSiguiente();
			delete aux;
		}
	}

	void Lista::insertarPrincipio(const Imagen &img){
		Celda *aux=new Celda;
		aux->setImagen(img);
		aux->setSiguiente(lista);
		lista=aux;
	}

	void Lista::insertarFinal(const Imagen &img){

		if (lista==NULL){
			insertarPrincipio(img);
		} else{
			Celda *p=lista;
		
			while(p->getSiguiente()!=NULL){
				p=p->getSiguiente();
			}
	
			Celda *nueva=new Celda;
			p->setSiguiente(nueva);
			nueva->setImagen(img);
			nueva->setSiguiente(NULL);
		}
	}

	int Lista::longitud() const{
		int lon=0;
		Celda *p=lista;
	
		while(p != NULL){
			p=p->getSiguiente();
			lon++;
		}
		return lon;
	}
	
	Imagen * Lista::get(int pos) const{
		if(pos<longitud()){
			Celda *p=lista;
			for(int i=0; i<pos; i++){
				p=p->getSiguiente();
			}
			return p->getImagen();
		}else{
			return 0;
		}	
	}
