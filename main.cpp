// ProjektV1.cpp : Ten plik zawiera funkcje ,,main". W nim rozpoczyna sie i konczy wykonywanie programu.
// Created by Jakub Junkiert, 2020/2021

#include "baza.h"
#include "menu.h"

using namespace std;

int main()
{
	baza* baza1 = new baza;

	menu(baza1);

	baza1->czyszczenie();
}
