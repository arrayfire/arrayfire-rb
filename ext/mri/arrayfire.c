#include "arrayfire.h"
#include <stdio.h>
#include <math.h>

VALUE ArrayFire = Qnil;
VALUE Af_Array = Qnil;
VALUE Blas = Qnil;
VALUE Cuda = Qnil;
VALUE Data = Qnil;
VALUE Device = Qnil;
VALUE Lapack = Qnil;
VALUE OpenCL = Qnil;


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

static VALUE arf_matmul(VALUE self, VALUE left_val, VALUE right_val);
static VALUE arf_dot(VALUE self, VALUE left_val, VALUE right_val);
static VALUE arf_transpose(VALUE self, VALUE left_val, VALUE right_val);
static VALUE arf_transpose_inplace(VALUE self, VALUE left_val, VALUE right_val);

static VALUE arf_get_stream(VALUE self);
static VALUE arf_get_native_id(VALUE self);
static VALUE arf_set_native_id(VALUE self);

static VALUE arf_get_context(VALUE self);
static VALUE arf_get_queue(VALUE self);
static VALUE arf_get_device_id(VALUE self);
static VALUE arf_set_device_id(VALUE self);
static VALUE arf_add_device_context(VALUE self);
static VALUE arf_set_device_context(VALUE self);
static VALUE arf_delete_device_context(VALUE self);
static VALUE arf_get_device_type(VALUE self);
static VALUE arf_get_platform(VALUE self);

static VALUE arf_constant(VALUE self);
static VALUE arf_constant_complex(VALUE self);
static VALUE arf_constant_long(VALUE self);
static VALUE arf_constant_ulong(VALUE self);
static VALUE arf_range(VALUE self);
static VALUE arf_iota(VALUE self);
static VALUE arf_identity(VALUE self);
static VALUE arf_diag_create(VALUE self);
static VALUE arf_diag_extract(VALUE self);
static VALUE arf_join(VALUE self);
static VALUE arf_join_many(VALUE self);
static VALUE arf_tile(VALUE self);
static VALUE arf_reorder(VALUE self);
static VALUE arf_shift(VALUE self);
static VALUE arf_moddims(VALUE self);
static VALUE arf_flat(VALUE self);
static VALUE arf_flip(VALUE self);
static VALUE arf_lower(VALUE self);
static VALUE arf_upper(VALUE self);
static VALUE arf_select(VALUE self);
static VALUE arf_select_scalar_r(VALUE self);
static VALUE arf_select_scalar_l(VALUE self);
static VALUE arf_replace(VALUE self);
static VALUE arf_replace_scalar(VALUE self);


static VALUE arf_svd(VALUE self);
static VALUE arf_svd_inplace(VALUE self);
static VALUE arf_lu(VALUE self);
static VALUE arf_lu_inplace(VALUE self);
static VALUE arf_qr(VALUE self);
static VALUE arf_qr_inplace(VALUE self);
static VALUE arf_cholesky(VALUE self, VALUE val);
static VALUE arf_cholesky_inplace(VALUE self);
static VALUE arf_solve(VALUE self);
static VALUE arf_solve_lu(VALUE self);
static VALUE arf_inverse(VALUE self);
static VALUE arf_rank(VALUE self);
static VALUE arf_det(VALUE self, VALUE val);
static VALUE arf_norm(VALUE self, VALUE val);
static VALUE arf_is_lapack_available(VALUE self);

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
  rb_define_method(Af_Array, "inverse",(METHOD)arf_inverse,0);

  Device = rb_define_class_under(ArrayFire, "Device", rb_cObject);
  rb_define_method(Device, "getInfo", (METHOD)get_info, 0);

  Blas = rb_define_class_under(ArrayFire, "BLAS", rb_cObject);
  rb_define_singleton_method(Blas, "matmul", (METHOD)arf_matmul, 2);
  rb_define_singleton_method(Blas, "dot", (METHOD)arf_dot, 2);
  rb_define_singleton_method(Blas, "transpose", (METHOD)arf_transpose, 2);
  rb_define_singleton_method(Blas, "transpose_inplace", (METHOD)arf_transpose_inplace, 2);

  Cuda = rb_define_class_under(ArrayFire, "CUDA", rb_cObject);
  rb_define_singleton_method(Cuda, "get_stream", (METHOD)arf_get_stream, 0);
  rb_define_singleton_method(Cuda, "get_native_id", (METHOD)arf_get_native_id, 0);
  rb_define_singleton_method(Cuda, "set_native_id", (METHOD)arf_set_native_id, 0);

  OpenCL = rb_define_class_under(ArrayFire, "OpenCL", rb_cObject);
  rb_define_singleton_method(OpenCL, "get_context", (METHOD)arf_get_context, 0);
  rb_define_singleton_method(OpenCL, "get_queue", (METHOD)arf_get_queue, 0);
  rb_define_singleton_method(OpenCL, "get_device_id", (METHOD)arf_get_device_id, 0);
  rb_define_singleton_method(OpenCL, "set_device_id", (METHOD)arf_set_device_id, 0);
  rb_define_singleton_method(OpenCL, "add_device_context", (METHOD)arf_add_device_context, 0);
  rb_define_singleton_method(OpenCL, "set_device_context", (METHOD)arf_set_device_context, 0);
  rb_define_singleton_method(OpenCL, "delete_device_context", (METHOD)arf_delete_device_context, 0);
  rb_define_singleton_method(OpenCL, "get_device_type", (METHOD)arf_get_device_type, 0);
  rb_define_singleton_method(OpenCL, "get_platform", (METHOD)arf_get_platform, 0);

  Data = rb_define_class_under(ArrayFire, "Data", rb_cObject);
  rb_define_singleton_method(Data, "constant", (METHOD)arf_constant, 0);
  rb_define_singleton_method(Data, "constant_complex", (METHOD)arf_constant_complex, 0);
  rb_define_singleton_method(Data, "constant_long", (METHOD)arf_constant_long, 0);
  rb_define_singleton_method(Data, "constant_ulong", (METHOD)arf_constant_ulong, 0);
  rb_define_singleton_method(Data, "range", (METHOD)arf_range, 0);
  rb_define_singleton_method(Data, "iota", (METHOD)arf_iota, 0);
  rb_define_singleton_method(Data, "identity", (METHOD)arf_identity, 0);
  rb_define_singleton_method(Data, "diag_create", (METHOD)arf_diag_create, 0);
  rb_define_singleton_method(Data, "diag_extract", (METHOD)arf_diag_extract, 0);
  rb_define_singleton_method(Data, "join", (METHOD)arf_join, 0);
  rb_define_singleton_method(Data, "join_many", (METHOD)arf_join_many, 0);
  rb_define_singleton_method(Data, "tile", (METHOD)arf_tile, 0);
  rb_define_singleton_method(Data, "reorder", (METHOD)arf_reorder, 0);
  rb_define_singleton_method(Data, "shift", (METHOD)arf_shift, 0);
  rb_define_singleton_method(Data, "moddims", (METHOD)arf_moddims, 0);
  rb_define_singleton_method(Data, "flat", (METHOD)arf_flat, 0);
  rb_define_singleton_method(Data, "flip", (METHOD)arf_flip, 0);
  rb_define_singleton_method(Data, "lower", (METHOD)arf_lower, 0);
  rb_define_singleton_method(Data, "upper", (METHOD)arf_upper, 0);
  rb_define_singleton_method(Data, "select", (METHOD)arf_select, 0);
  rb_define_singleton_method(Data, "select_scalar_r", (METHOD)arf_select_scalar_r, 0);
  rb_define_singleton_method(Data, "select_scalar_l", (METHOD)arf_select_scalar_l, 0);
  rb_define_singleton_method(Data, "replace", (METHOD)arf_replace, 0);
  rb_define_singleton_method(Data, "replace_scalar", (METHOD)arf_replace_scalar, 0);

  Lapack = rb_define_class_under(ArrayFire, "LAPACK", rb_cObject);
  rb_define_singleton_method(Lapack, "svd", (METHOD)arf_svd, 0);
  rb_define_singleton_method(Lapack, "svd_inplace", (METHOD)arf_svd_inplace, 0);
  rb_define_singleton_method(Lapack, "lu", (METHOD)arf_lu, 0);
  rb_define_singleton_method(Lapack, "lu_inplace", (METHOD)arf_lu_inplace, 0);
  rb_define_singleton_method(Lapack, "qr", (METHOD)arf_qr, 0);
  rb_define_singleton_method(Lapack, "qr_inplace", (METHOD)arf_qr_inplace, 0);
  rb_define_singleton_method(Lapack, "cholesky", (METHOD)arf_cholesky, 1);
  rb_define_singleton_method(Lapack, "cholesky_inplace", (METHOD)arf_cholesky_inplace, 0);
  rb_define_singleton_method(Lapack, "solve", (METHOD)arf_solve, 0);
  rb_define_singleton_method(Lapack, "solve_lu", (METHOD)arf_solve_lu, 0);
  rb_define_singleton_method(Lapack, "inverse", (METHOD)arf_inverse, 0);
  rb_define_singleton_method(Lapack, "rank", (METHOD)arf_rank, 0);
  rb_define_singleton_method(Lapack, "det", (METHOD)arf_det, 1);
  rb_define_singleton_method(Lapack, "norm", (METHOD)arf_norm, 1);
  rb_define_singleton_method(Lapack, "is_lapack_available", (METHOD)arf_is_lapack_available, 0);
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

// BLAS

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

static VALUE arf_dot(VALUE self, VALUE left_val, VALUE right_val){
  return Qnil;
}

static VALUE arf_transpose(VALUE self, VALUE left_val, VALUE right_val){
  return Qnil;
}

static VALUE arf_transpose_inplace(VALUE self, VALUE left_val, VALUE right_val){
  return Qnil;
}

// CUDA

static VALUE arf_get_stream(VALUE self){
  return Qnil;
}

static VALUE arf_get_native_id(VALUE self){
  return Qnil;
}

static VALUE arf_set_native_id(VALUE self){
  return Qnil;
}

// OpenCL

static VALUE arf_get_context(VALUE self){
  return Qnil;
}

static VALUE arf_get_queue(VALUE self){
  return Qnil;
}

static VALUE arf_get_device_id(VALUE self){
  return Qnil;
}

static VALUE arf_set_device_id(VALUE self){
  return Qnil;
}

static VALUE arf_add_device_context(VALUE self){
  return Qnil;
}

static VALUE arf_set_device_context(VALUE self){
  return Qnil;
}

static VALUE arf_delete_device_context(VALUE self){
  return Qnil;
}

static VALUE arf_get_device_type(VALUE self){
  return Qnil;
}

static VALUE arf_get_platform(VALUE self){
  return Qnil;
}

//Data


static VALUE arf_constant(VALUE self){
  return Qnil;
}

static VALUE arf_constant_complex(VALUE self){
  return Qnil;
}

static VALUE arf_constant_long(VALUE self){
  return Qnil;
}

static VALUE arf_constant_ulong(VALUE self){
  return Qnil;
}

static VALUE arf_range(VALUE self){
  return Qnil;
}

static VALUE arf_iota(VALUE self){
  return Qnil;
}

static VALUE arf_identity(VALUE self){
  return Qnil;
}

static VALUE arf_diag_create(VALUE self){
  return Qnil;
}

static VALUE arf_diag_extract(VALUE self){
  return Qnil;
}

static VALUE arf_join(VALUE self){
  return Qnil;
}

static VALUE arf_join_many(VALUE self){
  return Qnil;
}

static VALUE arf_tile(VALUE self){
  return Qnil;
}

static VALUE arf_reorder(VALUE self){
  return Qnil;
}

static VALUE arf_shift(VALUE self){
  return Qnil;
}

static VALUE arf_moddims(VALUE self){
  return Qnil;
}

static VALUE arf_flat(VALUE self){
  return Qnil;
}

static VALUE arf_flip(VALUE self){
  return Qnil;
}

static VALUE arf_lower(VALUE self){
  return Qnil;
}

static VALUE arf_upper(VALUE self){
  return Qnil;
}

static VALUE arf_select(VALUE self){
  return Qnil;
}

static VALUE arf_select_scalar_r(VALUE self){
  return Qnil;
}

static VALUE arf_select_scalar_l(VALUE self){
  return Qnil;
}

static VALUE arf_replace(VALUE self){
  return Qnil;
}

static VALUE arf_replace_scalar(VALUE self){
  return Qnil;
}

// Lapack

static VALUE arf_svd(VALUE self){
  return Qnil;
}

static VALUE arf_svd_inplace(VALUE self){
  return Qnil;
}

static VALUE arf_lu(VALUE self){
  return Qnil;
}

static VALUE arf_lu_inplace(VALUE self){
  return Qnil;
}

static VALUE arf_qr(VALUE self){
  return Qnil;
}

static VALUE arf_qr_inplace(VALUE self){
  return Qnil;
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

static VALUE arf_cholesky_inplace(VALUE self){
  return Qnil;
}

static VALUE arf_solve(VALUE self){
  return Qnil;
}

static VALUE arf_solve_lu(VALUE self){
  return Qnil;
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
static VALUE arf_rank(VALUE self){
  return Qnil;
}

static VALUE arf_det(VALUE self, VALUE val){

  afstruct* matrix;
  Data_Get_Struct(val, afstruct, matrix);

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

static VALUE arf_norm(VALUE self, VALUE val){
  afstruct* matrix
  Data_Get_Struct(val, afstruct, matrix);
  double norm = arf::norm_(matrix);
  return DBL2NUM(norm);
}

static VALUE arf_is_lapack_available(VALUE self){
  return Qnil;
}
