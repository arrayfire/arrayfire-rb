#include "arrayfire.h"
#include <stdio.h>
#include <math.h>

VALUE ArrayFire = Qnil;
VALUE Af_Array = Qnil;
VALUE Device = Qnil;
VALUE Blas = Qnil;
VALUE Lapack = Qnil;


// prototypes
void Init_arrayfire();
static VALUE test1(VALUE self);
static VALUE arf_init(int argc, VALUE* argv, VALUE self);
static VALUE arf_alloc(VALUE klass);
static void arf_free(afstruct* af);
static VALUE ndims(VALUE self);
static VALUE dimension(VALUE self);
static VALUE array(VALUE self);
static void array2(VALUE self);
static VALUE get_info(VALUE self);

static size_t*  interpret_shape(VALUE arg, size_t* dim);

#define DEF_ELEMENTWISE_RUBY_ACCESSOR(oper, name)                 \
static VALUE arf_ew_##name(VALUE left_val, VALUE right_val) {  \
  return elementwise_op(arf::EW_##oper, left_val, right_val);  \
}

#define DECL_ELEMENTWISE_RUBY_ACCESSOR(name)    static VALUE arf_ew_##name(VALUE left_val, VALUE right_val);
DECL_ELEMENTWISE_RUBY_ACCESSOR(add)


static VALUE elementwise_op(arf::ewop_t op, VALUE left_val, VALUE right_val);
/*
 * Macro defines an element-wise accessor function for some operation.
 *
 * This is only responsible for the Ruby accessor! You still have to write the actual functions, obviously.
 */

static VALUE arf_eqeq(VALUE left_val, VALUE right_val);


static VALUE arf_matmul(VALUE self, VALUE left_val, VALUE right_val);
static VALUE arf_cholesky(VALUE self, VALUE val);
static VALUE arf_det(VALUE self);
static VALUE arf_inverse(VALUE self);
static VALUE arf_norm(VALUE self);

void Init_arrayfire() {
  ArrayFire = rb_define_module("ArrayFire");
  rb_define_method(ArrayFire, "test1", (METHOD)test1, 0);

  Af_Array = rb_define_class_under(ArrayFire, "Af_Array", rb_cObject);
  rb_define_alloc_func(Af_Array, arf_alloc);
  rb_define_method(Af_Array, "initialize", (METHOD)arf_init, -1);
  rb_define_method(Af_Array, "ndims", (METHOD)ndims, 0);
  rb_define_method(Af_Array, "dimension", (METHOD)dimension, 0);
  rb_define_method(Af_Array, "array", (METHOD)array, 0);
  rb_define_method(Af_Array, "array2", (METHOD)array2, 0);
  rb_define_method(Af_Array, "+",(METHOD)arf_ew_add,1);
  rb_define_method(Af_Array, "==",(METHOD)arf_eqeq,1);
  rb_define_method(Af_Array, "det",(METHOD)arf_det,0);
  rb_define_method(Af_Array, "inverse",(METHOD)arf_inverse,0);
  rb_define_method(Af_Array, "norm",(METHOD)arf_norm,0);

  Device = rb_define_class_under(ArrayFire, "Device", rb_cObject);
  rb_define_method(Device, "getInfo", (METHOD)get_info, 0);

  Blas = rb_define_class_under(ArrayFire, "BLAS", rb_cObject);
  rb_define_singleton_method(Blas, "matmul", (METHOD)arf_matmul, 2);

  Lapack = rb_define_class_under(ArrayFire, "LAPACK", rb_cObject);
  rb_define_singleton_method(Lapack, "cholesky", (METHOD)arf_cholesky, 1);
}

VALUE test1(VALUE self) {
  VALUE x;
  x = rb_str_new_cstr("Hello, world!");
  return x;
}

VALUE arf_init(int argc, VALUE* argv, VALUE self)
{
  afstruct* afarray;
  Data_Get_Struct(self, afstruct, afarray);
  afarray->ndims = FIX2LONG(argv[0]);
  afarray->dimension = ALLOC_N(VALUE, argv[0]);
  size_t count = 1;
  for (size_t index = 0; index < FIX2LONG(argv[0]); index++) {
    afarray->dimension[index] = FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= afarray->dimension[index];
  }
  afarray->count = count;
  afarray->array = ALLOC_N(double, count);
  for (size_t index = 0; index < count; index++) {
    afarray->array[index] = NUM2DBL(RARRAY_AREF(argv[2], index));
  }
  dim_t dims[afarray->ndims] ;

  for (size_t index = 0; index < afarray->ndims; ++index){
    dims[index] = (dim_t)afarray->dimension[index];
  }
  return self;
}


static VALUE arf_alloc(VALUE klass)
{
  /* allocate */
  afstruct* af = ALLOC(afstruct);
  /* wrap */
  return Data_Wrap_Struct(klass, NULL, arf_free, af);
}


static void arf_free(afstruct* af)
{
  free(af);
}

static VALUE ndims(VALUE self)
{
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);

  return INT2NUM(af->ndims);
}

static VALUE dimension(VALUE self)
{
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);

  VALUE* dimension = ALLOC_N(VALUE, af->ndims);

  for (size_t index = 0; index < af->ndims; ++index){
    dimension[index] = INT2FIX(af->dimension[index]);
  }

  return rb_ary_new4(af->ndims, dimension);
}

static VALUE array(VALUE self)
{
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);

  VALUE* array = ALLOC_N(VALUE, af->count);

  for (size_t index = 0; index < af->count; ++index){
    array[index] = DBL2NUM(af->array[index]);
  }

  return rb_ary_new4(af->count, array);
}

static void array2(VALUE self){
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);
}

static VALUE get_info(VALUE self)
{
  VALUE x;
  af_info();
  return x;
}


DEF_ELEMENTWISE_RUBY_ACCESSOR(ADD, add)

static VALUE elementwise_op(arf::ewop_t op, VALUE left_val, VALUE right_val) {

  afstruct* left;
  afstruct* right;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(left_val, afstruct, left);
  Data_Get_Struct(right_val, afstruct, right);


  result->ndims = left->ndims;
  result->dimension = left->dimension;
  result->count = left->count;
  arf::add(result, left, right);

  return Data_Wrap_Struct(CLASS_OF(left_val), NULL, arf_free, result);
}

static VALUE arf_eqeq(VALUE left_val, VALUE right_val) {
  afstruct* left;
  afstruct* right;

  bool result = true;

  size_t i;
  size_t count = 1;

  Data_Get_Struct(left_val, afstruct, left);
  Data_Get_Struct(right_val, afstruct, right);

  printf("%d\n", left->ndims);

  for(size_t i = 0; i < left->ndims; i++){
    if(left->dimension[i]!= right->dimension[i]){
      return Qfalse;
    }
  }

  for(size_t i = 0; i < left->count; i++){
    if(left->array[i]!= right->array[i]){
      return Qfalse;
    }
  }

  return Qtrue;
}

static VALUE arf_matmul(VALUE self, VALUE left_val, VALUE right_val){

  afstruct* left;
  afstruct* right;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(left_val, afstruct, left);
  Data_Get_Struct(right_val, afstruct, right);


  result->ndims = left->ndims;
  size_t dimension[2];
  dimension[0] = left->dimension[0];
  dimension[1] = right->dimension[1];
  size_t count = dimension[0]*dimension[1];
  result->dimension = dimension;
  result->count = count;

  arf::matmul(result, left, right);

  return Data_Wrap_Struct(CLASS_OF(left_val), NULL, arf_free, result);
}

static VALUE arf_cholesky(VALUE self, VALUE val){

  afstruct* matrix;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(val, afstruct, matrix);


  result->ndims = matrix->ndims;
  result->dimension = matrix->dimension;
  result->count = matrix->count;
  arf::cholesky_(result, matrix);

  return Data_Wrap_Struct(CLASS_OF(val), NULL, arf_free, result);
}

static VALUE arf_det(VALUE self){

  afstruct* matrix;
  Data_Get_Struct(self, afstruct, matrix);

  af_array m;
  dim_t dims[matrix->ndims] ;
  for (size_t index = 0; index < matrix->ndims; ++index){
    dims[index] = (dim_t)matrix->dimension[index];
  }
  af_create_array( &m, matrix->array, matrix->ndims, dims, f64 );
  double real, imaginary;
  af_det(&real,&imaginary,m);
  return DBL2NUM(real);
}

static VALUE arf_inverse(VALUE self){

  afstruct* matrix;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(self, afstruct, matrix);

  result->ndims = matrix->ndims;
  result->dimension = matrix->dimension;
  result->count = matrix->count;
  arf::inverse_(result, matrix);

  return Data_Wrap_Struct(CLASS_OF(self), NULL, arf_free, result);
}

static VALUE arf_norm(VALUE self){
  afstruct* matrix;

  Data_Get_Struct(self, afstruct, matrix);

  double norm = arf::norm_(matrix);


  return DBL2NUM(norm);
}
