#include "pa2m.h"
#include "src/abb.h"
#include <string.h>
#include <stdio.h>

void prueba_abb_crear()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	pa2m_afirmar(abb != NULL, "Puedo crear un abb");
	pa2m_afirmar(abb_vacio(abb), "El abb creado está vacío");
	pa2m_afirmar(abb_tamanio(abb) == 0, "El abb creado tiene tamaño 0");
	abb_destruir(abb);
}

void prueba_abb_insertar_en_abb_nulo()
{
	char *valor = "valor";
	pa2m_afirmar(abb_insertar(NULL, valor) == NULL,
		     "No puedo insertar en un abb nulo");
}

void prueba_abb_insertar_en_abb_vacio()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char *valor = "valor";
	pa2m_afirmar(abb_insertar(abb, valor) == abb,
		     "Puedo insertar en un abb vacío");
	pa2m_afirmar(!abb_vacio(abb),
		     "El abb no está vacío luego de insertar el elemento");
	pa2m_afirmar(abb_tamanio(abb) == 1, "El abb tiene tamaño 1");
	abb_destruir(abb);
}

void prueba_abb_insertar_en_abb_con_elementos()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char *valor1 = "valor1";
	char *valor2 = "valor2";
	char *valor3 = "valor3";
	abb_insertar(abb, valor1);
	abb_insertar(abb, valor2);
	pa2m_afirmar(abb_insertar(abb, valor3) == abb,
		     "Puedo insertar en un abb con elementos");
	pa2m_afirmar(
		abb_tamanio(abb) == 3,
		"El abb tiene el tamaño correcto luego de insertar el elemento");
	pa2m_afirmar(abb_insertar(abb, valor1) == abb,
		     "Puedo insertar un elemento repetido en un abb");
	abb_destruir(abb);
}

void prueba_abb_eliminar_en_abb_nulo()
{
	char *valor = "valor";
	pa2m_afirmar(abb_quitar(NULL, valor) == NULL,
		     "No puedo eliminar en un abb nulo");
}

void prueba_abb_eliminar_en_abb_vacio()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char *valor = "valor";
	pa2m_afirmar(abb_quitar(abb, valor) == NULL,
		     "No puedo eliminar en un abb vacío");
	abb_destruir(abb);
}

void prueba_abb_eliminar_en_abb_con_elementos()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char *valor1 = "valor1";
	char *valor2 = "valor2";
	char *valor3 = "valor3";
	abb_insertar(abb, valor1);
	abb_insertar(abb, valor2);
	abb_insertar(abb, valor3);
	pa2m_afirmar(abb_quitar(abb, valor1) == valor1,
		     "Puedo eliminar un elemento del abb");
	pa2m_afirmar(
		abb_tamanio(abb) == 2,
		"El abb tiene el tamaño correcto luego de eliminar el elemento");
	pa2m_afirmar(abb_quitar(abb, valor1) == NULL,
		     "No puedo eliminar un elemento que no está en el abb");
	abb_destruir(abb);
}

void prueba_abb_buscar_en_abb_nulo()
{
	char *valor = "valor";
	pa2m_afirmar(abb_buscar(NULL, valor) == NULL,
		     "No puedo buscar un elemento en un abb nulo");
}

void prueba_abb_buscar_en_abb_vacio()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char *valor = "valor";
	pa2m_afirmar(abb_buscar(abb, valor) == NULL,
		     "No puedo buscar un elemento en un abb vacío");
	abb_destruir(abb);
}

void prueba_abb_buscar_en_abb_con_elementos()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char *valor1 = "valor1";
	char *valor2 = "valor2";
	abb_insertar(abb, valor1);
	abb_insertar(abb, valor2);
	pa2m_afirmar(abb_buscar(abb, valor1) == valor1,
		     "Puedo buscar un elemento del abb");
	pa2m_afirmar(abb_buscar(abb, valor2) == valor2,
		     "Puedo buscar otro elemento del abb");
	pa2m_afirmar(abb_buscar(abb, "valor4") == NULL,
		     "No puedo buscar un elemento que no está en el abb");
	abb_destruir(abb);
}

void prueba_abb_iterador_interno_en_abb_nulo()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	pa2m_afirmar(abb_con_cada_elemento(abb, INORDEN, 0, NULL) == 0,
		     "No puedo iterar un abb nulo");
	abb_destruir(abb);
}

void prueba_abb_iterador_interno_en_abb_vacio()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	pa2m_afirmar(abb_con_cada_elemento(abb, INORDEN, 0, NULL) == 0,
		     "Iterar un abb vacío devuelve 0 elementos iterados");
	abb_destruir(abb);
}

bool funcion_iteradora(void *dato, void *extra)
{
	return true;
}

void prueba_abb_iterador_interno_en_abb_con_elementos()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char *valor1 = "valor1";
	char *valor2 = "valor2";
	char *valor3 = "valor3";
	char *extra = "extra";
	abb_insertar(abb, valor1);
	abb_insertar(abb, valor2);
	abb_insertar(abb, valor3);
	pa2m_afirmar(
		abb_con_cada_elemento(abb, INORDEN, funcion_iteradora, extra) ==
			3,
		"Puedo iterar un abb con elementos de manera INORDEN y devuelve la cantidad de elementos iterados");
	pa2m_afirmar(
		abb_con_cada_elemento(abb, PREORDEN, funcion_iteradora,
				      extra) == 3,
		"Puedo iterar un abb con elementos de manera PREORDEN y devuelve la cantidad de elementos iterados");
	pa2m_afirmar(
		abb_con_cada_elemento(abb, POSTORDEN, funcion_iteradora,
				      extra) == 3,
		"Puedo iterar un abb con elementos de manera POSTORDEN y devuelve la cantidad de elementos iterados");
	abb_destruir(abb);
}

bool funcion_iteradora_false(void *dato, void *extra)
{
	if (strcmp(dato, "valor2") == 0)
		return false;
	return true;
}

void prueba_abb_iterador_interno_termina_antes()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char *valor1 = "valor1";
	char *valor2 = "valor2";
	char *valor3 = "valor3";
	char *extra = "extra";
	abb_insertar(abb, valor1);
	abb_insertar(abb, valor2);
	abb_insertar(abb, valor3);
	pa2m_afirmar(
		abb_con_cada_elemento(abb, INORDEN, funcion_iteradora_false,
				      extra) == 2,
		"Puedo iterar un abb con elementos de manera INORDEN y si la funcion devuelve false se termina de iterar, y devuelve la cantidad de elementos correcta");
	pa2m_afirmar(
		abb_con_cada_elemento(abb, PREORDEN, funcion_iteradora_false,
				      extra) == 2,
		"Puedo iterar un abb con elementos de manera PREORDEN y si la funcion devuelve false se termina de iterar, y devuelve la cantidad de elementos correcta");
	pa2m_afirmar(
		abb_con_cada_elemento(abb, POSTORDEN, funcion_iteradora_false,
				      extra) == 2,
		"Puedo iterar un abb con elementos de manera POSTORDEN y si la funcion devuelve false se termina de iterar, y devuelve la cantidad de elementos correcta");
	abb_destruir(abb);
}

void prueba_abb_recorrer_en_arbol_nulo()
{
	char **array = malloc(sizeof(char *) * 3);
	size_t tamanio = 3;
	pa2m_afirmar(abb_recorrer(NULL, INORDEN, (void **)array, tamanio) == 0,
		     "No puedo recorrer un abb nulo");
	free(array);
}

void prueba_abb_recorrer_en_arbol_vacio()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char **array = malloc(sizeof(char *) * 3);
	size_t tamanio = 3;
	pa2m_afirmar(abb_recorrer(abb, INORDEN, (void **)array, tamanio) == 0,
		     "Recorrer un abb vacío devuelve 0 elementos recorridos");
	free(array);
	abb_destruir(abb);
}

void prueba_recorrer_en_arbol_con_elementos()
{
	abb_t *abb = abb_crear((abb_comparador)strcmp);
	char *valor1 = "valor1";
	char *valor2 = "valor2";
	char *valor3 = "valor3";
	abb_insertar(abb, valor1);
	abb_insertar(abb, valor2);
	abb_insertar(abb, valor3);
	char **array = malloc(sizeof(char *) * 3);
	size_t tamanio = 3;
	pa2m_afirmar(
		abb_recorrer(abb, INORDEN, (void **)array, tamanio) == 3,
		"Puedo recorrer un abb con elementos de manera INORDEN y devuelve la cantidad de elementos recorridos");
	pa2m_afirmar(
		abb_recorrer(abb, PREORDEN, (void **)array, tamanio) == 3,
		"Puedo recorrer un abb con elementos de manera PREORDEN y devuelve la cantidad de elementos recorridos");
	pa2m_afirmar(
		abb_recorrer(abb, POSTORDEN, (void **)array, tamanio) == 3,
		"Puedo recorrer un abb con elementos de manera POSTORDEN y devuelve la cantidad de elementos recorridos");
	free(array);
	abb_destruir(abb);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== Creacion ========================");
	prueba_abb_crear();

	pa2m_nuevo_grupo(
		"\n======================== Insercion ========================");
	prueba_abb_insertar_en_abb_nulo();

	prueba_abb_insertar_en_abb_vacio();
	prueba_abb_insertar_en_abb_con_elementos();

	pa2m_nuevo_grupo(
		"\n======================== Eliminacion ========================");
	prueba_abb_eliminar_en_abb_nulo();

	prueba_abb_eliminar_en_abb_vacio();
	prueba_abb_eliminar_en_abb_con_elementos();

	pa2m_nuevo_grupo(
		"\n======================== Busqueda ========================");
	prueba_abb_buscar_en_abb_nulo();

	prueba_abb_buscar_en_abb_vacio();
	prueba_abb_buscar_en_abb_con_elementos();

	pa2m_nuevo_grupo(
		"\n======================== Iterador interno ========================");
	prueba_abb_iterador_interno_en_abb_nulo();

	prueba_abb_iterador_interno_en_abb_vacio();
	prueba_abb_iterador_interno_en_abb_con_elementos();
	prueba_abb_iterador_interno_termina_antes();

	pa2m_nuevo_grupo(
		"\n======================== Recorrer con array ========================");
	prueba_abb_recorrer_en_arbol_nulo();

	prueba_abb_recorrer_en_arbol_vacio();
	prueba_recorrer_en_arbol_con_elementos();

	return pa2m_mostrar_reporte();
}
