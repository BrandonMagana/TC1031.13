/*
El siguiente código contiene 3 Funciónes que realizan ordenamiento
de arreglos, con diferente complejidad de tiempo O().

Así mismo se encuentran 2 Funciónes encargas de la busqueda de datos dentro
de arreglos, con diferente complejidad de tiempo O().

Autor: Brandon Josué Magaña Mendoza A016460162
Fecha: 04/Septiembre/2021
*/

#include <iostream>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

//Función printVector
//Entrada:Vector de enteros x
//Salida: NO HAY
//Encargada de imprimir por pantalla los vectores
void printVector(vector<int> x){
    for(int i=0; i<x.size(); i++){
        cout << x[i]<<" ";
    }
    cout<<endl;
}

//Función crearVector
//Entrada: entero num_items
//Salida: vector de enteros
//Crea un vector de enteros de tamaño num_items
vector<int> crearVector(int num_items){
    vector<int> x(num_items,0);
    //srand() para diferentes resultados
    srand(time(0)+rand()%100);

    //generador de numeros aleatorios
    generate(x.begin(),x.end(),[](){
        return rand()%100;
    });
    return x;
}

//Función ordenaBurbuja
//Entrada:Vector de enteros x por referencia
//Salida: NO HAY
//Ordena los elementos del vector de menor a mayor
//Mediante el uso del algoritmo bubble sort
//O(n^2) cuadratíca
void ordenaBurbuja(vector<int>& x){
    for(int i=0; i<x.size();i++){
        for(int j=0;j<x.size()-i-1;j++){
            if (x[j]>x[j+1]){
                int valor_temporal=x[j];
                x[j]=x[j+1];
                x[j+1]=valor_temporal;
            }
        }
    }
}

//Función merge
//Entrada: vector de enteros x,entero izquiera, extero mitad, entero derecha
//Salida: NO HAY
//Combina 2 sub vectores del vector de enteros x
//O(n)Líneal
void merge(vector<int>& x, int izquierda,  int mitad,int derecha){
    int num_elementos_iz=mitad-izquierda+1;
    int num_elementos_der=derecha-mitad;

    vector<int> iz(num_elementos_iz);
    vector<int> der(num_elementos_der);

    for (int i=0; i<num_elementos_iz; i++){
        iz[i]=x[izquierda+i];
    }


    for (int j=0; j<num_elementos_der; j++){
        der[j]=x[mitad+1+j];
    }

    int i=0;
    int j=0;
    int k=izquierda;

    while(i<num_elementos_iz&& j<num_elementos_der){
        if(iz[i] <=der[j]){
            x[k]=iz[i];
            i++;
        }
        else{
            x[k]=der[j];
            j++;
        }
        k++;
    }

    while(i<num_elementos_iz){
        x[k]=iz[i];
        i++;
        k++;
    }

    while(j<num_elementos_der){
        x[k]=der[j];
        j++;
        k++;
    }
}

//Función ordenaMerge
//Entrada: vector de enteros x por referencia, entero izquierda, entero derecha
//Salida: NO HAY
//Ordena los elementos del vector de menor a mayor
//Mediante el uso del algoritmo merge sort recursivo
//O(n log n)linearítmico
void ordenaMerge(vector<int>& x, int izquierda, int derecha){
    if(izquierda<derecha){
        //Encontrar punto medio
        int mitad= izquierda +(derecha-izquierda)/2;
         //Ordenar la primera y segunda mitades
        ordenaMerge(x,izquierda,mitad);
        ordenaMerge(x,mitad+1,derecha);
        //Fusionar ambas mitades ordenadas
        merge(x, izquierda,mitad,derecha);
    }
}

//Función ordenaIntercambio
//Entrada: vector de enteros x por referencia
//Salida: NO HAY
//Ordena los elementos del vector de menor a mayor
//Mediante el uso del algoritmo insertion sort 
//O(n^2)cuadrática
void ordenaIntercambio(vector<int>& x){
    int n=x.size();
    int j;
    int aux;
    for(int i=1; i<n;i++){
        aux=x[i];
        j=i-1;
        while(j>=0 && aux<x[j]){
            x[j+1]=x[j];
            j--;
        }
        x[j+1]=aux;
    }
}

//Función busqSecuencial
//Entrada: vector de enteros x por referencia, entero dato
//Salida: entero: posición de dato dentro del arreglo
//Busca a dato dentro del arreglo utilizando el algoritmo sequential search, 
//De encontrarlo regresa su posición
//Caso contrario regresa un -1
//O(n) lineal
int busqSecuencial(vector<int> x, int dato){
    int i=0;
    while(i<x.size() && x[i]!=dato){
        i++;
    }
    if(i< x.size()) return i;
    return -1;
} 

//Función busqSecuencial
//Entrada: vector de enteros x por referencia, entero dato
//Salida: entero: posición de dato dentro del arreglo
//Busca a dato dentro del arreglo utilizando el algoritmo binary search, 
//De encontrarlo regresa su posición
//Caso contrario regresa un -1
//O(log n) logarítmico
int busqBinaria(vector<int> x, int dato){
    int inicio=0;
    int fin=x.size()-1;
    while(inicio<=fin){
        int mitad= (inicio + fin)/2;
        if(dato==x[mitad]) return mitad;
        else if(dato<x[mitad]){
            fin=mitad-1;
        }else{
            inicio=mitad+1;
        }
    }
    return -1;
}

int main(){
    //Prueba algoritmos de ordenamiento
    cout<<"Algoritmos de ordenamiento"<<endl<<endl;
    for(int i=0; i<4;i++){
        cout<<"Prueba #"<<i+1<<endl;
        cout<<"----ordenaBurbuja----"<<endl;
        vector<int> vec1=crearVector(5);
        cout<<"Vector antes de ordenamiento"<<endl;
        printVector(vec1);
        cout<<"Vector ordenado"<<endl;
        ordenaBurbuja(vec1);
        printVector(vec1);

        cout<<"----ordenaMerge----"<<endl;
        vector<int> vec2=crearVector(7);
        cout<<"Vector antes de ordenamiento"<<endl;
        printVector(vec2);
        cout<<"Vector ordenado"<<endl;
        ordenaMerge(vec2, 0, vec2.size()-1);
        printVector(vec2);

        cout<<"----ordenaIntercambio----"<<endl;
        vector<int> vec3=crearVector(5);
        cout<<"Vector antes de ordenamiento"<<endl;
        printVector(vec3);
        cout<<"Vector ordenado"<<endl;
        ordenaIntercambio(vec3);
        printVector(vec3);
        cout<<endl<<endl;
    }

    //Prueba Algoritmos de búsqueda
    cout<<"Algoritmos de busqueda\n"<<endl;
    vector<int> vect5=crearVector(20);
    cout<<"Vector generado:"<<endl;
    printVector(vect5);
    cout<<endl;

    int busquedas=0, aux=0;

    cout<<"Ingrese el numero de busquedas a realizar: ";
    cin>>busquedas; 
    int numeros[busquedas];

    for(int i=0; i<busquedas;i++){
        cout<<"Ingrese el numero a buscar: ";
        cin>>numeros[i];
    }

    cout<<endl<<"---busqSecuencial---"<<endl;
    for(int i=0; i<busquedas;i++){
        int result=busqSecuencial(vect5, numeros[i]);
        cout<<"El numero "<<numeros[i]<<" se encuentra en la posicion: "<<result<<endl;
    }
    

    ordenaIntercambio(vect5);
    cout<<endl<<"Vector ordenado:"<<endl;
    printVector(vect5);

    cout<<endl<<"---busqBinaria---"<<endl;
    for(int i=0; i<busquedas;i++){
        int result=busqBinaria(vect5, numeros[i]);
        cout<<"El numero "<<numeros[i]<<" se encuentra en la posicion: "<<result<<endl;
    }

    return 0;
}