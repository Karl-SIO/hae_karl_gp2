// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
//#include <iostream>
#include <cstdlib> //#include <stdlib.h>
#include <cstdio> //#include <stdio.h>
#include <chrono> 
#include <functional>

/*
int appel(int & s) {
	s++;
	return s;
};
*/

struct Vec3 {
	int x;
	int y;
	int z;
};

Vec3 incrX(Vec3 _in) {
	_in.x++;
	return _in;
}

Vec3 stackOverflow(Vec3 _in) {
	Vec3 temp = _in;
	temp.y++;
	return stackOverflow(temp);
}

void Strcpy(char * dst, const char * src)
{
	int i = 0;

	while (true)
	{
		dst[i] = src[i];
		if (src[i] == 0)
			break;
		i++;
	}
	// while (*dst++ = *src++);   Méthode complexe ultra condensé
};

int main()
{
	//Debug.Log(monobjet);
	//std::cout << "Hello World!\n"; 

	//int foo = 0;

	//const char * label = "sapin";

	const char label2[6] = { 's', 'a', 'p', 'i', 'n', 0 };

	const char * ptr = &label2[0];
	ptr++;
	printf("%c\n", *ptr);

	/*
	float v = 0.5f;
	double ff = 0.5;

	printf("Hello world this is a test : %d label : %s %f\n", foo, label, 66.66f);
	printf("Hello world : l2 : %s\n", label2);

	const char labelBug[5] = { 's', 'a', 'p', 'i', 'n' };
	printf("Hello world : lb : %s\n", labelBug);
	*/

	int x = 66;
	//x = appel(x);
	printf("xval: %d\n", x);
	//68 ?
	Vec3 toto = { 1, 2, 3 }; // New Vec3()
	incrX(toto);
	printf("xval: %f\n", toto.x);

	/*
	Vec3 bob = { 1, 2, 3 };
	bob = stackOverflow(bob);
	printf("val x : %f\n", bob.x);
	*/

	Vec3 vecTab[3];
	vecTab[0] = { 1, 2, 3 };
	vecTab[1] = { 4, 5, 6 };
	vecTab[2] = { 7, 8, 9 };
	printf("v0x %f\n", vecTab[0].x);
	vecTab[0].x++;
	printf("v0x %f\n", vecTab[0]);

	Vec3 * t0 = 0;
	Vec3 * t1 = nullptr;
	Vec3 * t2 = &vecTab[1];

	//*(t2.y) = 555;
	(*t2).y = 777;
	t2->y = 888;

	Vec3 * iter = &vecTab[0];
	int i = 0;
	for (i = 0; i < 3; ++i) {
		printf("val avec x : %d\n", iter->x);
		iter++;
		//iter = iter + 1;
		//iter = ( &vecTab[0] + 1 );
	}

	Vec3 * t3 = t2 + 1;
	t2++;

	/* Accès à la mémoire (F9 pour balise rouge debug)

	auto start = std::chrono::system_clock::now();
	int * bigBlock = (int*) malloc(1024 * 1024 * 1024);
	for (int k = 0; k < 64 * 1024 * 1024; ++k) {
		bigBlock[k] = 0xdeadbeef;
	}
	printf("beef ? : %x\n", bigBlock[1024 * 1024]);
	auto end = std::chrono::system_clock::now();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	printf("time ? : %d\n", millis);

	int _i = 0;
	*/

	/*
	Vec3 tableau[16];

	Vec3 *tableau0 = (Vec3*)malloc(sizeof(Vec3) * 16); // en C pur
	memset(tableau, 0, sizeof(Vec3) * 16);

	Vec3 *tableau1 = (Vec3*)calloc(sizeof(Vec3), 16); // en C pur

	Vec3 *tableau2 = new Vec3[16]; // en C++
	Vec3 * unSeulVec = new Vec3(); // en C++ allocation dynamique
	Vec3 unSeulVecAussiMaisSurLeTas = Vec3(); // en C++ allocation statique

	int _i = 0;
	*/

	// A function that returns the length of a char string
	std::function<int(const char*)> Strlen = [](const char * src) 
	{
		int counter = 0;
		const char * osrc = src;
		//for (int i = 0; i < 1024; i++) 
		while (true)
		{
			char current = *src;
			if (current == 0)
				break;
			src++;
			counter++;
		}
		return counter;
	};

	const char * source = "mon lapin est dodu";
	char * dest = (char*)calloc(1024, sizeof(char));
	Strcpy(dest, source);

	//printf("dest val:%s len:%d\n", Strlen(source),dest);
	printf("dest val: len:%d\n", Strlen(source));
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
