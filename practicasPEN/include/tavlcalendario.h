#ifndef _TAVLCALENDARIO_H_
#define _TAVLCALENDARIO_H_
#include "tvectorcalendario.h"

class TNodoAVL;

class TAVLCalendario{
	private:
		TNodoAVL *raiz;

		void InordenAux(TVectorCalendario &tvc, int &p) const; 
		void PreordenAux(TVectorCalendario &tvc, int &p) const; 
		void PostordenAux(TVectorCalendario &tvc, int &p) const; 

		bool InsertarRecursivo(const TCalendario &tc, bool &cRecurs);
		bool BorrarrRecursivo(const TCalendario &tc, bool &dRecurs);

		void DD(); 
		void II(); 
		void DI(); 
		void ID(); 

	public:
		TAVLCalendario(); 
		TAVLCalendario(const TAVLCalendario &tavlc); 
		~TAVLCalendario();
		TAVLCalendario &operator=(const TAVLCalendario &tavlc);  
		
		bool operator==(const TAVLCalendario &tavlc) const; 
		bool operator!=(const TAVLCalendario &tavlc) const;  
		bool EsVacio() const;
		bool Insertar(const TCalendario &tc);
		bool Buscar(const TCalendario &tc) const;
		int Altura() const;		
		int Nodos() const; 
		int NodosHoja() const; 

		TVectorCalendario Inorden() const; 
		TVectorCalendario Preorden() const; 
		TVectorCalendario Postorden() const; 

		bool Borrar(const TCalendario &tc);
		TCalendario Raiz() const; 

	friend ostream &operator<<(ostream &o, const TAVLCalendario &tavlc); 
};

class TNodoAVL{ 
	friend class TAVLCalendario;

	private:
		int fe;
		TCalendario item;
		TAVLCalendario iz, de;

	public:
		TNodoAVL();
		TNodoAVL(const TNodoAVL &nodo);
		~TNodoAVL();
		TNodoAVL &operator=(const TNodoAVL &nodo);

	friend ostream &operator<<(ostream &o, const TAVLCalendario &tavlc);
};

#endif