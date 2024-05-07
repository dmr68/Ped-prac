#include "../include/tvectorcalendario.h"
#include <cstring>

TVectorCalendario::TVectorCalendario(){
	tamano = 0;
	c = NULL;
}

TVectorCalendario::TVectorCalendario(int t){
	c = NULL;
	if(t < 0){
		tamano = 0;
	}
	else{
		tamano = t;
		c = new TCalendario [t];
	}
}

TVectorCalendario::TVectorCalendario(const TVectorCalendario &tvc){
	tamano = 0;
	c = NULL;
	*this = tvc;
}

TVectorCalendario::~TVectorCalendario(){
	if(c != NULL){
		delete [] c;
		c = NULL;
		tamano = 0;
	}
}

TVectorCalendario &TVectorCalendario::operator=(const TVectorCalendario &tvc){
	if(this != &tvc){
		if(tvc.c == NULL){
			c = NULL;
			tamano = 0;
		}
		else{
			if(c){
				delete [] c;
				c = NULL;
			}
			c = new TCalendario [tvc.tamano];
			for(int i = 0; i < tvc.tamano; i++){
				c[i] = tvc.c[i];
			}
			tamano = tvc.tamano;
		}
	}
	return *this;
}

bool TVectorCalendario::operator==(const TVectorCalendario &tvc) const{
	bool devolver = true;
	if(tamano == tvc.tamano){
		for(int i = 0; i < tvc.tamano && devolver; i++){
			if(!(c[i] == tvc.c[i])){
				devolver = false;
			}
		}
	}
	else{
		devolver = false;
	}
	return devolver;
}

bool TVectorCalendario::operator!=(const TVectorCalendario &tvc) const{
	return !(*this == tvc);
}

TCalendario TVectorCalendario::operator[](int i) const{
	if(i >= 1 && i <= tamano){
		return c[i-1];
	}
	else{
		return error;
	}	
}

TCalendario &TVectorCalendario::operator[](int i){
	if(i >= 1 && i <= tamano){
		return c[i-1];
	}
	else{
		return error;
	}
}

int TVectorCalendario::Tamano() const{
	return tamano;
}

int TVectorCalendario::Ocupadas() const{
	int devolver = 0;
	
	for(int i = 0; i < tamano; i++){
		if(c[i].EsVacio() == false){
			devolver++;
		}
	}
	return devolver;
}

bool TVectorCalendario::ExisteCal(const TCalendario &tc) const{
	bool devolver = false;
	for(int i  = 0; i < tamano && !devolver; i++){
		if(tc == c[i]){
			devolver = true;
		}
	}	
	return devolver;
}

void TVectorCalendario::MostrarMensajes(int dia, int mes, int anyo){
	TCalendario toCheck(dia, mes, anyo, NULL);	
	
	bool primero = true;
	
	cout << "[";
	for(int i = 0; i < tamano; i++){
		if(c[i] == toCheck || c[i] > toCheck){
			
			if(!primero){
				cout << ", ";
			}
			primero = false;
			cout << c[i];
		}
	}
	cout << "]";
}

bool TVectorCalendario::Redimensionar(int t){
	bool devolver = false;
	TCalendario *guarda;
	
	if(t > 0 && t != tamano){
		devolver = true;	// se puede redimensionar
		guarda = new TCalendario [t];

		for(int i = 0; i < tamano && i < t; i++){
			guarda[i] = c[i];
		}

		if(c){
			delete [] c;
			tamano = t;
			c = guarda;
		}
		else{
			tamano = t;
			c = guarda;
		}
	}	
	return devolver;	
}


ostream &operator<<(ostream &o, const TVectorCalendario &tvc){
	o << "[";
	for(int i = 1; i <= tvc.tamano; i++){
		o << "(" << i << ") " << tvc.c[i-1];
		if(i-1 != tvc.tamano-1){
			o << ", ";
		}
	}
	o << "]";

	return o;
}

