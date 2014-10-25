// $Header: /usr/people/mbwall/src/galib/ga/RCS/gaconfig.h,v 1.1 1996/11/13 01:36:31 mbwall Exp mbwall $
/* ----------------------------------------------------------------------------
  config.h
  mbwall 27jun95
  Copyright (c) 1995-1996 Massachusetts Institute of Technology
                          all rights reserved

 DESCRIPTION:
  Configuration header file for the GA library.  Use this file to set the
parameters that are specific to machine/compiler/operating system.  This file
also contains macros that control which parts of the library will be compiled
and which operators will be the defaults.

 MODIFICATIONS:
---------------------------------------------------------------------------- */
#ifndef _ga_config_h_
#define _ga_config_h_


/* ----------------------------------------------------------------------------
PREPROCESSOR DIRECTIVES

  Here are the preprocessor directives that the library understands.  If you 
are using a makefile, then put these in the line with the DEFINES macro.  For
example, to define the NO_TEMPLATES and BORLAND_INST options then do

       DEFINES = -DNO_TEMPLATES -DBORLAND_INST

In MacOS or DOS, use your development environment's preprocessor directives 
option to set the values.  Beware that if you use the makefile or your 
development environment to do the defines then someone may compile a program
later on that does not use the same defines you used to compile the library.
For best results (ie smallest chance of error), modify this header file rather
than using the makefile or development environment.
  Some of these are already set up for the OSes with which I am familiar.  See
below for the pre-defined sets.


   NO_STREAMS         If you want to compile the library without streams, set
                      this flag.  The library will compile with no stream
                      input or output in any class and no dependencies on the
		      streams library.

   NO_PID             For machines that do not have the getpid() function or
                      the unistd.h header file.

   NO_TEMPLATES       For compilers that do not do templates.  The only type
                      of genome available when you use this is binary 
                      string and any derived classes.  list, tree, and array 
		      all use templates.  You can still use the template code,
		      but you will have to hack it yourself to make it work.

   BORLAND_INST       For compilers that use the Borland instantiation model.
                      These compilers expect all of the template code to be
		      in the header file.  The Cfront model, on the other
                      hand, expects source files with names similar to the
		      header files, but all of the template code does not
		      need to be in the header files.
		    
		      When you define this flag, the source file that 
		      corresponds to the header file is explicitly included
		      at the end of the header file for all headers that
		      contain templates.

   NO_AUTO_INST       For compilers that do not do automatic instantiation
                      (such as g++ version 2.6.8) you will have to force
                      instantiations.  When this flag is defined, GAlib
		      forces an instantiation of all of the template classes
		      that it uses (such as real genome and string genome).

   USE_RAN1
   USE_RAN2
   USE_RAN3
   USE_RAND           
   USE_RANDOM
   USE_RAND48         These specify which random number function to use.  Only
                      one of these may be specified.  You may have to tweak 
		      random.h a bit as well (these functions are not defined 
		      the same way on each platform).  For best results, use
		      ran2 or ran3 (performance is slightly slower than most
		      system RNGs, but you'll get better results).

                      If you want to use another random number generator you
                      must hack random.h directly (see the comments in that
                      file).

   BITBASE            The built-in type to use for bit conversions.  This 
                      should be set to the type of the largest integer that
                      your system supports.  If you have long long int then
                      use it.  If you don't plan to use more than 16 or 32
                      bits to represent your binary-to-decimal mappings then
                      you can use something smaller (long int for example).
                      If you do not set this, GAlib will automatically use
                      the size of a long int.  The bitbase determines the
		      maximum number of bits you can use to represent a
		      decimal number in the binary-to-decimal genomes.

   BITS_IN_WORD       How many bits are in a word?  For most systems, a word is
                      a char and is 8 bits long.

---------------------------------------------------------------------------- */
// Here are the defines needed for some of the compilers/OSes on which I have
// been able to test the GA library.  You may have to remove and/or modify
// these to get things to work on your system.

// If only every compiler were as easy to use and as well maintained as the
// ones from metrowerks...
#if defined(__MWERKS__)
#define NO_AUTO_INST
#define NO_PID
#endif

// Symantec C++ for mac.  This compiler does not handle templates very well, 
// so if you want to use any of the template components of GAlib then you will
// probably have to do some hacking to get things to work.
#if defined(__SC__)
#define NO_PID
#endif

// You may or may not need the BORLAND_INST flag defined when you use a borland
// compiler.  I did not need it when I compiled using version 4.0, but I did
// need it when I compiled with an earlier version (I think it was 3.x but I
// do not remember for certain).
//   Note that the default random number generator when using a borland (or
// any PC compiler, for that matter) is the basic system's RNG.
// I did this because of the hassles of 16- vs 32-bit DOS/Windows rubbish.  If
// you want a better RNG, you can use the others in GAlib, but you'll have to
// do a bit of checking to make sure it works with your DOS/Windows config.
// All of the RNGs work fine under all of the 32-bit OSes I've tried, but they
// don't do so well in a 16-bit OS.
//  Use the randtest example to check GAlib's RNG after you compile everything.
#if defined(__BORLANDC__)
#define NO_PID
#define NO_AUTO_INST
#define USE_RAND		// comment this if you're using a 32-bit OS
//#define BORLAND_INST
#endif

// MicroSoft's Visual C++ programming environment.  You'll get bucketloads of
// warnings from this compiler - it can't figure out that 'float x = 0.0;' is
// a perfectly normal thing to do and, no, we're not losing any data in the
// assignment.
#if defined(_MSC_VER)
#define NO_PID
#define NO_AUTO_INST
#endif

// for g++ 2.6.3 - 2.7.1 (I haven't tested on other versions)
#if defined(__GNUG__)
#define NO_AUTO_INST
#endif














// If no RNG has been selected, use the ran2 generator by default
#if !defined(USE_RAND) && !defined(USE_RANDOM) && \
    !defined(USE_RAND48) && !defined(USE_RAN2) && !defined(USE_RAN3)
#define USE_RAN2
#endif

// This defines how many bits are in a single word on your system.  Most 
// systems have a word length of 8 bits.
#ifndef BITS_IN_WORD
#define BITS_IN_WORD 8
#endif

// Use this to set the maximum number of bits that can be used in binary-to-
// decimal conversions.  You should make this type the largest integer type 
// that your system supports.
#ifndef BITBASE
#define BITBASE long int
#endif




/* ----------------------------------------------------------------------------
SPACE SAVERS and DEFAULT OPERATORS

  These directives determine which operators will be used by default for each
of the objects in GAlib.
  If space is limited, you may want to compile the library with only the parts
that you need (compiling in DOS comes to mind).  Your compiler should do this
automatically for you (ie only use the parts that you use).  If not, then 
comment out the chunks in the files you're not going to use (for example, 
comment out the ordered initializer in the list object).
  To disable a certain type of genome, simply don't compile its source file.
The following directives are defined so that you can trim out the parts of the
genetic algorithm objects that are not in separate files.
---------------------------------------------------------------------------- */
// scaling schemes
#define USE_LINEAR_SCALING           1
#define USE_SIGMA_TRUNC_SCALING      1
#define USE_POWER_LAW_SCALING        1
#define USE_SHARING                  1

// selection schemes
#define USE_RANK_SELECTOR            1
#define USE_ROULETTE_SELECTOR        1
#define USE_TOURNAMENT_SELECTOR      1
#define USE_DS_SELECTOR              1
#define USE_SRS_SELECTOR             1
#define USE_UNIFORM_SELECTOR         1

// These are the compiled-in defaults for various genomes and GA objects
#define DEFAULT_SCALING              GALinearScaling
#define DEFAULT_SELECTOR             GARouletteWheelSelector
#define DEFAULT_TERMINATOR           TerminateUponGeneration

#define DEFAULT_1DBINSTR_INITIALIZER UniformInitializer
#define DEFAULT_1DBINSTR_MUTATOR     FlipMutator
#define DEFAULT_1DBINSTR_COMPARATOR  BitComparator
#define DEFAULT_1DBINSTR_CROSSOVER   OnePointCrossover
#define DEFAULT_2DBINSTR_INITIALIZER UniformInitializer
#define DEFAULT_2DBINSTR_MUTATOR     FlipMutator
#define DEFAULT_2DBINSTR_COMPARATOR  BitComparator
#define DEFAULT_2DBINSTR_CROSSOVER   OnePointCrossover
#define DEFAULT_3DBINSTR_INITIALIZER UniformInitializer
#define DEFAULT_3DBINSTR_MUTATOR     FlipMutator
#define DEFAULT_3DBINSTR_COMPARATOR  BitComparator
#define DEFAULT_3DBINSTR_CROSSOVER   OnePointCrossover

#define DEFAULT_BIN2DEC_ENCODER      GABinaryEncode
#define DEFAULT_BIN2DEC_DECODER      GABinaryDecode
#define DEFAULT_BIN2DEC_COMPARATOR   BitComparator

#define DEFAULT_1DARRAY_INITIALIZER  NoInitializer
#define DEFAULT_1DARRAY_MUTATOR      SwapMutator
#define DEFAULT_1DARRAY_COMPARATOR   ElementComparator
#define DEFAULT_1DARRAY_CROSSOVER    OnePointCrossover
#define DEFAULT_2DARRAY_INITIALIZER  NoInitializer
#define DEFAULT_2DARRAY_MUTATOR      SwapMutator
#define DEFAULT_2DARRAY_COMPARATOR   ElementComparator
#define DEFAULT_2DARRAY_CROSSOVER    OnePointCrossover
#define DEFAULT_3DARRAY_INITIALIZER  NoInitializer
#define DEFAULT_3DARRAY_MUTATOR      SwapMutator
#define DEFAULT_3DARRAY_COMPARATOR   ElementComparator
#define DEFAULT_3DARRAY_CROSSOVER    OnePointCrossover

#define DEFAULT_1DARRAY_ALLELE_INITIALIZER  UniformInitializer
#define DEFAULT_1DARRAY_ALLELE_MUTATOR      FlipMutator
#define DEFAULT_1DARRAY_ALLELE_COMPARATOR   ElementComparator
#define DEFAULT_1DARRAY_ALLELE_CROSSOVER    OnePointCrossover
#define DEFAULT_2DARRAY_ALLELE_INITIALIZER  UniformInitializer
#define DEFAULT_2DARRAY_ALLELE_MUTATOR      FlipMutator
#define DEFAULT_2DARRAY_ALLELE_COMPARATOR   ElementComparator
#define DEFAULT_2DARRAY_ALLELE_CROSSOVER    OnePointCrossover
#define DEFAULT_3DARRAY_ALLELE_INITIALIZER  UniformInitializer
#define DEFAULT_3DARRAY_ALLELE_MUTATOR      FlipMutator
#define DEFAULT_3DARRAY_ALLELE_COMPARATOR   ElementComparator
#define DEFAULT_3DARRAY_ALLELE_CROSSOVER    OnePointCrossover

#define DEFAULT_STRING_INITIALIZER   UniformInitializer
#define DEFAULT_STRING_MUTATOR       FlipMutator
#define DEFAULT_STRING_COMPARATOR    ElementComparator
#define DEFAULT_STRING_CROSSOVER     UniformCrossover

#define DEFAULT_REAL_INITIALIZER     UniformInitializer
#define DEFAULT_REAL_MUTATOR         GARealGaussianMutator
#define DEFAULT_REAL_COMPARATOR      ElementComparator
#define DEFAULT_REAL_CROSSOVER       UniformCrossover

#define DEFAULT_TREE_INITIALIZER     NoInitializer
#define DEFAULT_TREE_MUTATOR         SwapSubtreeMutator
#define DEFAULT_TREE_COMPARATOR      TopologyComparator
#define DEFAULT_TREE_CROSSOVER       OnePointCrossover

#define DEFAULT_LIST_INITIALIZER     NoInitializer
#define DEFAULT_LIST_MUTATOR         SwapMutator
#define DEFAULT_LIST_COMPARATOR      NodeComparator
#define DEFAULT_LIST_CROSSOVER       OnePointCrossover

#endif
