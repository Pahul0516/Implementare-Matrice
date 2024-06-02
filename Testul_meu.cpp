#include "Matrice.h"
#include <assert.h>

void testul_meu()
{
	Matrice m{ 4,4 };
	m.modifica(1, 1, 5);
	m.modifica(3, 3, 2);
	assert(m.difMaxMin() == 3);
	m.modifica(1, 1, -1);
	m.modifica(3, 3, -6);
	assert(m.difMaxMin() == 5);
	m.modifica(3, 3, 0);
	m.modifica(1, 1, 10000);
	m.modifica(1, 2, 0);
	assert(m.difMaxMin() == 10000);

}