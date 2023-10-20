#include "pa2m.h"
#include "src/abb.h"
#include <string.h>
#include <stdio.h>

void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i != j, "i=14 es diferente de j=16");
}

bool imprimir(void *clave, void *aux)
{
	char *clave2 = clave;
	if (clave2[0] == 'a')
		return false;
	printf("%s\n", (char *)clave);
	return true;
}

void abb_test()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char *clave1 = "a";
	char *clave2 = "b";
	char *clave3 = "c";
	abb_insertar(abb, clave2);
	abb_insertar(abb, clave1);
	abb_insertar(abb, clave3);
	size_t cantidad = abb_con_cada_elemento(abb, INORDEN, imprimir, NULL);
	printf("cantidad: %zu\n", cantidad);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	prueba_simple();
	// abb_test();

	return pa2m_mostrar_reporte();
}
