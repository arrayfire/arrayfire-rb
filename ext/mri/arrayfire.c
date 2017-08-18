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
VALUE Index = Qnil;
VALUE Lapack = Qnil;
VALUE OpenCL = Qnil;
VALUE Random = Qnil;
VALUE Sparse = Qnil;
VALUE Statistics = Qnil;
VALUE Util = Qnil;

// prototypes
void Init_arrayfire();

const char* get_backend_name(af_backend backend);
const char* get_cl_device_name(afcl_device_type device);
const char* get_cl_platform_name(afcl_platform platform);
const char* get_random_engine_name(af_random_engine_type engine);

af_backend arf_backend_type_from_rbsymbol(VALUE sym);
af_dtype arf_dtype_from_rbsymbol(VALUE sym);
af_mat_prop arf_mat_type_from_rbsymbol(VALUE sym);
af_moment_type arf_moment_type_from_rbsymbol(VALUE sym);
af_norm_type arf_norm_type_from_rbsymbol(VALUE sym);
af_random_engine_type arf_randome_engine_type_from_rbsymbol(VALUE sym);
af_source arf_source_from_rbsymbol(VALUE sym);

static VALUE arf_init(int argc, VALUE* argv, VALUE self);
static VALUE arf_alloc(VALUE klass);
static void arf_free(afstruct* af);
static VALUE arf_engine_alloc(VALUE klass);
static void arf_engine_free(afrandomenginestruct* afrandomengine);

// Af_Array
static VALUE arf_create_array(int argc, VALUE* argv);
static VALUE arf_create_handle(int argc, VALUE* argv);
static VALUE arf_copy_array(VALUE self);
static VALUE arf_write_array(VALUE self);
static VALUE arf_get_data_ptr(VALUE self);
static void arf_release_array(VALUE self);
static VALUE arf_retain_array(VALUE self);
static VALUE arf_get_data_ref_count(VALUE self);
static VALUE arf_eval(VALUE self);
static VALUE arf_eval_multiple(VALUE self);
static VALUE arf_set_manual_eval_flag(VALUE self, VALUE flag);
static VALUE arf_get_manual_eval_flag(VALUE self);
static VALUE arf_get_elements(VALUE self);
static VALUE arf_get_type(VALUE self);
static VALUE arf_get_dims(VALUE self);
static VALUE arf_get_numdims(VALUE self);
static VALUE arf_is_empty(VALUE self);
static VALUE arf_is_scalar(VALUE self);
static VALUE arf_is_row(VALUE self);
static VALUE arf_is_column(VALUE self);
static VALUE arf_is_vector(VALUE self);
static VALUE arf_is_complex(VALUE self);
static VALUE arf_is_real(VALUE self);
static VALUE arf_is_double(VALUE self);
static VALUE arf_is_single(VALUE self);
static VALUE arf_is_realfloating(VALUE self);
static VALUE arf_is_floating(VALUE self);
static VALUE arf_is_integer(VALUE self);
static VALUE arf_is_bool(VALUE self);
static VALUE arf_is_sparse(VALUE self);

// Algorithm
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

// Backend
static VALUE arf_get_backend_count(VALUE self);
static VALUE arf_get_available_backends(VALUE self);
static VALUE arf_get_backend_id(VALUE self, VALUE array_val);
static VALUE arf_get_active_backend(VALUE self);
static VALUE arf_get_backend_device_id(VALUE self, VALUE array_val);
static VALUE arf_set_backend(VALUE self, VALUE backend_val);

// BLAS
static VALUE arf_matmul(VALUE self, VALUE left_val, VALUE right_val, VALUE left_prop_val, VALUE right_prop_val);
static VALUE arf_dot(VALUE self, VALUE left_val, VALUE right_val, VALUE left_prop_val, VALUE right_prop_val);
static VALUE arf_transpose(VALUE self, VALUE input);
static VALUE arf_transpose_inplace(VALUE self, VALUE input);

// CUDA
static VALUE arf_get_stream(VALUE self, VALUE id);
static VALUE arf_get_native_id(VALUE self, VALUE cuda_device_id);
static VALUE arf_set_native_id(VALUE self, VALUE native_id);

// Device
static VALUE arf_info(VALUE self);
static VALUE arf_init2(VALUE self);
static VALUE arf_info_string(VALUE self, VALUE bool_val);
static VALUE arf_device_info(VALUE self);
static VALUE arf_get_device_count(VALUE self);
static VALUE arf_get_dbl_support(VALUE self, VALUE device);
static VALUE arf_set_device(VALUE self, VALUE device);
static VALUE arf_get_device(VALUE self);
static VALUE arf_sync(VALUE self, VALUE device_val);
static VALUE arf_alloc_device(VALUE self);
static VALUE arf_free_device(VALUE self);
static VALUE arf_alloc_pinned(VALUE self);
static VALUE arf_free_pinned(VALUE self);
static VALUE arf_alloc_host(VALUE self);
static VALUE arf_free_host(VALUE self);
static VALUE arf_device_array(VALUE self);
static VALUE arf_device_mem_info(VALUE self);
static VALUE arf_print_mem_info(VALUE self,  VALUE msg_val, VALUE device_id_val);
static void arf_device_gc(VALUE self);
static VALUE arf_set_mem_step_size(VALUE self, VALUE step_bytes);
static VALUE arf_get_mem_step_size(VALUE self);
static VALUE arf_lock_device_ptr(VALUE self, VALUE array_val);
static VALUE arf_unlock_device_ptr(VALUE self, VALUE array_val);
static VALUE arf_lock_array(VALUE self, VALUE array_val);
static VALUE arf_unlock_array(VALUE self, VALUE array_val);
static VALUE arf_is_locked_array(VALUE self, VALUE array_val);
static VALUE arf_get_device_ptr(VALUE self);

// OpenCL
static VALUE arf_get_context(VALUE self);
static VALUE arf_get_queue(VALUE self);
static VALUE arf_get_device_id(VALUE self);
static VALUE arf_set_device_id(VALUE self);
static VALUE arf_add_device_context(VALUE self);
static VALUE arf_set_device_context(VALUE self);
static VALUE arf_delete_device_context(VALUE self);
static VALUE arf_get_device_type(VALUE self);
static VALUE arf_get_platform(VALUE self);

// Data
static VALUE arf_constant(int argc, VALUE* argv);
static VALUE arf_constant_complex(VALUE self);
static VALUE arf_constant_long(int argc, VALUE* argv);
static VALUE arf_constant_ulong(int argc, VALUE* argv);
static VALUE arf_range(int argc, VALUE* argv);
static VALUE arf_iota(VALUE self);
static VALUE arf_identity(int argc, VALUE* argv);
static VALUE arf_diag_create(VALUE self, VALUE array_val, VALUE num_val);
static VALUE arf_diag_extract(VALUE self, VALUE array_val, VALUE num_val);
static VALUE arf_join(VALUE self, VALUE dim_val, VALUE first_array_val, VALUE second_array_val);
static VALUE arf_join_many(VALUE self);
static VALUE arf_tile(VALUE self, VALUE array_val, VALUE x_val, VALUE y_val, VALUE z_val, VALUE w_val);
static VALUE arf_reorder(VALUE self, VALUE array_val, VALUE x_val, VALUE y_val, VALUE z_val, VALUE w_val);
static VALUE arf_shift(VALUE self, VALUE array_val, VALUE x_val, VALUE y_val, VALUE z_val, VALUE w_val);
static VALUE arf_moddims(VALUE self);
static VALUE arf_flat(VALUE self, VALUE array_val);
static VALUE arf_flip(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_lower(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_upper(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_select(VALUE self, VALUE array_cond_val, VALUE array_a_val, VALUE array_b_val);
static VALUE arf_select_scalar_r(VALUE self, VALUE array_cond_val, VALUE array_a_val, VALUE b_val);
static VALUE arf_select_scalar_l(VALUE self, VALUE array_cond_val, VALUE a_val, VALUE array_b_val);
static void arf_replace(VALUE self, VALUE array_input_val, VALUE array_cond_val, VALUE array_b_val);
static void arf_replace_scalar(VALUE self, VALUE array_input_val, VALUE array_cond_val, VALUE b_val);

// Index
static VALUE arf_index(VALUE self);
static VALUE arf_lookup(VALUE self);
static VALUE arf_assign_seq(VALUE self);
static VALUE arf_index_gen(VALUE self);
static VALUE arf_assign_gen(VALUE self);
static VALUE arf_create_indexers(VALUE self);
static VALUE arf_set_array_indexer(VALUE self);
static VALUE arf_set_seq_indexer(VALUE self);
static VALUE arf_set_seq_param_indexer(VALUE self);
static VALUE arf_release_indexers(VALUE self);

// LAPACK
static VALUE arf_svd_func(VALUE self, VALUE u_val, VALUE s_val, VALUE vt_val, VALUE val);
static VALUE arf_svd_inplace_func(VALUE self, VALUE val);
static VALUE arf_lu_func(VALUE self, VALUE lower_val, VALUE upper_val, VALUE pivot_val, VALUE val);
static VALUE arf_lu_inplace_func(VALUE self);
static VALUE arf_qr_func(VALUE self, VALUE q_val, VALUE r_val, VALUE tau_val, VALUE val);
static VALUE arf_qr_inplace_func(VALUE self);
static VALUE arf_cholesky_func(VALUE self, VALUE output_val, VALUE val, VALUE is_upper_val);
static VALUE arf_cholesky_inplace_func(VALUE self);
static VALUE arf_solve(VALUE self, VALUE lhs_val, VALUE rhs_val);
static VALUE arf_solve_lu(VALUE self, VALUE lhs_val, VALUE rhs_val, VALUE piv_val);
static VALUE arf_inverse(VALUE self, VALUE val);
static VALUE arf_rank(VALUE self, VALUE val);
static VALUE arf_det(VALUE self, VALUE val);
static VALUE arf_norm(VALUE self, VALUE val);
static VALUE arf_is_lapack_available(VALUE self);

// Random
static VALUE arf_create_random_engine(VALUE self, VALUE seed_val);
static VALUE arf_retain_random_engine(VALUE self, VALUE engine_val);
static VALUE arf_random_engine_set_type(VALUE self, VALUE engine_val, VALUE type_val);
static VALUE arf_random_engine_get_type(VALUE self, VALUE engine_val);
static VALUE arf_random_uniform(VALUE self, VALUE ndims_val, VALUE dim_val, VALUE engine_val);
static VALUE arf_random_normal(VALUE self, VALUE ndims_val, VALUE dim_val, VALUE engine_val);
static VALUE arf_random_engine_set_seed(VALUE self, VALUE engine_val ,VALUE seed_val);
static VALUE arf_get_default_random_engine(VALUE self);
static VALUE arf_set_default_random_engine_type(VALUE self, VALUE type_val);
static VALUE arf_random_engine_get_seed(VALUE self, VALUE engine_val);
static VALUE arf_release_random_engine(VALUE self, VALUE engine_val);
static VALUE arf_randu(VALUE self, VALUE ndims_val, VALUE dim_val);
static VALUE arf_randn(VALUE self, VALUE ndims_val, VALUE dim_val);
static VALUE arf_set_seed(VALUE self, VALUE seed);
static VALUE arf_get_seed(VALUE self);

// Sparse
static VALUE arf_create_sparse_array(VALUE self, VALUE shape_array, VALUE values_array, VALUE rowIdx_val, VALUE colIdx_val, VALUE stype_val);
static VALUE arf_create_sparse_array_from_ptr(VALUE self);
static VALUE arf_create_sparse_array_from_dense(VALUE self, VALUE dense_val, VALUE stype_val);
static VALUE arf_sparse_convert_to(VALUE self, VALUE input_val, VALUE dest_storage_val);
static VALUE arf_sparse_to_dense(VALUE self, VALUE sparse_array);
static VALUE arf_sparse_get_info_func(VALUE self, VALUE values_val, VALUE rowIdx_val, VALUE colIdx_val, VALUE input_val);
static VALUE arf_sparse_get_values(VALUE self, VALUE input_val);
static VALUE arf_sparse_get_row_idx(VALUE self, VALUE input_val);
static VALUE arf_sparse_get_col_idx(VALUE self, VALUE input_val);
static VALUE arf_sparse_get_nnz(VALUE self, VALUE input_val);
static VALUE arf_sparse_get_storage(VALUE self, VALUE input_val);

// Statistics
static VALUE arf_mean(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_mean_weighted(VALUE self, VALUE array_val, VALUE weighted_array_val, VALUE dim_val);
static VALUE arf_var(VALUE self, VALUE array_val, VALUE is_biased, VALUE dim_val);
static VALUE arf_var_weighted(VALUE self, VALUE array_val, VALUE weighted_array_val, VALUE dim_val);
static VALUE arf_stdev(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_cov(VALUE self, VALUE first_array_val, VALUE second_array_val, VALUE is_biased);
static VALUE arf_median(VALUE self, VALUE array_val, VALUE dim_val);
static VALUE arf_mean_all(VALUE self, VALUE array_val);
static VALUE arf_mean_all_weighted(VALUE self, VALUE array_val, VALUE weighted_array_val);
static VALUE arf_var_all(VALUE self, VALUE array_val, VALUE is_biased);
static VALUE arf_var_all_weighted(VALUE self, VALUE array_val, VALUE weighted_array_val);
static VALUE arf_stdev_all(VALUE self, VALUE array_val);
static VALUE arf_median_all(VALUE self, VALUE array_val);
static VALUE arf_corrcoef(VALUE self, VALUE first_array_val, VALUE second_array_val);

// Util
static VALUE arf_print_array(VALUE self, VALUE input_val);
static VALUE arf_print_array_gen(VALUE self);
static VALUE arf_save_array(VALUE self, VALUE key_val, VALUE array_val, VALUE fn_val, VALUE append);
static VALUE arf_read_array_index(VALUE self);
static VALUE arf_read_array_key(VALUE self);
static VALUE arf_read_array_key_check(VALUE self);
static VALUE arf_array_to_string(VALUE self, VALUE exp_val, VALUE array_val, VALUE precision, VALUE transpose);
static VALUE arf_example_function(VALUE self);
static VALUE arf_get_version(VALUE self, VALUE major, VALUE minor, VALUE patch);
static VALUE arf_get_revision(VALUE self);
static VALUE arf_get_size_of(VALUE self, VALUE dtype_val);

#define DECL_ELEMENTWISE_RUBY_ACCESSOR(name)    static VALUE arf_ew_##name(VALUE left_val, VALUE right_val);
#define DECL_UNARY_RUBY_ACCESSOR(name)          static VALUE arf_unary_##name(VALUE self);

DECL_ELEMENTWISE_RUBY_ACCESSOR(add)
DECL_ELEMENTWISE_RUBY_ACCESSOR(subtract)
DECL_ELEMENTWISE_RUBY_ACCESSOR(multiply)
DECL_ELEMENTWISE_RUBY_ACCESSOR(divide)

DECL_ELEMENTWISE_RUBY_ACCESSOR(eqeq)
DECL_ELEMENTWISE_RUBY_ACCESSOR(neq)
DECL_ELEMENTWISE_RUBY_ACCESSOR(leq)
DECL_ELEMENTWISE_RUBY_ACCESSOR(geq)
DECL_ELEMENTWISE_RUBY_ACCESSOR(lt)
DECL_ELEMENTWISE_RUBY_ACCESSOR(gt)

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
static VALUE arf_eqeq_approx(VALUE left_val, VALUE right_val);

void Init_arrayfire() {
  ArrayFire = rb_define_module("ArrayFire");

  Af_Array = rb_define_class_under(ArrayFire, "Af_Array", rb_cObject);
  rb_define_alloc_func(Af_Array, arf_alloc);
  rb_define_method(Af_Array, "initialize", (METHOD)arf_init, -1);
  rb_define_singleton_method(Af_Array, "create_array", (METHOD)arf_create_array, -1);
  rb_define_singleton_method(Af_Array, "create_handle", (METHOD)arf_create_handle, -1);
  rb_define_method(Af_Array, "copy_array", (METHOD)arf_copy_array, 0);
  rb_define_method(Af_Array, "write_array", (METHOD)arf_write_array, 0);
  rb_define_method(Af_Array, "get_data_ptr", (METHOD)arf_get_data_ptr, 0);
  rb_define_method(Af_Array, "release_array", (METHOD)arf_release_array, 0);
  rb_define_method(Af_Array, "retain_array", (METHOD)arf_retain_array, 0);
  rb_define_method(Af_Array, "get_data_ref_count", (METHOD)arf_get_data_ref_count, 0);
  rb_define_method(Af_Array, "eval", (METHOD)arf_eval, 0);
  rb_define_method(Af_Array, "eval_multiple", (METHOD)arf_eval_multiple, 0);
  rb_define_singleton_method(Af_Array, "set_manual_eval_flag", (METHOD)arf_set_manual_eval_flag, 1);
  rb_define_singleton_method(Af_Array, "get_manual_eval_flag", (METHOD)arf_get_manual_eval_flag, 0);
  rb_define_method(Af_Array, "get_elements", (METHOD)arf_get_elements, 0);
  rb_define_method(Af_Array, "get_type", (METHOD)arf_get_type, 0);
  rb_define_method(Af_Array, "get_dims", (METHOD)arf_get_dims, 0);
  rb_define_method(Af_Array, "get_numdims", (METHOD)arf_get_numdims, 0);
  rb_define_method(Af_Array, "is_empty", (METHOD)arf_is_empty, 0);
  rb_define_method(Af_Array, "is_scalar", (METHOD)arf_is_scalar, 0);
  rb_define_method(Af_Array, "is_row", (METHOD)arf_is_row, 0);
  rb_define_method(Af_Array, "is_column", (METHOD)arf_is_column, 0);
  rb_define_method(Af_Array, "is_vector", (METHOD)arf_is_vector, 0);
  rb_define_method(Af_Array, "is_complex", (METHOD)arf_is_complex, 0);
  rb_define_method(Af_Array, "is_real", (METHOD)arf_is_real, 0);
  rb_define_method(Af_Array, "is_double", (METHOD)arf_is_double, 0);
  rb_define_method(Af_Array, "is_single", (METHOD)arf_is_single, 0);
  rb_define_method(Af_Array, "is_realfloating", (METHOD)arf_is_realfloating, 0);
  rb_define_method(Af_Array, "is_floating", (METHOD)arf_is_floating, 0);
  rb_define_method(Af_Array, "is_integer", (METHOD)arf_is_integer, 0);
  rb_define_method(Af_Array, "is_bool", (METHOD)arf_is_bool, 0);
  rb_define_method(Af_Array, "is_sparse", (METHOD)arf_is_sparse, 0);

  rb_define_alias(Af_Array, "ndims", "get_numdims");
  rb_define_alias(Af_Array, "dims", "get_dims");
  rb_define_alias(Af_Array, "to_cpu", "get_data_ptr");
  rb_define_alias(Af_Array, "elements", "get_data_ptr");

  rb_define_method(Af_Array, "+",(METHOD)arf_ew_add,1);
  rb_define_method(Af_Array, "-",(METHOD)arf_ew_subtract,1);
  rb_define_method(Af_Array, "*",(METHOD)arf_ew_multiply,1);
  rb_define_method(Af_Array, "/",(METHOD)arf_ew_divide,1);
  rb_define_method(Af_Array, "==",(METHOD)arf_eqeq,1);
  rb_define_method(Af_Array, "approx_equal",(METHOD)arf_eqeq_approx,1);

  rb_define_method(Af_Array, "=~",(METHOD)arf_ew_eqeq,1);
  rb_define_method(Af_Array, "!~", (METHOD)arf_ew_neq, 1);
  rb_define_method(Af_Array, "<=", (METHOD)arf_ew_leq, 1);
  rb_define_method(Af_Array, ">=", (METHOD)arf_ew_geq, 1);
  rb_define_method(Af_Array, "<", (METHOD)arf_ew_lt, 1);
  rb_define_method(Af_Array, ">", (METHOD)arf_ew_gt, 1);

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
  rb_define_singleton_method(Algorithm, "sum", (METHOD)arf_sum, 2);
  rb_define_singleton_method(Algorithm, "sum_nan", (METHOD)arf_sum_nan, 3);
  rb_define_singleton_method(Algorithm, "product", (METHOD)arf_product, 2);
  rb_define_singleton_method(Algorithm, "product_nan", (METHOD)arf_product_nan, 3);
  rb_define_singleton_method(Algorithm, "min", (METHOD)arf_min, 2);
  rb_define_singleton_method(Algorithm, "max", (METHOD)arf_max, 2);
  rb_define_singleton_method(Algorithm, "all_true", (METHOD)arf_all_true, 2);
  rb_define_singleton_method(Algorithm, "any_true", (METHOD)arf_any_true, 2);
  rb_define_singleton_method(Algorithm, "count", (METHOD)arf_count, 2);
  rb_define_singleton_method(Algorithm, "sum_all", (METHOD)arf_sum_all, 1);
  rb_define_singleton_method(Algorithm, "sum_nan_all", (METHOD)arf_sum_nan_all, 2);
  rb_define_singleton_method(Algorithm, "product_all", (METHOD)arf_product_all, 1);
  rb_define_singleton_method(Algorithm, "product_nan_all", (METHOD)arf_product_nan_all, 2);
  rb_define_singleton_method(Algorithm, "min_all", (METHOD)arf_min_all, 1);
  rb_define_singleton_method(Algorithm, "max_all", (METHOD)arf_max_all, 1);
  rb_define_singleton_method(Algorithm, "all_true_all", (METHOD)arf_all_true_all, 1);
  rb_define_singleton_method(Algorithm, "any_true_all", (METHOD)arf_any_true_all, 1);
  rb_define_singleton_method(Algorithm, "count_all", (METHOD)arf_count_all, 1);
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
  rb_define_singleton_method(Backend, "get_backend_count", (METHOD)arf_get_backend_count, 0);
  rb_define_singleton_method(Backend, "get_available_backends", (METHOD)arf_get_available_backends, 0);
  rb_define_singleton_method(Backend, "get_backend_id", (METHOD)arf_get_backend_id, 1);
  rb_define_singleton_method(Backend, "get_active_backend", (METHOD)arf_get_active_backend, 0);
  rb_define_singleton_method(Backend, "get_device_id", (METHOD)arf_get_backend_device_id, 1);
  rb_define_singleton_method(Backend, "set_backend", (METHOD)arf_set_backend, 1);

  Device = rb_define_class_under(ArrayFire, "Device", rb_cObject);
  rb_define_singleton_method(Device, "info", (METHOD)arf_info, 0);
  rb_define_singleton_method(Device, "init", (METHOD)arf_init2, 0);
  rb_define_singleton_method(Device, "info_string", (METHOD)arf_info_string, 0);
  rb_define_singleton_method(Device, "device_info", (METHOD)arf_device_info, 0);
  rb_define_singleton_method(Device, "get_device_count", (METHOD)arf_get_device_count, 0);
  rb_define_singleton_method(Device, "get_dbl_support", (METHOD)arf_get_dbl_support, 1);
  rb_define_singleton_method(Device, "set_device", (METHOD)arf_set_device, 1);
  rb_define_singleton_method(Device, "get_device", (METHOD)arf_get_device, 0);
  rb_define_singleton_method(Device, "sync", (METHOD)arf_sync, 1);
  rb_define_singleton_method(Device, "alloc_device", (METHOD)arf_alloc_device, 0);
  rb_define_singleton_method(Device, "free_device", (METHOD)arf_free_device, 0);
  rb_define_singleton_method(Device, "alloc_pinned", (METHOD)arf_alloc_pinned, 0);
  rb_define_singleton_method(Device, "free_pinned", (METHOD)arf_free_pinned, 0);
  rb_define_singleton_method(Device, "alloc_host", (METHOD)arf_alloc_host, 0);
  rb_define_singleton_method(Device, "free_host", (METHOD)arf_free_host, 0);
  rb_define_singleton_method(Device, "device_array", (METHOD)arf_device_array, 0);
  rb_define_singleton_method(Device, "device_mem_info", (METHOD)arf_device_mem_info, 0);
  rb_define_singleton_method(Device, "print_mem_info", (METHOD)arf_print_mem_info, 2);
  rb_define_singleton_method(Device, "device_gc", (METHOD)arf_device_gc, 0);
  rb_define_singleton_method(Device, "set_mem_step_size", (METHOD)arf_set_mem_step_size, 1);
  rb_define_singleton_method(Device, "get_mem_step_size", (METHOD)arf_get_mem_step_size, 0);
  rb_define_singleton_method(Device, "lock_device_ptr", (METHOD)arf_lock_device_ptr, 1);
  rb_define_singleton_method(Device, "unlock_device_ptr", (METHOD)arf_unlock_device_ptr, 1);
  rb_define_singleton_method(Device, "lock_array", (METHOD)arf_lock_array, 1);
  rb_define_singleton_method(Device, "unlock_array", (METHOD)arf_unlock_array, 1);
  rb_define_singleton_method(Device, "is_locked_array", (METHOD)arf_is_locked_array, 1);
  rb_define_singleton_method(Device, "get_device_ptr", (METHOD)arf_get_device_ptr, 0);

  Blas = rb_define_class_under(ArrayFire, "BLAS", rb_cObject);
  rb_define_singleton_method(Blas, "matmul", (METHOD)arf_matmul, 4);
  rb_define_singleton_method(Blas, "dot", (METHOD)arf_dot, 4);
  rb_define_singleton_method(Blas, "transpose", (METHOD)arf_transpose, 1);
  rb_define_singleton_method(Blas, "transpose_inplace", (METHOD)arf_transpose_inplace, 1);

  Cuda = rb_define_class_under(ArrayFire, "CUDA", rb_cObject);
  rb_define_singleton_method(Cuda, "get_stream", (METHOD)arf_get_stream, 1);
  rb_define_singleton_method(Cuda, "get_native_id", (METHOD)arf_get_native_id, 1);
  rb_define_singleton_method(Cuda, "set_native_id", (METHOD)arf_set_native_id, 1);

  Index = rb_define_class_under(ArrayFire, "Index", rb_cObject);
  rb_define_singleton_method(Index, "index", (METHOD)arf_index, 0);
  rb_define_singleton_method(Index, "lookup", (METHOD)arf_lookup, 0);
  rb_define_singleton_method(Index, "assign_seq", (METHOD)arf_assign_seq, 0);
  rb_define_singleton_method(Index, "index_gen", (METHOD)arf_index_gen, 0);
  rb_define_singleton_method(Index, "assign_gen", (METHOD)arf_assign_gen, 0);
  rb_define_singleton_method(Index, "create_indexers", (METHOD)arf_create_indexers, 0);
  rb_define_singleton_method(Index, "set_array_indexer", (METHOD)arf_set_array_indexer, 0);
  rb_define_singleton_method(Index, "set_seq_indexer", (METHOD)arf_set_seq_indexer, 0);
  rb_define_singleton_method(Index, "set_seq_param_indexer", (METHOD)arf_set_seq_param_indexer, 0);
  rb_define_singleton_method(Index, "release_indexers", (METHOD)arf_release_indexers, 0);

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
  rb_define_singleton_method(Data, "constant", (METHOD)arf_constant, -1);
  rb_define_singleton_method(Data, "constant_complex", (METHOD)arf_constant_complex, 0);
  rb_define_singleton_method(Data, "constant_long", (METHOD)arf_constant_long, -1);
  rb_define_singleton_method(Data, "constant_ulong", (METHOD)arf_constant_ulong, -1);
  rb_define_singleton_method(Data, "range", (METHOD)arf_range, -1);
  rb_define_singleton_method(Data, "iota", (METHOD)arf_iota, 0);
  rb_define_singleton_method(Data, "identity", (METHOD)arf_identity, -1);
  rb_define_singleton_method(Data, "diag_create", (METHOD)arf_diag_create, 2);
  rb_define_singleton_method(Data, "diag_extract", (METHOD)arf_diag_extract, 2);
  rb_define_singleton_method(Data, "join", (METHOD)arf_join, 3);
  rb_define_singleton_method(Data, "join_many", (METHOD)arf_join_many, 0);
  rb_define_singleton_method(Data, "tile", (METHOD)arf_tile, 5);
  rb_define_singleton_method(Data, "reorder", (METHOD)arf_reorder, 5);
  rb_define_singleton_method(Data, "shift", (METHOD)arf_shift, 5);
  rb_define_singleton_method(Data, "moddims", (METHOD)arf_moddims, 0);
  rb_define_singleton_method(Data, "flat", (METHOD)arf_flat, 1);
  rb_define_singleton_method(Data, "flip", (METHOD)arf_flip, 2);
  rb_define_singleton_method(Data, "lower", (METHOD)arf_lower, 2);
  rb_define_singleton_method(Data, "upper", (METHOD)arf_upper, 2);
  rb_define_singleton_method(Data, "select", (METHOD)arf_select, 3);
  rb_define_singleton_method(Data, "select_scalar_r", (METHOD)arf_select_scalar_r, 3);
  rb_define_singleton_method(Data, "select_scalar_l", (METHOD)arf_select_scalar_l, 3);
  rb_define_singleton_method(Data, "replace", (METHOD)arf_replace, 3);
  rb_define_singleton_method(Data, "replace_scalar", (METHOD)arf_replace_scalar, 3);

  Lapack = rb_define_class_under(ArrayFire, "LAPACK", rb_cObject);
  rb_define_singleton_method(Lapack, "svd_func", (METHOD)arf_svd_func, 4);
  rb_define_singleton_method(Lapack, "svd_inplace_func", (METHOD)arf_svd_inplace_func, 1);
  rb_define_singleton_method(Lapack, "lu_func", (METHOD)arf_lu_func, 4);
  rb_define_singleton_method(Lapack, "lu_inplace_func", (METHOD)arf_lu_inplace_func, 1);
  rb_define_singleton_method(Lapack, "qr_func", (METHOD)arf_qr_func, 4);
  rb_define_singleton_method(Lapack, "qr_inplace_func", (METHOD)arf_qr_inplace_func, 1);
  rb_define_singleton_method(Lapack, "cholesky_func", (METHOD)arf_cholesky_func, 3);
  rb_define_singleton_method(Lapack, "cholesky_inplace_func", (METHOD)arf_cholesky_inplace_func, 1);
  rb_define_singleton_method(Lapack, "solve", (METHOD)arf_solve, 2);
  rb_define_singleton_method(Lapack, "solve_lu", (METHOD)arf_solve_lu, 3);
  rb_define_singleton_method(Lapack, "inverse", (METHOD)arf_inverse, 1);
  rb_define_singleton_method(Lapack, "rank", (METHOD)arf_rank, 1);
  rb_define_singleton_method(Lapack, "det", (METHOD)arf_det, 1);
  rb_define_singleton_method(Lapack, "norm", (METHOD)arf_norm, 1);
  rb_define_singleton_method(Lapack, "is_lapack_available", (METHOD)arf_is_lapack_available, 0);

  Random = rb_define_class_under(ArrayFire, "Random", rb_cObject);
  rb_define_alloc_func(Random, arf_engine_alloc);
  rb_define_singleton_method(Random, "create_random_engine", (METHOD)arf_create_random_engine, 1);
  rb_define_singleton_method(Random, "retain_random_engine", (METHOD)arf_retain_random_engine, 1);
  rb_define_singleton_method(Random, "random_engine_set_type", (METHOD)arf_random_engine_set_type, 2);
  rb_define_singleton_method(Random, "random_engine_get_type", (METHOD)arf_random_engine_get_type, 1);
  rb_define_singleton_method(Random, "random_uniform", (METHOD)arf_random_uniform, 3);
  rb_define_singleton_method(Random, "random_normal", (METHOD)arf_random_normal, 3);
  rb_define_singleton_method(Random, "random_engine_set_seed", (METHOD)arf_random_engine_set_seed, 2);
  rb_define_singleton_method(Random, "get_default_random_engine", (METHOD)arf_get_default_random_engine, 0);
  rb_define_singleton_method(Random, "set_default_random_engine_type", (METHOD)arf_set_default_random_engine_type, 1);
  rb_define_singleton_method(Random, "random_engine_get_seed", (METHOD)arf_random_engine_get_seed, 1);
  rb_define_singleton_method(Random, "release_random_engine", (METHOD)arf_release_random_engine, 1);
  rb_define_singleton_method(Random, "randu", (METHOD)arf_randu, 2);
  rb_define_singleton_method(Random, "randn", (METHOD)arf_randn, 2);
  rb_define_singleton_method(Random, "set_seed", (METHOD)arf_set_seed, 1);
  rb_define_singleton_method(Random, "get_seed", (METHOD)arf_get_seed, 0);

  Sparse = rb_define_class_under(ArrayFire, "Sparse", rb_cObject);
  rb_define_singleton_method(Sparse, "create_sparse_array", (METHOD)arf_create_sparse_array, 5);
  rb_define_singleton_method(Sparse, "create_sparse_array_from_ptr", (METHOD)arf_create_sparse_array_from_ptr, 0);
  rb_define_singleton_method(Sparse, "create_sparse_array_from_dense", (METHOD)arf_create_sparse_array_from_dense, 2);
  rb_define_singleton_method(Sparse, "sparse_convert_to", (METHOD)arf_sparse_convert_to, 2);
  rb_define_singleton_method(Sparse, "sparse_to_dense", (METHOD)arf_sparse_to_dense, 1);
  rb_define_singleton_method(Sparse, "sparse_get_info_func", (METHOD)arf_sparse_get_info_func, 4);
  rb_define_singleton_method(Sparse, "sparse_get_values", (METHOD)arf_sparse_get_values, 1);
  rb_define_singleton_method(Sparse, "sparse_get_row_idx", (METHOD)arf_sparse_get_row_idx, 1);
  rb_define_singleton_method(Sparse, "sparse_get_col_idx", (METHOD)arf_sparse_get_col_idx, 1);
  rb_define_singleton_method(Sparse, "sparse_get_nnz", (METHOD)arf_sparse_get_nnz, 1);
  rb_define_singleton_method(Sparse, "sparse_get_storage", (METHOD)arf_sparse_get_storage, 1);

  Statistics = rb_define_class_under(ArrayFire, "Statistics", rb_cObject);
  rb_define_singleton_method(Statistics, "mean", (METHOD)arf_mean, 2);
  rb_define_singleton_method(Statistics, "mean_weighted", (METHOD)arf_mean_weighted, 3);
  rb_define_singleton_method(Statistics, "var", (METHOD)arf_var, 3);
  rb_define_singleton_method(Statistics, "var_weighted", (METHOD)arf_var_weighted, 3);
  rb_define_singleton_method(Statistics, "stdev", (METHOD)arf_stdev, 2);
  rb_define_singleton_method(Statistics, "cov", (METHOD)arf_cov, 3);
  rb_define_singleton_method(Statistics, "median", (METHOD)arf_median, 2);
  rb_define_singleton_method(Statistics, "mean_all", (METHOD)arf_mean_all, 1);
  rb_define_singleton_method(Statistics, "mean_all_weighted", (METHOD)arf_mean_all_weighted, 2);
  rb_define_singleton_method(Statistics, "var_all", (METHOD)arf_var_all, 2);
  rb_define_singleton_method(Statistics, "var_all_weighted", (METHOD)arf_var_all_weighted, 2);
  rb_define_singleton_method(Statistics, "stdev_all", (METHOD)arf_stdev_all, 1);
  rb_define_singleton_method(Statistics, "median_all", (METHOD)arf_median_all, 1);
  rb_define_singleton_method(Statistics, "corrcoef", (METHOD)arf_corrcoef, 2);

  Util = rb_define_class_under(ArrayFire, "Util", rb_cObject);
  rb_define_singleton_method(Util, "print_array", (METHOD)arf_print_array, 1);
  rb_define_singleton_method(Util, "print_array_gen", (METHOD)arf_print_array_gen, 0);
  rb_define_singleton_method(Util, "save_array", (METHOD)arf_save_array, 4);
  rb_define_singleton_method(Util, "read_array_index", (METHOD)arf_read_array_index, 0);
  rb_define_singleton_method(Util, "read_array_key", (METHOD)arf_read_array_key, 0);
  rb_define_singleton_method(Util, "read_array_key_check", (METHOD)arf_read_array_key_check, 0);
  rb_define_singleton_method(Util, "array_to_string", (METHOD)arf_array_to_string, 4);
  rb_define_singleton_method(Util, "example_function", (METHOD)arf_example_function, 0);
  rb_define_singleton_method(Util, "get_version", (METHOD)arf_get_version, 3);
  rb_define_singleton_method(Util, "get_revision", (METHOD)arf_get_revision, 0);
  rb_define_singleton_method(Util, "get_size_of", (METHOD)arf_get_size_of, 1);

}

/*
 * call-seq:
 *     new(dimesnsion) -> Af_Array
 *     new(dims, dimesnsion, elements, data_type) -> Af_Array
 *
 * Create a new Af_Array.
 *
 */

VALUE arf_init(int argc, VALUE* argv, VALUE self)
{
  afstruct* afarray;
  Data_Get_Struct(self, afstruct, afarray);
  if(argc > 0){
    af_dtype dtype = (argc == 4) ? arf_dtype_from_rbsymbol(argv[3]) : f64;

    dim_t ndims = (dim_t)FIX2LONG(argv[0]);
    dim_t* dimensions = (dim_t*)malloc(ndims * sizeof(dim_t));
    dim_t count = 1;
    for (dim_t index = 0; index < ndims; index++) {
      dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
      count *= dimensions[index];
    }
    double* host_array = (double*)malloc(count * sizeof(double));
    for (dim_t index = 0; index < count; index++) {
      host_array[index] = (double)NUM2DBL(RARRAY_AREF(argv[2], index));
    }

    af_create_array(&afarray->carray, host_array, ndims, dimensions, dtype);
    af_print_array(afarray->carray);
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

static VALUE arf_engine_alloc(VALUE klass)
{
  /* allocate */
  afrandomenginestruct* afrandomengine = ALLOC(afrandomenginestruct);
  /* wrap */
  return Data_Wrap_Struct(klass, NULL, arf_engine_free, afrandomengine);
}

static void arf_free(afstruct* af)
{
  free(af);
}

static void arf_engine_free(afrandomenginestruct* afrandomengine)
{
  free(afrandomengine);
}

static VALUE arf_eqeq(VALUE left_val, VALUE right_val) {
  afstruct* left;
  afstruct* right;
  afstruct* result = ALLOC(afstruct);
  Data_Get_Struct(left_val, afstruct, left);
  Data_Get_Struct(right_val, afstruct, right);
  af_eq(&result->carray,  left->carray, right->carray, true);

  dim_t count;
  af_get_elements(&count, result->carray);
  bool* data = (bool*)malloc(count * sizeof(bool));
  af_get_data_ptr(data, result->carray);

  for (dim_t index = 0; index < count; index++){
    if(!data[index]){
      return Qfalse;
    }
  }
  return Qtrue;
}

static VALUE arf_eqeq_approx(VALUE left_val, VALUE right_val) {

  afstruct* left;
  afstruct* right;

  dim_t left_count;
  dim_t right_count;

  Data_Get_Struct(left_val, afstruct, left);
  Data_Get_Struct(right_val, afstruct, right);

  af_get_elements(&left_count, left->carray);
  af_get_elements(&right_count, right->carray);

  if(left_count != right_count){return Qfalse;}

  double* left_arr = (double*)malloc(left_count * sizeof(double));
  af_get_data_ptr(left_arr, left->carray);

  double* right_arr = (double*)malloc(left_count * sizeof(double));
  af_get_data_ptr(right_arr, right->carray);

  for (dim_t index = 0; index < left_count; index++){
    double diff = left_arr[index] - right_arr[index];
    if(diff < 0){diff *= -1;}
    if(diff > 1e-3){
      return Qfalse;
    }
  }
  return Qtrue;
}

#include "cmodules/array.c"
#include "cmodules/algorithm.c"
#include "cmodules/arith.c"
#include "cmodules/backend.c"
#include "cmodules/blas.c"
#include "cmodules/cuda.c"
#include "cmodules/data.c"
#include "cmodules/defines.c"
#include "cmodules/device.c"
#include "cmodules/index.c"
#include "cmodules/lapack.c"
#include "cmodules/opencl.c"
#include "cmodules/random.c"
#include "cmodules/sparse.c"
#include "cmodules/statistics.c"
#include "cmodules/util.c"
