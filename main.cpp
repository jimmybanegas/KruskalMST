#include "Test.h"
#include <iostream>
#include "Edge.h"

using namespace std;

map<int,bool> visitados;

bool hasCycle(int** graph, int size, int actual, int padre)
{
    if(visitados[actual])
        return true;

    visitados[actual]=true;

    for(int i=0;i<size;i++)
        if(graph[actual][i]!=-1 && i!= padre)
            if(hasCycle(graph,size,i,actual))
                return true;

    visitados[actual]=false;

    return false;
}

bool hasCycle(int** graph, int size)
{
    for(int i=0;i<size;i++)
        visitados[i]=false;

    for(int i=0;i<size;i++)
    {
        if(hasCycle(graph,size,i,0))
            return true;
    }

    return false;
}

int** initAnswerGraph(int size)
{
    int **answer = new int* [size];
    for(int i=0;i<size;i++)
    {
        answer[i]= new int[size];
        for(int j=0;j<size;j++)
            answer[i][j]=-1;
    }
    return answer;
}

int** getKruskalMST(int** graph, int size, vector<Edge*> edges)
{
    //Inicializar el grafo de respuesta con -1 par empezar a recorrerlo
    int ** answer = initAnswerGraph(size);

    for(int i = 0; i<edges.size();i++)
    {
        //Asignar los valores de el inicio y el destino en la tabla que formamos con el peso de la arista
        answer[edges[i]->source][edges[i]->destination] = edges[i]->weight;
        answer[edges[i]->destination][edges[i]->source] = edges[i]->weight;

        //Mandanos a llamar la funcion para identificar ciclos
        if(hasCycle(answer,size))
        {
            //Solo si tiene ciclos descartamos esa arista, de lo contrario queda como la inicializamos antes
           answer[edges[i]->source][edges[i]->destination] = -1;
           answer[edges[i]->destination][edges[i]->source] = -1;
        }
    }
    return answer;
}

int main ()
{
    test();
    return 0;
}
