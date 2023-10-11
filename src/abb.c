#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

nodo_abb_t *crear_nodo(void *elemento)
{
	nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));

	if (!nodo)
		return NULL;

	nodo->elemento = elemento;

	return nodo;
}

void *buscar_nodo(nodo_abb_t *nodo, void *elemento, abb_t *arbol)
{
	if (!nodo || arbol->comparador(nodo->elemento, elemento) == 0)
		return nodo;

	if (arbol->comparador(nodo->elemento, elemento) < 0)
		return buscar_nodo(nodo->derecha, elemento, arbol);

	return buscar_nodo(nodo->izquierda, elemento, arbol);
}

nodo_abb_t *insertar_nodo(nodo_abb_t *nodo, void *elemento, abb_t *arbol)
{
	if (!nodo)
		return crear_nodo(elemento);

	if (arbol->comparador(nodo->elemento, elemento) <= 0)
		nodo->derecha = insertar_nodo(nodo->derecha, elemento, arbol);
	else
		nodo->izquierda = insertar_nodo(nodo->izquierda, elemento, arbol);

	return nodo;
}

nodo_abb_t *buscar_predecesor(nodo_abb_t *nodo)
{
    if (!nodo)
        return NULL;
    
    if (!nodo->derecha)
        return nodo;
    
    return buscar_predecesor(nodo->derecha);
}

void *quitar_nodo(nodo_abb_t *nodo, void *elemento, abb_t *arbol)
{
	if (!nodo)
		return NULL;

	if (arbol->comparador(nodo->elemento, elemento) == 0) {
		if (!nodo->izquierda && !nodo->derecha) {
			free(nodo);
			return NULL;
		}

		if (!nodo->izquierda || !nodo->derecha) {
			nodo_abb_t *nodo_aux = nodo->izquierda ? nodo->izquierda : nodo->derecha;
			free(nodo);
			return nodo_aux;
		}

		nodo_abb_t *maximo_izquierdo = buscar_predecesor(nodo->izquierda);
		nodo->elemento = maximo_izquierdo->elemento;
        nodo->izquierda = quitar_nodo(nodo->izquierda, maximo_izquierdo->elemento, arbol);
        return nodo;
	}

	if (arbol->comparador(nodo->elemento, elemento) < 0)
		nodo->derecha = quitar_nodo(nodo->derecha, elemento, arbol);
	
	nodo->izquierda = quitar_nodo(nodo->izquierda, elemento, arbol);

	return nodo;
}

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador)
		return NULL;

	abb_t *arbol = calloc(1, sizeof(abb_t));

	if (!arbol)
		return NULL;

	arbol->comparador = comparador;

	return arbol;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;

	arbol->nodo_raiz = insertar_nodo(arbol->nodo_raiz, elemento, arbol);
	arbol->tamanio++;

	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;

	nodo_abb_t *nodo_aux = buscar_nodo(arbol->nodo_raiz, elemento, arbol);

	if (!nodo_aux)
		return NULL;

	void *elemento_aux = nodo_aux->elemento;
	arbol->nodo_raiz = quitar_nodo(arbol->nodo_raiz, elemento, arbol);
	arbol->tamanio--;

	return elemento_aux;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;

	nodo_abb_t *nodo_aux = buscar_nodo(arbol->nodo_raiz, elemento, arbol);
	
	return nodo_aux ? nodo_aux->elemento : NULL;
}

bool abb_vacio(abb_t *arbol)
{
	if (!arbol)
		return true;

	return arbol->tamanio == 0;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol)
		return 0;

	return arbol->tamanio;
}

void destruir_nodo(nodo_abb_t *nodo)
{
	if (!nodo)
		return;

	destruir_nodo(nodo->izquierda);
	destruir_nodo(nodo->derecha);
	free(nodo);
}

void destruir_elemento(nodo_abb_t *nodo, void (*destructor)(void *))
{
	if (!nodo)
		return;

	destruir_elemento(nodo->izquierda, destructor);
	destruir_elemento(nodo->derecha, destructor);
	destructor(nodo->elemento);
}

void abb_destruir(abb_t *arbol)
{
	if (!arbol)
		return;

	destruir_nodo(arbol->nodo_raiz);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;

	destruir_elemento(arbol->nodo_raiz, destructor);

	abb_destruir(arbol);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
