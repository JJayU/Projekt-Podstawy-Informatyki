#include "linijka.h"

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <string>

#include "blad.h"

using namespace std;

linijka::linijka(int a, int b, int tid)
{
	id = tid;
	l1 = a;
	l2 = b;
	wynik = t1 = t2 = t3 = t4 = -1;
}

linijka::linijka(int a, int b, int tid, int twynik)
{
	id = tid;
	l1 = a;
	l2 = b;
	wynik = twynik;
	t1 = t2 = t3 = t4 = -1;
}

linijka::~linijka()
{
	//zniszono obiekt klasy linijka
}


//----METODY OBLICZEN NWD----


//niezoptymalizowany algorytm euklidesa iteracyjny
int linijka::metoda1(int templ1, int templ2)
{
	try
	{
		if (templ1 < 0 || templ2 < 0)
			throw blad(1);

		if (templ1 == 0 || templ2 == 0)
				return 0;

		while (templ1 != templ2)
		{
			if (templ1 > templ2)
			{
				templ1 = templ1 - templ2;
			}
			else
			{
				templ2 = templ2 - templ1;
			}
		}

		return templ1;
	}
	catch (blad blad)
	{
		blad.wyswietl();
	}
}

//niezoptymalizowany algorytm euklidesa rekurencyjny
int linijka::metoda2(int templ1, int templ2, int licznik)
{
	try
	{
		if (templ1 < 0 || templ2 < 0)
			throw blad(1);
		if (licznik > MAXILOSCREKURENCJI)
			return -1;
		if (templ1 == 0 || templ2 == 0)
			return 0;
		if (templ1 != templ2)
		{
			if (templ1 > templ2)
			{
				return metoda2(templ1 - templ2, templ2, licznik + 1);
			}
			else
			{
				return metoda2(templ1, templ2 - templ1, licznik + 1);
			}
		}
		return templ1;
	}
	catch (blad blad)
	{
		blad.wyswietl();
	}
}

//zoptymalizowany algorytm euklidesa iteracyjny
int linijka::metoda3(int templ1, int templ2)
{
	try
	{
		if (templ1 < 0 || templ2 < 0)
			throw blad(1);

		int templiczba;

		while (templ2 != 0)
		{
			templiczba = templ2;
			templ2 = templ1 % templ2;
			templ1 = templiczba;
		}

		return templ1;
	}
	catch (blad blad)
	{
		blad.wyswietl();
	}
}

//zoptymalizowany algorytm euklidesa rekurencyjny
int linijka::metoda4(int templ1, int templ2)
{
	try
	{
		if (templ1 < 0 || templ2 < 0)
			throw blad(1);

		if (templ2 != 0)
			return metoda4(templ2, templ1 % templ2);

		return templ1;
	}
	catch (blad blad)
	{
		blad.wyswietl();
	}
}



//----POZOSTALE METODY KLASY----

void linijka::policzWszystko()
{
	/*
	* metoda sprawdza czy obiekt posiada juz wpisany wynik, jezeli nie to liczy go pierwsza metoda a
	* nastepnie sprawdza czy policzone sa poszczegolne czasy operacji, jezeli nie - dokonuje obliczen
	*/
	if (wynik == -1)
		wynik = metoda1(l1, l2);
	if (t1 == -1)
		t1 = zmierzCzas(1);
	if (t2 == -1)
		t2 = zmierzCzas(2);
	if (t3 == -1)
		t3 = zmierzCzas(3);
	if (t4 == -1)
		t4 = zmierzCzas(4);
}

int linijka::podajWynik()
{
	/*
	* Metoda zwraca wynik jezeli istnieje, jezeli nie - wywoluje metode policz(3) (najwydajnieszy algorytm NWD) i zwraca wynik.
	*/

	if(wynik == -1)
		policz(3);

	return wynik;
}

int linijka::zmierzCzas(int metoda)
{
	/*
	* Metoda mierzy czas wykonania operacji NWD, wybrana metoda (1-4).
	*
	* Do pomiaru czasu wykorzystywana jest biblioteka chrono.
	* W przypadku gdy WYSOKAPRECYZJA ustawiona jest jako 1, kazda operacja wykonywana jest 1000 razy,
	* aby czas mogl byc zmierzony z wieksza dokladnoscia.
	*/

	try
	{
		switch (metoda)
		{
		case 1:
		{
			auto start = chrono::steady_clock::now();
			if (WYSOKAPRECYZJA == 1)
			{
				for (int i = 0; i < 1000; i++)
					metoda1(l1, l2);
			}
			else
				metoda1(l1, l2);
			chrono::duration<double> czaswykonania = chrono::steady_clock::now() - start;
			return(chrono::duration_cast<chrono::microseconds>(czaswykonania).count());
			break;
		}
		case 2:
		{
			auto start = chrono::steady_clock::now();
			if (WYSOKAPRECYZJA == 1)
			{
				for (int i = 0; i < 1000; i++)
					metoda2(l1, l2, 0);
			}
			else
				metoda2(l1, l2, 0);
			chrono::duration<double> czaswykonania = chrono::steady_clock::now() - start;
			if (metoda2(l1, l2, 0) == -1)
				return -1;
			return(chrono::duration_cast<chrono::microseconds>(czaswykonania).count());
			break;
		}
		case 3:
		{
			auto start = chrono::steady_clock::now();
			if (WYSOKAPRECYZJA == 1)
			{
				for (int i = 0; i < 1000; i++)
					metoda3(l1, l2);
			}
			else
				metoda3(l1, l2);
			chrono::duration<double> czaswykonania = chrono::steady_clock::now() - start;
			return(chrono::duration_cast<chrono::microseconds>(czaswykonania).count());
			break;
		}
		case 4:
		{
			auto start = chrono::steady_clock::now();
			if (WYSOKAPRECYZJA == 1)
			{
				for (int i = 0; i < 1000; i++)
					metoda4(l1, l2);
			}
			else
				metoda4(l1, l2);
			chrono::duration<double> czaswykonania = chrono::steady_clock::now() - start;
			return(chrono::duration_cast<chrono::microseconds>(czaswykonania).count());
			break;
		}
		default:
			throw blad(9);
			break;
		}
	}
	catch (blad blad)
	{
		blad.wyswietl();
	}
}

int linijka::podajCzas(int metoda)
{
	/*
	* Metoda zwraca czas wykonania operacji NWD wybrana metoda (1-4).
	*/

	try
	{
		switch (metoda)
		{
		case 1:
			return t1;
			break;
		case 2:
			return t2;
			break;
		case 3:
			return t3;
			break;
		case 4:
			return t4;
			break;
		default:
			throw blad(7);
			break;
		}
	}
	catch (blad blad)
	{
		blad.wyswietl();
	}
}

int linijka::policz(int metoda)
{
	/*
	* Metoda zwraca wynik operacji NWD wybrana metoda (1-4).
	*
	* W przypadku braku wyniku lub czasu, zostaje on policzony.
	*/

	try
	{
		switch (metoda)
		{
		case 1:
			if (wynik == -1)
				wynik = metoda1(l1, l2);
			if (t1 == -1)
				t1 = zmierzCzas(1);
			return metoda1(l1, l2);
			break;
		case 2:
			if (wynik == -1)
				wynik = metoda2(l1, l2, 0);
			if (t2 == -1)
				t2 = zmierzCzas(2);
			return metoda2(l1, l2, 0);
			break;
		case 3:
			if (wynik == -1)
				wynik = metoda3(l1, l2);
			if (t3 == -1)
				t3 = zmierzCzas(3);
			return metoda3(l1, l2);
			break;
		case 4:
			if (wynik == -1)
				wynik = metoda4(l1, l2);
			if (t4 == -1)
				t4 = zmierzCzas(4);
			return metoda4(l1, l2);
			break;
		default:
			throw blad(8);
			break;
		}
	}
	catch (blad blad)
	{
		blad.wyswietl();
	}
}

int linijka::podajLiczbe(int liczba)
{
	/*
	* Metoda zwraca l1 lub l2.
	*/

	try
	{
		if (liczba == 1)
			return l1;
		else if (liczba == 2)
			return l2;
		else
			throw blad(10);
	}
	catch (blad blad)
	{
		blad.wyswietl();
	}
}

int linijka::podajID()
{
	/*
	* Metoda zwraca numer ID obiektu.
	*/

	return id;
}

void linijka::rysujLinieTabeli()
{
	/*
	* Metoda rysuje na ekranie linie oddzielajaca.
	*/

	cout << "#----";
	for (int i = 0; i < 7; i++)
	{
		cout << "#";
		for (int a = 0; a < SZEROKOSC_POLA; a++)
		{
			cout << "-";
		}
	}
	cout << "#" << endl;
}

void linijka::rysujLinieZDanymi()
{
	/*
	* Metoda rysuje na ekranie linie z danymi zawierajaca:
	*	- ID
	*	- l1
	*	- l2
	*	- wynik NWD
	*	- czasy wykonywania operacji NWD wszystkimi metodami
	*
	* Szerokosc kolumn definiowana jest poprzez SZEROKOSC_POLA.
	*/

	cout << "# " << setw(2) << id << " ";
	cout << "# " << setw(SZEROKOSC_POLA - 2) << l1 << " ";
	cout << "# " << setw(SZEROKOSC_POLA - 2) << l2 << " ";

	cout << "# " << setw(SZEROKOSC_POLA - 2) << ( wynik < 0 ? "-": to_string(wynik) ) << " ";

	for (int i = 1; i < 5; i++)
	{
		if (podajCzas(i) < 0)
			cout << "# " << setw(SZEROKOSC_POLA - 1) << "- ";
		else
			cout << "# " << setw(SZEROKOSC_POLA - 5) << podajCzas(i) << (WYSOKAPRECYZJA ? " ns " : " us ");
	}
	cout << "#" << endl;
}

void linijka::rysujPodsumowanie(int w1, int w2, int w3, int w4)
{
	/*
	* Metoda rysuje na ekranie podsumowanie czasow wykonywania operacji NWD wszystkimi metodami.
	* Czasy podawane sa jako argumenty typu int.
	*/

	cout << "     ";
	for (int i = 0; i < 3; i++)
	{
		for (int a = 0; a < SZEROKOSC_POLA + 1; a++)
		{
			cout << " ";
		}
	}

	w1 < 0 ? cout << "# " << setw(SZEROKOSC_POLA - 1) << "BRAK " : cout << "# " << setw(SZEROKOSC_POLA - 5) << (WYSOKAPRECYZJA && w1 > 1000 ? w1 / 1000.0 : w1) << (WYSOKAPRECYZJA && w1 < 1000 ? " ns " : " us ");
	w2 < 0 ? cout << "# " << setw(SZEROKOSC_POLA - 1) << "BRAK " : cout << "# " << setw(SZEROKOSC_POLA - 5) << (WYSOKAPRECYZJA && w2 > 1000 ? w2 / 1000.0 : w2) << (WYSOKAPRECYZJA && w2 < 1000 ? " ns " : " us ");
	w3 < 0 ? cout << "# " << setw(SZEROKOSC_POLA - 1) << "BRAK " : cout << "# " << setw(SZEROKOSC_POLA - 5) << (WYSOKAPRECYZJA && w3 > 1000 ? w3 / 1000.0 : w3) << (WYSOKAPRECYZJA && w3 < 1000 ? " ns " : " us ");
	w4 < 0 ? cout << "# " << setw(SZEROKOSC_POLA - 1) << "BRAK " : cout << "# " << setw(SZEROKOSC_POLA - 5) << (WYSOKAPRECYZJA && w4 > 1000 ? w4 / 1000.0 : w4) << (WYSOKAPRECYZJA && w4 < 1000 ? " ns " : " us ");

	cout << "#\n     ";

	for (int i = 0; i < 3; i++)
	{
		for (int a = 0; a < SZEROKOSC_POLA + 1; a++)
		{
			cout << " ";
		}
	}
	for (int i = 0; i < 4; i++)
	{
		cout << "#";
		for (int a = 0; a < SZEROKOSC_POLA; a++)
		{
			cout << "-";
		}
	}
	cout << "#" << endl;
}

void linijka::rysujNaglowek()
{
	/*
	* Metoda rysuje na ekranie naglowek tabeli zawieracacej wszystkie dane.
	*/

	rysujLinieTabeli();
	cout << "# ID # L1";
	for (int a = 0; a < SZEROKOSC_POLA - 3; a++)
	{
		cout << " ";
	}
	cout << "# L2";
	for (int a = 0; a < SZEROKOSC_POLA - 3; a++)
	{
		cout << " ";
	}
	cout << "# NWD";
	for (int a = 0; a < SZEROKOSC_POLA - 4; a++)
	{
		cout << " ";
	}
	cout << "# CZAS 1";
	for (int a = 0; a < SZEROKOSC_POLA - 7; a++)
	{
		cout << " ";
	}
	cout << "# CZAS 2";
	for (int a = 0; a < SZEROKOSC_POLA - 7; a++)
	{
		cout << " ";
	}
	cout << "# CZAS 3";
	for (int a = 0; a < SZEROKOSC_POLA - 7; a++)
	{
		cout << " ";
	}
	cout << "# CZAS 4";
	for (int a = 0; a < SZEROKOSC_POLA - 7; a++)
	{
		cout << " ";
	}
	cout << "#\n";
	rysujLinieTabeli();
}

void linijka::rysujNaglowekKrotki()
{
	/*
	* Metoda rysuje na ekranie skrocony naglowek tabeli.
	*/

	cout << "# ID # L1";
	for (int a = 0; a < SZEROKOSC_POLA - 3; a++)
	{
		cout << " ";
	}
	cout << "# L2";
	for (int a = 0; a < SZEROKOSC_POLA - 3; a++)
	{
		cout << " ";
	}
	cout << "# NWD";
	for (int a = 0; a < SZEROKOSC_POLA - 4; a++)
	{
		cout << " ";
	}
	cout << "#\n";
}

void linijka::rysujLinieZDanymiKrotka()
{
	/*
	* Metoda rysuje na ekranie skrocona linie z danymi zawierajaca:
	*	- ID
	*	- l1
	*	- l2
	*	- wynik
	*/

	cout << "# " << setw(2) << id << " ";
	cout << "# " << setw(SZEROKOSC_POLA - 2) << l1 << " ";
	cout << "# " << setw(SZEROKOSC_POLA - 2) << l2 << " ";
	cout << "# " << setw(SZEROKOSC_POLA - 2) << (wynik < 0 ? "-" : to_string(wynik)) << " #\n";
}
