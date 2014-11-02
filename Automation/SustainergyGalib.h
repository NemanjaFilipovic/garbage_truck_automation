#include <vector>
#include <ctime>
#define _INITIAL_POPULATION_SIZE 5

using namespace std;

typedef struct
{
    int GbinIndex[_LENGTH + 1];
} genome;

vector<genome> Population;
bool search_(genome g, int element){

    for(int i = 0; i<_LENGTH; i++)
        if(g.GbinIndex[i] == element) return true;
    return false;



}

void CreateInitialPopulation()
{
    srand(time(0));

    for(int i = 0; i < _INITIAL_POPULATION_SIZE; i++)
    {
        genome CurrentGenome;
        for(int cnter = 1; cnter < _LENGTH; cnter++) CurrentGenome.GbinIndex[cnter] = -1;
        CurrentGenome.GbinIndex[0] = 0;
        CurrentGenome.GbinIndex[_LENGTH] = 0;
        for(int y = 1; y < _LENGTH; y++)
        {


            startOfRandomization:
            int tmp = rand() % _LENGTH;

            if(!search_(CurrentGenome, tmp))
            {
                CurrentGenome.GbinIndex[y] = tmp;


            } else{ goto startOfRandomization; cout << "'";};
        }
        for(int s = 0; s <= _LENGTH; s++) cout << CurrentGenome.GbinIndex[s] << " ";
        Population.push_back(CurrentGenome);
        cout << endl;
    }
    return;
}

void CrossOver(genome Mother, genome Father)
{

    genome son, daughter;
    int CrossoverPoint = rand() % _LENGTH;
    for(int i = 0; i<CrossoverPoint; i++)
    {
        son.GbinIndex[i] = Father.GbinIndex[i];
        daughter.GbinIndex[i] = Mother.GbinIndex[i];
    }
    for(int i = CrossoverPoint; i<_LENGTH; i++)
    {
        son.GbinIndex[i] = Mother.GbinIndex[i];
        daughter.GbinIndex[i] = Father.GbinIndex[i];
    }
    Population.push_back(son);
    Population.push_back(daughter);
    return;
}

void Mutate(genome* GenomeToMutate)
{

    int FirstPosition = rand() % _LENGTH;
    int SecondPosition = rand() % _LENGTH;
    int temp = GenomeToMutate->GbinIndex[FirstPosition];
    GenomeToMutate->GbinIndex[FirstPosition] = GenomeToMutate->GbinIndex[SecondPosition];
    GenomeToMutate->GbinIndex[SecondPosition] = temp;

    return;
}

double fittness(genome g)
{
    double fit;
    int prevGBin = 0;
    double distanceTravelled = 0;
    double garbageMass = 0;

    for(int i = 0; i<=_LENGTH; i++){
            distanceTravelled += nodes[0][g.GbinIndex[i]][prevGBin];
            prevGBin = g.GbinIndex[i];
            garbageMass += gBinArr[g.GbinIndex[i]].gCurrent;

    }
    cout << endl << "travelled: " << distanceTravelled << " Mass: " << garbageMass << endl;

    return fit;
}

