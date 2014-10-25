#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include "GraphAndDijkstra.h"
#include "OpenFile.h"
#include "GeneticA.h"
using namespace std;

double fittness(gTruck currentTruck, int nNodes, int* nodes_)
{
    double fit;
    for(int i = 0; i < nNodes; i++)
    {

    }
    return fit;

}


int main()
{
    clock_t start;

    FILE* outputFile = fopen("outFile", "w");

    //----read File --------
    ReadFile();
    InitVars(gTruckCnt, _LENGTH);


    start = clock();
    calculateEveryDistance();
    printf("Time of execution: %d ms", (clock() - start));


    for(int cnter = 0; cnter < _LENGTH; cnter++)
    {
        fprintf(outputFile,"--------%d-------\n", cnter);
        for(int i = 0; i<_LENGTH; i++) fprintf(outputFile,"%d ", nodes[0][i][cnter]);
        fprintf(outputFile,"\n");
        for(int i = 0; i<_LENGTH; i++) fprintf(outputFile,"%d ", nodes[1][i][cnter]);
        fprintf(outputFile,"\n");

    }
    //getchar();


    return 0;
}
