#ifndef _TLISTACALENDARIO_H_
#define _TLISTACALENDARIO_H_
#include "tcalendario.h"
#include <iostream>
using namespace std;

class TNodoCalendario;
class TListaPos;
class TListaCalendario;


class TNodoCalendario{
	private:
		TCalendario c;
		TNodoCalendario *siguiente;
	public:
		TNodoCalendario();
		TNodoCalendario(const TNodoCalendario &tnc);
		~TNodoCalendario();

		TNodoCalendario &operator=(const TNodoCalendario &tnc);

	friend class TListaPos; 
	friend class TListaCalendario;
	friend ostream &operator<<(ostream &o, const TListaCalendario &tlc);
};


class TListaPos{
	private:
		TNodoCalendario *pos;
	public:
		TListaPos();
		TListaPos(const TListaPos &tlp);
		~TListaPos();

		TListaPos &operator=(const TListaPos &tlp);
		bool operator==(const TListaPos &tlp) const;
		bool operator!=(const TListaPos &tlp) const;

		TListaPos Siguiente() const;
		bool  EsVacia() const;

	friend class TListaCalendario;
};


class TListaCalendario{
	private:
		TNodoCalendario *primero;
		void Liberar();
	public:
		TListaCalendario();
		TListaCalendario(const TListaCalendario &tlc);
		~TListaCalendario();
		TListaCalendario &operator=(const TListaCalendario &tlc);

		bool operator==(const TListaCalendario &tlc) const;
		TListaCalendario operator+(const TListaCalendario &tlc) const;
		TListaCalendario operator-(const TListaCalendario &tlc) const;

		bool Insertar(const TCalendario &tc);
		bool Borrar(const TCalendario &tc);
		bool Borrar(const TListaPos &tlp);
		bool Borrar(int dia, int mes, int anyo);
	
		bool EsVacia() const;
		TCalendario Obtener(const TListaPos &tlp) const;
		bool Buscar(const TCalendario &tc) const;
		int Longitud() const;
		TListaPos Primera() const;
		TListaPos Ultima() const;

		TListaCalendario SumarSubl(int I_L1, int F_L1, const TListaCalendario &L2, int I_L2, int F_L2) const;
		TListaCalendario ExtraerRango(int n1, int n2);
		
	friend ostream &operator<<(ostream &o, const TListaCalendario &tlc);
};
#endif