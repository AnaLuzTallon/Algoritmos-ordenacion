/* 
//@filename mergesort.cpp
//@author  Ángel Álvarez, AnaLuz Tallón 
//@date 2020-02-11
//
//@brief	Programa realizado para explicar el funcionamiento del algoritmo de ordenación MERGESORT
*/

//Declaración de Librerias a utilizar

#include <iostream>

#include <iomanip>
#define DEFAULT "\033[1;0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"



using namespace std; 


/**
 * @brief	Módulo que imprime por pantalla el vector de enteros indicado.
 * @pre		vector[] debe ser un vector de tipo entero.
 * @pre		util_vector debe ser menor que la DIMENSION total de vector.
 * @param	int vector[](E) Referecia a un vector de tipo entero. Se pasa con el modificador CONST puesto que no se va a modificar.
 * @param	int util_vector Variable que indica el número de elementos ocupados en vector y la siguiente posición disponible para la inserción. Se pasa por COPIA puesto que no se va a modificar vector.
 * @post	Los elementos del vector saldrán impresos por pantalla. NO SE INSERTA SALTO DE LÍNEA AL FINAL DEL PROCEDIMIENTO.
 EJEMPLO  --> 1 2 3 4 5
**/
 
void imprimeVectorEnteros(const int vector[], int util_vector) {
	for(int i = 0; i < util_vector; i++) {
		cout << vector[i] << " ";
	}
}

/**
 * @brief	Módulo que filtra datos y devuelve un número entero.
 * @return 	Devuelve un número entero
**/
int introduceEntero() {
	// Declaración del vector de caracteres que usaremos como entrada
	const int DIM_ENTRADA = 10;
	char entrada[DIM_ENTRADA] = "";
	
	// Variable donde se va a almacenar el entero de salida
	int numero;
	// Variables auxiliares para el filtro de datos
	bool esEntero;
	bool negativo;
	
	do {
		// Reiniciamos los valores para el filtrado
		esEntero = true;
		negativo = false;
		numero = 0;
		// Entrada a la cadena de caracteres
		cin >> entrada;
		for(int i = 0; (entrada[i] != '\0') && esEntero ; i++) {
			// Condición para el número negativo
			if ((i == 0) && (entrada[i] == 45)) {
				negativo = true;
			}
			else if ((entrada[i] >= 48) && (entrada[i] <= 57)) {
				numero *= 10;
				if (negativo) {
					numero -= (entrada[i] - 48);
				}
				else {
					numero += (entrada[i] - 48);
				}
			}
			else {
				esEntero = false;
			}
		}

		if (!esEntero) {
			cout << RED << "El valor introducido no es un número entero." << DEFAULT << endl;
			cout << "Introduzca un valor entero: ";
		}
	} while (!esEntero);
	
	return numero;
}
	 
/**
 * @brief	Módulo que permite la introducción de valores en un vector de tipo entero. Este módulo borrará los valores que haya anteriormente introducidos.
 * @param 	int vector[](S) Referencia a un vector de tipo INT al cual vamos a introducir valores. Se pasa SIN el modificador CONST puesto que vamos a modificarlo.
 * @param	int util_vector(S) Variable que indica cuantos elementos de vector estan ocupados y cual es la siguiente posición libre para la escritura. Se pasa por REFERENCIA puesto que se va a modificar el vector.
 * @param 	int DIM_VECTOR(E) Variable que indica la dimensión total del vector. Es una variable CONST, no se puede modificar. Se usará como filtro.
 * @post 	vector[] Contendrá valores de tipo INT.
 * @post	util_vector será <= DIM_VECTOR
**/
void introduceVectorEnteros(int vector[], int &util_vector, const int DIM_VECTOR) {

	do {
		cout << "¿Cuantos valores desea introducir al vector? : ";
		util_vector = introduceEntero();
		if ((util_vector < 0) || (util_vector > DIM_VECTOR)) {
			cout << RED << "El valor introducido debe ser un número entero mayor o igual que 0 y menor o igual que " << DIM_VECTOR << DEFAULT << endl;
		}

	} while ((util_vector < 0) || (util_vector > DIM_VECTOR));
	
	
	for (int i = 0; i < util_vector; i++) {
		cout << "Introduzca el valor que se guardará en la posición " << i << " del vector: ";
		vector[i] = introduceEntero();
	}
}

/*
 *  @brief Este módulo ordena dos vectores ordenados de menor a mayor, EJ: vector_izq[1, 4] vector_dcha[2, 3] vector_salida[1, 2, 3, 4]
 *  @pre Los dos vectores de entrada deben de estar ordenados de menor a mayor. 
 *  @pre La dimensión del vector de salida debe de ser mayor o igual que la suma de los utiles de entrada. 
  *  @param int vector_izq[] (E) referencia a un vector de tipo entero al que se  va a fusionar ordenadamente con otro vector, como este vector  no se va a modificar lo referenciamos CON EL MODIFICADOR CONST. 
 *  @param int util_vector_izq (E) variable que indica el numero de elementos que hay en el vector y la siguiente posición que hay disponible de escritura. Se realiza un paso por copia puesto que no se va a modificar el tamaño del vector. 
  *  @param int vector_dcha[] (E) referencia a un vector de tipo entero al que se  va a fusionar ordenadamente con otro vector, como este vector  no se va a modificar lo referenciamos CON EL MODIFICADOR CONST. 
 *  @param int util_vector_dcha (E) variable que indica el numero de elementos que hay en el vector y la siguiente posición que hay disponible de escritura. Se realiza un paso por copia puesto que no se va a modificar el tamaño del vector. 
 *  @param int vector_salida[] (S) referencia a un vector de tipo entero en el que se va a guardar los dos vectores fusionados, como este vector se va a modificar lo referenciamos SIN EL MODIFICADOR CONST. 
 **  @param int util_vector_salida (E) variable que indica el numero de elementos que hay en el vector y la siguiente posición que hay disponible de escritura. Se realiza un paso por copia puesto que no se va a modificar el tamaño del vector. 
 *  @post int vector_salida será el resultado de la combinación de los dos vectores ordenados 
*/

void  ordena_ordenados(const int vector_izq[], int util_vector_izq, const int vector_dcha[], int util_vector_dcha, int vector_salida[], int util_vector_salida) {

	// 1) DECLARACION DE VARIABLES CONTADORAS 
	int i= 0; // Será el indice correspondiente del vector_izq
	int j=0; //Será el indice correspondiente al vector_dcha
	int k=0; // Será el indice correspondiente al vector_salida.

	for (k=0 ; k < util_vector_salida; k += 1)
	{
		if ( i == util_vector_izq){
			vector_salida[k]= vector_dcha[j];
			j ++;
		}else if ( j == util_vector_dcha){
			vector_salida[k]=vector_izq[i];
			i++; 
		}else if ( vector_izq[i] <= vector_dcha[j]){
			vector_salida[k]=vector_izq[i];
			i++; 
		}else if ( vector_izq[i] > vector_dcha[j]){
			vector_salida[k]= vector_dcha[j];
			j ++;
		}
		//imprimeVectorEnteros(vector_salida, util_vector_salida);
	}


}

/**  @brief Este módulo ordena un vector de ENTEROS de menor a menor utilizando un algoritmo basado en el método merge. 
 *  @pre La variable util_vector debe ser mayor a 0. 
 *  @param int vector[] (E/S) referencia a un vector de tipo entero al que se le va aplicar el algoritmo de ordenación, como este vector se va a modificar lo referenciamos SIN EL MODIFICADOR CONST. 
 *  @param int util_vector (E) variable que indica el numero de elementos que hay en el vector y la siguiente posición que hay disponible de escritura. Se realiza un paso por copia puesto que no se va a modificar el tamaño del vector. 
 *  @post El vector se encontrará ordenado de menor a mayor.  
 *  EJ: vector={4, 2, 1, 3} --> vector={1, 2, 3, 4}
 *  @version 1.0
 *  @author Ángel Álvarez (1.0)  &&  AnaLuz Tallón (1.0)
*/

void mergesort( int vector[], int util_vector){

	// 1) DECLARACION DE VARIABLES Y VECTORES  A UTILIZAR 
	//Vectores
	int util_vector_izq=util_vector/2; //La util del vector va hacer igual que su tamaño, por ello es constante.
	int vector_izq[util_vector_izq];
	int util_vector_dcha=util_vector - util_vector_izq;  //La util del vector va hacer igual que su tamaño, por ello es constante.
	int vector_dcha[util_vector_dcha];
	
	// 2) OPERACIONES 
	if (util_vector != 1){  // Filtro de fin de recursividad  
		for (int  i= 0; i < util_vector_izq; i += 1)
		{
			vector_izq[i]=vector[i];
		}
		for (int i = util_vector_izq; i < util_vector; i += 1)
		{
			vector_dcha[i-util_vector_izq]=vector[i];	
		}

		//Invocación de módulos recursivos
		mergesort(vector_izq, util_vector_izq);
		mergesort(vector_dcha, util_vector_dcha);

		// Invocación de módulo ordena ordenados
		ordena_ordenados(vector_izq, util_vector_izq, vector_dcha, util_vector_dcha, vector, util_vector);
	}
	
}


// Programa principal
int main() {
	// 1) Declaración del vector
	const int DIM_VECTOR=10;
	int vector[DIM_VECTOR];
	int util_vector=0;

	// 2) Inicialización del vector
	introduceVectorEnteros(vector, util_vector, DIM_VECTOR);
	imprimeVectorEnteros(vector, util_vector);
	cout << endl; 
	
	// 3) Invocación de función de ordenación
	mergesort(vector, util_vector);
	imprimeVectorEnteros(vector, util_vector);
	cout << endl; 
}
