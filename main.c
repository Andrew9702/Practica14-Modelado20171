#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

/*Compara 2 'Elemento' que contienen como valor un 'int'*/
//Los parametros const void, apuntan a un espacio de memoria que no será modificado
//Si los enteros son identicos se regresa 0 (C no tiene booleanos :/)
int cmp_int(const void *a, const void *b){
    //Se obtiene el apuntador a elemento de los parametros.
    elemento *direccionP = (elemento *) a;
    //Lo mismo para b
    elemento *direccionP2 = (elemento *) b;
    //Obtenemos el valor de los 'elemento'
    //Version con flechas es más facil para castings
    int v1 = *(int*)direccionP->valor;
    int v2 = *(int*)direccionP2->valor;
    //hacemos las comparaciones
    if(v1 < v2){
        return -1;
    } 
    if(v1 == v2){
        return 0;
    }
    if(v1>v2){
        return 1;
    }

    return 0; 
}

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista){
	if(*lista == NULL){
		return 0;
	} else{
		size_t size = 0;
		int indice = 0;
		Elemento* sigue = *lista;
		while(sigue != NULL){
			sigue = (*sigue).siguiente;
			size+=1;
			indice+=1;
		}
        	return size;
	}
}

/*Crea una lista vacía*/
Lista crea_lista(){
	//Se aparta el espacio en el heap para la lista
	Lista lista = malloc(sizeof(Lista));
	return lista;
}

/*Función que ordena una lista usando una función comparadora*/
//Recomiendo apoyarte de tu función 'cmp_int', qsort y un arreglo
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){
	//Obtenemos el tamaño de la lista
	size_t tamano = longitud(lista);
	//Hacemos un arreglo del tamaño de la lista
	int valores[longitud];
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
	qsort(valores,longitud,sizeof(int),(*cmp));
	//Ya ordenados los volvemos a meter a la lista
	for(indice;indice<tamano;indice++){
		*(int*)nodo->valor = valores[indice];
		*nodo = (*nodo).siguiente;
	}
    
}

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista lista){

}

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento *quita_elemento(Lista, size_t posicion){

}

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista*/
int inserta_elemento(Lista lista, void *valor){
	//Obtenemos el tamaño de la lista
	size_t tamano = longitud(lista);
	//Creamos un nuevo elemento
	Elemento *recien = malloc(sizeof(Elemento));
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
	while(lista){
		int valor = *(int*)lista->valor;
		printf("%d\n", valor);
		lista = lista->siguiente;
	}
    
}

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insesrtar);
    };
}
