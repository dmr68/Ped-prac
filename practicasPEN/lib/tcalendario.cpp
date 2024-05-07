#include "../include/tcalendario.h"
#include <cstring>


TCalendario::TCalendario(){
	dia = 1; mes = 1;
	anyo = 1900;
	mensaje = NULL;
}


TCalendario::TCalendario(int dia, int mes, int anyo, const char* mensaje){
	if(ComprobarFecha(dia, mes, anyo)){
		this->mensaje = NULL;
		if(mensaje){
			this->mensaje = strdup(mensaje);
		}

		this->dia = dia;
		this->mes = mes;
		this->anyo = anyo;
	}
	else{
		this->dia = this->mes = 1;
		this->anyo = 1900;
		this->mensaje = NULL;
	}
}


TCalendario::TCalendario(const TCalendario &tc){
	mensaje = NULL;
	if(tc.mensaje){
		mensaje = strdup(tc.mensaje);
	}

	dia = tc.dia;
	mes = tc.mes;
	anyo = tc.anyo;
}


TCalendario::~TCalendario(){
	if(mensaje){
		delete[] mensaje;
		mensaje = NULL;	
	}

	dia = mes = 1;
	anyo = 1900;
}


TCalendario & TCalendario::operator=(const TCalendario &tc){
	bool fech = this->ModFecha(tc.dia, tc.mes, tc.anyo);
	bool mens = this->ModMensaje(tc.mensaje);
	return *this;
}


TCalendario TCalendario::operator+(int incremento) const{
	TCalendario dev(*this);

	for(int i = 0; i < incremento; i++){
		dev++;
	}

	return dev;
}


TCalendario TCalendario::operator-(int decremento) const{
	TCalendario dev(*this);

	for(int i = 0; i < decremento; i++){
		dev--;
	}

	return dev;
}


TCalendario TCalendario::operator++(int){	// Se incrementa después de la asignación
	TCalendario dev(*this);
	++(*this);
	return dev;
}

TCalendario & TCalendario::operator++(){
	dia++;
	if(mes != 2){
		if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
			if(dia > 30){
				dia = 1;
				mes++;
			}
		}
		else{
			if(dia > 31){
				dia = 1;
				mes++;
				if(mes == 13){
					mes = 1; 
					anyo++;
				}
			}
		}
	}
	else{
		if((anyo % 4 == 0 && anyo % 100 != 0) || anyo % 400 == 0){
			if(dia == 30){
				mes = 3;
				dia = 1;
			}
		}
		else{
			if(dia == 29){
				mes = 3;
				dia = 1;
			}
		}
	}
	return *this;
}

TCalendario TCalendario::operator--(int){
	TCalendario dev(*this);
	--(*this);
	return dev;
}

TCalendario & TCalendario::operator--(){
	dia--;
	if(dia == 0){
		if(mes == 1){
			dia = 31;
			mes = 12;
			anyo--;
		}
		else if(mes == 3){
			mes--;
			if((anyo % 4 == 0 && anyo % 100 != 0) || anyo % 400 == 0){
				dia = 29;
			}
			else{
				dia = 28;
			}
		}
		else{
			mes--;
			if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
				dia = 30;
			}
			else{
				dia = 31;
			}
		}
	}

	TCalendario comprueba; // fecha 1/1/1900
	if(*this < comprueba){
		*this = comprueba;
	}
	return *this;
}

bool TCalendario::ComprobarFecha(int dia, int mes, int anyo) const{
	bool dev = false;

	if(anyo >= 1900 && mes > 0 && dia > 0 && mes <= 12){

		if(mes == 2){
			if((anyo % 4 == 0 && anyo % 100 != 0) || anyo % 400 == 0){	// bisiesto
				if(dia <= 29){
					dev = true;
				}
			}
			else{
				if(dia <= 28){
					dev = true;
				}
			}
		}
		else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
			if(dia <= 30){
				dev = true;
			}
		}
		else{
			if(dia <= 31){
				dev = true;
			}
		}
	}

	return dev;
}

bool TCalendario::ModFecha(int dia, int mes, int anyo){
	if(ComprobarFecha(dia, mes, anyo)){
		this->dia = dia;
		this->mes = mes;
		this->anyo = anyo;
		return true;
	}

	return false;
}


bool TCalendario::ModMensaje(char *msg){
	delete[] mensaje;
	if(msg){
        mensaje = strdup(msg);
        return true;
    } 
    else{
        mensaje = NULL;
        return true;
    }

	return false;
}

bool TCalendario::operator==(const TCalendario &tc) const{
	bool comprobacion = false;
	if(mensaje != NULL && tc.mensaje != NULL){
			if(strcmp(mensaje, tc.mensaje) == 0){
				comprobacion = true;
			}
		}
		else{
			if(mensaje == NULL && tc.mensaje == NULL){
				comprobacion = true;
			}
		}

	return dia == tc.dia && mes == tc.mes && anyo == tc.anyo && comprobacion;
}

bool TCalendario::operator!=(const TCalendario &tc) const{
	return !(*this == tc);
}

int TCalendario::ComparaMsgMayor(const char *msg1, const char *msg2) const{
	int dev = 0; // iguales

	if(msg1 || msg2){
		if(!msg1){
			dev = 2;
		}
		else if(!msg2){
			dev = 1;
		}
		else{
			if(strcmp(msg1, msg2) < 0){
				dev = 2;
			}
			else if(strcmp(msg1, msg2) > 0){
				dev = 1;
			}
		}
	}

	return dev;
}

bool TCalendario::operator>(const TCalendario &tc) const{
	bool dev = true;

	// this > tc
	if(anyo < tc.anyo)
		dev = false;
	else{
		if(anyo == tc.anyo){
			if(mes < tc.mes){
				dev = false;
			}
			else{
				if(mes == tc.mes){
					if(dia < tc.dia){
						dev = false;
					}
					else{
						if(dia == tc.dia){
							if(ComparaMsgMayor(mensaje, tc.mensaje) == 2 || ComparaMsgMayor(mensaje, tc.mensaje) == 0){
								dev = false;
							}
						}	
					}
				}
			}
		}
	}

	return dev;
}

bool TCalendario::operator<(const TCalendario &tc) const{
	bool dev = true;

	if(*this > tc || *this == tc ){
		dev = false;
	}

	return dev;
}


bool TCalendario::EsVacio() const{
	return dia == 1 && mes == 1 && anyo == 1900 && mensaje == NULL;
}
int TCalendario::Dia() const{
	return dia;
}
int TCalendario::Mes() const{
	return mes;
}
int TCalendario::Anyo() const{
	return anyo;
}
char *TCalendario::Mensaje() const{
	return mensaje;
}

ostream &operator<<(ostream &o, const TCalendario &tc){
	if(tc.dia < 10){
		o << "0";
	}
	o << tc.dia << "/";

	if(tc.mes < 10){
		o << "0";
	}
	o << tc.mes << "/" << tc.anyo << " \"";

	if(tc.mensaje){
		o << tc.mensaje;
	}
	o << "\"";

	return o;
}




