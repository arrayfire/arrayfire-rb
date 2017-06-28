#include "arrayfire.h"
#include <stdio.h>
#include <math.h>

VALUE ArrayFire = Qnil;
VALUE Af_Array = Qnil;
VALUE Algorithm = Qnil;
VALUE Backend = Qnil;
VALUE Blas = Qnil;
VALUE Cuda = Qnil;
VALUE Data = Qnil;
VALUE Device = Qnil;
VALUE Lapack = Qnil;
VALUE OpenCL = Qnil;
VALUE Random = Qnil;

// prototypes
void Init_arrayfire();
static VALUE arf_init(int argc, VALUE* argv, VALUE self);
static VALUE arf_alloc(VALUE klass);
static void arf_free(afstruct* af);

static VALUE arf_sum(VALUE self);
static VALUE arf_sum_nan(VALUE self);
static VALUE arf_product(VALUE self);
static VALUE arf_product_nan(VALUE self);
static VALUE arf_min(VALUE self);
static VALUE arf_max(VALUE self);
static VALUE arf_all_true(VALUE self);
static VALUE arf_any_true(VALUE self);
static VALUE arf_count(VALUE self);
static VALUE arf_sum_all(VALUE self);
static VALUE arf_sum_nan_all(VALUE self);
static VALUE arf_product_all(VALUE self);
static VALUE arf_product_nan_all(VALUE self);
static VALUE arf_min_all(VALUE self);
static VALUE arf_max_all(VALUE self);
static VALUE arf_all_true_all(VALUE self);
static VALUE arf_any_true_all(VALUE self);
static VALUE arf_count_all(VALUE self);
static VALUE arf_imin(VALUE self);
static VALUE arf_imax(VALUE self);
static VALUE arf_imin_all(VALUE self);
static VALUE arf_imax_all(VALUE self);
static VALUE arf_accum(VALUE self);
static VALUE arf_scan(VALUE self);
static VALUE arf_scan_by_key(VALUE self);
static VALUE arf_where(VALUE self);
static VALUE arf_diff1(VALUE self);
static VALUE arf_diff2(VALUE self);
static VALUE arf_sort(VALUE self);
static VALUE arf_sort_index(VALUE self);
static VALUE arf_sort_by_key(VALUE self);
static VALUE arf_set_unique(VALUE self);
static VALUE arf_set_union(VALUE self);
static VALUE arf_set_intersect(VALUE self);

static VALUE arf_get_backend_count(VALUE self);
static VALUE arf_get_available_backends(VALUE self);
static VALUE arf_get_backend_id(VALUE self);
static VALUE arf_get_active_backend(VALUE self);
static VALUE arf_get_backend_device_id(VALUE self);

static VALUE arf_matmul(VALUE self, VALUE left_val, VALUE right_val);
static VALUE arf_dot(VALUE self, VALUE left_val, VALUE right_val);
static VALUE arf_transpose(VALUE self, VALUE left_val, VALUE right_val);
static VALUE arf_transpose_inplace(VALUE self, VALUE left_val, VALUE right_val);

static VALUE arf_get_stream(VALUE self);
static VALUE arf_get_native_id(VALUE self);
static VALUE arf_set_native_id(VALUE self);

static VALUE arf_info(VALUE self);
static VALUE arf_init2(VALUE self);
static VALUE arf_info_string(VALUE self);
static VALUE arf_device_info(VALUE self);
static VALUE arf_get_device_count(VALUE self);
static VALUE arf_get_dbl_support(VALUE self);
static VALUE arf_set_device(VALUE self);
static VALUE arf_get_device(VALUE self);
static VALUE arf_sync(VALUE self);
static VALUE arf_alloc_device(VALUE self);
static VALUE arf_free_device(VALUE self);
static VALUE arf_alloc_pinned(VALUE self);
static VALUE arf_free_pinned(VALUE self);
static VALUE arf_alloc_host(VALUE self);
static VALUE arf_free_host(VALUE self);
static VALUE arf_device_array(VALUE self);
static VALUE arf_device_mem_info(VALUE self);
static VALUE arf_print_mem_info(VALUE self);
static VALUE arf_device_gc(VALUE self);
static VALUE arf_set_mem_step_size(VALUE self);
static VALUE arf_get_mem_step_size(VALUE self);
static VALUE arf_lock_device_ptr(VALUE self);
static VALUE arf_unlock_device_ptr(VALUE self);
static VALUE arf_lock_array(VALUE self);
static VALUE arf_unlock_array(VALUE self);
static VALUE arf_is_locked_array(VALUE self);
static VALUE arf_get_device_ptr(VALUE self);

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

static VALUE arf_create_random_engine(VALUE self);
static VALUE arf_retain_random_engine(VALUE self);
static VALUE arf_random_engine_set_type(VALUE self);
static VALUE arf_random_engine_get_type(VALUE self);
static VALUE arf_random_uniform(VALUE self);
static VALUE arf_random_normal(VALUE self);
static VALUE arf_random_engine_set_seed(VALUE self);
static VALUE arf_get_default_random_engine(VALUE self);
static VALUE arf_set_default_random_engine_type(VALUE self);
static VALUE arf_random_engine_get_seed(VALUE self);
static VALUE arf_release_random_engine(VALUE self);
static VALUE arf_randu(VALUE self);
static VALUE arf_randn(VALUE self);
static VALUE arf_set_seed(VALUE self);
static VALUE arf_get_seed(VALUE self);

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
  rb_define_method(Af_Array, "+",(METHOD)arf_ew_add,1);
  rb_define_method(Af_Array, "==",(METHOD)arf_eqeq,1);
  rb_define_method(Af_Array, "inverse",(METHOD)arf_inverse,0);

  Algorithm = rb_define_class_under(ArrayFire, "Algorithm", rb_cObject);
  rb_define_method(Algorithm, "sum", (METHOD)arf_sum, 0);
  rb_define_method(Algorithm, "sum_nan", (METHOD)arf_sum_nan, 0);
  rb_define_method(Algorithm, "product", (METHOD)arf_product, 0);
  rb_define_method(Algorithm, "product_nan", (METHOD)arf_product_nan, 0);
  rb_define_method(Algorithm, "min", (METHOD)arf_min, 0);
  rb_define_method(Algorithm, "max", (METHOD)arf_max, 0);
  rb_define_method(Algorithm, "all_true", (METHOD)arf_all_true, 0);
  rb_define_method(Algorithm, "any_true", (METHOD)arf_any_true, 0);
  rb_define_method(Algorithm, "count", (METHOD)arf_count, 0);
  rb_define_method(Algorithm, "sum_all", (METHOD)arf_sum_all, 0);
  rb_define_method(Algorithm, "sum_nan_all", (METHOD)arf_sum_nan_all, 0);
  rb_define_method(Algorithm, "product_all", (METHOD)arf_product_all, 0);
  rb_define_method(Algorithm, "product_nan_all", (METHOD)arf_product_nan_all, 0);
  rb_define_method(Algorithm, "min_all", (METHOD)arf_min_all, 0);
  rb_define_method(Algorithm, "max_all", (METHOD)arf_max_all, 0);
  rb_define_method(Algorithm, "all_true_all", (METHOD)arf_all_true_all, 0);
  rb_define_method(Algorithm, "any_true_all", (METHOD)arf_any_true_all, 0);
  rb_define_method(Algorithm, "count_all", (METHOD)arf_count_all, 0);
  rb_define_method(Algorithm, "imin", (METHOD)arf_imin, 0);
  rb_define_method(Algorithm, "imax", (METHOD)arf_imax, 0);
  rb_define_method(Algorithm, "imin_all", (METHOD)arf_imin_all, 0);
  rb_define_method(Algorithm, "imax_all", (METHOD)arf_imax_all, 0);
  rb_define_method(Algorithm, "accum", (METHOD)arf_accum, 0);
  rb_define_method(Algorithm, "scan", (METHOD)arf_scan, 0);
  rb_define_method(Algorithm, "scan_by_key", (METHOD)arf_scan_by_key, 0);
  rb_define_method(Algorithm, "where", (METHOD)arf_where, 0);
  rb_define_method(Algorithm, "diff1", (METHOD)arf_diff1, 0);
  rb_define_method(Algorithm, "diff2", (METHOD)arf_diff2, 0);
  rb_define_method(Algorithm, "sort", (METHOD)arf_sort, 0);
  rb_define_method(Algorithm, "sort_index", (METHOD)arf_sort_index, 0);
  rb_define_method(Algorithm, "sort_by_key", (METHOD)arf_sort_by_key, 0);
  rb_define_method(Algorithm, "set_unique", (METHOD)arf_set_unique, 0);
  rb_define_method(Algorithm, "set_union", (METHOD)arf_set_union, 0);
  rb_define_method(Algorithm, "set_intersect", (METHOD)arf_set_intersect, 0);

  Backend = rb_define_class_under(ArrayFire, "Backend", rb_cObject);
  rb_define_method(Backend, "get_backend_count", (METHOD)arf_get_backend_count, 0);
  rb_define_method(Backend, "get_available_backends", (METHOD)arf_get_available_backends, 0);
  rb_define_method(Backend, "get_backend_id", (METHOD)arf_get_backend_id, 0);
  rb_define_method(Backend, "get_active_backend", (METHOD)arf_get_active_backend, 0);
  rb_define_method(Backend, "get_device_id", (METHOD)arf_get_backend_device_id, 0);

  Device = rb_define_class_under(ArrayFire, "Device", rb_cObject);
  rb_define_singleton_method(Device, "info", (METHOD)arf_info, 0);
  rb_define_method(Device, "init", (METHOD)arf_init, 0);
  rb_define_method(Device, "info_string", (METHOD)arf_info_string, 0);
  rb_define_method(Device, "device_info", (METHOD)arf_device_info, 0);
  rb_define_method(Device, "get_device_count", (METHOD)arf_get_device_count, 0);
  rb_define_method(Device, "get_dbl_support", (METHOD)arf_get_dbl_support, 0);
  rb_define_method(Device, "set_device", (METHOD)arf_set_device, 0);
  rb_define_method(Device, "get_device", (METHOD)arf_get_device, 0);
  rb_define_method(Device, "sync", (METHOD)arf_sync, 0);
  rb_define_method(Device, "alloc_device", (METHOD)arf_alloc_device, 0);
  rb_define_method(Device, "free_device", (METHOD)arf_free_device, 0);
  rb_define_method(Device, "alloc_pinned", (METHOD)arf_alloc_pinned, 0);
  rb_define_method(Device, "free_pinned", (METHOD)arf_free_pinned, 0);
  rb_define_method(Device, "alloc_host", (METHOD)arf_alloc_host, 0);
  rb_define_method(Device, "free_host", (METHOD)arf_free_host, 0);
  rb_define_method(Device, "device_array", (METHOD)arf_device_array, 0);
  rb_define_method(Device, "device_mem_info", (METHOD)arf_device_mem_info, 0);
  rb_define_method(Device, "print_mem_info", (METHOD)arf_print_mem_info, 0);
  rb_define_method(Device, "device_gc", (METHOD)arf_device_gc, 0);
  rb_define_method(Device, "set_mem_step_size", (METHOD)arf_set_mem_step_size, 0);
  rb_define_method(Device, "get_mem_step_size", (METHOD)arf_get_mem_step_size, 0);
  rb_define_method(Device, "lock_device_ptr", (METHOD)arf_lock_device_ptr, 0);
  rb_define_method(Device, "unlock_device_ptr", (METHOD)arf_unlock_device_ptr, 0);
  rb_define_method(Device, "lock_array", (METHOD)arf_lock_array, 0);
  rb_define_method(Device, "unlock_array", (METHOD)arf_unlock_array, 0);
  rb_define_method(Device, "is_locked_array", (METHOD)arf_is_locked_array, 0);
  rb_define_method(Device, "get_device_ptr", (METHOD)arf_get_device_ptr, 0);

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

  Random = rb_define_class_under(ArrayFire, "Random", rb_cObject);
  rb_define_method(Random, "create_random_engine", (METHOD)arf_create_random_engine, 0);
  rb_define_method(Random, "retain_random_engine", (METHOD)arf_retain_random_engine, 0);
  rb_define_method(Random, "random_engine_set_type", (METHOD)arf_random_engine_set_type, 0);
  rb_define_method(Random, "random_engine_get_type", (METHOD)arf_random_engine_get_type, 0);
  rb_define_method(Random, "random_uniform", (METHOD)arf_random_uniform, 0);
  rb_define_method(Random, "random_normal", (METHOD)arf_random_normal, 0);
  rb_define_method(Random, "random_engine_set_seed", (METHOD)arf_random_engine_set_seed, 0);
  rb_define_method(Random, "get_default_random_engine", (METHOD)arf_get_default_random_engine, 0);
  rb_define_method(Random, "set_default_random_engine_type", (METHOD)arf_set_default_random_engine_type, 0);
  rb_define_method(Random, "random_engine_get_seed", (METHOD)arf_random_engine_get_seed, 0);
  rb_define_method(Random, "release_random_engine", (METHOD)arf_release_random_engine, 0);
  rb_define_method(Random, "randu", (METHOD)arf_randu, 0);
  rb_define_method(Random, "randn", (METHOD)arf_randn, 0);
  rb_define_method(Random, "set_seed", (METHOD)arf_set_seed, 0);
  rb_define_method(Random, "get_seed", (METHOD)arf_get_seed, 0);
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

// Algorithm

static VALUE arf_sum(VALUE self){
  return Qnil;
}
static VALUE arf_sum_nan(VALUE self){
  return Qnil;
}
static VALUE arf_product(VALUE self){
  return Qnil;
}
static VALUE arf_product_nan(VALUE self){
  return Qnil;
}
static VALUE arf_min(VALUE self){
  return Qnil;
}
static VALUE arf_max(VALUE self){
  return Qnil;
}
static VALUE arf_all_true(VALUE self){
  return Qnil;
}
static VALUE arf_any_true(VALUE self){
  return Qnil;
}
static VALUE arf_count(VALUE self){
  return Qnil;
}
static VALUE arf_sum_all(VALUE self){
  return Qnil;
}
static VALUE arf_sum_nan_all(VALUE self){
  return Qnil;
}
static VALUE arf_product_all(VALUE self){
  return Qnil;
}
static VALUE arf_product_nan_all(VALUE self){
  return Qnil;
}
static VALUE arf_min_all(VALUE self){
  return Qnil;
}
static VALUE arf_max_all(VALUE self){
  return Qnil;
}
static VALUE arf_all_true_all(VALUE self){
  return Qnil;
}
static VALUE arf_any_true_all(VALUE self){
  return Qnil;
}
static VALUE arf_count_all(VALUE self){
  return Qnil;
}
static VALUE arf_imin(VALUE self){
  return Qnil;
}
static VALUE arf_imax(VALUE self){
  return Qnil;
}
static VALUE arf_imin_all(VALUE self){
  return Qnil;
}
static VALUE arf_imax_all(VALUE self){
  return Qnil;
}
static VALUE arf_accum(VALUE self){
  return Qnil;
}
static VALUE arf_scan(VALUE self){
  return Qnil;
}
static VALUE arf_scan_by_key(VALUE self){
  return Qnil;
}
static VALUE arf_where(VALUE self){
  return Qnil;
}
static VALUE arf_diff1(VALUE self){
  return Qnil;
}
static VALUE arf_diff2(VALUE self){
  return Qnil;
}
static VALUE arf_sort(VALUE self){
  return Qnil;
}
static VALUE arf_sort_index(VALUE self){
  return Qnil;
}
static VALUE arf_sort_by_key(VALUE self){
  return Qnil;
}
static VALUE arf_set_unique(VALUE self){
  return Qnil;
}
static VALUE arf_set_union(VALUE self){
  return Qnil;
}
static VALUE arf_set_intersect(VALUE self){
  return Qnil;
}

// Backend

static VALUE arf_get_backend_count(VALUE self){
   return Qnil;
}

static VALUE arf_get_available_backends(VALUE self){
   return Qnil;
}

static VALUE arf_get_backend_id(VALUE self){
   return Qnil;
}

static VALUE arf_get_active_backend(VALUE self){
   return Qnil;
}

static VALUE arf_get_backend_device_id(VALUE self){
   return Qnil;
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

// Device

static VALUE arf_info(VALUE self){
  af_info();
  return Qnil;
}

static VALUE arf_init2(VALUE self){
  return Qnil;
}

static VALUE arf_info_string(VALUE self){
  return Qnil;
}

static VALUE arf_device_info(VALUE self){
  return Qnil;
}

static VALUE arf_get_device_count(VALUE self){
  return Qnil;
}

static VALUE arf_get_dbl_support(VALUE self){
  return Qnil;
}

static VALUE arf_set_device(VALUE self){
  return Qnil;
}

static VALUE arf_get_device(VALUE self){
  return Qnil;
}

static VALUE arf_sync(VALUE self){
  return Qnil;
}

static VALUE arf_alloc_device(VALUE self){
  return Qnil;
}

static VALUE arf_free_device(VALUE self){
  return Qnil;
}

static VALUE arf_alloc_pinned(VALUE self){
  return Qnil;
}

static VALUE arf_free_pinned(VALUE self){
  return Qnil;
}

static VALUE arf_alloc_host(VALUE self){
  return Qnil;
}

static VALUE arf_free_host(VALUE self){
  return Qnil;
}

static VALUE arf_device_array(VALUE self){
  return Qnil;
}

static VALUE arf_device_mem_info(VALUE self){
  return Qnil;
}

static VALUE arf_print_mem_info(VALUE self){
  return Qnil;
}

static VALUE arf_device_gc(VALUE self){
  return Qnil;
}

static VALUE arf_set_mem_step_size(VALUE self){
  return Qnil;
}

static VALUE arf_get_mem_step_size(VALUE self){
  return Qnil;
}

static VALUE arf_lock_device_ptr(VALUE self){
  return Qnil;
}

static VALUE arf_unlock_device_ptr(VALUE self){
  return Qnil;
}

static VALUE arf_lock_array(VALUE self){
  return Qnil;
}

static VALUE arf_unlock_array(VALUE self){
  return Qnil;
}

static VALUE arf_is_locked_array(VALUE self){
  return Qnil;
}

static VALUE arf_get_device_ptr(VALUE self){
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

// Random

static VALUE arf_create_random_engine(VALUE self){
  return Qnil;
}
static VALUE arf_retain_random_engine(VALUE self){
  return Qnil;
}
static VALUE arf_random_engine_set_type(VALUE self){
  return Qnil;
}
static VALUE arf_random_engine_get_type(VALUE self){
  return Qnil;
}
static VALUE arf_random_uniform(VALUE self){
  return Qnil;
}
static VALUE arf_random_normal(VALUE self){
  return Qnil;
}
static VALUE arf_random_engine_set_seed(VALUE self){
  return Qnil;
}
static VALUE arf_get_default_random_engine(VALUE self){
  return Qnil;
}
static VALUE arf_set_default_random_engine_type(VALUE self){
  return Qnil;
}
static VALUE arf_random_engine_get_seed(VALUE self){
  return Qnil;
}
static VALUE arf_release_random_engine(VALUE self){
  return Qnil;
}
static VALUE arf_randu(VALUE self){
  return Qnil;
}
static VALUE arf_randn(VALUE self){
  return Qnil;
}
static VALUE arf_set_seed(VALUE self){
  return Qnil;
}
static VALUE arf_get_seed(VALUE self){
  return Qnil;
}
