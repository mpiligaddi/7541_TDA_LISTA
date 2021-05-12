#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define VACIO 0

lista_t* lista_crear() {

	lista_t* lista_nueva = NULL;
	lista_nueva = malloc(sizeof(lista_t));
	if(!lista_nueva) {
		return NULL;
	}
	lista_nueva->nodo_inicio = NULL;
	lista_nueva->nodo_fin = NULL;
	lista_nueva->cantidad = 0;
	return lista_nueva;

}

/* Pre: Recibe un elemento de tipo void*
   Post: Devuelve el nodo que se creo o NULL en caso de error
*/

nodo_t* nodo_crear(void* elemento) {

	nodo_t* nodo = NULL;
	nodo = malloc(sizeof(nodo_t));
	if(!nodo) {
		return NULL;
	}
	nodo->elemento = elemento;
	nodo_t* nodo_siguiente = NULL;
	nodo->siguiente = nodo_siguiente;
	return nodo;

}

bool lista_vacia(lista_t* lista) {

	if((lista == NULL) || (lista->cantidad == VACIO)) {
		return true;
	}
	return false;

}

int lista_insertar(lista_t* lista, void* elemento) {

	if(lista == NULL) {
		return -1;
	}
	nodo_t* nodo = nodo_crear(elemento);
	if(!nodo) {
		return -1;
	}
	if(lista_vacia(lista) == true) {
		lista->nodo_inicio = nodo;
		lista->nodo_fin = nodo;
		(lista->cantidad)++;
		return 0;
	}
	lista->nodo_fin->siguiente = nodo; 
	lista->nodo_fin = nodo;
	(lista->cantidad)++; 
	return 0;

}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion) {
	
	if(lista == NULL) {
		return -1;
	}
	nodo_t* nodo = nodo_crear(elemento);
	if(!nodo) {
		return -1;
	}
	if(lista_vacia(lista) == true) {
		lista->nodo_inicio = nodo;
		lista->nodo_fin = nodo;
		(lista->cantidad)++;
		return 0;
	}
	if((posicion != 0) && ((lista->cantidad-1) < posicion)) { 
		lista->nodo_fin->siguiente = nodo; 
		lista->nodo_fin = nodo;
		(lista->cantidad)++; 
		return 0;
	}
	if(posicion == 0) {
		nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo;
		lista->cantidad++;
		return 0;
	}
	size_t i = 0;
	nodo_t* aux_1 = lista->nodo_inicio;
	nodo_t* aux_2 = aux_1->siguiente;
	while(i != posicion-1) {
		aux_1 = aux_2;
		aux_2 = aux_1->siguiente;
		i++;
	}
	nodo->siguiente = aux_2;
	aux_1->siguiente = nodo;
	(lista->cantidad)++;
	return 0;

}

int lista_borrar(lista_t* lista) {

	if((lista_vacia(lista) == true)) {
		return -1;
	}
	if(lista->cantidad == 1) { 
		lista->nodo_inicio = NULL;
		free(lista->nodo_fin);
		lista->nodo_fin = NULL;
		(lista->cantidad)--;
		return 0;
	}
	nodo_t* nodo_anterior = lista->nodo_inicio;
	nodo_t* nodo_a_eliminar =  nodo_anterior->siguiente;
	while(nodo_a_eliminar->siguiente != NULL) { 
		nodo_anterior = nodo_a_eliminar; 
		nodo_a_eliminar = nodo_a_eliminar->siguiente; 
	}
	lista->nodo_fin = nodo_anterior;
	nodo_anterior->siguiente = NULL;
	(lista->cantidad)--;
	free(nodo_a_eliminar);
	return 0;

}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion) {

	if(lista_vacia(lista) == true) {
		return -1;
	}
	if(lista->nodo_inicio->siguiente == NULL) {
		lista->nodo_inicio = NULL;
		free(lista->nodo_fin);
		lista->nodo_fin = NULL;
		(lista->cantidad)--;
		return 0;
	}
	if(posicion == 0) {
		nodo_t* nodo_a_eliminar = lista->nodo_inicio;
		lista->nodo_inicio = nodo_a_eliminar->siguiente;
		free(nodo_a_eliminar);
		(lista->cantidad)--;
		return 0;
	}
	if(lista->cantidad <= (posicion+1)) {
		if(lista_borrar(lista) == 0) {
			return 0;
		}
		return -1;
	}
	nodo_t* nodo_anterior = lista->nodo_inicio;
	nodo_t* nodo_a_eliminar =  nodo_anterior->siguiente;
	size_t contador = 0; 
	while(contador != (posicion-1)) {
		nodo_anterior = nodo_a_eliminar; 
		nodo_a_eliminar = nodo_a_eliminar->siguiente; 
		(contador)++;
	}
	nodo_anterior->siguiente = nodo_a_eliminar->siguiente;
	(lista->cantidad)--;
	free(nodo_a_eliminar);
	return 0;

}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion) {

	if((lista_vacia(lista) == true) || (lista->cantidad < posicion)) {
		return NULL;
	}
	if(posicion == 0) {
		return (lista->nodo_inicio->elemento);
	}
	nodo_t* nodo_anterior = lista->nodo_inicio;
	nodo_t* nodo_a_devolver =  nodo_anterior->siguiente;
	int contador = 0;
	void* elemento_requerido = NULL;
	while(contador != (posicion-1)) { 
		nodo_anterior = nodo_a_devolver; 
		nodo_a_devolver = nodo_a_devolver->siguiente; 
		(contador)++;
	}
	elemento_requerido = nodo_a_devolver->elemento;
	return elemento_requerido;

}

void* lista_ultimo(lista_t* lista) {

	if(lista_vacia(lista) == true) {
		return NULL;
	}
	return (lista->nodo_fin->elemento);

}

size_t lista_elementos(lista_t* lista) {

	if(lista_vacia(lista) == true) {
		return 0;
	}
	return (lista->cantidad);

}

int lista_apilar(lista_t* lista, void* elemento) {

	return lista_insertar(lista, elemento);

}

int lista_desapilar(lista_t* lista) {

	return lista_borrar(lista);

}

void* lista_tope(lista_t* lista) {

	return lista_ultimo(lista);

}

int lista_encolar(lista_t* lista, void* elemento) {

	return lista_apilar(lista,elemento);

}

int lista_desencolar(lista_t* lista) {

	return lista_borrar_de_posicion(lista, 0);

}

void* lista_primero(lista_t* lista) {

	return lista_elemento_en_posicion(lista, 0);

}

/* Pre: Recibe un elemento de tipo nodo_t*
   Post: Libera la memoria reservada para los nodos creados 
*/

void nodo_destruir(nodo_t* nodo) {

	if(!nodo) {
		return;
	}
	nodo_t* nodo_siguiente = nodo->siguiente;
	free(nodo);
	nodo_destruir(nodo_siguiente);

}

void lista_destruir(lista_t* lista) {

	if(!lista) {
		return;
	}
	nodo_destruir(lista->nodo_inicio);
	free(lista);

}

lista_iterador_t* lista_iterador_crear(lista_t* lista) {

	lista_iterador_t* iterador = NULL;
	iterador = malloc(sizeof(lista_iterador_t));

	if(!iterador) {
		return NULL;
	}
	if(lista == NULL) {
		free(iterador);
		return NULL;
	}
	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;
	return iterador;

}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador) {

	if((iterador != NULL) && (iterador->corriente != NULL)) {
		return true;
	}
	return false;

}

bool lista_iterador_avanzar(lista_iterador_t* iterador) {

	if(iterador && iterador->corriente) {
		iterador->corriente = iterador->corriente->siguiente;
	}

	return (iterador && iterador->corriente);

}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador) {

	if((!iterador) || (!iterador->corriente)) {
		return NULL;
	}
	return (iterador->corriente->elemento);

}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto) {

	if((!lista) || (funcion == NULL)) {
		return 0;
	}
	size_t elementos_iterados = 0;
	nodo_t* nodo_inicial = lista->nodo_inicio;
	while((nodo_inicial) && (funcion(nodo_inicial->elemento,contexto))) { 
		nodo_inicial = nodo_inicial->siguiente;
		(elementos_iterados)++;
	}
	return elementos_iterados;

}

void lista_iterador_destruir(lista_iterador_t* iterador) {
	
	if(iterador) {
		free(iterador);
	}

}
