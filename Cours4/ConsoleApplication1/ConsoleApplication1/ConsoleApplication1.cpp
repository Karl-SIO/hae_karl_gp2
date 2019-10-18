// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "IntArray.hpp"
#include "Util.hpp"
#include "List.hpp"
#include "Tree.hpp"

void assert(bool b)
{
	if (!b) throw std::exception();
}

void testIntList()
{
	/*
	IntList maListe(8);
	//IntList * maListe = new IntList(0);

	int toto = 0;

	maListe.Append(66);
	assert(maListe.Length() == 2);

	maListe.Concat(33);
	assert(maListe.Length() == 2);
	assert(maListe->elem == 33);

	maListe.Remove(12);
	assert(maListe.Length() == 3);
	assert(maListe.Remove(33));

	bool MRP = maListe.Contains(60);
	assert(MRP == false);
	bool MRP2 = maListe.Contains(65);
	assert(MRP2 == true);

	int _k = 0;
	*/
}

void testFloatTree() 
{
	FloatTree * tree = new FloatTree();
	Node<float> * leaf = new FloatNode(8);
	leaf->insertLeft(4);
	assert(leaf->left->elem == 4);

	leaf->insertRight(9);
	assert(leaf->right->elem == 9);

	leaf->insert(16);
	leaf->insert(3);
	leaf->insert(5);
	assert(leaf->getLength() == 6);

	//leaf->remove(16);

	assert(leaf->Contains(16) == true);
	leaf->remove(16);
	assert(leaf->Contains(16) == false);
	assert(leaf->Contains(4) == true);
	leaf->remove(4);
	assert(leaf->Contains(4) == false);
	assert(leaf->Contains(0) == true);
	leaf->remove(0);
	assert(leaf->Contains(0) == false);

	tree->dfsPrint();

	int k = 0;
}

int main()
{
    std::cout << "Hello World!\n"; 

	int sizes[4] = { 4, 8, 16, 32 };
	const int len = 4;
	double prev = 0.00000000001;
	/*
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

	{
		
		double t0 = TimeUtils::getTimestamp();
		IntArray test;
		test[0] = 1; test[1] = 2; test[2] = 3; test[3] = 4; test[4] = 5;
		test.binarySearch(4);
		double t1 = TimeUtils::getTimestamp();
		printf("key position : %d\n", test.binarySearch(4));
		printf("temps de calcul : %f s for %d\n", (t1 - t0), test.getLength());

		IntArray test(10);
		int pos = 0;

		test[pos++] = 5;
		test[pos++] = 10;
		test[pos++] = 15;
		test[pos++] = 50;

		assert(test.binarySearch(4) == 0);
		assert(test.binarySearch(5) == 0);
		assert(test.binarySearch(6) == 1);
		assert(test.binarySearch(50) == 3);
		assert(test.binarySearch(60) == 4);
	}

	{
		IntArray test(10);
		int pos = 0;

		test[pos++] = 1;
		test[pos++] = 3;
		test[pos++] = 5;
		
		for (int i = 0; i < 10; ++i)
		{
			printf("i:%d b:%d lin:%d \n", i, test.binarySearch(i), test.searchPosition(i));
		}
	}
*/


	// List
	{
	
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
