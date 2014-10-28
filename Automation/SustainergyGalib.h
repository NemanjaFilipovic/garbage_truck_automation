#include <vector>

#define _INITIAL_POPULATION_SIZE 5

using namespace std;

typedef struct
{
    int GbinIndex[_LENGTH];
} genome;

vector<genome> Population;


void CreateInitialPopulation()
{
    for(int i = 0; i < _INITIAL_POPULATION_SIZE; i++)
        for(int y = 0; y < _INITIAL_POPULATION_SIZE; y++)
        {
            genome CurrentGenome;
            CurrentGenome.GbinIndex[i] = rand() % _LENGTH;
            Population.push_back(CurrentGenome);

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
    int temp = GenomeToMutate.GbinIndex[FirstPosition];
    GenomeToMutate.GbinIndex[FirstPosition] = GenomeToMutate.GbinIndex[SecondPosition];
    GenomeToMutate.GbinIndex[SecondPosition] = temp;

    return;
}
