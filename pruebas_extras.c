#include "lista.h"
#include "pa2mm.h"

#define ERROR -1
#define ULTIMO_ELEMENTO 4
#define AMARILLO "\x1B[33;1m"

void probar_creacion_lista() {

	lista_t* una_lista = lista_crear();
	pa2m_afirmar(una_lista != NULL, "Puedo crear una lista");
	pa2m_afirmar(una_lista->nodo_inicio == NULL, "Nodo inicio inicializado a NULL");
	pa2m_afirmar(una_lista->nodo_fin == NULL, "Nodo fin inicializado a NULL");
	pa2m_afirmar(una_lista->cantidad == 0, "Cantidad inicializada en 0");
	lista_destruir(una_lista);

}

/* Pre: recibe una lista que contiene n elementos, un vector de elementos y una posicion de un determinado elemento de la lista
   Post: Devuelve true si el elemento se inserto correctamente o false si no
*/

bool inserto_correctamente(lista_t* lista, int elementos[], size_t posicion) { 

	bool elementos_iguales = true;
	size_t contador = 0;

	int* lista_elemento = NULL;

	while((elementos_iguales == true) && (contador != posicion)) { 
		lista_elemento = (int*) lista_elemento_en_posicion(lista, contador);
		if(lista_elemento != (elementos+contador)) {
			elementos_iguales = false;
		}
		contador++;
	}
	return elementos_iguales;

}

/* Pre: recibe una lista que contiene n elementos, un elemento y una posicion de un determinado elemento de la lista
   Post: Devuelve true si el elemento se inserto correctamente o false si no
*/

bool inserto_correctamente_desordenado(lista_t* lista, int elementos, size_t posicion) {

	bool elementos_iguales = true;
	int* lista_elemento = NULL;
	lista_elemento = (int*) lista_elemento_en_posicion(lista, posicion);
	if(*lista_elemento != elementos) {
		elementos_iguales = false;
	}
	return elementos_iguales;

}

void probar_lista_insertar() {

	lista_t* lista = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_insertar(NULL,&elementos[0]) == ERROR, "Error al pasar NULL como lista");
	pa2m_afirmar((lista->nodo_inicio == NULL) && (lista->nodo_fin == NULL), "No se agrego ningun nodo en la lista");
	pa2m_afirmar(lista->cantidad == 0, "La cantidad de elementos en la lista sigue siendo 0");

	int elementos_insertados = 0;
	if(lista_insertar(lista, &elementos[0]) == 0) {
		elementos_insertados++;
	}
	pa2m_afirmar(elementos_insertados == 1, "Se pudo insertar el primer elemento a la lista");
	pa2m_afirmar(lista->cantidad == 1, "Se actualizo la cantidad de elementos en la lista");
	pa2m_afirmar((lista->nodo_inicio == lista->nodo_fin) && (lista->nodo_inicio != NULL), "El primer elemento insertado es el primero y el ultimo");
	for(int i = 1 ; i < 4 ; i++) {
		if(lista_insertar(lista, &elementos[i]) == 0) {
			elementos_insertados++;
		}
	}
	pa2m_afirmar(elementos_insertados == 4, "Se pudo insertar mas de un elemento a la lista");
	pa2m_afirmar(lista->cantidad == 4, "Se actualizo la cantidad total de elementos en la lista");
	pa2m_afirmar(inserto_correctamente(lista, elementos,4) == true, "Insercion correcta de todos los elementos de la lista");
	lista_destruir(lista);

}

void probar_lista_insertar_en_posicion() {

	lista_t* lista = lista_crear();
	int elementos[5] = {0, 1, 2, 3, 4};
	pa2m_afirmar(lista_insertar_en_posicion(NULL,&elementos[0],0) == ERROR, "Error al pasar NULL como lista");
	pa2m_afirmar((lista->nodo_inicio == NULL) && (lista->nodo_fin == NULL), "No se agrego ningun nodo en la lista");
	pa2m_afirmar(lista->cantidad == 0, "La cantidad de elementos en la lista sigue siendo 0");

	int elementos_insertados = 0;
	if(lista_insertar_en_posicion(lista, &elementos[0],1000) == 0) { 
		elementos_insertados++;
	}
	pa2m_afirmar((elementos_insertados == 1) && (inserto_correctamente_desordenado(lista,elementos[0],0) == true), "Se pudo insertar un elemento con posicion no valida en una lista vacia");
	pa2m_afirmar(elementos_insertados == 1, "Se pudo insertar el primer elemento a la lista");
	pa2m_afirmar(lista->cantidad == 1, "Se actualizo la cantidad de elementos en la lista");
	pa2m_afirmar((lista->nodo_inicio == lista->nodo_fin) && (lista->nodo_inicio != NULL), "El primer elemento insertado es el primero y el ultimo nodo");
	if(lista_insertar_en_posicion(lista, &elementos[1],0) == 0) {  
		elementos_insertados++;
	}
	pa2m_afirmar((elementos_insertados == 2) && (inserto_correctamente_desordenado(lista,elementos[1],0) == true), "Se pudo insertar un elemento en la posicion inicial de la lista");
	pa2m_afirmar(lista->cantidad == 2, "Se actualizo la cantidad de elementos en la lista");
	if(lista_insertar_en_posicion(lista, &elementos[2],1000) == 0) { 
		elementos_insertados++;
	}
	pa2m_afirmar((elementos_insertados == 3) && (inserto_correctamente_desordenado(lista,elementos[2],2) == true), "Se pudo insertar un elemento en la posicion final de una lista CON elementos en caso de no existir la posicion indicada");
	pa2m_afirmar(lista->cantidad == 3, "Se actualizo la cantidad de elementos en la lista");
	if(lista_insertar_en_posicion(lista, &elementos[3],1) == 0) { 
		elementos_insertados++;
	}
	pa2m_afirmar(elementos_insertados == 4, "Se pudo insertar un elemento en la posicion 1 de la lista");
	pa2m_afirmar(lista->cantidad == 4, "Se actualizo la cantidad de elementos en la lista");
	pa2m_afirmar(inserto_correctamente_desordenado(lista,elementos[3],1) == true, "Todos los elementos de la lista fueron correctamente insertados");
	lista_destruir(lista);

}

void probar_lista_borrar() {

	lista_t* lista = lista_crear();
	lista_t* lista_nueva = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_borrar(NULL) == ERROR, "Error al pasar NULL como lista");
	pa2m_afirmar(lista_borrar(lista) == ERROR, "Error al querer borrar un elemento de una lista vacia");
	for(int i = 0 ; i < 1 ; i++) {
		lista_insertar(lista_nueva, &elementos[i]);
	}
	pa2m_afirmar((lista_borrar(lista_nueva) == 0) && (lista_nueva->cantidad == 0) && (lista_nueva->nodo_inicio == NULL) && (lista_nueva->nodo_fin == NULL), "Se pudo borrar todos los elementos de una lista");
	lista_destruir(lista_nueva);

	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(lista, &elementos[i]);
	}
	pa2m_afirmar((lista_borrar(lista) == 0) && (lista->cantidad == 3) && (lista->nodo_inicio->siguiente->siguiente->elemento == &elementos[2]) && (lista->nodo_inicio->siguiente->siguiente->siguiente == NULL), "Se pudo borrar el ultimo elemento de una lista a la que le quedan elementos aun");

	lista_destruir(lista);

}

void probar_lista_borrar_de_posicion() {

	lista_t* lista = lista_crear();
	lista_t* lista_nueva = lista_crear();
	int elementos[4] = {1, 2, 3, 4};

	pa2m_afirmar(lista_borrar_de_posicion(NULL,0) == ERROR, "Error al pasar NULL como lista");
	pa2m_afirmar(lista_borrar_de_posicion(lista,0) == ERROR, "Error al querer borrar un elemento de una lista vacia");
	for(int i = 0 ; i < 1 ; i++) {
		lista_insertar(lista_nueva, &elementos[i]);
	}
	pa2m_afirmar((lista_borrar_de_posicion(lista_nueva,0) == 0) && (lista_nueva->cantidad == 0) && (lista_nueva->nodo_inicio == NULL) && (lista_nueva->nodo_fin == NULL), "Se pudo borrar todos los elementos de una lista");
	lista_destruir(lista_nueva);

	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(lista, &elementos[i]);
	}
	pa2m_afirmar((lista_borrar_de_posicion(lista,1000) == 0) && (lista->cantidad == 3) && (lista->nodo_inicio->siguiente->siguiente->elemento == &elementos[2]) && (lista->nodo_inicio->siguiente->siguiente->siguiente == NULL) , "Se pudo borrar el ultimo elemento de una lista en caso de recibir una posicion no valida");
	pa2m_afirmar((lista_borrar_de_posicion(lista,2) == 0) && (lista->cantidad == 2)  && (lista->nodo_inicio->siguiente->elemento == &elementos[1]) && (lista->nodo_inicio->siguiente->siguiente == NULL) , "Se pudo borrar el ultimo elemento de una lista a la que le quedan elementos aun");
	lista_destruir(lista);

}

void probar_lista_elemento_en_posicion() {

	lista_t* lista = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_elemento_en_posicion(lista,0) == NULL, "Devuelve NULL en caso de querer devolver un elemento de una lista vacia");
	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(lista, &elementos[i]);
	}
	int* elemento = NULL;
	elemento = lista_elemento_en_posicion(lista, 0);
	pa2m_afirmar(*elemento == elementos[0], "Devuelve el elemento de la primera posicion correctamente");
	elemento = lista_elemento_en_posicion(lista, 1);
	pa2m_afirmar(*elemento == elementos[1], "Devuelve el elemento de la posicion 1 correctamente");
	elemento = lista_elemento_en_posicion(lista, 3);
	pa2m_afirmar(*elemento == elementos[3], "Devuelve el elemento de la ultima posicion correctamente");
	lista_destruir(lista);

}

void probar_lista_ultimo() {

	lista_t* lista = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_ultimo(lista) == NULL, "Devuelve NULL en caso de querer devolver el ultimo elemento de una lista vacia");
	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(lista, &elementos[i]);
	}
	int* elemento = NULL;
	elemento = lista_ultimo(lista);
	pa2m_afirmar(*elemento == elementos[3], "Devuelve el elemento de la ultima posicion correctamente");
	lista_destruir(lista);

}

void probar_lista_elementos() {

	lista_t* lista = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_elementos(lista) == 0, "Devuelve 0 en caso de querer obtener la cantidad de elementos de una lista vacia");
	size_t cant_elementos = 0;
	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(lista, &elementos[i]);
		cant_elementos++;
	}
	pa2m_afirmar(lista_elementos(lista) == cant_elementos, "Devuelve la cantidad correcta de elementos que hay en la lista");
	lista_destruir(lista);

}

void probar_lista_apilar() {

	lista_t* pila = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_apilar(NULL,&elementos[0]) == ERROR, "Error al pasar NULL como pila");

	int elementos_insertados = 0;
	if(lista_apilar(pila, &elementos[0]) == 0) {
		elementos_insertados++;
	}
	pa2m_afirmar(elementos_insertados == 1, "Se pudo apilar el primer elemento a la pila");
	pa2m_afirmar(pila->cantidad == 1, "Se actualizo la cantidad de elementos en la pila");
	pa2m_afirmar((pila->nodo_inicio == pila->nodo_fin) && (pila->nodo_inicio != NULL), "El primer elemento apilado es el primero y el ultimo");
	for(int i = 1 ; i < 4 ; i++) {
		if(lista_apilar(pila, &elementos[i]) == 0) {
			elementos_insertados++;
		}
	}
	pa2m_afirmar(elementos_insertados == 4, "Se pudo apilar mas de un elemento a la pila");
	pa2m_afirmar(pila->cantidad == 4, "Se actualizo la cantidad total de elementos en la pila");
	pa2m_afirmar(inserto_correctamente(pila, elementos,4) == true, "Insercion correcta de todos los elementos de la pila");
	lista_destruir(pila);

}

void probar_lista_desapilar() {

	lista_t* pila = lista_crear();
	lista_t* pila_nueva = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_desapilar(NULL) == ERROR, "Error al pasar NULL como pila");
	pa2m_afirmar(lista_desapilar(pila) == ERROR, "Error al querer borrar un elemento de una pila vacia");
	for(int i = 0 ; i < 1 ; i++) {
		lista_insertar(pila_nueva, &elementos[i]);
	}
	pa2m_afirmar((lista_desapilar(pila_nueva) == 0) && (pila_nueva->cantidad == 0) && (pila_nueva->nodo_inicio == NULL) && (pila_nueva->nodo_fin == NULL), "Se pudo borrar todos los elementos de una pila");
	lista_destruir(pila_nueva);
	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(pila, &elementos[i]);
	}
	pa2m_afirmar((lista_desapilar(pila) == 0) && (pila->cantidad == 3) && (pila->nodo_inicio->siguiente->siguiente->elemento == &elementos[2]) && (pila->nodo_inicio->siguiente->siguiente->siguiente == NULL), "Se pudo borrar el ultimo elemento de una pila a la que le quedan elementos aun");
	lista_destruir(pila);

}

void probar_lista_tope() {

	lista_t* pila = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_tope(pila) == NULL, "Devuelve NULL en caso de querer devolver el ultimo elemento de una pila vacia");
	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(pila, &elementos[i]);
	}
	int* elemento = NULL;
	elemento = lista_tope(pila);
	pa2m_afirmar(*elemento == elementos[3], "Devuelve el elemento que esta en el tope de la pila correctamente");
	lista_destruir(pila);

}

void probar_lista_encolar() {

	lista_t* cola = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_encolar(NULL,&elementos[0]) == ERROR, "Error al pasar NULL como cola");
	int elementos_insertados = 0;
	if(lista_encolar(cola, &elementos[0]) == 0) {
		elementos_insertados++;
	}
	pa2m_afirmar(elementos_insertados == 1, "Se pudo apilar el primer elemento a la cola");
	pa2m_afirmar(cola->cantidad == 1, "Se actualizo la cantidad de elementos en la cola");
	pa2m_afirmar((cola->nodo_inicio == cola->nodo_fin) && (cola->nodo_inicio != NULL), "El primer elemento encolado es el primero y el ultimo");
	for(int i = 1 ; i < 4 ; i++) {
		if(lista_encolar(cola, &elementos[i]) == 0) {
			elementos_insertados++;
		}
	}
	pa2m_afirmar(elementos_insertados == 4, "Se pudo encolar mas de un elemento a la cola");
	pa2m_afirmar(cola->cantidad == 4, "Se actualizo la cantidad total de elementos en la cola");
	pa2m_afirmar(inserto_correctamente(cola, elementos,4) == true, "Se encolaron correctamente todos los elementos");
	lista_destruir(cola);

}

void probar_lista_desencolar() {

	lista_t* cola = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_desencolar(NULL) == ERROR, "Error al pasar NULL como cola");
	pa2m_afirmar(lista_desencolar(cola) == ERROR, "Error al querer desencolar un elemento de una cola vacia");
	for(int i = 0 ; i < 1 ; i++) {
		lista_encolar(cola, &elementos[i]);
	}
	pa2m_afirmar((lista_desencolar(cola) == 0) && (cola->cantidad == 0) && (cola->nodo_inicio == NULL) && (cola->nodo_fin == NULL), "Se pudo desencolar todos los elementos de una cola");
	for(int i = 0 ; i < 5 ; i++) {
		lista_encolar(cola, &elementos[i]);
	}
	pa2m_afirmar((lista_desencolar(cola) == 0)  && (cola->cantidad == 4), "Se pudo desencolar el primer elementos de una cola a la cual le quedan elementos aun");
	lista_destruir(cola);

}

void probar_lista_primero() {

	lista_t* cola = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	pa2m_afirmar(lista_elemento_en_posicion(cola,0) == NULL, "Devuelve NULL en caso de querer devolver un elemento de una cola vacia");
	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(cola, &elementos[i]);
	}
	int* elemento = NULL;
	elemento = lista_elemento_en_posicion(cola, 0);
	pa2m_afirmar(*elemento == elementos[0], "Devuelve el elemento de la primera posicion de la cola correctamente");
	lista_destruir(cola);

}

void probar_lista_iterador_crear() {

	lista_t* lista = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(lista, &elementos[i]);
	}
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador != NULL, "Puedo crear un iterador");
	lista_iterador_destruir(iterador);	
	lista_destruir(lista);

	lista_t* lista_nueva = lista_crear();
	lista_iterador_t* iterador_nuevo = lista_iterador_crear(lista_nueva);
	pa2m_afirmar(iterador_nuevo != NULL, "Se puede crear un iterador con una lista vacia");
	lista_iterador_t* iterador_null= lista_iterador_crear(NULL);
	pa2m_afirmar(iterador_null == NULL, "Un iterador de una lista nula es nulo");	
	lista_iterador_destruir(iterador_nuevo);
	lista_destruir(lista_nueva);
	lista_iterador_destruir(iterador_null);
}

void probar_lista_iterador_tiene_siguiente() {

	lista_t* lista = lista_crear();
	lista_t* lista_vacia = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(lista, &elementos[i]);
	}
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador != NULL, "Puedo crear un iterador");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == true, "El iterador tiene siguiente" );
	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == &elementos[0], "El primer elemento es el correcto");
	pa2m_afirmar(lista_iterador_tiene_siguiente(NULL) == false, "Devuelve FALSE en caso de recibir un iterador NULL");

	lista_iterador_t* iterador_lista_vacia = lista_iterador_crear(lista_vacia);
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_lista_vacia) == false, "Devuelve FALSE en caso de no tener mas elementos sobre los cuales iterar");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador_lista_vacia) == NULL, "Si no hay elementos, el iterador devuelve NULL como elemento actual ");
	lista_iterador_destruir(iterador_lista_vacia);
	lista_destruir(lista_vacia);
	lista_iterador_destruir(iterador);	
	lista_destruir(lista);

}

void probar_lista_iterador_avanzar() {

	lista_t* lista = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(lista, &elementos[i]);
	}
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == &elementos[0], "El iterador esta en la posicion 0");
	pa2m_afirmar((lista_iterador_avanzar(iterador) == true) && (lista_iterador_elemento_actual(iterador) == &elementos[1]), "El iterador avanzo a la posicion 1");
	pa2m_afirmar((lista_iterador_avanzar(iterador) == true) && (lista_iterador_elemento_actual(iterador) == &elementos[2]), "El iterador avanzo a la posicion 2");
	pa2m_afirmar((lista_iterador_avanzar(iterador) == true) && (lista_iterador_elemento_actual(iterador) == &elementos[3]), "El iterador avanzo a la ultima posicion");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);

}

/*	
	Pre: Recibe un elemento y un auxiliar de tipo void*
	Post: Devuelve true si no es el ultimo elemento o false si no.
	Se trata de una funcion que utilice para las pruebas de iterador interno (en este caso imprime por pantalla, pero podria haber sido cualquier otra accion). 
*/

bool mostrar_elemento_actual(void* elemento, void* aux) {
	printf("El elemento es el numero: %i\n", *(int*)elemento ); 
	(*(int*)aux)+=1;
	if(*(int*)elemento == ULTIMO_ELEMENTO) {
		return false;
	}
	return true;
}

void probar_iterador_interno_lista() {

	lista_t* una_lista = lista_crear();
	int elementos[4] = {1, 2, 3, 4};
	for(int i = 0 ; i < 4 ; i++) {
		lista_insertar(una_lista, &elementos[i]);
	}
	int contador = 0;
	size_t elementos_recorridos = 0;
	pa2m_afirmar(lista_con_cada_elemento(NULL, mostrar_elemento_actual, &contador) == 0, "Devuelve 0 en caso de recibir una lista en NULL");
	pa2m_afirmar(lista_con_cada_elemento(una_lista, NULL, &contador) == 0, "Devuelve 0 en caso de recibir una funcion en NULL");
	elementos_recorridos = lista_con_cada_elemento(una_lista, mostrar_elemento_actual, &contador);
	pa2m_afirmar(elementos_recorridos == 3, "Devuelve la cantidad de elementos iterados");
	lista_destruir(una_lista);

}

int main() {

	pa2m_nuevo_grupo("PRUEBAS DE LISTA");

	printf(AMARILLO"\t-CREACION DE LISTA-\n");
	probar_creacion_lista();

	printf(AMARILLO"\t-INSERCION DE ELEMENTOS EN LA LISTA-\n");
	probar_lista_insertar();

	printf(AMARILLO"\t-INSERSION DE ELEMENTOS EN DETERMINADA EN POSICION DE LA LISTA-\n");
	probar_lista_insertar_en_posicion();

	printf(AMARILLO"\t-BORRADO DE ELEMENTOS EN LA ULTIMA POSICION DE LA LISTA-\n");
	probar_lista_borrar();

	printf(AMARILLO"\t-BORRADO DE ELEMENTOS EN DETERMINADA POSICION DE LISTA-\n");
	probar_lista_borrar_de_posicion();

	printf(AMARILLO"\t-ELEMENTO EN POSICION INDICADA DE LA LISTA-\n");
	probar_lista_elemento_en_posicion();

	printf(AMARILLO"\t-ELEMENTO EN ULTIMA POSICION DE LA LISTA-\n");
	probar_lista_ultimo();

	printf(AMARILLO"\t-CANTIDAD DE ELEMENTOS EN LISTA-\n");
	probar_lista_elementos();

	pa2m_nuevo_grupo("PRUEBAS DE PILA");

	printf(AMARILLO"\t-APILAR ELEMENTOS EN LA PILA-\n");
	probar_lista_apilar();

	printf(AMARILLO"\t-DESAPILAR ELEMENTOS EN LA PILA-\n");
	probar_lista_desapilar();

	printf(AMARILLO"\t-TOPE DE LA PILA-\n");
	probar_lista_tope();

	pa2m_nuevo_grupo("PRUEBAS DE COLA");

	printf(AMARILLO"\t-ENCOLAR ELEMENTOS EN LA COLA-\n");
	probar_lista_encolar();

	printf(AMARILLO"\t-DESENCOLAR ELEMENTOS EN LA COLA-\n");
	probar_lista_desencolar();

	printf(AMARILLO"\t-PRIMER ELEMENTO DE LA COLA-\n");
	probar_lista_primero();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR EXTERNO");

	printf(AMARILLO"\t-CREACION DE ITERADOR-\n");
	probar_lista_iterador_crear();

	printf(AMARILLO"\t-ITERADOR TIENE SIGUIENTE-\n");
	probar_lista_iterador_tiene_siguiente();

	printf(AMARILLO"\t-ITERADOR AVANZAR-\n");
	probar_lista_iterador_avanzar();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR INTERNO");

	printf(AMARILLO"\t-ITERADOR LISTA CON CADA ELEMENTO-\n");
	probar_iterador_interno_lista();

	pa2m_mostrar_reporte();
	return 0;
}