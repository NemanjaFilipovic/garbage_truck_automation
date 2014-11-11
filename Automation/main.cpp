
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

#include <ctime>
#include "GraphAndDijkstra.h"
#include "OpenFile.h"
#include "SustainergyGalib.h"
using namespace std;



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
    CreateInitialPopulation();
    cout << endl << "Masses: ";

    for(int i = 0; i<_LENGTH; i++) cout << gBinArr[i].gCurrent << " ";
    cout << endl;

    cout << "Population: " << endl;

    CrossOverPMX(Population.at(0), Population.at(1));
    for(int i = 0; i < Population.size(); i++){
        cout << "Animal " << i << ": ";
        for(int y = 0; y < _LENGTH; y++) cout << Population[i].GbinIndex[y] << " ";
        cout << endl;
    }
    for(int cnter = 0; cnter < _LENGTH; cnter++)
    {
        fprintf(outputFile,"--------%d-------\n", cnter);
        for(int i = 0; i<_LENGTH; i++) fprintf(outputFile,"%d ", nodes[0][i][cnter]);
        fprintf(outputFile,"\n");
        for(int i = 0; i<_LENGTH; i++) fprintf(outputFile,"%d ", nodes[1][i][cnter]);
        fprintf(outputFile,"\n");

    }
    /*
    for(int i = 0; i< _INITIAL_POPULATION_SIZE; i++){
        fittness(Population[i]);
    }*/
    fclose(outputFile);
    //getchar();


    return 0;
}
