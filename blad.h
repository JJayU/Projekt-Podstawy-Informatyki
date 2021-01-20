#pragma once

// Klasa obslugujaca wyjatki.
class blad
{
public:
	int numer;

	// Konstruktor klasy 'blad', przyjmuje kod bledu jako argument.
	blad(int kod);

	// Destruktor
	~blad();

	// Metoda wyswietlajaca opis bledu na ekranie.
	void wyswietl();
};