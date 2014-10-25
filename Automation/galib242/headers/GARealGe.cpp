// $Header: /usr/people/mbwall/src/galib/ga/RCS/GARealGenome.C,v 1.2 1996/11/13 16:53:57 mbwall Exp mbwall $
/* ----------------------------------------------------------------------------
  real.C
  mbwall 11nov95
  Copyright (c) 1995-1996 Massachusetts Institute of Technology
                          all rights reserved

 DESCRIPTION:
   Source file for the real number specialization of the array genome.

 MODIFICATIONS:
---------------------------------------------------------------------------- */
#include "GARealGe.h"

const char * 
GA1DArrayAlleleGenome<float>::className() const {return "GARealGenome";}
int GA1DArrayAlleleGenome<float>::classID() const {return GAID::FloatGenome;}

GA1DArrayAlleleGenome<float>::
GA1DArrayAlleleGenome(unsigned int length, const GAAlleleSet<float> & s,
		      GAGenome::Evaluator f, void * u) :
GA1DArrayGenome<float>(length, f, u){
  naset = 1;
  aset = new GAAlleleSet<float>[1];
  aset[0] = s;

  initializer(DEFAULT_REAL_INITIALIZER);
  mutator(DEFAULT_REAL_MUTATOR);
  comparator(DEFAULT_REAL_COMPARATOR);
  crossover(DEFAULT_REAL_CROSSOVER);
}

GA1DArrayAlleleGenome<float>::
GA1DArrayAlleleGenome(const GAAlleleSetArray<float> & sa,
		      GAGenome::Evaluator f, void * u) :
GA1DArrayGenome<float>(sa.size(), f, u){
  naset = sa.size();
  aset = new GAAlleleSet<float>[naset];
  for(int i=0; i<naset; i++)
    aset[i] = sa.set(i);

  initializer(DEFAULT_REAL_INITIALIZER);
  mutator(DEFAULT_REAL_MUTATOR);
  comparator(DEFAULT_REAL_COMPARATOR);
  crossover(DEFAULT_REAL_CROSSOVER);
}

GA1DArrayAlleleGenome<float>::~GA1DArrayAlleleGenome(){
  delete [] aset;
}



#ifndef NO_STREAMS
// The read specialization takes in each number and stuffs it into the array.
int
GA1DArrayAlleleGenome<float>::read(istream & is) {
  unsigned int i=0;
  float val;
  do{
    is >> val;
    if(!is.fail()) gene(i++, val);
  } while(!is.fail() && !is.eof() && i < nx);

  if(is.eof() && i < nx){
    GAErr(GA_LOC, className(), "read", gaErrUnexpectedEOF);
    is.clear(ios::badbit | is.rdstate());
    return 1;
  }
  return 0;
}

// No need to specialize the write method.
#endif







// We must also specialize the allele set so that the alleles are handled
// properly.
float
GAAlleleSet<float>::allele() const {
  if(core->type == GAAllele::ENUMERATED)
    return core->a[GARandomInt(0, core->sz-1)];
  else if(core->type == GAAllele::DISCRETIZED){
    float n = (core->a[1] - core->a[0])/core->a[2];
    return core->a[0] + GARandomInt(0,(int)n)*core->a[2];
  }
  else{
    return GARandomFloat(core->a[0], core->a[1]);
  }
}

float
GAAlleleSet<float>::allele(unsigned int i) const {
  if(core->type == GAAllele::ENUMERATED)
    return core->a[i % core->sz];
  else if(core->type == GAAllele::DISCRETIZED){
    float n = (core->a[1] - core->a[0])/core->a[2];
    if(i > n) i = (int)n;
    return core->a[0] + i*core->a[2];
  }
  else{
    GAErr(GA_LOC, "GAAlleleSet", "allele", gaErrNoAlleleIndex);
    return core->a[0];
  }
}







/* ----------------------------------------------------------------------------
   Operator specializations
---------------------------------------------------------------------------- */
// The Gaussian mutator picks a new value based on a Gaussian distribution
// around the current value.  We respect the bounds (if any).
//*** need to figure out a way to make the stdev other than 1.0 
int 
GARealGaussianMutator(GAGenome& g, float pmut){
  GA1DArrayAlleleGenome<float> &child=(GA1DArrayAlleleGenome<float> &)g;
  register int n, i;
  if(pmut <= 0.0) return(0);

  float nMut = pmut * (float)(child.length());
  int length = child.length()-1;
  if(nMut < 1.0){		// we have to do a flip test on each element
    nMut = 0;
    for(i=length; i>=0; i--){
      float value = child.gene(i);
      if(GAFlipCoin(pmut)){
	if(child.alleleset(i).type() == GAAllele::ENUMERATED ||
	   child.alleleset(i).type() == GAAllele::DISCRETIZED)
	  value = child.alleleset(i).allele();
	else if(child.alleleset(i).type() == GAAllele::BOUNDED){
	  value += GAUnitGaussian();
	  value = GAMax(child.alleleset(i).lower(), value);
	  value = GAMin(child.alleleset(i).upper(), value);
	}
	child.gene(i, value);
	nMut++;
      }
    }
  }
  else{				// only mutate the ones we need to
    for(n=1; n<nMut; n++){
      int idx = GARandomInt(0,length);
      float value = child.gene(idx);
      if(child.alleleset(idx).type() == GAAllele::ENUMERATED ||
	 child.alleleset(idx).type() == GAAllele::DISCRETIZED)
	value = child.alleleset(idx).allele();
      else if(child.alleleset(idx).type() == GAAllele::BOUNDED){
	value += GAUnitGaussian();
	value = GAMax(child.alleleset(idx).lower(), value);
	value = GAMin(child.alleleset(idx).upper(), value);
      }
      child.gene(idx, value);
    }
  }
  return((int)nMut);
}


// Arithmetic crossover generates a new value that is the average of the parent
// values.  Note that this means both children in a sexual crossover will be
// identical.  If parents are not the same length, the extra elements are not
// set!  You might want to add some noise to this so that both children are not
// the same...
int 
GARealArithmeticCrossover(const GAGenome& p1, const GAGenome& p2,
			  GAGenome* c1, GAGenome* c2) {
  GA1DArrayGenome<float> &mom=(GA1DArrayGenome<float> &)p1;
  GA1DArrayGenome<float> &dad=(GA1DArrayGenome<float> &)p2;

  int n=0;

  if(c1 && c2){
    GA1DArrayGenome<float> &sis=(GA1DArrayGenome<float> &)*c1;
    GA1DArrayGenome<float> &bro=(GA1DArrayGenome<float> &)*c2;

    int len = GAMax(mom.length(), dad.length());
    for(int i=0; i<len; i++) {
      sis.gene(i, 0.5 * (mom.gene(i) + dad.gene(i)));
      bro.gene(i, 0.5 * (mom.gene(i) + dad.gene(i)));
    }
    n = 2;
  }
  else if(c1 || c2){
    GA1DArrayGenome<float> &sis = 
      (c1 ? (GA1DArrayGenome<float> &)*c1 : (GA1DArrayGenome<float> &)*c2);

    int len = GAMax(mom.length(), dad.length());
    for(int i=0; i<len; i++) {
      sis.gene(i, 0.5 * (mom.gene(i) + dad.gene(i)));
    }
    n = 1;
  }

  return n;
}


// Blend crossover generates a new value based on the interval between parents.
// We generate a uniform distribution based on the distance between parent
// values, then choose the child value based upon that distribution.
int 
GARealBlendCrossover(const GAGenome& p1, const GAGenome& p2,
		     GAGenome* c1, GAGenome* c2) {
  GA1DArrayGenome<float> &mom=(GA1DArrayGenome<float> &)p1;
  GA1DArrayGenome<float> &dad=(GA1DArrayGenome<float> &)p2;

  int n=0;

  if(c1 && c2){
    GA1DArrayGenome<float> &sis=(GA1DArrayGenome<float> &)*c1;
    GA1DArrayGenome<float> &bro=(GA1DArrayGenome<float> &)*c2;

    int len = GAMax(mom.length(), dad.length());
    for(int i=0; i<len; i++) {
      float dist = 0;
      if(mom.gene(i) > dad.gene(i)) 
	dist = mom.gene(i) - dad.gene(i);
      else 
	dist = dad.gene(i) - mom.gene(i);
      float lo = (GAMin(mom.gene(i), dad.gene(i))) - 0.5*dist;
      float hi = (GAMax(mom.gene(i), dad.gene(i))) + 0.5*dist;
      sis.gene(i, GARandomFloat(lo, hi));
      bro.gene(i, GARandomFloat(lo, hi));
    }
    n = 2;
  }
  else if(c1 || c2){
    GA1DArrayGenome<float> &sis = 
      (c1 ? (GA1DArrayGenome<float> &)*c1 : (GA1DArrayGenome<float> &)*c2);

    int len = GAMax(mom.length(), dad.length());
    for(int i=0; i<len; i++) {
      float dist = 0;
      if(mom.gene(i) > dad.gene(i)) 
	dist = mom.gene(i) - dad.gene(i);
      else 
	dist = dad.gene(i) - mom.gene(i);
      float lo = (GAMin(mom.gene(i), dad.gene(i))) - 0.5*dist;
      float hi = (GAMax(mom.gene(i), dad.gene(i))) + 0.5*dist;
      sis.gene(i, GARandomFloat(lo, hi));
    }
    n = 1;
  }

  return n;
}


// These must be included _after_ the instantiations because some compilers get
// all wigged out about the declaration/specialization order.  Note that some
// compilers require a syntax different than others when forcing the 
// instantiation (i.e. GNU wants the 'template class', borland does not).
#ifdef NO_AUTO_INST
#include "GAAllele.cpp"
#include "GA1DArra.cpp"

#if defined(__GNUG__)
template class GAAlleleSet<float>;
template class GAAlleleSetCore<float>;
template class GAAlleleSetArray<float>;

template class GAArray<float>;
template class GA1DArrayGenome<float>;
template class GA1DArrayAlleleGenome<float>;
#else
GAAlleleSet<float>;
GAAlleleSetCore<float>;
GAAlleleSetArray<float>;

GAArray<float>;
GA1DArrayGenome<float>;
GA1DArrayAlleleGenome<float>;
#endif
#endif

