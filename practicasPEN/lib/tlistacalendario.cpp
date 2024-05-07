#include "../include/tlistacalendario.h"

TNodoCalendario::TNodoCalendario(){
	siguiente = NULL;
}

TNodoCalendario::TNodoCalendario(const TNodoCalendario &tnc){
	c = tnc.c;
	siguiente = tnc.siguiente;
}

TNodoCalendario::~TNodoCalendario(){
	siguiente = NULL;
}

TNodoCalendario &TNodoCalendario::operator=(const TNodoCalendario &tnc){
	siguiente = tnc.siguiente;
	c = tnc.c;
	return *this;
}



TListaPos::TListaPos(const TListaPos &tlp){
	pos = tlp.pos;
}

TListaPos::TListaPos(){
	pos = NULL;
}

TListaPos::~TListaPos(){
	pos = NULL;
}

TListaPos &TListaPos::operator=(const TListaPos &tlp){
	pos = tlp.pos;
	return *this;
}

bool TListaPos::operator==(const TListaPos &tlp) const{
	return pos == tlp.pos;
}

bool TListaPos::operator!=(const TListaPos &tlp) const{
	return pos != tlp.pos;
}

TListaPos TListaPos::Siguiente() const{
	TListaPos dev_sig;
	if(pos){
		dev_sig.pos = this->pos->siguiente;
	}
	return dev_sig;
}

bool TListaPos::EsVacia() const{
	bool devolver = true;

	if(pos){
		devolver = false;
	}

	return devolver;
}



TListaCalendario::TListaCalendario(){
	primero = NULL;
}

TListaCalendario::TListaCalendario(const TListaCalendario &tlc){
	primero = NULL;
	*this = tlc;
}

TListaCalendario::~TListaCalendario(){
	TNodoCalendario *pri, *borrar;
	
	pri = primero;
	while(pri){
		borrar = pri;
		pri = pri->siguiente;
		delete borrar;
	}
	primero = NULL;
}

TListaCalendario &TListaCalendario::operator=(const TListaCalendario &tlc){
	if(this != &tlc){
		this->~TListaCalendario();
		/*for(TNodoCalendario *ptl = tlc.primero; ptl; ptl = ptl->siguiente){
			this->Insertar(ptl->c);
		}	*/
		TNodoCalendario *punt = tlc.primero; // Inicialización del puntero al primer nodo

		while(punt){
		    this->Insertar(punt->c); // Insertar el valor del calendario contenido en el nodo
		    punt = punt->siguiente; // Avanzar al siguiente nodo
		}
	}
	return *this;
}

bool TListaCalendario::operator==(const TListaCalendario &tlc) const{
	TNodoCalendario *punt, *punt_tlc;	
	bool devolver = true;
	punt_tlc = tlc.primero;
	punt = this->primero;

	while(punt && punt_tlc && devolver){
		if(punt->c == punt_tlc->c){
			punt_tlc = punt_tlc->siguiente;
			punt = punt->siguiente;
		}
		else{
			devolver = false;
		}
	}

	return !(punt || punt_tlc) && devolver;
}

TListaCalendario TListaCalendario::operator+(const TListaCalendario &tlc) const{
	TListaCalendario aux(*this);
	TNodoCalendario *punt;

	punt = tlc.primero;
	while(punt){
		aux.Insertar(punt->c);

		punt = punt->siguiente;
	}

	return aux;
}

TListaCalendario TListaCalendario::operator-(const TListaCalendario &tlc) const{
	TListaCalendario aux(*this);
	TNodoCalendario *punt;	

	punt = tlc.primero;
	while(punt){
		aux.Borrar(punt->c);

		punt = punt->siguiente;
	}

	return aux;
}

bool TListaCalendario::Insertar(const TCalendario &tc){
	bool devolver = false;
	TNodoCalendario *p_new, *punt, *p_aux = NULL;

	bool encontrado = false, check_min = false;
	
	punt = primero;
	while(punt){
		if(tc < punt->c){
			check_min = true;
		}
		else{
			if(tc != punt->c){
				p_aux = punt;
				punt = punt->siguiente;
			}
			else{
				encontrado = true;
			}
		}

		if(check_min || encontrado){
			break;
		}
	}

	if(encontrado == false){
		devolver = true;
		p_new = new TNodoCalendario();
		p_new->c = tc;
		p_new->siguiente = NULL;
		
		if(p_aux){
			p_aux->siguiente = p_new;
		}
		else{
			primero = p_new;
		}

		p_new->siguiente = punt;
	}

	return devolver;
}

bool TListaCalendario::Borrar(const TCalendario &tc){
	bool devolver = false;

	TNodoCalendario *punt = primero;
	TNodoCalendario *p_aux = NULL;
	while(punt){
		if(!devolver){
			if(punt->c == tc){
				devolver = true;
			}
			else{
				p_aux = punt;
				punt = punt->siguiente;
			}
		}
		else{
			break;
		}
	}

	if(devolver){
		if(p_aux){ 
			p_aux->siguiente = punt->siguiente;
		}
		else if(p_aux == NULL){
			primero = primero->siguiente;
		}
		delete punt;
	}
	return devolver;
}

bool TListaCalendario::Borrar(const TListaPos &tlp){
	bool devolver = false;
	
	if(tlp.pos != NULL){
		TNodoCalendario *punt = primero;
		TNodoCalendario *p_aux = NULL;
		while(punt){
			if(!devolver){
				if(punt == tlp.pos){
					devolver = true;
				}
				else{
					p_aux = punt;
					punt = punt->siguiente;
				}
			}
			else{
				break;
			}
		}

		if(devolver){
			if(p_aux){ 
				p_aux->siguiente = punt->siguiente;
			}
			else{
				primero = primero->siguiente;
			}

			delete punt;
		}
	}

	return devolver;
}

bool TListaCalendario::Borrar(int d, int m, int a){
	bool devolver = false;
	TCalendario toCheck(d, m, a, NULL);
	
	TNodoCalendario *punt = primero;
	while(punt && punt->c < toCheck){
		if(punt->c < toCheck){
			devolver = true;

			primero = primero->siguiente;
			delete punt;
			punt = primero;	
		}
		else{
			break;
		}
	}
	return devolver;
}

bool TListaCalendario::EsVacia() const{
	bool devolver = true;

	if(primero){
		devolver = false;
	}

	return devolver;
}

TCalendario TListaCalendario::Obtener(const TListaPos &tlp) const{
	if(tlp.pos){
		return tlp.pos->c;
	}
	return TCalendario();
}

bool TListaCalendario::Buscar(const TCalendario &tc) const{
	bool devolver = false;

	TNodoCalendario *punt = primero;
	while(punt){
		if(devolver){
			break;
		}
		else{
			if(punt->c == tc){
				devolver = true;
			}
			else{
				punt = punt->siguiente;
			}
		}
	}
	return devolver;
}

int TListaCalendario::Longitud() const{
	int devolver = 0;
    for(TNodoCalendario *punt = primero; punt; punt = punt->siguiente){
        devolver++;
    }
    return devolver;
}

TListaPos TListaCalendario::Primera() const{
	TListaPos devolver;
	devolver.pos = primero;
	return devolver;
}

TListaPos TListaCalendario::Ultima() const{
    TListaPos devolver;

    devolver.pos = primero;
    while(devolver.pos){
    	if(devolver.pos->siguiente){
        	devolver.pos = devolver.pos->siguiente;
    	}
    	else{
    		break;
    	}
    }

    return devolver;
}

TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2){
	TListaCalendario devolver;
	TNodoCalendario *punt = primero;

	int p = 0;
	TNodoCalendario *p_aux = NULL;
	while(true){
		p++;
		if(p >= n1 && p <= n2){
			devolver.Insertar(punt->c);
			if(punt == primero){
				primero = primero->siguiente;
				delete punt;
				punt = primero;
			}
			else{
				p_aux->siguiente = punt->siguiente;
				delete punt;
				punt = punt->siguiente;
			}
		}
		else{
			p_aux = punt;
			punt = punt->siguiente;
		}

		if(!punt){
			break;
		}
	}
	
	return devolver;
}

TListaCalendario TListaCalendario::SumarSubl(int I_L1, int F_L1, const TListaCalendario &L2, int I_L2, int F_L2) const{
	TListaCalendario devolver_L3;
	
	int p = 1;
	TNodoCalendario *punt = primero;
	while(true){
		if(p <= F_L1 && p >= I_L1){
			devolver_L3.Insertar(punt->c);
		}
		p++;
		punt = punt->siguiente;
		if(!punt){ break;}
	}

	p = 1;
	punt = L2.primero;
	while(true){
		if(p >= I_L2 && p <= F_L2){
			devolver_L3.Insertar(punt->c);
		}
		p++;
		punt = punt->siguiente;
		if(!punt){ break;}
	}
	
	return devolver_L3;
}

ostream &operator<<(ostream &o, const TListaCalendario &tlc){
	TNodoCalendario *punt;
	
	o << "<";

	punt = tlc.primero;
	while(punt){
		o << punt->c;
		if(punt->siguiente != NULL){
			o << " ";		
		}

		punt = punt->siguiente;
	}	
	o << ">";

	return o;
}






