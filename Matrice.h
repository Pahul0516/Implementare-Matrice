#pragma once

typedef int TElem;


#define NULL_TELEMENT 0


struct Triplet {
	int linie;
	int coloana;
	TElem valoare;
};

class Matrice {

private:
	/* aici e reprezentarea */
	Triplet* elemente; // vectorul de triplete (linie, coloană, valoare)
	int* stanga;       // vector pentru copiii stânga
	int* dreapta;      // vector pentru copiii dreapta
	int capacitate;    // capacitatea actuală a vectorilor
	int dimensiune;    // numărul actual de elemente
	int radacina;      // indexul rădăcinii arborelui
	int nrL, nrC;


	void redimensioneaza();
	int creeazaNod(int linie, int coloana, TElem valoare);
	int adaugaRec(int radacina, int linie, int coloana, TElem valoare);
	TElem cautaRec(int radacina, int linie, int coloana);
	int gasesteMinim(int radacina);
	int gasesteMaximul(int radacina);
	int stergeRec(int radacina, int linie, int coloana, TElem& valoareStearsa);	

 
public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice();

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j);


	// returnare numar linii
	int nrLinii();

	// returnare numar coloane
	int nrColoane();


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

	int difMaxMin();


};
