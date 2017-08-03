#ifndef RUBY_ARRAYFIRE_H
  #define RUBY_ARRAYFIRE_H
#endif

#include <ruby.h>

typedef struct AF_STRUCT
{
  af_array carray;
}afstruct;

typedef struct RANDOM_ENGINE_STRUCT
{
  af_random_engine cengine;
}afrandomenginestruct;

#ifndef HAVE_RB_ARRAY_CONST_PTR
static inline const VALUE *
rb_array_const_ptr(VALUE a)
{
  return FIX_CONST_VALUE_PTR((RBASIC(a)->flags & RARRAY_EMBED_FLAG) ?
    RARRAY(a)->as.ary : RARRAY(a)->as.heap.ptr);
}
#endif

#ifndef RARRAY_CONST_PTR
# define RARRAY_CONST_PTR(a) rb_array_const_ptr(a)
#endif

#ifndef RARRAY_AREF
# define RARRAY_AREF(a, i) (RARRAY_CONST_PTR(a)[i])
#endif

/*
 * Functions
 */

#ifdef __cplusplus
typedef VALUE (*METHOD)(...);
//}; // end of namespace nm
#endif


#ifdef __cplusplus
extern "C" {
#endif

  void Init_arrayfire();

#ifdef __cplusplus
}
#endif
