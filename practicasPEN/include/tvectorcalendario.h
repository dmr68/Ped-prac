#ifndef _TVECTORCALENDARIO_H_
#define _TVECTORCALENDARIO_H_
#include <iostream>
#include "tcalendario.h"
using namespace std;

class TVectorCalendario{
	friend ostream &operator<<(ostream &o, const TVectorCalendario &tvc);

	private:
		TCalendario *c;
		int tamano;
		TCalendario error;

	public:
		TVectorCalendario();
		TVectorCalendario(int t);
		TVectorCalendario(const TVectorCalendario &tvc);
		
		~TVectorCalendario();
		TVectorCalendario &operator=(const TVectorCalendario &tvc);

		bool operator==(const TVectorCalendario &tvc) const;
		bool operator!=(const TVectorCalendario &tvc) const;

		TCalendario operator[](int i) const;
		TCalendario &operator[](int i);

		int Tamano() const;
		int Ocupadas() const;
		bool ExisteCal(const TCalendario &tc) const;
		void MostrarMensajes(int dia, int mes, int anyo);
		bool Redimensionar(int t);



};
#endif