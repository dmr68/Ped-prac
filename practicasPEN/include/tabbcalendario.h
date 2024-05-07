#ifndef _TABBCALENDARIO_H_
#define _TABBCALENDARIO_H_
#include "tvectorcalendario.h"

class TNodoABB;

class TABBCalendario{
	private:
		TNodoABB *raiz;

		void InordenAux(TVectorCalendario &tvc, int &p) const;
		void PreordenAux(TVectorCalendario &tvc, int &p) const;
		void PostordenAux(TVectorCalendario &tvc, int &p) const;

	public:
		TABBCalendario();
		TABBCalendario(const TABBCalendario &tabbc);
		~TABBCalendario();
		TABBCalendario &operator=(const TABBCalendario &tabbc);
		
		bool operator==(const TABBCalendario &tabbc) const;
		bool EsVacio() const;
		bool Insertar(const TCalendario &tc);
		bool Borrar(const TCalendario &tc);
		bool Buscar(const TCalendario &tc) const;
		TCalendario Raiz() const;
		int Altura() const;		
		int Nodos() const;
		int NodosHoja() const;
		TVectorCalendario Inorden() const;
		TVectorCalendario Preorden() const;
		TVectorCalendario Postorden() const;
		TVectorCalendario Niveles() const;

		TABBCalendario operator+(const TABBCalendario &tabbc) const;
		TABBCalendario operator-(const TABBCalendario &tabbc) const;

	friend ostream &operator<<(ostream &o, const TABBCalendario &tabbc);
};

class TNodoABB{
	friend class TABBCalendario;

	private:
		TCalendario item;
		TABBCalendario iz, de;

	public:
		TNodoABB();
		TNodoABB(const TNodoABB &nodo);
		~TNodoABB();
		TNodoABB &operator=(const TNodoABB &nodo);

	friend ostream &operator<<(ostream &o, const TABBCalendario &tabbc);
};

#endif