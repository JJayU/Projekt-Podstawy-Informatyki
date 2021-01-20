#include "blad.h"
#include <string>
#include <iostream>
#include <conio.h>

using namespace std;

blad::blad(int kod)
{
	numer = kod;
}

blad::~blad()
{
	//zniszczono obiekt klasy blad
}

void blad::wyswietl()
{
	/*
		Wyswietla na ekranie kod i opis bledu.
	*/

	string opis;

	switch (numer)
	{
	case 1: opis = "Niepoprawna wartosc l1 lub l2!"; break;
	case 2: opis = "Nie mozna odczytac pliku"; break;
	case 3: opis = "Nie mozna utworzyc pliku"; break;
	case 4: opis = "Podany obiekt nie istnieje"; break;
	case 5: opis = "Niepoprawne ID obiektu w odczytanym pliku"; break;
	case 6: opis = "Niepoprawne dane w odczytanym pliku"; break;
	case 7: opis = "Niepoprawny argument w metodzie \"linijka::podajCzas()\""; break;
	case 8: opis = "Niepoprawny argument w metodzie \"linijka:policz()\""; break;
	case 9: opis = "Niepoprawny argument w metodzie \"linijka:zmierzCzas()\""; break;
	case 10: opis = "Niepoprawny argument w metodzie \"linijka:podajLiczbe()\""; break;
	default: opis = "Niepoprawny numer bledu!"; break;
	}

	cout << "\033[31m------------" << endl;
	cout << " Blad " << numer << ":\n " << opis << endl; 
	cout << "------------\033[0m" << endl;

	_getch();
}