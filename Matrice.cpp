#include "Matrice.h"

#include <exception>

using namespace std;


//complexitate Teta(1)
Matrice::Matrice(int nrLinii, int nrColoane) {
	/* de adaugat */
	if (nrLinii <= 0 || nrColoane <= 0) {
		throw std::exception("Numar de linii sau coloane invalid");
	}
	this->nrL = nrLinii;
	this->nrC = nrColoane;
	capacitate = 2;
	dimensiune = 0;
	radacina = -1;
	elemente = new Triplet[capacitate];
	stanga = new int[capacitate];
	dreapta = new int[capacitate];
}

//complexitate Teta(1)
int Matrice::nrLinii()
{
	/* de adaugat */
	return nrL;
}

//complexitate Teta(1)
int Matrice::nrColoane()
{
	/* de adaugat */
	return nrC;
}

//complexitate O(log2(n))
TElem Matrice::element(int i, int j)
{
	/* de adaugat */
	if (i < 0 || i >= nrL || j < 0 || j >= nrC) {
		throw std::exception("Pozitie invalida in matrice");
	}
	return cautaRec(radacina, i, j);
}


//complexitate O(log2(n))
TElem Matrice::modifica(int i, int j, TElem e) 
{
	/* de adaugat */
	if (i < 0 || i >= nrL || j < 0 || j >= nrC) {
		throw std::exception("Pozitie invalida in matrice");
	}

	TElem vecheaValoare = element(i, j);

	TElem val = cautaRec(radacina, i, j);
	stergeRec(radacina, i, j, val);


	radacina = adaugaRec(radacina, i, j, e);
	return vecheaValoare;
}

Matrice::~Matrice() {
    delete[] elemente;
    delete[] stanga;
    delete[] dreapta;
}

//complexitate(Teta(n))
void Matrice::redimensioneaza() 
{
	int newCapacitate = capacitate * 2;
	Triplet* newElemente = new Triplet[newCapacitate];
	int* newStanga = new int[newCapacitate];
	int* newDreapta = new int[newCapacitate];

	for (int i = 0; i < dimensiune; i++) {
		newElemente[i] = elemente[i];
		newStanga[i] = stanga[i];
		newDreapta[i] = dreapta[i];
	}

	delete[] elemente;
	delete[] stanga;
	delete[] dreapta;

	elemente = newElemente;
	stanga = newStanga;
	dreapta = newDreapta;
	capacitate = newCapacitate;
}

//complexitate (Teta(1))
int Matrice::creeazaNod(int linie, int coloana, TElem valoare) 
{
	if (dimensiune == capacitate) {
		redimensioneaza();
	}
	elemente[dimensiune] = { linie, coloana, valoare };
	stanga[dimensiune] = -1;
	dreapta[dimensiune] = -1;
	return dimensiune++;
}

//complexitate(O(log2(n)))
int Matrice::adaugaRec(int radacina, int linie, int coloana, TElem valoare) 
{
	if (radacina == -1) {
		return creeazaNod(linie, coloana, valoare);
	}
	if (elemente[radacina].linie == linie && elemente[radacina].coloana == coloana) {
		elemente[radacina].valoare = valoare;
	}
	else if (linie < elemente[radacina].linie || (elemente[radacina].linie == linie && coloana < elemente[radacina].coloana)) {
		stanga[radacina] = adaugaRec(stanga[radacina], linie, coloana, valoare);
	}
	else {
		dreapta[radacina] = adaugaRec(dreapta[radacina], linie, coloana, valoare);
	}
	return radacina;
}

//complexitate(O(log2(n)))
TElem Matrice::cautaRec(int radacina, int linie, int coloana) 
{
	if (radacina == -1) {
		return NULL_TELEMENT;
	}
	if (elemente[radacina].linie == linie && elemente[radacina].coloana == coloana) {
		return elemente[radacina].valoare;
	}
	if (linie < elemente[radacina].linie || (elemente[radacina].linie == linie && coloana < elemente[radacina].coloana)) {
		return cautaRec(stanga[radacina], linie, coloana);
	}
	else {
		return cautaRec(dreapta[radacina], linie, coloana);
	}
}

//complexitate(O(n))
int Matrice::gasesteMinim(int radacina) 
{
	int current = radacina;
	while (stanga[current] != -1) {
		current = stanga[current];
	}
	return current;
}

//complexitate(O(n))
int Matrice::gasesteMaximul(int radacina) 
{
	int current = radacina;
	while (dreapta[current] != -1) {
		current = dreapta[current];
	}
	return current;
}


//complexitate (O(n))
int Matrice::difMaxMin()
{
	int m1, m2;
	m1 = elemente[gasesteMinim(this->radacina)].valoare;
	m2 = elemente[gasesteMaximul(this->radacina)].valoare;
	return m1 - m2;
}

//complexitate(log2(n))
int Matrice::stergeRec(int radacina, int linie, int coloana, TElem& valoareStearsa) 
{
	if (radacina == -1) {
		return radacina;
	}
	if (linie < elemente[radacina].linie || (elemente[radacina].linie == linie && coloana < elemente[radacina].coloana)) {
		stanga[radacina] = stergeRec(stanga[radacina], linie, coloana, valoareStearsa);
	}
	else if (linie > elemente[radacina].linie || (elemente[radacina].linie == linie && coloana > elemente[radacina].coloana)) {
		dreapta[radacina] = stergeRec(dreapta[radacina], linie, coloana, valoareStearsa);
	}
	else {
		valoareStearsa = elemente[radacina].valoare;
		if (stanga[radacina] == -1) {
			return dreapta[radacina];
		}
		else if (dreapta[radacina] == -1) {
			return stanga[radacina];
		}
		int minimDreapta = gasesteMinim(dreapta[radacina]);
		elemente[radacina] = elemente[minimDreapta];
		dreapta[radacina] = stergeRec(dreapta[radacina], elemente[minimDreapta].linie, elemente[minimDreapta].coloana, valoareStearsa);
	}
	return radacina;
}