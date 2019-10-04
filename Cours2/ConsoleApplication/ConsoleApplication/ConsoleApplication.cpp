// ConsoleApplication.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <cstring>
#include <cstdio>

static void TestRec();

int StrChr(char * grange, char chat)
{
	/*
	for((init);(condition);(increment))

	init()
	while(condition())
	{
		increment();
	}
	*/

	int length = strlen(grange);
	for (int i = 0; i < length; ++i)
	{
		if (grange[i] == chat)
		{
			return i;
		}
	}
	return -1;



	/* Ma version

	strlen(grange);
	int position = -1;
	int i = 0;

	while (* grange != 0)
	{
		if (* grange == chat)
		{
			return position;
		}
		grange++;
		i++;

	}
	return -1;
	*/	
}

int StrChr2(char * grange, char chat)
{
	char * oldGrange = grange;
	while (*grange)
	{
		if (*grange == chat)
		{
			return (int)(grange - oldGrange);
		}
		grange++;
	}
	return -1;	
}

int StrChr3(char * grange, char chat)
{
	int counter = 0;

	while (grange[counter] != 0)
	{
		if (grange[counter] == chat)
		{
			return counter;
		}
		counter++;
	}

	return -1;
}

char * StrStr(char * meuleDeFoin, char * aiguille)
{
	int lengthMeule = strlen(meuleDeFoin);
	int lengthAiguille = strlen(aiguille);

	for (int i = 0; i < lengthMeule; ++i)
	{
		bool found = true;

		for (int j = 0; j < lengthAiguille; ++j)
		{
			if (meuleDeFoin[j] != aiguille[j])
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return meuleDeFoin;
		}
		meuleDeFoin++;
	}
	return nullptr;
}
/*
char * StrStr2(char * meuleDeFoin, char * aiguille)
{
	int lengthMeule = strlen(meuleDeFoin);
	int lengthAiguille = strlen(aiguille);

	for (int i = 0; i < lengthMeule; ++i)
	{
		char contenuTemporaire[256];
		strncpy(contenuTemporaire, meuleDeFoin + i, strlen(aiguille));

		if (Strcmp(contenuTemporaire, aiguille) == 0)
		{
			return (meuleDeFoin + i);
		}
	}
	return nullptr;
}
*/
int Max(int a, int b)
{
	return (a < b) ? b : a;
}
int Min(int a, int b)
{
	return (a > b) ? a : b;
}

int Strcmp(char * meule, char * aiguille)
{
	//Return -1 si meule est inférieur lexicographiquement
	//Return 1 si meule est supérieur lexicographiquement
	//Return 0 si meule est égale à l'aiguille lexicographiquement

	int lenMeule = strlen(meule);
	int lenAiguille = strlen(aiguille);

	int maxLen = Max(lenMeule, lenAiguille);
	int minLen = Min(lenMeule, lenAiguille);

	for (int i = 0; i < minLen; i++)
	{
		if (meule[i] < aiguille[i])
		{
			return -1;
		}
		else if(meule[i] > aiguille[i])
		{
			return 1;
		}
		// if equal continue;
	}
	// Une des deux chaines est plus courte que l'autre
	if (minLen == maxLen) return 0;
	if (maxLen == lenMeule) return 1;

	return 1;
}

void Memcpy(char * dest, char * src, int size)
{
	while (size >= 0)
	{
		// copier src[size] dans dest[size]
		dest[size] = src[size];
		size--;
	}
}

void Memcpy2(char * dest, char * src, int size)
{
	for (int i = 0; size < 0; i++)
	{
		dest[i] = src[i];
	}
}

int main()
{
    //std::cout << "Hello World!\n"; 

	char licorne[32] = "licorne";
	char vomi[32] = "vomit";

	Memcpy(licorne, vomi, strlen(licorne)+1);
	printf("licorne %s\n", licorne);

	Memcpy2(licorne, vomi, strlen(licorne)+1);
	printf("licorne %s\n", licorne);

	char chateau[32] = "chateau";
	char soldat = 'e';
	int posSoldat = StrChr2(chateau, soldat);
	printf("le soldat est en position %d\n", posSoldat);

	/*
	char text1[] = "dragon";
	char text2[] = "drag";
	int ziText = Strcmp(text1, text2);
	printf("alors %d\n", ziText);
	*/

	char text[1024] = "Lorem ipsum dolor sit amet";
	char token[1024] = "dolor";
	char * tokenInText = StrStr(text, token);
	int pos = (int)(tokenInText - text);
	printf("le token est en position %d\n", pos); 
	// environ 11
	int a = 0;

	TestRec();
}

int add_0(int a, int b)
{
	int i = 0;
	for (i = 0; i < a + b; ++i)
	return i;
}

int add_1(int a, int b)
{
	int val = a;
	for (int i = 0; i < b; ++i)
		val++;
	return val;
}

int add_2(int a, int b)
{
	if (a == 0)
		return b;
	else
		return add_2(a - 1, b + 1);
}

int add_3(int a, int b)
{
	if (a == 0)
		return b;
	else if (b == 0)
		return a;
	else
		int inter = 1 + add_3(a - 1, b);
		return 1 + add_3(a - 1, b);
}

int sub(int a, int b)
{
	printf("a = %d b = %d\n", a, b);
	// Cas terminal
	if (b == 0) return a;
	if (a == 0) return b;
	// Cas général b inf
	if (b < 0) return sub(a + 1, b + 1);
	// Cas général b inf
	if (b> 0) return sub(a - 1, b - 1);
}

int sub2(int a, int b)
{
	if (b == 0) return a;
	else if (b > 0)
		return sub2(a, b - 1) - 1;
	else
		return sub2(a, b + 1) + 1;
}

int mul(int a, int b)
{
	printf("a = %d b = %d\n", a, b);
	if (b == 0) return 0;
	if (a == 0) return 0;
	if (b > 0) return a + mul(a, b - 1);
	// b < 0
	return a - mul(a, -b + 1);
}

static void TestRec()
{
	//int foo = add_2(2, 2);
	//int foo2 = add_3(3, 2);
	//int foo3 = sub(3, 2);
	int foo4 = mul(4, -2);
	int i = 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
