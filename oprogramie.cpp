#include "oprogramie.h"

using namespace std;

void oprogramie()
{
	/*
		Wyswietla informacje o programie na ekranie.
	*/

    system("cls");

    cout <<
    "\033[36m"
    "**************************************************\n"
    "*  Kalkulator NWD (Najwiekszy Wspolny Dzielnik)  *\n"
    "*                   Wersja 1.1                   *\n"
    "**************************************************\n\n"
    "\033[0m"

    "Program umozliwia liczenie NWD dla par liczb. Kazda para dodawana jest do tabeli, ktora wyswietla je wszystkie.\n"
    "Operacja NWD liczona jest czterema roznymi metodami, dla porownania czasu ich wykonywania.\n"
    "Zastosowane algorytmy to:\n"
    "1 - Niezoptymalizowany algorytm Euklidesa iteracyjny\n"
    "2 - Niezoptymalizowany algorytm Euklidesa rekurencyjny\n"
    "3 - Zoptymalizowany algorytm Euklidesa iteracyjny\n"
    "4 - Zoptymalizowany algorytm Euklidesa rekurencyjny\n\n"
    "CZAS 1, CZAS 2... w tabeli oznaczaja czasy wykonywania powyzszych algorytmow.\n\n"

    "Tabele mozna zapisac do pliku lub dokonac jej odczytu z pliku.\n\n"

    "Copyright Jakub Junkiert 2020/2021";

    _getch();
}
