#ifndef RUBY_ARRAYFIRE_H
  #define RUBY_ARRAYFIRE_H
#endif

/*
 * Functions
 */

#ifdef __cplusplus
typedef VALUE (*METHOD)(...);
//}; // end of namespace nm
#endif

#include <ruby.h>
// #include <test.cpp>
#ifdef __cplusplus
extern "C" {
#endif

  void Init_arrayfire();
  static void matmul_benchmark();
  // External API


#ifdef __cplusplus
}
#endif

