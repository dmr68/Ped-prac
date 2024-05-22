#include "../include/tavlcalendario.h"

// TNodoAVL
TNodoAVL::TNodoAVL(){
	fe = 0;
}

TNodoAVL::TNodoAVL(const TNodoAVL &tn){
	item = tn.item;
	iz = tn.iz;
	de = tn.de;
	fe = tn.fe;
}

TNodoAVL::~TNodoAVL(){
	fe = 0;
}

TNodoAVL &TNodoAVL::operator=(const TNodoAVL &tn){
	if(this != &tn){
		item = tn.item;
		iz = tn.iz;
		de = tn.de;
		fe = tn.fe;
	}
	return *this;
}


// TAVL
void TAVLCalendario::DD(){
	TNodoAVL *auxi;
	
	auxi = raiz;
	raiz = auxi->de.raiz;
	auxi->de.raiz = raiz->iz.raiz;
	raiz->iz.raiz = auxi;

	if(raiz->fe == 0){
		raiz->iz.raiz->fe = 1;
		raiz->fe = -1;
	}
	else{
		raiz->iz.raiz->fe = 0;
		raiz->fe = 0;
	}
}

void TAVLCalendario::II(){
	TNodoAVL *auxi;
	
	auxi = raiz;
	raiz = auxi->iz.raiz;
	auxi->iz.raiz = raiz->de.raiz;
	raiz->de.raiz = auxi;

	if(raiz->fe == 0){
		raiz->de.raiz->fe = -1;
		raiz->fe = 1;
	}
	else{
		raiz->de.raiz->fe = 0;
		raiz->fe = 0;
	}

}

void TAVLCalendario::DI(){
	TNodoAVL *auxi;
	auxi = raiz;
	raiz = raiz->de.raiz->iz.raiz;

	TNodoAVL *izq, *der;
	izq = raiz->iz.raiz;
	der = raiz->de.raiz;

	raiz->de.raiz = auxi->de.raiz;
	raiz->iz.raiz = auxi;
	auxi->de.raiz = izq;
	raiz->de.raiz->iz.raiz = der;

	if(raiz->fe == 0){
		raiz->iz.raiz->fe = 0;
		raiz->de.raiz->fe = 0;
		raiz->fe = 0;
	}
	else if(raiz->fe == -1){
		raiz->iz.raiz->fe = 0;
		raiz->de.raiz->fe = 1;	
		raiz->fe = 0;
	}
	else{
		raiz->iz.raiz->fe = -1;
		raiz->de.raiz->fe = 0;	
		raiz->fe = 0;
	}		
}

void TAVLCalendario::ID(){
	TNodoAVL *auxi;
	auxi = raiz;
	raiz = raiz->iz.raiz->de.raiz;

	TNodoAVL *izq, *der;
	izq = raiz->iz.raiz;
	der = raiz->de.raiz;

	raiz->iz.raiz = auxi->iz.raiz;
	raiz->de.raiz = auxi;
	auxi->iz.raiz = der;
	raiz->iz.raiz->de.raiz = izq;

	if(raiz->fe == 0){
		raiz->iz.raiz->fe = 0;
		raiz->de.raiz->fe = 0;
		raiz->fe = 0;
	}
	else if(raiz->fe == -1){
		raiz->iz.raiz->fe = 0;
		raiz->de.raiz->fe = 1;	
		raiz->fe = 0;
	}
	else{
		raiz->iz.raiz->fe = -1;	
		raiz->de.raiz->fe = 0;	
		raiz->fe = 0;
	}

}

TAVLCalendario::TAVLCalendario(){
	raiz = NULL;
}

TAVLCalendario::TAVLCalendario(const TAVLCalendario &tavlc){
	raiz = NULL;	
	if(tavlc.raiz){
		raiz = new TNodoAVL(*(tavlc.raiz));
	}
}

TAVLCalendario::~TAVLCalendario(){
	if(raiz){
		delete raiz;
		raiz = NULL;
	}
}

TAVLCalendario &TAVLCalendario::operator=(const TAVLCalendario &tavlc){
	if(this != &tavlc){
		this->~TAVLCalendario();
		
		raiz = NULL;

		if(tavlc.raiz){
			raiz = new TNodoAVL(*(tavlc.raiz));
		}
	}
	return *this;
}

bool TAVLCalendario::operator==(const TAVLCalendario &tavlc) const{
	if(Inorden() == tavlc.Inorden()){
		return true;
	}
	return false;
}

bool TAVLCalendario::operator!=(const TAVLCalendario &tavlc) const{
	if(Inorden() != tavlc.Inorden()){
		return true;
	}
	return false;
}

bool TAVLCalendario::EsVacio() const{
	if(raiz){
		return false;
	}
	return true;
}

bool TAVLCalendario::InsertarRecursivo(const TCalendario &tc, bool &cRecurs){
	bool devolver = false, cIzq, cDer;
	int check = 0;
	

	cIzq = cDer = false;
	if(!raiz){
		devolver = cRecurs = true;

		raiz = new TNodoAVL();
		raiz->item = tc;
	}
	else{
		if(tc == raiz->item){
			devolver = cRecurs = false;
		}
		else if(tc > raiz->item){
			devolver = raiz->de.InsertarRecursivo(tc, cDer);
		}
		else{
			devolver = raiz->iz.InsertarRecursivo(tc, cIzq);
		}
	}

	if(cDer){
		raiz->fe++;
		check = raiz->fe;
		if(check == 0){
			cRecurs = false;
		}
		else if(check == 1){
			cRecurs = true;
		}
		else{
			cRecurs = false;
			check = raiz->de.raiz->fe;
			
			if(check == 1){DD();}
			else{DI();}
		}		
	}

	if(cIzq){
		raiz->fe--;
		check = raiz->fe;
		if(check == 0){
			cRecurs = false;
		}
		else if(check == -1){
			cRecurs = true;
		}
		else{
			cRecurs = false;
			check = raiz->iz.raiz->fe;

			if(check == 1){ID();}
			else{II();}
		}
	}

	return devolver;
}

bool TAVLCalendario::Insertar(const TCalendario &tc){
	bool cRecurs, devolver = false;

	devolver = InsertarRecursivo(tc, cRecurs);
	
	return devolver;
}


bool TAVLCalendario::Buscar(const TCalendario &tc) const{
	bool devolver = false;

	if(raiz and !devolver){
		if(tc == raiz->item){
			devolver = true;
		}
		else{
			devolver = raiz->de.Buscar(tc) || raiz->iz.Buscar(tc);
		}
	}

	return devolver;
}

int TAVLCalendario::Altura() const{
	if(!raiz){
		return 0;
	}

	return 1 + max(raiz->iz.Altura(), raiz->de.Altura());
}

int TAVLCalendario::Nodos() const{
	if(!raiz){
		return 0;
	}

	return 1 + raiz->iz.Nodos() + raiz->de.Nodos();
}

int TAVLCalendario::NodosHoja() const{
	if(!raiz){
		return 0;
	}
	else{
		if(!raiz->iz.raiz && !raiz->de.raiz){
			return 1 + raiz->iz.NodosHoja() + raiz->de.NodosHoja();
		}
	}
	
	return raiz->iz.NodosHoja() + raiz->de.NodosHoja();
}


void TAVLCalendario::InordenAux(TVectorCalendario &tvc, int &p) const{
	if(raiz){
		raiz->iz.InordenAux(tvc, p);
		tvc[p] = raiz->item;
		p++;
		raiz->de.InordenAux(tvc, p);
	}
}
TVectorCalendario TAVLCalendario::Inorden() const{
	int posicion = 1;

	TVectorCalendario v(Nodos());
	InordenAux(v, posicion);

	return v;
}

void TAVLCalendario::PreordenAux(TVectorCalendario &tvc, int &p) const{
	if(raiz){
		tvc[p] = raiz->item;
		p++;
		raiz->iz.PreordenAux(tvc, p);
		raiz->de.PreordenAux(tvc, p);
	}
}
TVectorCalendario TAVLCalendario::Preorden() const{
	int posicion = 1;

	TVectorCalendario v(Nodos());
	PreordenAux(v, posicion);

	return v;
}

void TAVLCalendario::PostordenAux(TVectorCalendario &tvc, int &p) const{
	if(raiz){
		raiz->iz.PostordenAux(tvc, p);
		raiz->de.PostordenAux(tvc, p);
		tvc[p] = raiz->item;
		p++;
	}
}
TVectorCalendario TAVLCalendario::Postorden() const{
	int posicion = 1;

	TVectorCalendario v(Nodos());
	PostordenAux(v, posicion);

	return v;
}

bool TAVLCalendario::BorrarrRecursivo(const TCalendario &c, bool &dRecurs){
	bool devolver = false, dIzq, dDer;;
	int check = 0;

	TNodoAVL *pBorrar;
	TCalendario aux;
	TVectorCalendario in;
	
	dIzq = dDer = false;
	if(raiz){
		if(c < raiz->item){
			devolver = raiz->iz.BorrarrRecursivo(c, dIzq);
		}
		else if(c > raiz->item){
			devolver = raiz->de.BorrarrRecursivo(c, dDer);
		}
		else if(!raiz->iz.raiz && !raiz->de.raiz){
			devolver = dRecurs = true;
			delete raiz;
			raiz = NULL;
		}
		else if(raiz->iz.raiz && !raiz->de.raiz){
				devolver = dRecurs = true;
				pBorrar = raiz;
				raiz = raiz->iz.raiz;
				pBorrar->iz.raiz = NULL;
				delete pBorrar;
		}
		else if(!raiz->iz.raiz && raiz->de.raiz){
			devolver = dRecurs = true;
			pBorrar = raiz;
			raiz = raiz->de.raiz;
			pBorrar->de.raiz = NULL;
			delete pBorrar;
		}
		else{
			devolver = true;
			in = raiz->iz.Inorden();
			aux = in[in.Tamano()];
			raiz->item = aux;
			raiz->iz.BorrarrRecursivo(aux, dIzq);				
		}
	}

	if(dDer){
		raiz->fe--;

		check = raiz->fe;
		if(check == 0){
			dRecurs = true;
		}
		else if(check == -1){
			dRecurs = false;
		}
		else{
			dRecurs = true;

			check = raiz->iz.raiz->fe;
			if(check == 0 || check == -1){
				if(check == 0){
					dRecurs = false;
				}

				II();
			}
			else{
				ID();
			}
		}
	}

	if(dIzq){
		raiz->fe++;

		check = raiz->fe;
		if(check == 0){
			dRecurs = true;
		}
		else if(check == 1){
			dRecurs = false;
		}
		else{
			dRecurs = true;

			check = raiz->de.raiz->fe;
			if(check == 0 || check == 1){
				if(check == 0){
					dRecurs = false;
				}

				DD();
			}
			else{
				DI();
			}	
		}
	}

	return devolver;
}

bool TAVLCalendario::Borrar(const TCalendario &c){
	bool devolver = false, dRecurs;

	devolver = BorrarrRecursivo(c, dRecurs);

	return devolver;
}

TCalendario TAVLCalendario::Raiz() const{
	if(raiz){
		return raiz->item;
	}
	return TCalendario();
}


ostream &operator<<(ostream &o, const TAVLCalendario &tavlc){
	o << tavlc.Inorden();
	return o;
}

