/*
    Act 5.1 - Implementación individual de operaciones sobre conjuntos
    Autor:
        * Brandon Josué Magaña Mendoza A01640162
    Programa que implementa una tabla de dispersión que incluye  
    2 técnicas de hashing para el manejo de colisiones.

    Métodos:
        * quadratic(Set &set, vector<int> data)
        * chain(Set &set, vector<int> data)
*/

#include <bits/stdc++.h>

using namespace std;

class Node {
    //Clase auxiliar nodo para la creación de listas 
    //ligadas en caso de colisiones
    public:
        // Entero que representa la información en ese nodo
        int data;
        //Puntero de tipo nodo que apunta al nodo siguiente en la lista ligada
        Node* next;
        
        /*
            Función Constructor de clase Node
            Argumentos:
                * data -> int:Entero que representa la información en ese nodo
            Return:
                * No Hay
            Complejidad:
                * O(1) Constante
        */
        Node(int data){
            this->data = data;
            this->next = NULL;
        }
};
    
class Set{

    public:
        // Vector de nodos para representar una tabla de dispersión
        // que maneja colisiones por encadenamiento
        vector<Node*> set_chainning = vector<Node*>(11); 
        // Vector de enteros para representar una tabla de dispersión 
        // que maneja colisiones mediante sondeo cuadratico 
        vector<int> set_quadratic = vector<int>(11);

        /*
            Método void que inserta un elemento a la tabla de dispersión
            utilizando manejo de colisiones por encadenamiento
            Argumentos:
                * insert -> int : entero que representa el elemento a insertar
            Return:
                * No hay
            Complejidad:
                * O(n) lineal
        */
        void insert_chainning(int insert){
            int index = insert % 11; 
            Node* insertedValue= new Node(insert);
            
            if(!set_chainning[index]) {
                set_chainning[index] = insertedValue; 
                return;
            }
            if(!searchChainedSet(set_chainning[index],insert))
                chainedColition(set_chainning[index],insertedValue);
        }
        
        /*
            Método void que imprime la lista de dispersión que utiliza
            encadenamiento para las colisiones.
            Argumentos:
                * No hay
            Return: 
                * No hay
            Complejidad:
                * O(n)
        */
        void printChainedSet(){
            for(auto node : set_chainning ){
                printLinkedList(node);
            }
        }
        
        /*
            Método booleano que identifica si un valor se encuentra 
            dentro de la tabla de dispersión.
            Argumentos: 
                * head -> Node: Nodo que representa el primer 
                                valor de la lista ligada
                * key -> int: entero que representa el valor a buscar
            Return:
                * true si el valor se encuentra en la lista
                * false si el valor no se encuentra en la lista
            Complejidad:
                O(n) lineal
            
        */
        bool searchChainedSet(Node* head, int key){
            Node* current = head;
            while(current){
                if(current->data == key)
                    return true;
                current = current->next;
            }
            return false;
        }

        /*
            Método void que inserta un elemento a la tabla de dispersión
            utilizando manejo de colisiones por sondeo cuadrático
            Argumentos:
                * insert -> int : entero que representa el elemento a insertar
            Return:
                * No hay
            Complejidad:
                * O(n) lineal
        */
        void insertQuadratic(int insert){
            if(searchQuadraticSet(insert)) return;
            int index = insert%11; // HashFunction
            if (!set_quadratic[index])
            	set_quadratic[index] = insert;
        	else
              	QuadraticColition(index,insert);
        }

        /*
            Método void que imprime la lista de dispersión que utiliza
            sondeo cuadrático para las colisiones.
            Argumentos:
                * No hay
            Return: 
                * No hay
            Complejidad:
                * O(n)
        */
        void printQuadraticSet(){
            cout<<" ";
            for(int i = 0; i<11; i++){
              cout<<set_quadratic[i]<<" ";
            }
            cout<<"\n";
        }
        
        /*
            Método booleano que identifica si un valor se encuentra 
            dentro de la tabla de dispersión.
            Argumentos: 
                * key -> int: entero que representa el valor a buscar
            Return:
                * true si el valor se encuentra en la lista
                * false si el valor no se encuentra en la lista
            Complejidad:
                O(n) lineal
            
        */
        bool searchQuadraticSet(int key){
            for(int i : set_quadratic){
                if(i == key){
                    return true;
                }
            }
            return false;
        }
        
    private: 
        /*
            Método que realiza las operaciones para agregar un elemento
            en caso de colisión mediante encadenamiento.
            Argumentos:
                * head -> Node : representa el inicio de la lista
                * insertedValue -> Node : representa el nodo con el
                                          valor a insertar 
            Return:
                * No hay
            Complejidad:
                O(n) lineal
        */
        void chainedColition(Node* head, Node* insertedValue){
            Node* current = head;
            while(current->next){
                current = current->next; 
            } 
            current->next = insertedValue; 
            return;
        }

        /*
            Método que imprime los valores dentro de una lista ligada
            Argumentos:
                * head -> Node : representa el primer nodo 
                                 de una lista ligada
            Return:
                * No hay
            Complejidad:
                * O(n) lineal
        */
        void printLinkedList(Node* head){
            if(!head){
                return;
            }
            cout<<" ";
            Node* current=head;
            while(current){
                cout<<current->data<<"->";
                current=current->next;
            }
            cout<<endl;
        }

        /*
            Método que realiza las operaciones para agregar un elemento
            en caso de colisión mediante sondeo cuadrático.
            Argumentos:
                * index -> int : indice donde se produjo la colisión
                * insert -> int : valor a insertar 
            Return:
                * No hay
            Complejidad:
                O(n) lineal
        */
        void QuadraticColition(int index, int insert){
            int newIndex;
            for(int i = 0; i<11;i++){
                newIndex = (index + (int)pow(i,2))%11;
                if(!set_quadratic[newIndex]){
                    set_quadratic[newIndex]=insert;
                    return;
                }
            }
        }     
}; 

/*
    Función que añade una lista de valores dentro 
    de una tabla de dispersión mediante encadenamiento
    Argumentos:
        * &hash -> Set : tabla de dispersión donde 
                         se almacenarán los valores
        * toChain -> vector<int> : vector con los valores a insertar
    Return:
        * No hay
    Complejidad:
        * O(n) lineal
*/
void chain(Set &hash, vector<int> toChain){
    for(int i : toChain){
        hash.insert_chainning(i);
    }
}

/*
    Función que añade una lista de valores dentro 
    de una tabla de dispersión mediante sondeo cuadrático
    Argumentos:
        * &hash -> Set : tabla de dispersión donde 
                         se almacenarán los valores
        * toQuadratic -> vector<int> : vector con los valores a insertar
    Return:
        * No hay
    Complejidad:
        * O(n) lineal
*/
void quadratic(Set &hash, vector<int> toQuadratic){
    for(int i : toQuadratic){
        hash.insertQuadratic(i);
    }
}

/*
    Función que imprime los valores dentro de un vector
    Argumentos:
        * vect -> vector<int> : lista de enteros a imprimir
    Return:
        * No hay
    Complejidad:
        * O(n) lineal
*/
void printVector(vector<int> vect){
    cout<<" ";
    for(int element : vect){
        cout<<element<<" ";
    }
    cout<<endl<<endl;
}

int main() {
    //Casos Prueba
    cout<<" ------------------"<<endl;
    cout<<" | Caso Prueba #1 |"<<endl;
    cout<<" ------------------"<<endl;
    
    //Creación de objeto tipo Set
    Set s1;
    
    //Creación de vector de valores a insertar
    vector<int> prueba1{50, 700, 76, 85, 92, 73, 101};
    
    //Impresión por pantalla de valores a insertar
    cout<<" Lista de elementos a insertar:"<<endl;
    printVector(prueba1);
    
    //Tabla de dispersión utilizando encadenamiento
    chain(s1,prueba1);
    cout<<" Tabla de dispersion utilizando"<<
          "encadenamiento para colisiones:"<<endl;
    s1.printChainedSet();
    cout<<endl;
    
    //Tabla de dispersión utilizando sondeo cuadrático
    quadratic(s1,prueba1);
    cout<<" Tabla de dispersion utilizando"<<
          "sondeo cuadratico para colisiones:"<<endl;
    s1.printQuadraticSet();
    cout<<endl;
    
    cout<<" ------------------"<<endl;
    cout<<" | Caso Prueba #2 |"<<endl;
    cout<<" ------------------"<<endl;
    
    //Creación de objeto tipo Set
    Set s2;
    
    //Creación de vector de valores a insertar
    vector<int> prueba2{541, 73, 7, 88, 115, 341, 23,14};
    
    //Impresión por pantalla de valores a insertar
    cout<<" Lista de elementos a insertar:"<<endl;
    printVector(prueba2);
    
    //Tabla de dispersión utilizando encadenamiento
    chain(s2,prueba2);
    cout<<" Tabla de dispersion utilizando"<<
          "encadenamiento para colisiones:"<<endl;
    s2.printChainedSet();
    cout<<endl;
    
    //Tabla de dispersión utilizando sondeo cuadrático
    quadratic(s2,prueba2);
    cout<<" Tabla de dispersion utilizando"<<
          "sondeo cuadratico para colisiones:"<<endl;
    s2.printQuadraticSet();
    cout<<endl;

    cout<<" ------------------"<<endl;
    cout<<" | Caso Prueba #3 |"<<endl;
    cout<<" ------------------"<<endl;
    
    //Creación de objeto tipo Set
    Set s3;
    
    //Creación de vector de valores a insertar
    vector<int> prueba3{68, 33, 92, 13, 16, 156, 201, 114, 10, 41, 23};
    
    //Impresión por pantalla de valores a insertar
    cout<<" Lista de elementos a insertar:"<<endl;
    printVector(prueba3);
    
    //Tabla de dispersión utilizando encadenamiento
    chain(s3,prueba3);
    cout<<" Tabla de dispersion utilizando"<<
          "encadenamiento para colisiones:"<<endl;
    s3.printChainedSet();
    cout<<endl;
    
    //Tabla de dispersión utilizando sondeo cuadrático
    quadratic(s3,prueba3);
    cout<<" Tabla de dispersion utilizando"<<
          "sondeo cuadratico para colisiones:"<<endl;
    s3.printQuadraticSet();
    cout<<endl;

    cout<<" ------------------"<<endl;
    cout<<" | Caso Prueba #4 |"<<endl;
    cout<<" ------------------"<<endl;
    
    //Creación de objeto tipo Set
    Set s4;
    
    //Creación de vector de valores a insertar
    vector<int> prueba4{86, 832, 29, 31, 61, 565, 120, 141, 1, 94, 69};
    
    //Impresión por pantalla de valores a insertar
    cout<<" Lista de elementos a insertar:"<<endl;
    printVector(prueba4);
    
    //Tabla de dispersión utilizando encadenamiento
    chain(s4,prueba4);
    cout<<" Tabla de dispersion utilizando"<<
          "encadenamiento para colisiones:"<<endl;
    s4.printChainedSet();
    cout<<endl;
    
    //Tabla de dispersión utilizando sondeo cuadrático
    quadratic(s4,prueba4);
    cout<<" Tabla de dispersion utilizando"<<
          "sondeo cuadratico para colisiones:"<<endl;
    s4.printQuadraticSet();
    cout<<endl;
}
