#include <ruby.h>
#include <algorithm> // std::min
#include <fstream>
#include <arrayfire.h>
#include <stdio.h>
#include <math.h>
/*
 * Project Includes
 */

#include "arrayfire.h"
#include "ruby_arrayfire.h"

namespace arf {

  enum ewop_t {
    EW_ADD,
    EW_SUB,
    EW_MUL,
    EW_DIV,
    EW_POW,
    EW_MOD,
    EW_EQEQ,
    EW_NEQ,
    EW_LT,
    EW_GT,
    EW_LEQ,
    EW_GEQ,
  };
  using namespace af;
  static array A; // populated before each timing
  static void fn()
  {
      array B = matmul(A, A);  // matrix multiply
      B.eval();                // ensure evaluated
  }

  static void createArray(afstruct *afarray)
  {
    dim_t dims[afarray->ndims] ;

    for (size_t index = 0; index < afarray->ndims; ++index){
      dims[index] = (dim_t)afarray->dimension[index];
    }
  }

  #include "arith.cpp"
  #include "blas.cpp"
  #include "lapack.cpp"
}
extern "C" {
  #include "arrayfire.c"
}
