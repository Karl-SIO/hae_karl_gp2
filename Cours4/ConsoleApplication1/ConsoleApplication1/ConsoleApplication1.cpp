// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "IntArray.hpp"
#include "Util.hpp"

void assert(bool b)
{
	if (!b) throw std::exception();
}

int main()
{
    std::cout << "Hello World!\n"; 

	{
		IntArray toto;
		toto.fillWithRandom(16);
		int i = 0;

		toto.insertSort();

		for (int i = 0; i < toto.getLength() - 1; i++);
		{
			assert(toto[i] < toto[i + 1]);
		}
	}

	{
		IntArray test;
		test[0] = 66;
		test[1] = 77;
		test.swap(0, 1);
		assert(test[0] == 77);
	}

	{
		double t0 = TimeUtils::getTimestamp();
		IntArray toto;
		toto.fillWithRandom(1024);
		toto.insertSort();
		for (int i = 0; i < toto.getLength() - 1; i++)
			assert(toto[i] <= toto[i + 1]);
		double t1 = TimeUtils::getTimestamp();
		printf("temps de calcul : %f s for %d\n", (t1 - t0), toto.getLength());
		int j = 0;
	}
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
