#include "menu.h"

using namespace std;

void menu(baza* baza)
{
	/*
		Wyswietla na ekranie menu i prosi uzytkownika o wybor.
		W zaleznosci od wyboru wywoluje odpowiednia metode z klasy 'baza' lub opuszcza petle.
	*/

	// Zmienna informujaca o stanie otwarcia menu.
	// Gdy 'false', menu zostaje zamkniete.
	bool menuOtwarte = true;

	while (menuOtwarte)
	{
		system("CLS");
		cout << "\033[32mMenu programu: \033[0m\n";
		cout << "\033[32m 1 \033[0m - wyswietl tabele\n";
		cout << "\033[32m 2 \033[0m - dodaj wpis\n";
		cout << "\033[32m 3 \033[0m - usun wpis\n";
		cout << "\033[32m 4 \033[0m - policz wszystko i wyswietl\n";
		cout << "\033[32m 5 \033[0m - otworz plik\n";
		cout << "\033[32m 6 \033[0m - zapisz do pliku\n";
		cout << "\033[32m 7 \033[0m - wypelnij randomowo\n";
		cout << "\033[32m 8 \033[0m - usun wszystko\n";
		cout << "\033[32m 9 \033[0m - o programie\n";
		cout << "\033[32m Inne \033[0m - zakoncz program\n";

		char wybor = _getch();

		switch (wybor)
		{
		case '1':
			baza->rysujTabele();
			break;
		case '2':
			baza->dodajWpis();
			break;
		case '3':
			baza->usunWpis();
			break;
		case '4':
			baza->liczWszystko();
			baza->rysujTabele();
			break;
		case '5':
			baza->otworzPlik();
			break;
		case '6':
			baza->zapiszPlik();
			break;
		case '7':
			baza->wypelnijRandomowo();
			break;
		case '8':
			baza->czyszczenie();
			system("cls");
			cout << "\033[36mOperacja wykonana\033[0m";
			_getch();
			break;
        case '9':
            oprogramie();
            break;
		default:
			menuOtwarte = false;
			break;
		}
	}
}
