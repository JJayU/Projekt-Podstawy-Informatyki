#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>

#include "linijka.h"
#include "blad.h"

#define DLUGOSC_TABLICY 100					// Okresla dlugosc tablicy wskaznikow na obiekty typu linijka.

//  Klasa przechowujaca tablice obiektow typu linijka.
// Wielkosc tabeli definiowana jest przez stala DLUGOSC_TABLICY, znajdujaca sie w pliku baza.h
class baza
{
private:
	linijka* dane[DLUGOSC_TABLICY];			// Tablica wskaznikow na obiekty typu linijka.
	bool zajeteKomorki[DLUGOSC_TABLICY];	// Tablica pomocnicza, wskazuje zajetosc pol w tablicy dane[].
	int dlugosc;							// Zmienna okreslajaca dlugosc tablicy wskaznikow na obiekty typu linijka.

public:
	//Konstruktor domyslny klasy 'baza'. Nie przyjmuje argumentow.
	baza();

	//Destruktor klasy 'baza'.
	~baza();

	//Metoda czyszczaca glowna tablice, tablice zajetych komorek oraz niszczaca wszystkie obiekty.
	void czyszczenie();

	//Metoda wypelniajaca wolne komorki tablicy randomowymi liczbami.
	void wypelnijRandomowo();

	//Metoda wyzwalajaca liczenie i pomiar czasu dla wszystkich wpisow w tabeli.
	void liczWszystko();

	//Metoda usuwajaca wpis z tablicy.
	void usunWpis();

	//Metoda dodajaca nowy wpis do tablicy.
	void dodajWpis();

	//Metoda rysujaca tabele (argumenty: wskaznik na tablice glowna, tablica zajetosci komorek, liczba reprezentujaca dlugosc tablicy).
	void rysujTabele();

	//Metoda zapisujaca zawartosc glownej tablicy do pliku binarnego.
	void zapiszPlik();

	//Metoda otwierajaca plik binarny i zapisujaca jego zawartosc do glownej tablicy.
	void otworzPlik();
};

#if DLUGOSC_TABLICY < 1
	#error "Dlugosc tablicy nie moze byc mniejsza od 1!!!"
#endif // DLUGOSC_TABLICY < 0
