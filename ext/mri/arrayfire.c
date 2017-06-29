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

static VALUE arf_sum(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_sum_nan(VALUE self, VALUE array_val, VALUE dim_val, VALUE nan_val);
static VALUE arf_product(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_product_nan(VALUE self, VALUE array_val, VALUE dim_val, VALUE nan_val);
static VALUE arf_min(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_max(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_all_true(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_any_true(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_count(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_sum_all(VALUE self, VALUE array_val);
static VALUE arf_sum_nan_all(VALUE self, VALUE array_val, VALUE nan_val);
static VALUE arf_product_all(VALUE self, VALUE array_val);
static VALUE arf_product_nan_all(VALUE self, VALUE array_val, VALUE nan_val);
static VALUE arf_min_all(VALUE self, VALUE array_val);
static VALUE arf_max_all(VALUE self, VALUE array_val);
static VALUE arf_all_true_all(VALUE self, VALUE array_val);
static VALUE arf_any_true_all(VALUE self, VALUE array_val);
static VALUE arf_count_all(VALUE self, VALUE array_val);
static VALUE arf_imin(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_imax(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_imin_all(VALUE self, VALUE array_val);
static VALUE arf_imax_all(VALUE self, VALUE array_val);
static VALUE arf_accum(VALUE self, VALUE array_val, VALUE dim_val);
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
static VALUE arf_transpose(VALUE self, VALUE input);
static VALUE arf_transpose_inplace(VALUE self, VALUE input);

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


static VALUE arf_svd(VALUE self, VALUE val);
static VALUE arf_svd_inplace(VALUE self, VALUE val);
static VALUE arf_lu(VALUE self, VALUE val);
static VALUE arf_lu_inplace(VALUE self);
static VALUE arf_qr(VALUE self, VALUE val);
static VALUE arf_qr_inplace(VALUE self);
static VALUE arf_cholesky(VALUE self, VALUE val);
static VALUE arf_cholesky_inplace(VALUE self);
static VALUE arf_solve(VALUE self, VALUE lhs_val, VALUE rhs_val);
static VALUE arf_solve_lu(VALUE self, VALUE lhs_val, VALUE rhs_val, VALUE piv_val);
static VALUE arf_inverse(VALUE self, VALUE val);
static VALUE arf_rank(VALUE self, VALUE val);
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

#define DEF_ELEMENTWISE_RUBY_ACCESSOR(name, oper)                          \
static VALUE arf_ew_##name(VALUE left_val, VALUE right_val) {              \
  afstruct* left;                                                          \
  afstruct* right;                                                         \
  afstruct* result = ALLOC(afstruct);                                      \
  Data_Get_Struct(left_val, afstruct, left);                               \
  Data_Get_Struct(right_val, afstruct, right);                             \
  af_##oper(&result->carray,  left->carray, right->carray, true);          \
  af_print_array(result->carray);                                          \
  return Data_Wrap_Struct(CLASS_OF(left_val), NULL, arf_free, result);     \
}

#define DEF_UNARY_RUBY_ACCESSOR(oper, name)                                \
static VALUE arf_unary_##name(VALUE self) {                                \
  afstruct* obj;                                                           \
  afstruct* result = ALLOC(afstruct);                                      \
  Data_Get_Struct(self, afstruct, obj);                                    \
  af_##oper(&result->carray, obj->carray);                                 \
  af_print_array(result->carray);                                          \
  return Data_Wrap_Struct(CLASS_OF(self), NULL, arf_free, result);         \
}

#define DECL_ELEMENTWISE_RUBY_ACCESSOR(name)    static VALUE arf_ew_##name(VALUE left_val, VALUE right_val);
#define DECL_UNARY_RUBY_ACCESSOR(name)          static VALUE arf_unary_##name(VALUE self);

DECL_ELEMENTWISE_RUBY_ACCESSOR(add)
DECL_ELEMENTWISE_RUBY_ACCESSOR(subtract)
DECL_ELEMENTWISE_RUBY_ACCESSOR(multiply)
DECL_ELEMENTWISE_RUBY_ACCESSOR(divide)

DECL_UNARY_RUBY_ACCESSOR(sin)
DECL_UNARY_RUBY_ACCESSOR(cos)
DECL_UNARY_RUBY_ACCESSOR(tan)
DECL_UNARY_RUBY_ACCESSOR(asin)
DECL_UNARY_RUBY_ACCESSOR(acos)
DECL_UNARY_RUBY_ACCESSOR(atan)
DECL_UNARY_RUBY_ACCESSOR(sinh)
DECL_UNARY_RUBY_ACCESSOR(cosh)
DECL_UNARY_RUBY_ACCESSOR(tanh)
DECL_UNARY_RUBY_ACCESSOR(asinh)
DECL_UNARY_RUBY_ACCESSOR(acosh)
DECL_UNARY_RUBY_ACCESSOR(atanh)
DECL_UNARY_RUBY_ACCESSOR(exp)
DECL_UNARY_RUBY_ACCESSOR(log2)
DECL_UNARY_RUBY_ACCESSOR(log1p)
DECL_UNARY_RUBY_ACCESSOR(log10)
DECL_UNARY_RUBY_ACCESSOR(sqrt)
DECL_UNARY_RUBY_ACCESSOR(erf)
DECL_UNARY_RUBY_ACCESSOR(erfc)
DECL_UNARY_RUBY_ACCESSOR(cbrt)
DECL_UNARY_RUBY_ACCESSOR(lgamma)
DECL_UNARY_RUBY_ACCESSOR(tgamma)
DECL_UNARY_RUBY_ACCESSOR(floor)
DECL_UNARY_RUBY_ACCESSOR(ceil)

/*
 * Macro defines an element-wise accessor function for some operation.
 *
 * This is only responsible for the Ruby accessor! You still have to write the actual functions, obviously.
 */

static VALUE arf_eqeq(VALUE left_val, VALUE right_val);


static VALUE arf_matmul(VALUE self, VALUE left_val, VALUE right_val);

void Init_arrayfire() {
  ArrayFire = rb_define_module("ArrayFire");

  Af_Array = rb_define_class_under(ArrayFire, "Af_Array", rb_cObject);
  rb_define_alloc_func(Af_Array, arf_alloc);
  rb_define_method(Af_Array, "initialize", (METHOD)arf_init, -1);
  rb_define_method(Af_Array, "+",(METHOD)arf_ew_add,1);
  rb_define_method(Af_Array, "-",(METHOD)arf_ew_subtract,1);
  rb_define_method(Af_Array, "*",(METHOD)arf_ew_multiply,1);
  rb_define_method(Af_Array, "/",(METHOD)arf_ew_divide,1);
  rb_define_method(Af_Array, "==",(METHOD)arf_eqeq,1);

  rb_define_method(Af_Array, "sin", (METHOD)arf_unary_sin, 0);
  rb_define_method(Af_Array, "cos", (METHOD)arf_unary_cos, 0);
  rb_define_method(Af_Array, "tan", (METHOD)arf_unary_tan, 0);
  rb_define_method(Af_Array, "asin", (METHOD)arf_unary_asin, 0);
  rb_define_method(Af_Array, "acos", (METHOD)arf_unary_acos, 0);
  rb_define_method(Af_Array, "atan", (METHOD)arf_unary_atan, 0);
  rb_define_method(Af_Array, "sinh", (METHOD)arf_unary_sinh, 0);
  rb_define_method(Af_Array, "cosh", (METHOD)arf_unary_cosh, 0);
  rb_define_method(Af_Array, "tanh", (METHOD)arf_unary_tanh, 0);
  rb_define_method(Af_Array, "asinh", (METHOD)arf_unary_asinh, 0);
  rb_define_method(Af_Array, "acosh", (METHOD)arf_unary_acosh, 0);
  rb_define_method(Af_Array, "atanh", (METHOD)arf_unary_atanh, 0);
  rb_define_method(Af_Array, "exp", (METHOD)arf_unary_exp, 0);
  rb_define_method(Af_Array, "log2", (METHOD)arf_unary_log2, 0);
  rb_define_method(Af_Array, "log1p", (METHOD)arf_unary_log1p, 0);
  rb_define_method(Af_Array, "log10", (METHOD)arf_unary_log10, 0);
  rb_define_method(Af_Array, "sqrt", (METHOD)arf_unary_sqrt, 0);
  rb_define_method(Af_Array, "erf", (METHOD)arf_unary_erf, 0);
  rb_define_method(Af_Array, "erfc", (METHOD)arf_unary_erfc, 0);
  rb_define_method(Af_Array, "cbrt", (METHOD)arf_unary_cbrt, 0);
  rb_define_method(Af_Array, "lgamma", (METHOD)arf_unary_lgamma, 0);
  rb_define_method(Af_Array, "tgamma", (METHOD)arf_unary_tgamma, 0);
  rb_define_method(Af_Array, "floor", (METHOD)arf_unary_floor, 0);
  rb_define_method(Af_Array, "ceil", (METHOD)arf_unary_ceil, 0);

  Algorithm = rb_define_class_under(ArrayFire, "Algorithm", rb_cObject);
  rb_define_singleton_method(Algorithm, "sum", (METHOD)arf_sum, 0);
  rb_define_singleton_method(Algorithm, "sum_nan", (METHOD)arf_sum_nan, 0);
  rb_define_singleton_method(Algorithm, "product", (METHOD)arf_product, 0);
  rb_define_singleton_method(Algorithm, "product_nan", (METHOD)arf_product_nan, 0);
  rb_define_singleton_method(Algorithm, "min", (METHOD)arf_min, 0);
  rb_define_singleton_method(Algorithm, "max", (METHOD)arf_max, 0);
  rb_define_singleton_method(Algorithm, "all_true", (METHOD)arf_all_true, 0);
  rb_define_singleton_method(Algorithm, "any_true", (METHOD)arf_any_true, 0);
  rb_define_singleton_method(Algorithm, "count", (METHOD)arf_count, 0);
  rb_define_singleton_method(Algorithm, "sum_all", (METHOD)arf_sum_all, 0);
  rb_define_singleton_method(Algorithm, "sum_nan_all", (METHOD)arf_sum_nan_all, 0);
  rb_define_singleton_method(Algorithm, "product_all", (METHOD)arf_product_all, 0);
  rb_define_singleton_method(Algorithm, "product_nan_all", (METHOD)arf_product_nan_all, 0);
  rb_define_singleton_method(Algorithm, "min_all", (METHOD)arf_min_all, 0);
  rb_define_singleton_method(Algorithm, "max_all", (METHOD)arf_max_all, 0);
  rb_define_singleton_method(Algorithm, "all_true_all", (METHOD)arf_all_true_all, 0);
  rb_define_singleton_method(Algorithm, "any_true_all", (METHOD)arf_any_true_all, 0);
  rb_define_singleton_method(Algorithm, "count_all", (METHOD)arf_count_all, 0);
  rb_define_singleton_method(Algorithm, "imin", (METHOD)arf_imin, 0);
  rb_define_singleton_method(Algorithm, "imax", (METHOD)arf_imax, 0);
  rb_define_singleton_method(Algorithm, "imin_all", (METHOD)arf_imin_all, 0);
  rb_define_singleton_method(Algorithm, "imax_all", (METHOD)arf_imax_all, 0);
  rb_define_singleton_method(Algorithm, "accum", (METHOD)arf_accum, 0);
  rb_define_singleton_method(Algorithm, "scan", (METHOD)arf_scan, 0);
  rb_define_singleton_method(Algorithm, "scan_by_key", (METHOD)arf_scan_by_key, 0);
  rb_define_singleton_method(Algorithm, "where", (METHOD)arf_where, 0);
  rb_define_singleton_method(Algorithm, "diff1", (METHOD)arf_diff1, 0);
  rb_define_singleton_method(Algorithm, "diff2", (METHOD)arf_diff2, 0);
  rb_define_singleton_method(Algorithm, "sort", (METHOD)arf_sort, 0);
  rb_define_singleton_method(Algorithm, "sort_index", (METHOD)arf_sort_index, 0);
  rb_define_singleton_method(Algorithm, "sort_by_key", (METHOD)arf_sort_by_key, 0);
  rb_define_singleton_method(Algorithm, "set_unique", (METHOD)arf_set_unique, 0);
  rb_define_singleton_method(Algorithm, "set_union", (METHOD)arf_set_union, 0);
  rb_define_singleton_method(Algorithm, "set_intersect", (METHOD)arf_set_intersect, 0);

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
  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = (dim_t*)malloc(ndims * sizeof(dim_t));
  dim_t count = 1;
  for (size_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }
  float* host_array = (float*)malloc(count * sizeof(float));
  for (size_t index = 0; index < count; index++) {
    host_array[index] = (float)NUM2DBL(RARRAY_AREF(argv[2], index));
  }

  af_create_array(&afarray->carray, host_array, 2, dimensions, f32);

  af_print_array(afarray->carray);

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

static VALUE arf_eqeq(VALUE left_val, VALUE right_val) {
  return Qnil;
}

DEF_ELEMENTWISE_RUBY_ACCESSOR(add, add)
DEF_ELEMENTWISE_RUBY_ACCESSOR(subtract, sub)
DEF_ELEMENTWISE_RUBY_ACCESSOR(multiply, mul)
DEF_ELEMENTWISE_RUBY_ACCESSOR(divide, div)

DEF_UNARY_RUBY_ACCESSOR(sin, sin)
DEF_UNARY_RUBY_ACCESSOR(cos, cos)
DEF_UNARY_RUBY_ACCESSOR(tan, tan)
DEF_UNARY_RUBY_ACCESSOR(asin, asin)
DEF_UNARY_RUBY_ACCESSOR(acos, acos)
DEF_UNARY_RUBY_ACCESSOR(atan, atan)
DEF_UNARY_RUBY_ACCESSOR(sinh, sinh)
DEF_UNARY_RUBY_ACCESSOR(cosh, cosh)
DEF_UNARY_RUBY_ACCESSOR(tanh, tanh)
DEF_UNARY_RUBY_ACCESSOR(asinh, asinh)
DEF_UNARY_RUBY_ACCESSOR(acosh, acosh)
DEF_UNARY_RUBY_ACCESSOR(atanh, atanh)
DEF_UNARY_RUBY_ACCESSOR(exp, exp)
DEF_UNARY_RUBY_ACCESSOR(log2, log2)
DEF_UNARY_RUBY_ACCESSOR(log1p, log1p)
DEF_UNARY_RUBY_ACCESSOR(log10, log10)
DEF_UNARY_RUBY_ACCESSOR(sqrt, sqrt)
DEF_UNARY_RUBY_ACCESSOR(erf, erf)
DEF_UNARY_RUBY_ACCESSOR(erfc, erfc)
DEF_UNARY_RUBY_ACCESSOR(cbrt, cbrt)
DEF_UNARY_RUBY_ACCESSOR(lgamma, lgamma)
DEF_UNARY_RUBY_ACCESSOR(tgamma, tgamma)
DEF_UNARY_RUBY_ACCESSOR(floor, floor)
DEF_UNARY_RUBY_ACCESSOR(ceil, ceil)

// Algorithm

#include "cmodules/algorithm.c"

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

#include "cmodules/blas.c"

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

#include "cmodules/device.c"
#include "cmodules/opencl.c"
#include "cmodules/data.c"
#include "cmodules/lapack.c"
#include "cmodules/random.c"
