/* ----------------------------------------------------------------------------
  randtest.C
  mbwall 27nov95
  Copyright (c) 1995-1996  Massachusetts Institute of Technology

 DESCRIPTION:
   Program to test the random number generator in GAlib.  Handy for debugging.
---------------------------------------------------------------------------- */
#include <stdio.h>
#include <iostream.h>
#include <string.h>
#include "garandom.h"

int
main(int argc, char **argv)
{
  cout << "This program checks the random number generators in GAlib.\n";
  cout << "These are not rigorous statistical tests, but they should\n";
  cout << "give you a quick indication of whether or not the library is\n";
  cout << "working properly.  Command-line options include:\n\n";
  cout << "  hist   - do the histogram tests.  Histograms should be nearly\n";
  cout << "           flat, i.e. each number has an equal chance of being\n";
  cout << "           chosen.\n";
  cout << "  bnds   - do the bounds tests.  All numbers generated should\n";
  cout << "           be within the limits specified in the test.\n";
  cout << "  seed n - specify the seed number to use for the RNG.  You\n";
  cout << "           should get the same results every time if you specify\n";
  cout << "           the same seed every time.  A seed of 0 tells the lib\n";
  cout << "           to pick its own seed based upon the current time.\n";
  cout << "\n"; 
  cout.flush();

  static const int HIST_SIZE=501;
  static const int NFLIPS=10000;
  static const long int NUM_CHECKS=1000000L;
  int i, j, histogram[HIST_SIZE];
  double counter, mean;

  int dohist = 0;
  int dobnds = 0;
  int domeans = 1;
  int seed = 0;

  for(i=1; i<argc; i++){
    if(strcmp("hist", argv[i]) == 0){
      dohist = 1;
    }
    else if(strcmp("bnds", argv[i]) == 0){
      dobnds = 1;
    }
    else if(strcmp("seed", argv[i]) == 0){
      seed = atoi(argv[++i]);
    }
  }

// Tell us which RNG we're using...

  cout << "Using the ";

#if defined(USE_RAN1)
  cout << " RAN1 ";
#endif
#if defined(USE_RAN2)
  cout << " RAN2 ";
#endif
#if defined(USE_RAN3)
  cout << " RAN3 ";
#endif
#if defined(USE_RAND)
  cout << " RAND ";
#endif
#if defined(USE_RANDOM)
  cout << " RANDOM ";
#endif
#if defined(USE_RAND48)
  cout << " RAND48 ";
#endif

  cout << " random number generator (RNG).\n";

// initialize the RNG by calling the seed routine with our seed

  GARandomSeed(seed);

// histograms of the tests

  if(dohist) {
    cout << "plotting histograms of calls to random number functions...\n";

    memset(histogram, 0, HIST_SIZE*sizeof(int));
    cout << "\n100 random integers in [0, 1] with GARandomInt():\n";
    for(i=0; i<100; i++)
      histogram[GARandomInt()]++;
    for(i=0; i<=1; i++){
      cout << i << "\t";
      for(j=0; j<histogram[i]; j++)
	cout << ".";
      cout << "\n";
    }
    cout.flush();
    
    memset(histogram, 0, HIST_SIZE*sizeof(int));
    cout << "\n100 random integers in [0, 1] with GARandomInt(0,1):\n";
    for(i=0; i<100; i++)
      histogram[GARandomInt(0,1)]++;
    for(i=0; i<=1; i++){
      cout << i << "\t";
      for(j=0; j<histogram[i]; j++)
	cout << ".";
      cout << "\n";
    }
    cout.flush();
    
    memset(histogram, 0, HIST_SIZE*sizeof(int));
    cout<<"\n10000 random integers in [-20, -10] with GARandomInt(-20,-10):\n";
    for(i=0; i<10000; i++)
      histogram[GARandomInt(-20,-10)+20]++;
    for(i=0; i<=10; i++){
      cout << (i-20) << "\t";
      for(j=0; j<histogram[i]; j++)
	if(j%20 == 0) cout << ".";
      cout << "\n";
    }
    cout.flush();
    
    memset(histogram, 0, HIST_SIZE*sizeof(int));
    cout << "\n300 random integers in [0, 5] with GARandomInt(0,5):\n";
    for(i=0; i<300; i++)
      histogram[GARandomInt(0,5)]++;
    for(i=0; i<=5; i++){
      cout << i << "\t";
      for(j=0; j<histogram[i]; j++)
	cout << ".";
      cout << "\n";
    }
    cout.flush();
    
    memset(histogram, 0, HIST_SIZE*sizeof(int));
    cout << "\n10000 random integers in [0, 100] with GARandomInt(0,100):\n";
    for(i=0; i<10000; i++)
      histogram[GARandomInt(0,100)]++;
    for(i=0; i<=100; i++){
      cout << i << "\t";
      for(j=0; j<histogram[i]; j++)
	if(j%2 == 0) cout << ".";
      cout << "\n";
    }
    cout.flush();
    
    memset(histogram, 0, HIST_SIZE*sizeof(int));
    cout<<"\n10000 random integers in [-10, 100] with GARandomInt(-10,100):\n";
    for(i=0; i<10000; i++)
      histogram[GARandomInt(-10,100)+10]++;
    for(i=0; i<=110; i++){
      cout << (i-10) << "\t";
      for(j=0; j<histogram[i]; j++)
	if(j%2 == 0) cout << ".";
      cout << "\n";
    }
    cout.flush();
  }

// calculate means on various types

  if(domeans) {
    cout << "\ncheck for averages of repeated biased coin tosses...\n";

    counter = 0;
    cout << NFLIPS << " calls to GARandomBit()\t\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomBit();
    cout << counter << " hits (should be about " << 0.5*NFLIPS << ")\n";
    cout.flush();
    
    counter = 0;
    cout << NFLIPS << " calls to GARandomInt()\t\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomInt();
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about 0.5)\n"; cout.flush();
    
    counter = 0;
    cout << NFLIPS << " calls to GARandomInt(0,5)\t\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomInt(0,5);
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about 2.5)\n"; cout.flush();
    
    counter = 0;
    cout << NFLIPS << " calls to GARandomFloat()\t\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomFloat();
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about 0.5)\n"; cout.flush();
    
    counter = 0;
    cout << NFLIPS << " calls to GARandomFloat(0,5)\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomFloat(0,5);
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about 2.5)\n"; cout.flush();
        
    counter = 0;
    cout << NFLIPS << " calls to GARandomFloat(-10,-5)\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomFloat(-10,-5);
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about -7.5)\n"; cout.flush();
        
    counter = 0;
    cout << NFLIPS << " calls to GARandomFloat(-10,10)\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomFloat(-10,10);
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about 0.0)\n"; cout.flush();

    counter = 0;
    cout << NFLIPS << " calls to GARandomDouble()\t\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomDouble();
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about 0.5)\n"; cout.flush();
    
    counter = 0;
    cout << NFLIPS << " calls to GARandomDouble(0,2)\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomDouble(0,2);
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about 1.0)\n"; cout.flush();
    
    counter = 0;
    cout << NFLIPS << " calls to GARandomDouble(0,5)\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomDouble(0,5);
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about 2.5)\n"; cout.flush();
    
    counter = 0;
    cout << NFLIPS << " calls to GARandomDouble(-10,-5)\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomDouble(-10,-5);
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about -7.5)\n"; cout.flush();
        
    counter = 0;
    cout << NFLIPS << " calls to GARandomDouble(-10,10)\t";
    for(i=0; i<NFLIPS; i++)
      counter += GARandomDouble(-10,10);
    mean = counter/(double)NFLIPS;
    cout << mean << " (should be about 0.0)\n"; cout.flush();

    // check means of repeated coin tosses
    
    cout << "\n";
    float ave;
    cout << "[0, 1] with GARandomFloat()...\t\t";
    ave = 0;
    for(i=0; i<50; i++)
      ave += GARandomFloat();
    cout << ave/50 << " ";
    ave = 0;
    for(i=0; i<50; i++)
      ave += GARandomFloat();
    cout << ave/50 << " ";
    ave = 0;
    for(i=0; i<50; i++)
      ave += GARandomFloat();
    cout << ave/50 << "\n";
    cout.flush();
    
    cout << "[0, 1] with GARandomFloat(0,1)...\t";
    ave = 0;
    for(i=0; i<50; i++)
      ave += GARandomFloat(0,1);
    cout << ave/50 << " ";
    ave = 0;
    for(i=0; i<50; i++)
      ave += GARandomFloat(0,1);
    cout << ave/50 << " ";
    ave = 0;
    for(i=0; i<50; i++)
      ave += GARandomFloat(0,1);
    cout << ave/50 << "\n";
    cout.flush();
    
    cout << "[0, 100] with GARandomFloat(0,100)...\t";
    ave = 0;
    for(i=0; i<50; i++)
      ave += GARandomFloat(0,100);
    cout << ave/50 << " ";
    ave = 0;
    for(i=0; i<50; i++)
      ave += GARandomFloat(0,100);
    cout << ave/50 << " ";
    ave = 0;
    for(i=0; i<50; i++)
      ave += GARandomFloat(0,100);
    cout << ave/50 << "\n";
    cout.flush();
    
    double aved;
    cout << "[0, 1] with GARandomDouble()...\t\t";
    aved = 0;
    for(i=0; i<50; i++)
      aved += GARandomDouble();
    cout << aved/50 << " ";
    aved = 0;
    for(i=0; i<50; i++)
      aved += GARandomDouble();
    cout << aved/50 << " ";
    aved = 0;
    for(i=0; i<50; i++)
      aved += GARandomDouble();
    cout << aved/50 << "\n";
    cout.flush();
    
    cout << "[0, 1] with GARandomDouble(0,1)...\t";
    aved = 0;
    for(i=0; i<50; i++)
      aved += GARandomDouble(0,1);
    cout << aved/50 << " ";
    aved = 0;
    for(i=0; i<50; i++)
      aved += GARandomDouble(0,1);
    cout << aved/50 << " ";
    aved = 0;
    for(i=0; i<50; i++)
      aved += GARandomDouble(0,1);
    cout << aved/50 << "\n";
    cout.flush();
    
    cout << "[0, 100] with GARandomDouble(0,100)...\t";
    aved = 0;
    for(i=0; i<50; i++)
      aved += GARandomDouble(0,100);
    cout << aved/50 << " ";
    aved = 0;
    for(i=0; i<50; i++)
      aved += GARandomDouble(0,100);
    cout << aved/50 << " ";
    aved = 0;
    for(i=0; i<50; i++)
      aved += GARandomDouble(0,100);
    cout << aved/50 << "\n";
    cout.flush();
    
    cout << "\n";
    
    int count;
    cout << "1% coin flip...\t\t";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.01);
    counter = (double)count / (double)i;
    cout << counter << " ";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.01);
    counter = (double)count / (double)i;
    cout << counter << " ";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.01);
    counter = (double)count / (double)i;
    cout << counter << "\n";
    cout.flush();
    
    cout << "25% coin flip...\t";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.25);
    counter = (double)count / (double)i;
    cout << counter << " ";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.25);
    counter = (double)count / (double)i;
    cout << counter << " ";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.25);
    counter = (double)count / (double)i;
    cout << counter << "\n";
    cout.flush();

    cout << "50% coin flip...\t";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.5);
    counter = (double)count / (double)i;
    cout << counter << " ";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.5);
    counter = (double)count / (double)i;
    cout << counter << " ";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.5);
    counter = (double)count / (double)i;
    cout << counter << "\n";
    cout.flush();
    
    cout << "75% coin flip...\t";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.75);
    counter = (double)count / (double)i;
    cout << counter << " ";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.75);
    counter = (double)count / (double)i;
    cout << counter << " ";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.75);
    counter = (double)count / (double)i;
    cout << counter << "\n";
    cout.flush();
    
    cout << "99% coin flip...\t";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.99);
    counter = (double)count / (double)i;
    cout << counter << " ";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.99);
    counter = (double)count / (double)i;
    cout << counter << " ";
    count = 0;
    for(i=0; i<NFLIPS; i++)
      count += GAFlipCoin(0.99);
    counter = (double)count / (double)i;
    cout << counter << "\n";
    cout.flush();
    
    long lcount;
    cout << "\ncalls to GARandomBit (these should yield 50%)...\n";
    lcount = 0;
    for(i=0; i<NFLIPS; i++)
      lcount += GARandomBit();
    counter = (double)lcount / (double)i;
    cout << counter << " ";
    lcount = 0;
    for(i=0; i<NFLIPS; i++)
      lcount += GARandomBit();
    counter = (double)lcount / (double)i;
    cout << counter << " ";
    lcount = 0;
    for(i=0; i<NFLIPS; i++)
      lcount += GARandomBit();
    counter = (double)lcount / (double)i;
    cout << counter << "\n";
    cout.flush();
  }

// check for values outside of bounds

  if(dobnds) {
    cout << "\ncheck for out of bounds...\n";

    long int ii, err;

    int vali, lasti=0;

    cout << "GARandomInt(-10,5) ..."; cout.flush();
    err = 0;
    for(ii=0; ii<NUM_CHECKS; ii++){
      vali = GARandomInt(-10,5);
      if(vali < -10 || vali > 5){ err += 1; lasti = vali; }
    }
    if(err) cout << " " << err << " values out of bounds.\n";
    else cout << "ok\n";
    cout.flush();
    
    cout << "GARandomInt(0,3) ..."; cout.flush();
    err = 0;
    for(ii=0; ii<NUM_CHECKS; ii++){
      vali = GARandomInt(0,3);
      if(vali < 0 || vali > 3){ err += 1; lasti = vali; }
    }
    if(err) cout << " " << err << " values out of bounds.\n";
    else cout << "ok\n";
    cout.flush();
    
    cout << "GARandomInt(200,255) ..."; cout.flush();
    err = 0;
    for(ii=0; ii<NUM_CHECKS; ii++){
      vali = GARandomInt(200,255);
      if(vali < 200 || vali > 255){ err += 1; lasti = vali; }
    }
    if(err) cout << " " << err << " values out of bounds.\n";
    else cout << "ok\n";
    cout.flush();

    float valf, lastf=0.0;

    cout << "GARandomFloat(-10,5) ..."; cout.flush();
    for(ii=0; ii<NUM_CHECKS; ii++){
      valf = GARandomFloat(-10,5);
      if(valf < -10 || valf > 5){ err += 1; lastf = valf; }
    }
    if(err) cout << " " << err << " values out of bounds (" << lastf << ").\n";
    else cout << "ok\n";
    cout.flush();
    
    cout << "GARandomFloat(0,3) ..."; cout.flush();
    err = 0;
    for(ii=0; ii<NUM_CHECKS; ii++){
      valf = GARandomFloat(0,3);
      if(valf < 0 || valf > 3){ err += 1; lastf = valf; }
    }
    if(err) cout << " " << err << " values out of bounds (" << lastf << ").\n";
    else cout << "ok\n";
    cout.flush();
    
    cout << "GARandomFloat(200,255) ..."; cout.flush();
    err = 0;
    for(ii=0; ii<NUM_CHECKS; ii++){
      valf = GARandomFloat(200,255);
      if(valf < 200 || valf > 255){ err += 1; lastf = valf; }
    }
    if(err) cout << " " << err << " values out of bounds (" << lastf << ").\n";
    else cout << "ok\n";
    cout.flush();

    double vald, lastd=0.0;

    cout << "GARandomDouble(-10,5) ..."; cout.flush();
    for(ii=0; ii<NUM_CHECKS; ii++){
      vald = GARandomDouble(-10,5);
      if(vald < -10 || vald > 5){ err += 1; lastd = vald; }
    }
    if(err) cout << " " << err << " values out of bounds (" << lastd << ").\n";
    else cout << "ok\n";
    cout.flush();
    
    cout << "GARandomDouble(0,3) ..."; cout.flush();
    err = 0;
    for(ii=0; ii<NUM_CHECKS; ii++){
      vald = GARandomDouble(0,3);
      if(vald < 0 || vald > 3){ err += 1; lastd = vald; }
    }
    if(err) cout << " " << err << " values out of bounds (" << lastd << ").\n";
    else cout << "ok\n";
    cout.flush();
    
    cout << "GARandomDouble(200,255) ..."; cout.flush();
    err = 0;
    for(ii=0; ii<NUM_CHECKS; ii++){
      vald = GARandomDouble(200,255);
      if(vald < 200 || vald > 255){ err += 1; lastd = vald; }
    }
    if(err) cout << " " << err << " values out of bounds (" << lastd << ").\n";
    else cout << "ok\n";
    cout.flush();
  }

  return 0;
}

