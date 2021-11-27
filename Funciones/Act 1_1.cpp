/*
El siguiente código contiene 3 funciones que realizan la suma 
de 1 hasta un número x,con diferente complejidad de tiempo. O()

Autor: Brandon Josué Magaña Mendoza A016460162
Fecha: 17/agosto/2021
*/

#include <iostream>

using namespace std;

//Función SumaRecursiva
//Entrada: entero x
//Salida: entero: suma de 1 a x
//O(n) Lineal
int sumaRecursiva(int x){
    //base
    if (x==1) return 1;
    //inducción
    return sumaRecursiva(x-1)+x; 
    
}

//Función SumaDirecta
//Entrada: entero x
//Salida: entero: suma de 1 a x
//O(1) Constante
int sumaDirecta(int x){
    return (x*(x+1))/2; 
}

//Función Sumalterativa
//Entrada: entero: x
//Salida: entero: suma de 1 a x
//O(n) Lineal
int sumalterativa(int x){
    int suma=0;
    for(int i=1; i<=x;i++){
        suma+=i;
    }
    return suma;
}

int main(){
    cout<<"Caso 1)"<<endl;
    cout<<"Suma hasta: 50"<<endl;
    cout<<"Resultado esperado = 1275"<<endl;
    cout<<"Resultado utilizando Sumalterativa()= "<<sumalterativa(50)<<endl;
    cout<<"Resultado utilizando SumaRecursiva()= "<<sumaRecursiva(50)<<endl;
    cout<<"Resultado utilizando SumaDirecta()= "<<sumaDirecta(50)<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"Caso 2)"<<endl;
    cout<<"Suma hasta: 148"<<endl;
    cout<<"Resultado esperado = 11026"<<endl;
    cout<<"Resultado utilizando Sumalterativa()= "<<sumalterativa(148)<<endl;
    cout<<"Resultado utilizando SumaRecursiva()= "<<sumaRecursiva(148)<<endl;
    cout<<"Resultado utilizando SumaDirecta()= "<<sumaDirecta(148)<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"Caso 3)"<<endl;
    cout<<"Suma hasta: 24"<<endl;
    cout<<"Resultado esperado = 300"<<endl;
    cout<<"Resultado utilizando Sumalterativa()= "<<sumalterativa(24)<<endl;
    cout<<"Resultado utilizando SumaRecursiva()= "<<sumaRecursiva(24)<<endl;
    cout<<"Resultado utilizando SumaDirecta()= "<<sumaDirecta(24)<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"Caso 4)"<<endl;
    cout<<"Suma hasta: 88"<<endl;
    cout<<"Resultado esperado = 3916"<<endl;
    cout<<"Resultado utilizando Sumalterativa()= "<<sumalterativa(88)<<endl;
    cout<<"Resultado utilizando SumaRecursiva()= "<<sumaRecursiva(88)<<endl;
    cout<<"Resultado utilizando SumaDirecta()= "<<sumaDirecta(88)<<endl;
}