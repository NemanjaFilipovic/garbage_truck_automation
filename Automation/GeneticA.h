#include "ga/ga.h"

float Objective(GAGenome&);

void runGA()
{
    unsigned int length = 10;
    GA1DBinaryStringGenome genome(length, &Objective); // create a genome



}

float Objective(GAGenome& g)
{
    GA1DBinaryStringGenome & genome = (GA1DBinaryStringGenome &)g;
    float score=0.0;
    for(int i=0; i<genome.length(); i++)
        score += genome.gene(i);
    return score;


}
