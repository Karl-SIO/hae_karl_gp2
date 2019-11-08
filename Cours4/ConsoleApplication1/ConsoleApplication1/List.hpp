#pragma once

template<typename Type>

class List
{
public:

	Type * elem;

	List<Type> * next = nullptr;

	List(const Type & elem)
	{
		this->elem = elem;
	};

	int Length()
	{
		if(nullptr == next) return 1;
		else return next->Length() + 1;
	}

	//Ajoute elem à la fin de liste
	void Append(const Type & elem)
	{
		if (next == nullptr)
		{
			next = new List(elem);
		}
		else
		{
			next->Append(elem);
		}
	}

	//Ajoute elem au début de liste
	List<Type> * Concat(const Type & elem)
	{
		// var maListe
		// maListe = [3 5 5]
		// maliste = maListe->Concat(4);
		// maListe 4 [3 5 5]
		// maListe [4 3 5 5]

		// créer un nouvel element de liste
		// accrocher soit meme au nouvel element
		// renvoyer le nouvel element

		auto newElem = new List(elem);
		newElem->next = this;
		return newElem;
	}
	List<Type> * Remove(const Type & removeElem)
	{
		// tester si je suis sur le bon element
		// si oui, me supprimer et raccrocher le reste
		// sinon passer la patate chaude
		auto ElemRemoved;
		if (this->elem == removeElem)
		{
			auto suiteDeListe = next;
			this->next = nullptr;
			delete this;
			if (suiteDeListe != nullptr)
			{
				return suiteDeListe->Remove(removeElem);
			}
		}
		else
		{
			if (next)
			{
				next = next->Remove(removeElem);
			}
			return this;
		}
	}
	bool Contains(const Type & elemATrouver)
	{
		if (elem == elemATrouver)
		{
			return true;
		}
		else if (next == nullptr)
		{
			return false;
		}
		else
		{
			return next.Contains(elemATrouver);
		}
	}
};

typedef List<int> IntList;