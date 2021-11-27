/*
    Act 4.2 - Grafos: Algoritmos complementarios
    Autor:
        * Brandon Josué Magaña Mendoza A01640162
        Programa que implementa un grafo y determina si es o no cíclico.
        Métodos:
            * loadGraph(int n, int m, AdjacentList &list);
            * isTree()
            * printGraph()
*/
#include <bits/stdc++.h>

using namespace std;

class AdjacentList{
    //Clase auxiliar que cuenta con métodos estáticos para generar una lista de adyacencia
    private:
        /*
            Método estático void de tipo privado que imprime los valores dentro de un vector
            Argumentos:
                values -> vector<int>: representa los valores dentro de la lista de adyacencia de un vertice
            Return:
                No hay
            Complejidad:
                O(n) Lineal
        */
        static void printValues(vector<int> values){
            for(int &it : values)
                cout<< it <<" ";
            cout<<endl;
        }
    
    public:
        /*
            Método estático void que imprime todos los valores dentro de una lista de adyacencia
            Argumentos:
                * listaAdyacencia -> map<int, vector<int>> : representa una lista de adyacencia
            Return:
                * No Hay
            Complejidad:
                *O(n+ m)
        */
        static void printLista(map<int, vector<int>> listaAdyacencia){
            for(map<int, vector<int>>::iterator it=listaAdyacencia.begin(); 
            it!=listaAdyacencia.end();it++){
                cout<<" "<<it->first<< "-> ";
                printValues(it->second);
            }
        }

        /*
            Método estático de tipo void que agrega un vertice a una lista de adyacencia
            Argumentos:
                * listaAdyacencia -> map<int, vector<int>> : representa una lista de adyacencia
                * vertex -> int : representa un vertice en la lista de adyacencia
            Return:
                * No Hay
            Complejidad:
                * O(1) Constante
        */
        static void addVertex(map<int, vector<int>> &adjacentList,int vertex){
            vector<int> emptyvector={};
            adjacentList.insert({vertex,emptyvector});
        }

        /*
            Método estático void que agrega una arista a un determinado vertice
            Argumentos:
                * adjacentList -> map<int, vector<int>> : representa una lista de adyacencia
                * origen -> int : representa el vertice origen de la arista
                * destino -> int: representa el vertice destino de la arista
            Return:
                * No Hay
            Complejidad:
                * O(1) Constante
        */
        static void addEdge(map<int, vector<int>> &adjacentList,int origen, int destino){
            if(adjacentList.find(origen) != adjacentList.end())
                adjacentList[origen].push_back(destino);
        }

        /*
            Método estático void que agrega una lista de aristas a un determinado vertice
            Argumentos:
                * adjacentList -> map<int, vector<int>> : representa una lista de adyacencia
                * origen -> int : representa el vertice origen de la arista
                * destinos -> vector<int>: representa una lista de vertices destino de las aristas
            Return:
                * No Hay
            Complejidad:
                * O(n) lineal
        */
        static void addEdge(map<int, vector<int>> &adjacentList,int origen, vector<int> destinos){
            if(adjacentList.find(origen) != adjacentList.end()){
                for(int destino : destinos){
                    addEdge(adjacentList, origen, destino);
                }
            }
        }

        /*
            Método estático int que regresa el número de aristas en una lista de adyacencia
            Argumentos:
                * &adjacentList -> map<int, vector<int>> : representa una lista de adyacencia
            Return:
                * int : que representa el numero de aristas dentro de la lista de adyacencia
            Complejidad:
                * O(n) lineal
        */
        static int countEdges(map<int, vector<int>> &adjacentList){
            map<int, vector<int>>::iterator it;
            int edges=0;
            for(it = adjacentList.begin(); it != adjacentList.end(); it++){
                edges += it->second.size();
            }
            return edges;
        }

        /*    
            Método estático int que regresa el número de vertices en una lista de adyacencia
            Argumentos:
                * &adjacentList -> map<int, vector<int>> : representa una lista de adyacencia
            Return:
                * int : que representa el numero de vertices dentro de la lista de adyacencia
            Complejidad:
                * O(1) constante
        */
        static int countVertexs(map<int, vector<int>> &adjacentList){
            return adjacentList.size();
        }
};

class Grafo{

    public:
        //Mapa que repreresenta los vertices del grafo y sus aristas
        map<int, vector<int>> adjacentList;
        //Entero que representa el número de vertices ene el grafo
        int vertex;
        //Entero que representa el número de aristas en el grafo
        int edges;
        //Vector booleano que auxilia a la detección de ciclos en un grafo
        vector<bool> recursive;
        //Vector booleano que representa los vertices que han sido visitados 
        //para la detección de ciclos en el grafo
        vector<bool> visited;

        /*
            Método void que Inicializa los atributos de un grafo.
            Argumentos:
                * n -> int: representa el número de vertices del grafo
                * m -> int: representa el número de aristas del grafo
                * & lista -> map<int, vector<int>>: valor por referencia que 
                             representa al grafo en forma de lista de adyacencia
            Return:
                * No hay
            Complejidad:
                * O(1) constante
        */
        void loadGraph(int n, int m, map<int, vector<int>> &lista){
            this->vertex=n;
            this->edges=m;
            this->adjacentList=lista;
            this->recursive = vector<bool>(n,false);
            this->visited = vector<bool>(n,false);
        }

        /*
            Método void que despliega la información del grafo:
            número de vertices, aristas y la lista de adyacencia
            Argumentos:
                * No Hay
            Return:
                * No Hay
            Complejidad:
                * O(n + m)
        */
        void printGraph(){
            cout<<" Vertices: "<<vertex<<endl;
            cout<<" Aristas: "<<edges<<endl;
            cout<<" Grafo(representado mediante lista de adyacencia):"<<endl;
            AdjacentList::printLista(this->adjacentList);
            cout<<endl;
        }

        /*
            Método booleano que determina si un grafo es o no cíclico
            Argumentos:
                * No Hay
            Return:
                * true en caso de detectar un ciclo
                * false en caso de no contar con ciclos
            Complejidad:
                * O(n + m)
        */
        bool isTree(){
            for(int i = 0; i<this->vertex; i++){
                if(dfs(i)){
                    return true;
                }
            }
            return false;
        }

        /*
            Método booleano que realiza una busqueda a profundidad por cada arista 
            de un determinado vertice hasta encontrarse con un cíclo
            Argumentos:
                * index -> int: representa un vertice del grafo
            Return:
                * true en caso de detectar un ciclo
                * false en caso de no contar con ciclos
            Complejidad:
                O(n) lineal
            
        */
        bool dfs(int index){
            if(recursive[index]){
                return true;
            }

            if(visited[index]){
                return false;
            }
            
            visited[index]=true;
            recursive[index]=true;
            
            vector<int> neighbors=this->adjacentList[index];
            for(int edge : neighbors){
                if(dfs(edge)){
                    return true;
                }
            }
            
            recursive[index] = false;
            return false;
        }

        
};

int main(){

    cout<<" ----------"<<endl;
    cout<<" | Grafos |"<<endl;
    cout<<" ----------\n"<<endl;

    cout<<" Caso de prueba #1:"<<endl;
    cout<<" ------------------"<<endl;
    //Creación de lista de adyacencia
    map<int, vector<int>> listaAdyacencia1;
    
    //Creación de Vertices
    AdjacentList::addVertex(listaAdyacencia1, 0);
    AdjacentList::addVertex(listaAdyacencia1, 1);
    AdjacentList::addVertex(listaAdyacencia1, 2);    
    AdjacentList::addVertex(listaAdyacencia1, 3);
    AdjacentList::addVertex(listaAdyacencia1, 4);
    AdjacentList::addVertex(listaAdyacencia1, 5);
    
    //Creación de Aristas
    AdjacentList::addEdge(listaAdyacencia1,0, {1,5});
    AdjacentList::addEdge(listaAdyacencia1,1, {2});
    AdjacentList::addEdge(listaAdyacencia1,2, {3});
    AdjacentList::addEdge(listaAdyacencia1,3, {4,5});
    AdjacentList::addEdge(listaAdyacencia1,4, {5});

    //Creación de objeto de tipo grafo
    Grafo grafo;
    
    //Carga de Lista de adyacencia a objeto de tipo grafo
    grafo.loadGraph(AdjacentList::countVertexs(listaAdyacencia1),
                    AdjacentList::countEdges(listaAdyacencia1),
                    listaAdyacencia1);

    //Despliegue de Información del grafo
    cout<<" Informacion del grafo: "<<endl;
    grafo.printGraph();
    //Llamado a función tree para determinar si un grafo es o no un árbol
    cout<<" Es arbol?(0=N / 1=S): "<<grafo.isTree()<<"\n"<<endl;
    
    cout<<" Caso de prueba #2:"<<endl;
    cout<<" ------------------"<<endl;
    //Creación de lista de adyacencia
    map<int, vector<int>> listaAdyacencia2;
    
    //Creación de Vertices
    AdjacentList::addVertex(listaAdyacencia2, 0);
    AdjacentList::addVertex(listaAdyacencia2, 1);
    AdjacentList::addVertex(listaAdyacencia2, 2);    
    AdjacentList::addVertex(listaAdyacencia2, 3);
    AdjacentList::addVertex(listaAdyacencia2, 4);
    AdjacentList::addVertex(listaAdyacencia2, 5);
    
    //Creación de Aristas
    AdjacentList::addEdge(listaAdyacencia2,0, {1});
    AdjacentList::addEdge(listaAdyacencia2,1, {3});
    AdjacentList::addEdge(listaAdyacencia2,2, {1});
    AdjacentList::addEdge(listaAdyacencia2,3, {0,2,4});
    AdjacentList::addEdge(listaAdyacencia2,4, {1,3,5});
    AdjacentList::addEdge(listaAdyacencia2,5, {0});

    //Creación de objeto de tipo grafo
    Grafo grafo2;
    
    //Carga de Lista de adyacencia a objeto de tipo grafo
    grafo2.loadGraph(AdjacentList::countVertexs(listaAdyacencia2),
                     AdjacentList::countEdges(listaAdyacencia2),
                     listaAdyacencia2);

    //Despliegue de Información del grafo
    cout<<" Informacion del grafo: "<<endl;
    grafo2.printGraph();
    //Llamado a función tree para determinar si un grafo es o no un árbol
    cout<<" Es arbol?(0=N / 1=S): "<<grafo2.isTree()<<"\n"<<endl;

    cout<<" Caso de prueba #3:"<<endl;
    cout<<" ------------------"<<endl;
    //Creación de lista de adyacencia
    map<int, vector<int>> listaAdyacencia3;
    
    //Creación de Vertices
    AdjacentList::addVertex(listaAdyacencia3, 0);
    AdjacentList::addVertex(listaAdyacencia3, 1);
    AdjacentList::addVertex(listaAdyacencia3, 2);    
    AdjacentList::addVertex(listaAdyacencia3, 3);
    AdjacentList::addVertex(listaAdyacencia3, 4);
    AdjacentList::addVertex(listaAdyacencia3, 5);
    AdjacentList::addVertex(listaAdyacencia3, 6);
    AdjacentList::addVertex(listaAdyacencia3, 7);
    
    //Creación de Aristas
    AdjacentList::addEdge(listaAdyacencia3,1, {4,6});
    AdjacentList::addEdge(listaAdyacencia3,2, {7});
    AdjacentList::addEdge(listaAdyacencia3,3, {4,7});
    AdjacentList::addEdge(listaAdyacencia3,4, {5});
    AdjacentList::addEdge(listaAdyacencia3,7, {0,5,6});

    //Creación de objeto de tipo grafo
    Grafo grafo3;
    
    //Carga de Lista de adyacencia a objeto de tipo grafo
    grafo3.loadGraph(AdjacentList::countVertexs(listaAdyacencia3),
                     AdjacentList::countEdges(listaAdyacencia3),
                     listaAdyacencia3);

    //Despliegue de Información del grafo
    cout<<" Informacion del grafo: "<<endl;
    grafo3.printGraph();
    //Llamado a función tree para determinar si un grafo es o no un árbol
    cout<<" Es arbol?(0=N / 1=S): "<<grafo3.isTree()<<"\n"<<endl;

    cout<<" Caso de prueba #4:"<<endl;
    cout<<" ------------------"<<endl;
    //Creación de lista de adyacencia
    map<int, vector<int>> listaAdyacencia4;
    
    //Creación de Vertices
    AdjacentList::addVertex(listaAdyacencia4, 0);
    AdjacentList::addVertex(listaAdyacencia4, 1);
    AdjacentList::addVertex(listaAdyacencia4, 2);    
    AdjacentList::addVertex(listaAdyacencia4, 3);
    AdjacentList::addVertex(listaAdyacencia4, 4);
    AdjacentList::addVertex(listaAdyacencia4, 5);
    AdjacentList::addVertex(listaAdyacencia4, 6);
    AdjacentList::addVertex(listaAdyacencia4, 7);
    AdjacentList::addVertex(listaAdyacencia4, 8);
    AdjacentList::addVertex(listaAdyacencia4, 9);
    AdjacentList::addVertex(listaAdyacencia4, 10);
    
    //Creación de Aristas
    AdjacentList::addEdge(listaAdyacencia4,0, {1,5,6});
    AdjacentList::addEdge(listaAdyacencia4,2, {0});
    AdjacentList::addEdge(listaAdyacencia4,3, {0});
    AdjacentList::addEdge(listaAdyacencia4,4, {0});
    AdjacentList::addEdge(listaAdyacencia4,5, {8});
    AdjacentList::addEdge(listaAdyacencia4,6, {0,5});
    AdjacentList::addEdge(listaAdyacencia4,7, {6,8});
    AdjacentList::addEdge(listaAdyacencia4,8, {6,7,9});
    AdjacentList::addEdge(listaAdyacencia4,10, {4});

    //Creación de objeto de tipo grafo
    Grafo grafo4;
    
    //Carga de Lista de adyacencia a objeto de tipo grafo
    grafo4.loadGraph(AdjacentList::countVertexs(listaAdyacencia4),
                     AdjacentList::countEdges(listaAdyacencia4),
                     listaAdyacencia4);

    //Despliegue de Información del grafo
    cout<<" Informacion del grafo: "<<endl;
    grafo4.printGraph();
    //Llamado a función tree para determinar si un grafo es o no un árbol
    cout<<" Es arbol?(0=N / 1=S): "<<grafo4.isTree()<<"\n"<<endl;
}

