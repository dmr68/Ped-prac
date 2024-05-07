#include "../include/tabbcalendario.h"
#include <queue> // para niveles

// TNodoABB
TNodoABB::TNodoABB(){}

TNodoABB::TNodoABB(const TNodoABB &nodo){
	item = nodo.item;
	iz = nodo.iz;
	de = nodo.de;
}

TNodoABB::~TNodoABB(){}

TNodoABB &TNodoABB::operator=(const TNodoABB &nodo){
	if(this != &nodo){
		iz = nodo.iz;
		de = nodo.de;
		item = nodo.item;
	}
	return *this;
}


// TABB
TABBCalendario::TABBCalendario(){
	raiz = NULL;
}

TABBCalendario::TABBCalendario(const TABBCalendario &tabbc){
	raiz = NULL;	
	if(tabbc.raiz){
		raiz = new TNodoABB(*(tabbc.raiz));
	}
}

TABBCalendario::~TABBCalendario(){
	if(raiz){
		delete raiz;
		raiz = NULL;
	}
}

TABBCalendario &TABBCalendario::operator=(const TABBCalendario &tabbc){
	if(this != &tabbc){
		this->~TABBCalendario();
		
		raiz = NULL;

		if(tabbc.raiz){
			raiz = new TNodoABB(*(tabbc.raiz));
		}
	}
	return *this;
}

bool TABBCalendario::operator==(const TABBCalendario &tabbc) const{
	if(Inorden() == tabbc.Inorden()){
		return true;
	}
	return false;
}

bool TABBCalendario::EsVacio() const{
	if(raiz){
		return false;
	}
	return true;
}

bool TABBCalendario::Insertar(const TCalendario &tc){
	bool devolver = false;
	
	if(!raiz){
		devolver = true;
		raiz = new TNodoABB();
		raiz->item = tc;
	}
	else{
		if(tc == raiz->item){
			devolver = false;
		}
		else if(tc > raiz->item){
			devolver = raiz->de.Insertar(tc);
		}
		else{
			devolver = raiz->iz.Insertar(tc);
		}
	}

	return devolver;
}

bool TABBCalendario::Borrar(const TCalendario &c){
	bool devolver = false;

	TNodoABB *ptborro;
	TCalendario borro;
	TVectorCalendario in;
	if(raiz){
		if(c < raiz->item){
			devolver = raiz->iz.Borrar(c);
		}
		else if(c > raiz->item){
			devolver = raiz->de.Borrar(c);
		}
		else if(!raiz->iz.raiz && !raiz->de.raiz){
			delete raiz;
			devolver = true;
			raiz = NULL;
		}
		else if(raiz->iz.raiz && !raiz->de.raiz){
				devolver = true;
				ptborro = raiz;
				raiz = raiz->iz.raiz;
				ptborro->iz.raiz = NULL;
				delete ptborro;		
		}
		else if(!raiz->iz.raiz && raiz->de.raiz){
			devolver = true;
			ptborro = raiz;
			raiz = raiz->de.raiz;
			ptborro->de.raiz = NULL;
			delete ptborro;
		}
		else{
			devolver = true;
			in = raiz->iz.Inorden();
			borro = in[in.Tamano()];	// criterio mayor izquierda
			raiz->item = borro;
			raiz->iz.Borrar(borro);				
		}
	}

	return devolver;
}

bool TABBCalendario::Buscar(const TCalendario &tc) const{
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

TCalendario TABBCalendario::Raiz() const{
	if(raiz){
		return raiz->item;
	}
	return TCalendario();
}

int TABBCalendario::Altura() const{
	if(!raiz){
		return 0;
	}

	return 1 + max(raiz->iz.Altura(), raiz->de.Altura());
}

int TABBCalendario::Nodos() const{
	if(!raiz){
		return 0;
	}

	return 1 + raiz->iz.Nodos() + raiz->de.Nodos();
}

int TABBCalendario::NodosHoja() const{
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


void TABBCalendario::InordenAux(TVectorCalendario &tvc, int &p) const{
	if(raiz){
		raiz->iz.InordenAux(tvc, p);
		tvc[p] = raiz->item;
		p++;
		raiz->de.InordenAux(tvc, p);
	}
}
TVectorCalendario TABBCalendario::Inorden() const{
	int posicion = 1;

	TVectorCalendario v(Nodos());
	InordenAux(v, posicion);

	return v;
}

void TABBCalendario::PreordenAux(TVectorCalendario &tvc, int &p) const{
	if(raiz){
		tvc[p] = raiz->item;
		p++;
		raiz->iz.PreordenAux(tvc, p);
		raiz->de.PreordenAux(tvc, p);
	}
}
TVectorCalendario TABBCalendario::Preorden() const{
	int posicion = 1;

	TVectorCalendario v(Nodos());
	PreordenAux(v, posicion);

	return v;
}

void TABBCalendario::PostordenAux(TVectorCalendario &tvc, int &p) const{
	if(raiz){
		raiz->iz.PostordenAux(tvc, p);
		raiz->de.PostordenAux(tvc, p);
		tvc[p] = raiz->item;
		p++;
	}
}
TVectorCalendario TABBCalendario::Postorden() const{
	int posicion = 1;

	TVectorCalendario v(Nodos());
	PostordenAux(v, posicion);

	return v;
}

TVectorCalendario TABBCalendario::Niveles() const{
	TVectorCalendario devolver(Nodos());
	int p = 1;
	TNodoABB *n;
	
	queue<TNodoABB *> queue;
	queue.push(raiz);
	while(!queue.empty()){
		n = queue.front();
		queue.pop();
		if(n){
			devolver[p++] = n->item;
			queue.push(n->iz.raiz);
			queue.push(n->de.raiz);
		}
	}

	return devolver;
}

TABBCalendario TABBCalendario::operator+(const TABBCalendario &tabbc) const{
	TABBCalendario devolver(*this);

	TVectorCalendario aInsertar = tabbc.Inorden();
	for(int i = 1; i <= aInsertar.Tamano(); i++){
		devolver.Insertar(aInsertar[i]); // si esta repetido no lo inserta
	}

	return devolver;
}

TABBCalendario TABBCalendario::operator-(const TABBCalendario &tabbc) const{
	TABBCalendario devolver;
	
	TVectorCalendario aBuscar = Inorden();
	for(int i = 1; i <= aBuscar.Tamano(); i++){
		if(!tabbc.Buscar(aBuscar[i])){
			devolver.Insertar(aBuscar[i]);
		}
	}	

	return devolver;
}

ostream &operator<<(ostream &o, const TABBCalendario &tabbc){
	o << tabbc.Niveles();
	return o;
}

