#include "baza.h"

using namespace std;

baza::baza()
{
	/*
		Przypisuje zmiennej 'dlugosc' dlugosc tablicy okreslona na poczatku pliku .baza.h'.
		Nastepnie czysci tablice dane[] oraz zajeteKomorki[].
	*/
	dlugosc = DLUGOSC_TABLICY;
	for (int i = 0; i < DLUGOSC_TABLICY; i++)
	{
		dane[i] = NULL;
		zajeteKomorki[i] = false;
	}
}

baza::~baza()
{
	/*
		Zapewnia wyczyszczenie pamieci, zapobiega wyciekowi pamieci.
	*/
	czyszczenie();
}

void baza::czyszczenie()
{
	/*
		Usuwa obiekty wskazywane przez tablice dane[] i aktualizuje zajetosc komorek w tablicy zajeteKomorki[].
	*/
	for (int i = 0; i < DLUGOSC_TABLICY; i++)
	{
		if (zajeteKomorki[i] == true)
		{
			delete dane[i];
			zajeteKomorki[i] = false;
		}
	}
}

void baza::rysujTabele()
{
	/*
		Tworzy cztery zmienne sumujace czasy wykonywania operacji NWD dla kazdej metody.
		Nastepnie rysuje naglowek metoda 'rysujNaglowek()' i wyswietla poszczegolne obiekty klasy 'linijka'.
		Przy kazdym wyswietlaniu pobiera czasy operacji NWD i dodaje je do zmiennych sumujacych.
		Na koncu wyswietla podsumowanie, korzystajac z metody 'rysujPodsumowanie()'.
	*/

	// Zmienne sumujace czasy wykonywania operacji NWD dla kazdej metody.
	int st1, st2, st3, st4;
	st1 = st2 = st3 = st4 = 0;

	system("cls");
	linijka::rysujNaglowek();

	for (int i = 0; i < dlugosc; i++)
	{
		// Sprawdza czy komorka o numerze 'i' zawiera obiekt.
		if (zajeteKomorki[i] == true)
		{
			dane[i]->rysujLinieZDanymi();
			dane[i]->podajCzas(1) < 0 ? st1 += 0 : st1 += dane[i]->podajCzas(1);
			dane[i]->podajCzas(2) < 0 ? st2 += 0 : st2 += dane[i]->podajCzas(2);
			dane[i]->podajCzas(3) < 0 ? st3 += 0 : st3 += dane[i]->podajCzas(3);
			dane[i]->podajCzas(4) < 0 ? st4 += 0 : st4 += dane[i]->podajCzas(4);
		}
	}

	linijka::rysujLinieTabeli();
	linijka::rysujPodsumowanie(st1, st2, st3, st4);

	cout << "\n\nNacisnij dowolny przycisk aby wyjsc...";
	_getch();
}

void baza::dodajWpis()
{
	system("cls");
	cout << "Dodawanie nowego wpisu do tablicy:\n";

	int numerKomorki = 0;

	// Sprawdza zajetosc komorek w tablicy dane[].
	while (zajeteKomorki[numerKomorki] == true && numerKomorki < DLUGOSC_TABLICY)
	{
		numerKomorki++;
	}

	// Jezeli wszystkie pola w tablicy dane[] sa zajete - anuluj operacje.
	if (numerKomorki >= DLUGOSC_TABLICY)
	{
		cout << "\033[31mBrak miejsca na nowy wpis!\nUsun istniejacy wpis aby zrobic miejsce\033[0m\n\nNacisnij dowolny przycisk aby kontynuowac...";
		_getch();
	}
	else
	{
		cout << "Dodawanie wpisu o ID = " << numerKomorki << endl;

		zajeteKomorki[numerKomorki] = true;

		int liczba1, liczba2;
		liczba1 = liczba2 = -1;

		cout << "Podaj pierwsza liczbe: ";
		cin >> liczba1;

		// Sprawdza poprawnosc wprowadzonej liczby.
		while (liczba1 < 0 || cin.fail())
		{
			if (liczba1 < 0)
				cout << "\033[31mPodana liczba musi byc nieujemna!" << endl;
			else
				cout << "\033[31mNiepoprawne dane!" << endl;
			cout << "\033[0mPodaj liczbe jeszcze raz: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> liczba1;
		}

		cout << "Podaj druga liczbe: ";
		cin >> liczba2;

		// Sprawdza poprawnosc wprowadzonej liczby.
		while (liczba2 < 0 || cin.fail())
		{
			if (liczba2 < 0)
				cout << "\033[31mPodana liczba musi byc nieujemna!" << endl;
			else
				cout << "\033[31mNiepoprawne dane!" << endl;
			cout << "\033[0mPodaj liczbe jeszcze raz: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> liczba2;
		}

		try
		{
			// Zabezpieczenie przed wpisaniem do obiektu 'linijka' niepoprawnych wartosci.
			if (liczba1 < 0 || liczba2 < 0)
				throw blad(1);

			// Tworzy nowy obiekt typu 'linijka'.
			dane[numerKomorki] = new linijka(liczba1, liczba2, numerKomorki);
		}
		catch (blad* blad)
		{
			blad->wyswietl();
		}

		cout << "\nWpis dodany pomyslnie!\nWcisnij t aby policzyc NWD dla powyzszych liczb lub dowolny przycisk aby kontynuowac...";
		char wybor = _getch();
		if (wybor == 't' || wybor == 'T')
		{
			cout << "\nLiczenie...";
			dane[numerKomorki]->policzWszystko();
			cout << "\nNWD dla tych liczb to: \033[32m" << dane[numerKomorki]->podajWynik() << "\033[0m" << endl;
		}

		cout << "\nWcisnij t aby dodac kolejny wpis lub dowolny przycisk aby wyjsc... ";
		wybor = _getch();
		if (wybor == 't' || wybor == 'T')
		{
			dodajWpis();
		}
	}
}

void baza::usunWpis()
{
	/*
		Pyta o numer ID wpisu, ktory ma zostac usuniety.
		Nastepnie sprawdza czy taki wpis istnieje.
		Jezeli istnieje - usuwa go.
	*/

	cout << "Podaj ID wpisu do usuniecia: ";
	int iddousuniecia;
	cin >> iddousuniecia;

	if (iddousuniecia >= 0 && iddousuniecia < DLUGOSC_TABLICY && zajeteKomorki[iddousuniecia] == true && !cin.fail())
	{
		delete dane[iddousuniecia];
		zajeteKomorki[iddousuniecia] = false;
		cout << "\033[36mWpis usuniety pomyslnie\033[0m\n";
	}
	else
	{
		cout << "\033[31mNiepoprawne ID\n\033[0m";
		cin.clear();
		cin.ignore(100, '\n');
	}


	cout << "Nacisnij dowolny przycisk aby kontunuowac...";
	_getch();
}

void baza::liczWszystko()
{
	/*
		Wywoluje metode 'policzWszystko()' dla wszystkich istniejacych obiektow typu 'linijka' w bazie.
	*/

	cout << "Liczenie...";
	for (int i = 0; i < DLUGOSC_TABLICY; i++)
	{
		if (zajeteKomorki[i] == true)
		{
			dane[i]->policzWszystko();
		}
	}
}

void baza::wypelnijRandomowo()
{
	/*
		Wypelnia wszystkie wolne komorki w tablicy 'dane[]' nowymi obiektami.
		Obiekty te posiadaja pseudolosowe wartosci 'l1' oraz 'l2'.
		Nastepnie wywoluje metode 'rysujTabele()'.
	*/

	srand(int(time(NULL)));
	for (int i = 0; i < DLUGOSC_TABLICY; i++)
	{
		if (zajeteKomorki[i] == false)
		{
			zajeteKomorki[i] = true;
			dane[i] = new linijka(rand() % 10000, rand() % 10000, i);
		}
	}
	rysujTabele();
}

void baza::otworzPlik()
{
	/*
		Otwiera plik binarny 'plik.dat', znajdujacy sie w folderze, w ktorym wykonywany jest program.
		Zwraca blad 2 w przypadku braku mozliwosci otwarcia pliku.

		Jezeli otwarcie pliku sie uda, czysci baze danych i rysuje na ekranie krotki naglowek.
		Nastepnie pobiera po cztery 4-bajtowe zmienne typu int dla kazdego wpisu.
		Jezeli dane sa prawidlowe, zostaje utworzony nowy obiekt typu 'linijka' w tablicy 'dane[]'.
		Kazda odczytana linia jest wyswietlana na ekranie.
	*/
	system("cls");

	try
	{
		ifstream plik;
		plik.open("plik.dat", ios::binary | ios::in);

		if (plik.good())
		{
			czyszczenie();

			cout << "Dane pobrane z pliku:\n\n";
			linijka::rysujNaglowekKrotki();

			try
			{
				while (plik.peek() != EOF)
				{
					int id, a, b, wynik;
					plik.read((char*)&id, 4);
					plik.read((char*)&a, 4);
					plik.read((char*)&b, 4);
					plik.read((char*)&wynik, 4);

					// Zabezpieczenie przed proba odczytu pliku z wieksza iloscia obiektow typu 'linijka' niz zdefiniowane w obecnym programie.
					if (id >= DLUGOSC_TABLICY || id < 0)
						throw blad(5);
					if (a < 0 || b < 0 || wynik < 0)
						throw blad(6);

					zajeteKomorki[id] = true;
					dane[id] = new linijka(a, b, id, wynik);

					dane[id]->rysujLinieZDanymiKrotka();
				}
			}
			catch (blad blad)
			{
				blad.wyswietl();
			}

			plik.close();

			cout << "\nNacisnij dowolny przycisk aby kontynuowac...";
		}
		else
		{
			throw blad(2);
		}
	}
	catch (blad blad)
	{
		blad.wyswietl();
	}
	_getch();
}

void baza::zapiszPlik()
{
	/*
		Zapisuje wszystkie istniejace obiekty z tablicy 'dane[]' do pliku binarnego.
		Kazdy obiekt zajmuje 16 bajtow.

		Format zapisanych danych:
		+-----------+-----+------+------+-------+
		|   Bajty   | 0-3 |  4-7 | 8-11 | 12-15 |
		+-----------+-----+------+------+-------+
		| Zawartosc |  id |  l1  |  l2  | wynik |
		+-----------+-----+------+------+-------+
	*/

	system("cls");

	try
	{
		ofstream plik;
		plik.open("plik.dat", ios::binary | ios::out);

		if (!plik.good())
			throw blad(3);

		for (int i = 0; i < DLUGOSC_TABLICY; i++)
		{
			if (zajeteKomorki[i] == true)
			{
				int a = dane[i]->podajID();
				plik.write((char*)&a, sizeof(a));
				a = dane[i]->podajLiczbe(1);
				plik.write((char*)&a, sizeof(a));
				a = dane[i]->podajLiczbe(2);
				plik.write((char*)&a, sizeof(a));
				a = dane[i]->podajWynik();
				plik.write((char*)&a, sizeof(a));
			}
		}

		plik.close();

		cout << "\033[36mZapisano do pliku \"plik.dat\"\n\033[0mNacisnij dowolny przycisk aby kontynuowac...";
		_getch();
	}
	catch (blad blad)
	{
		blad.wyswietl();
	}
}
