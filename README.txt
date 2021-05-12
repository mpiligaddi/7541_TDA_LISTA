README: TDA LISTA.

Facultad de Ingeniería - UBA.

Cátedra Mendez - Camejo.

Alumna: Maria Pilar Gaddi.



Primera sección: Presentación del TDA.

	-Introducción: 
		El presente TDA consta de cinco archivos para poder ser compilado y ejecutado correctamente:

			lista.c: donde se implementan todas las funciones de la biblioteca utiles.h brindada por la cátedra. 

			lista.h: donde se encuentran declaradas las funciones implementadas en lista.c

			lista_minipruebas.c: donde se encuentran las "pruebas guia" del TDA, con todos los "casos felices". La misma fue brindada por la cátedra y la utilice para tener un panorama general de como estaba funcionando el programa. 

			pruebas_extras.c: donde se encuentran implementadas todas las funciones que tienen como objetivo ser parte de las "pruebas propias" del TDA, basandome en los anteriores "casos felices" y teniendo en cuenta los "casos borde".

			pa2mm.h: donde se encuentran algunas de las funciones utilizadas en pruebas_extras.c para realizar las pruebas. Esta biblioteca fue brindada por la cátedra. 

	-Linea de compilación: 
		El programa debe ser compilado bajo la siguiente linea de compilación:
			gcc *.c -o lista_se -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

	-Linea de ejecución: 
		El programa debe ser ejecutado bajo la siguiente linea de ejecución:
			valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se

	ACLARACION: En caso de querer utilizar el main de lista_minipruebas.c, este se encuentra abajo de todo como comentario. Sacar de comentario y comentar el main "principal" de pruebas_extras.c. La linea de compilación y ejecución son las mismas mencionadas anteriormente.

	-Funcionamiento del código: 

		Para lograr un buen funcionamiento del código, mi objetivo fue lograr entender concretamente que es lo que hacia cada función y cúal era el objetivo de cada una de estas. 
		En el código hay tanto manejo de memoria dinámica (ubicada en el HEAP) como de estática (ubicada en el STACK), por lo que me pareció fundamental el buen uso de punteros, que fue lo que más tuve en cuenta, realizando gráficos en papel para poder entenderlos mejor, de esta forma me resultó mas visible la forma en que funcionaba el TDA y como cada tema se unía con otro. 
		Dentro de cada función me enfoque, ademas, en tener en cuenta los posibles casos bordes que antes no los tenía muy a la vista ya que lo aclaraba en las pre-condiciones. De esta forma me di cuenta de la cantidad de casos límite que podrían existir, y más a la hora de llevarlo a la práctica real. 
		Más al final del TDA, al arrancar con las funciones de cola y pila, me di cuenta que podía reutilizar algunas funciones de la lista, adaptandolas para la pila y para la cola. Por ejemplo, para lista_apilar utilice lista_insertar ya que la ultima función insertaba un elemento al final de la lista, de esta forma no solo m sirvió para insertar en la pila sino también para insertar en la cola. 
		Aquellas funciones que no fueron brindadas por la catedra y que no eran "funciones de pruebas", que necesitaban pre-post condiciones las indique. En el caso de las pruebas no las indique ya que estas no las necesitan.

	-¿Por qué se eligió dicha implementación?:

		Elegí dicha implementación para darle importancia al buen uso de los punteros, ver como estos funcionan en una lista, una pila, o en una cola. 
		Utilizando nombres de variables descriptivas y sin ambiguedades, pude visualizar de mejor forma lo que se necesitaba hacer, y de esta forma lograba encontrar los errores más rápido. 
		En cuanto a los iteradores, me sirvió mucho saber cuales eran las diferencias entre cada uno (interno/externo) y tener en cuenta que, en el caso del iterador interno, no necesitaba reservar memoria del HEAP, ya que, en caso utilizarse, tendría que utilizar funciones propias del iterador externo, lo que podría generar algún error (ejemplo, que el iterador falle al crearse). En ese caso, no tendría forma de comunicar el error en las pruebas por como está armada la función lista_con_cada_elemento. 

Segunda sección: Preguntas teoricas.

	-¿Qué es una lista? ¿Cúales son las diferencias entre ser simple y doblente enlazada?

		La lista es un Tipo de Dato Abstracto que se encarga de agrupar elementos. Cada uno de estos tiene un sucesor (menos el último) y un predecesor (menos el primero). Este TDA esta basado en los nodos enlazados y la idea principal es que, un nodo, al poder conocer su siguiente, puede crear una lista de nodos. Cuando se recorre una lista, la misma llega al final cuando el último nodo apunta a NULL.

		Una lista simplemente enlazada tiene una dirección unidireccional ya que cada nodo conoce al siguiente. Además,la lista mantiene referencia al primer nodo y reservo/libero memoria para cada nodo.
		En cambio, en el caso de una lista doblemente enlazada, se puede recorrer en cualquier dirección (por ejemplo, desde el primer nodo hasta el último o alrevés). Además,cada nodo conoce al siguiente, pero también al anterior. 


	-¿Cúales son las características fundamentales de las pilas? ¿Y de las colas?

		Las características fundamentales de las pilas son que se tratan de un TDA que se encargan de agrupar elementos. Se caracteriza por tener una estructura LIFO (Last In, First Out) lo que significa que lo primero que sale es el ultimo elemento de la pila, y el elemento que entra lo hace atraves del final de la pila. Un ejemplo podría ser una pila de platos, que se van apilando y se van agregando platos al final de la pila, mientras que los mismos se sacan por el mismo lugar. 
		Una pila se puede implementar con un vector estático, vector dinámico o con una lista de nodos enlazados (que es la más utilizada)
		Las características fundamentales de las colas son que se tratan de un TDA que se encargan de agrupar elementos, como en el caso de la lista o la pila. Se caracteriza por tener una estructura FIFO (First In, First Out) en donde se elemina por el frente y se inserta por el final. Un ejemplo podría ser una cola del supermercado, las personas que pertenecen a la cola van siendo "eliminadas" por el principio de la cola, mientras que se van "agregando" al final de la misma.
		Una cola se puede implementar con un vector estático, dinámico o con una lista de nodos enlazados (la más utilizada).

	-¿Qué es un iterador? ¿Cúal es su función?

		Un iterador se trata de un TDA aparte que me permite iterar sobre mi TDA original. Con "iterar" se refiere a recorrer secuencialmente los datos almacenados. Con este recorrido o iteración se pueden llevar a cabo diferentes acciones en alguno de los nodos de mi TDA original, asi como borrarlos, agregar uno nuevo, invocar funciones con cada elemento de los mismos, entre otras. Existen dos tipos de iteradores: el iterador interno y el externo.

	-¿En qué se diferencia un iterador interno de uno externo?

		La diferencia entre el iterador interno y el externo es que, en el caso del primero, en este se produce una iteración instantanea por lo que permite recorrer los elementos sin tener que controlar el ciclo en el cual se recorre el mismo. Maneja toda la iteracion dentro de la estructura de datos, por lo que es mas directo de usar. 

		En cambio, en el caso del iterador externo, este es un TDA que permite manejar la iteracion (es decir, el recorrido de la estructura) mediante sus propias primitivas.
		En el caso de el iterador externo, en principio debo crearlo (reservando memoria en el HEAP) y una vez que se utilizo, liberar la memoria reservada por malloc(). En el caso de este iterador, voy a ir recorriendo elemento por elemento, de a uno a la vez. De esta forma, controlo cuando comienza y cuando termina la iteración.