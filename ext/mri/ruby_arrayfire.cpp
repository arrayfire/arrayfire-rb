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

  static void hostArray(afstruct *afarray)
  {

  }

  static void add(afstruct *result, afstruct *left, afstruct *right)
  {
    array l = array(left->dimension[0], left->dimension[1], left->array);
    array r = array(right->dimension[0], right->dimension[1], right->array);
    array res = operator+(l,r);
    result->array = res.host<double>();
  }



  static void cholesky_(afstruct *result, afstruct *matrix)
  {
    array m = array(matrix->dimension[0], matrix->dimension[1], matrix->array);
    bool is_upper = true;
    array res;
    cholesky(res, m, is_upper);
    result->array = res.host<double>();
  }

  static void inverse_(afstruct *result, afstruct *matrix)
  {
    array m = array(matrix->dimension[0], matrix->dimension[1], matrix->array);
    array res = inverse(m);
    result->array = res.host<double>();
  }

  static double norm_(afstruct *matrix)
  {
    array m = array(matrix->dimension[0], matrix->dimension[1], matrix->array);
    return norm(m, AF_NORM_EUCLID, 1, 1);
  }

  #include "blas.cpp"
}
extern "C" {
  #include "arrayfire.c"
}
