#include <iostream> 
using namespace std; 


void imprimeVectorEnteros( const int vector[], int util_vector){
	cout << "( "; 	
	for ( int i = 0; i < util_vector; i += 1)
	{
		cout << vector[i] << " "; 
	}
	cout << ")"; 
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

/*
 *  @brief Este módulo ordena un vector de ENTEROS de menor a menor utilizando un algoritmo basado en el método merge. 
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



int main() {
	const int DIM_VECTOR=10;
	int vector[DIM_VECTOR]={4,9,2,1,3,5,3};
	int util_vector=7;

	imprimeVectorEnteros(vector, util_vector);
	cout << endl; 
	mergesort(vector, util_vector);
	imprimeVectorEnteros(vector, util_vector);
	cout << endl; 
}
