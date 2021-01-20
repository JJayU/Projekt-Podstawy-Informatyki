#pragma once

#define SZEROKOSC_POLA 13			//szerokosc kolumny tabeli
#define WYSOKAPRECYZJA 1			//tryb wysokiej precyzji ( 1 - aktywny )
#define MAXILOSCREKURENCJI 1000		//maksymalna ilosc rekurencji, zabezpiecza program przed przepelnieniem stosu

//Klasa reprezentujaca pare liczb oraz wynik operacji NWD dla tych liczb
class linijka
{
private:
	int id;													//numer linii
	int l1, l2;												//liczba 1 i liczba 2
	int wynik;												//wynik operacji NWD
	int t1, t2, t3, t4;										//czasy obliczen metodami 1,2,3,4

	int metoda1(int, int);									//niezoptymalizowany algorytm euklidesa iteracyjny
	int metoda2(int, int, int);								//niezoptymalizowany algorytm euklidesa rekurencyjny
	int metoda3(int, int);									//zoptymalizowany algorytm euklidesa iteracyjny
	int metoda4(int, int);									//zoptymalizowany algorytm euklidesa rekurencyjny

public:
	linijka(int, int, int);									//konstruktor, przyjmuje dwie liczby typu int oraz ID
	linijka(int, int, int, int);							//konstruktor, przyjmuje dwie liczby typu int, ID oraz wynik, u?ywany tylko do odczytu z pliku!
	~linijka();												//destruktor
	void policzWszystko();									//liczy NWD dla l1 i l2 wszystkimi dostepnymi metodami
	int policz(int);										//zwraca NWD dla l1 i l2 wybrana metoda (1-4)
	int podajWynik();										//zwraca wynik NWD dla l1 i l2
	int zmierzCzas(int);									//mierzy i zwraca czas operacji NWD wybrana metoda (1-4)
	int podajCzas(int);										//zwraca czas operacji NWD wybrana metoda (1-4)
	int podajLiczbe(int);									//zwraca l1 lub l2
	int podajID();											//zwraca ID

	void rysujLinieZDanymi();								//rysuje na ekranie linie zawierajaca wszystkie dane
	void rysujLinieZDanymiKrotka();							//rysuje na ekranie linie zawierajaca tylko dwie liczby i wynik
	static void rysujLinieTabeli();							//rysuje na ekranie linie oddzielajaca
	static void rysujNaglowek();							//rysuje na ekranie naglowek tabeli
	static void rysujNaglowekKrotki();						//rysuje na ekranie krotki naglowek tabeli
	static void rysujPodsumowanie(int, int, int, int);		//rysuje podsumowanie tabeli zawierajace cztery czasy podane jako argumenty
};

// zabezpieczenie programu przed proba rysowania kolumn zbyt krotkich by pomiescic wszystkie dane
#if SZEROKOSC_POLA < 12
#error "Szerokosc pola nie moze byc mniejsza niz 12!"
#endif // SZEROKOSC_POLA < 12
