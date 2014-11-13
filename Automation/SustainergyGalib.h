#include <vector>
#include <ctime>
#define _INITIAL_POPULATION_SIZE 5
#define _MORTALITY 2
#define _MUTATION_PROBABILITY 10
using namespace std;

typedef struct
{
    int GbinIndex[_LENGTH + 1];
    double FittnessScore;
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

        Population.push_back(CurrentGenome);

    }
    return;
}
/*
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
*/

genome MixGenes(genome first, genome second, int crossOverPnt){
    genome result;
    for(int i = 0; i < _LENGTH; i++)
        result.GbinIndex[i] = first.GbinIndex[i];
    for(int i = 0; i < crossOverPnt; i++){
        int tmp = result.GbinIndex[i];
        result.GbinIndex[i] = second.GbinIndex[i];
        for(int y = i + 1; y < _LENGTH; y++)
            if(result.GbinIndex[y] == result.GbinIndex[i]){
                result.GbinIndex[y] = tmp;
                break;
            }


    }
    return result;

}

void CrossOverPMX(genome Mother, genome Father)
{
    genome son, daughter;
    int crossOverPoint = rand() % _LENGTH;
    cout << "Cross pnt: " << crossOverPoint << endl;
    son = MixGenes(Father, Mother, crossOverPoint);
    daughter = MixGenes(Mother, Father, crossOverPoint);
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
bool compare(const genome &a, const genome &b){ return a.FittnessScore < b.FittnessScore;}

void processGeneration(){
    for(int i = 0; i < Population.size(); i++)
        Population[i].FittnessScore = fittness(Population[i]);
    std::sort(Population.begin(), Population.end(), compare);
    for(int i = Population.size() - 1; i>=Population.size()-_MORTALITY; i--){
        Population.pop_back();
    }
    for(int i = 0; i < _MORTALITY / 2; i++){
        int rand1 = rand() % Population.size();
        int rand2;
        for(rand2 = rand() % Population.size(); rand2==rand1; rand2 = rand() % Population.size());
        CrossOverPMX(Population[rand1], Population[rand2]);

    }

    //TODO if not diverse enough change this!!! (or include new animals)
    for(int i = _MORTALITY; i < Population.size(); i++){
        if(rand() % 100 < _MUTATION_PROBABILITY) Mutate(&Population[i]);
    }
    return;
}

