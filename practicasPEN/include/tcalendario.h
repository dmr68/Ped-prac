#ifndef _TCALENDARIO_H_
#define _TCALENDARIO_H_
#include <iostream>
using namespace std;

class TCalendario{
	friend ostream &operator<<(ostream &o, const TCalendario &tc);

	private:
		int dia, mes, anyo;
		char* mensaje;
		bool ComprobarFecha(int d, int m, int a) const;
		int ComparaMsgMayor(const char *msg1, const char *msg2) const;

	public:
		TCalendario();
		TCalendario(int dia, int mes, int anyo, const char* mensaje);
		TCalendario(const TCalendario &tc);
		~TCalendario();

		TCalendario &operator=(const TCalendario &tc);

		TCalendario operator+(int inc) const;
		TCalendario operator-(int dec) const;
		TCalendario operator++(int inc);
		TCalendario &operator++();
		TCalendario operator--(int dec);
		TCalendario &operator--();
		
		bool ModFecha(int d, int m, int a);
		bool ModMensaje(char *m);

		bool operator==(const TCalendario &tc) const;
		bool operator!=(const TCalendario &tc) const;
				
		bool operator>(const TCalendario &tc) const;
		bool operator<(const TCalendario &tc) const;

		bool EsVacio() const;
		int Dia() const;
		int Mes() const;
		int Anyo() const;
		char *Mensaje() const;
};
#endif