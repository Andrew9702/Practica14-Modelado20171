#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

/*Compara 2 'Elemento' que contienen como valor un 'int'*/
//Los parametros const void, apuntan a un espacio de memoria que no será modificado
//Si los enteros son identicos se regresa 0 (C no tiene booleanos :/)
int cmp_int(const void *a, const void *b){
    //Se obtiene el apuntador a elemento de los parametros.
    Elemento *direccionP = (Elemento *) a;
    //Lo mismo para b
    Elemento *direccionP2 = (Elemento *) b;
    //Obtenemos el valor de los 'elemento'
    //Version con flechas es más facil para castings
    int v1 = *(int*)direccionP->valor;
    int v2 = *(int*)direccionP2->valor;
    //hacemos las comparaciones
    if(v1 == v2){
        return 0;
    }
}

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista){
	if(*lista == NULL){
		return 0;
	} else{
		size_t size = 0;
		Elemento* derecho = *lista;
		while(derecho != NULL){
			derecho = derecho->siguiente;
			size+=1;
		}
        return size;
	}
}

/*Crea una lista vacía*/
Lista crea_lista(){
	//Se aparta el espacio en el heap para la lista
	Lista lista = calloc(1 ,sizeof(Lista));
	return lista;
}

/*Función que ordena una lista usando una función comparadora*/
//Recomiendo apoyarte de tu función 'cmp_int', qsort y un arreglo
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){
	//Obtenemos el tamaño de la lista
	size_t tamano = longitud(lista);
	//Hacemos un arreglo del tamaño de la lista
	int valores[tamano];
	int indice = 0;
	//tomamos un valor auxiliar para tomar elementos de la lista
	Elemento *nodo = *lista;
	//En este for vamos a rellenar el arreglo con los valores de la lista
	for(indice;indice<tamano;indice++){
		//Obtenemos el valor del elemento
		int valorElem = *(int*)nodo->valor;
		valores[indice] = valorElem;
		nodo = (*nodo).siguiente;
	}
	//Quicksort se basa en un arreglo para funcionar, por eso la creacion del mismo
	//Llamamos a Qsort para que ordene los valores del arreglo
	//Aquí mandamos a llamar a la funcion que ordena enteros
	qsort(valores,tamano,sizeof(int),(*cmp));
	//Ya ordenados los volvemos a meter a la lista
	for(indice;indice<tamano;indice++){
		*(int*)nodo->valor = valores[indice];
		nodo = (*nodo).siguiente;
	}
    
}

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista lista){
	//Una manera practica es borrar toda la lista one by one
	size_t largo = longitud(lista);
	int indice = 0;
	//Necesitamos algo que apunte al elemento para que no se pierdan los valores
	Elemento *aiuda;
	//De esta manera iremos quitando los valores en la lista de cabeza en cabeza
	for(indice;indice<largo;indice++){
		aiuda = quita_elemento(lista,0);
		//En el caso de que lleguemos al ultimo evitemos problemas
		if(aiuda!=NULL){
			free(aiuda -> valor);
			free(aiuda);
		}
	}
	free(lista);
}

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento *quita_elemento(Lista lista, size_t posicion){
	//Servira´para recorrer la lista
	int indice = 0;
	//Caso de que la lista sea null
	if(*lista == NULL){
		return NULL;
	}

	//Casos para tramposos, si no existe el indice, pos ya
	if(posicion>=longitud(lista)){
		return NULL;
	}

	//Indice invalido, por si las moscas
	if(posicion<0){
		return NULL;
	}
	//Caso en que sea la primera posicion
	if(posicion == 0){
		//Apuntador al elemento siguiente del que se quiere remover
		Elemento *reemplazoHead = (*lista)->siguiente;
		//Apuntador al elemento que se va a quitar
		Elemento *original = *lista;
		(*lista)->siguiente = NULL;
		(*lista) -> valor = NULL;
		*lista = reemplazoHead;
		return original;
	}

	//Caso de que sea el ultimo elemento de la lista
	if(posicion == longitud(lista)-1){
		//Establecemos un nodo que se ira igualando hasta llegar a uno antes del ultimo
		Elemento *vagonero = *lista;
		for(indice;indice<longitud(lista)-1;indice++){
			vagonero = vagonero -> siguiente;
		}
		Elemento *cola = vagonero->siguiente;
		cola -> valor = NULL;
		vagonero -> siguiente = NULL;
		return cola;

	} else { //Si no es ni el primero ni el ultimo 
		//Siempre vamos a empezar por la cabeza, por lo que para llegar a una posicion, simplemente podemos iterar sobre lista
		Elemento *antes = *lista;
		for(indice;indice<posicion;indice++){
			antes = antes->siguiente;
		}
		//Ya tenemos el que queremos eliminar
		Elemento *encontrado = antes->siguiente;
		//Igualamos el siguiente del nodo anterior al que buscamos, al siguiente del que buscamos
		antes -> siguiente = encontrado->siguiente;
		//Le quitamos sus valores al que queriamos encontrar
		encontrado ->siguiente = NULL;
		encontrado ->valor = NULL;
		return encontrado;
	}
}

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista*/
int inserta_elemento(Lista lista, void *valor){
	//Obtenemos el tamaño de la lista
	size_t tamano = longitud(lista);
	//Creamos un nuevo elemento
	Elemento *recien = calloc(1, sizeof(Elemento));
	//Le damos direcciones a este nuevo elemento
	(*recien).siguiente = *lista;
	recien->valor = valor;
	//Apuntamos la cabeza al nuevo elemento
	*lista = recien;
	int nuevoTam = tamano + 1;
	return nuevoTam;
}

/*Imprime los elementos de la lista como enteros*/
void imprime_lista_int(Lista lista){
	size_t largo = longitud(lista);
	int indice = 0;
	Elemento *aux = *lista;
	while(lista){
		int valor = *(int*)aux->valor;
		printf("el valor en el indice %d es:  %d\n", indice, valor);
		indice+=1;
		aux = aux->siguiente;
	} 
}

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos al ser creada\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos despues de haberla rellenado\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {
    	free(borrado->valor);
    	free(borrado);
	}
    printf("La lista sin la primer cabeza tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos, ese indice no existe\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    printf("*****************Esta es tu lista antes de ser ordenada************\n");
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
    system("PAUSE");

}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}
