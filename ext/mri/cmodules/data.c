static VALUE arf_constant(int argc, VALUE* argv){
  afstruct* output = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = ALLOC_N(dim_t, ndims);
  dim_t count = 1;
  for (dim_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }
  double data = NUM2DBL(argv[2]);

  af_err flag = af_constant(&output->carray, data, 2, dimensions, f32);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_constant_complex(VALUE self){
  return Qnil;
}

static VALUE arf_constant_long(int argc, VALUE* argv){
  afstruct* output = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = ALLOC_N(dim_t, ndims);
  dim_t count = 1;
  for (dim_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }
  long data = NUM2LONG(argv[2]);

  af_err flag = af_constant_long(&output->carray, data, 2, dimensions);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_constant_ulong(int argc, VALUE* argv){
  afstruct* output = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = ALLOC_N(dim_t, ndims);
  dim_t count = 1;
  for (dim_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }
  unsigned long data = NUM2LONG(argv[2]);

  af_err flag = af_constant_ulong(&output->carray, data, 2, dimensions);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_range(int argc, VALUE* argv){
  afstruct* output = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = ALLOC_N(dim_t, ndims);
  dim_t count = 1;
  for (dim_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }
  int seq_dim = NUM2INT(argv[2]);
  af_err flag = af_range(&output->carray, ndims, dimensions, seq_dim, f32);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_iota(VALUE self){
  return Qnil;
}

static VALUE arf_identity(int argc, VALUE* argv){
  afstruct* output = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = ALLOC_N(dim_t, ndims);
  dim_t count = 1;
  for (dim_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }

  af_err flag = af_identity(&output->carray, ndims, dimensions, f32);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_diag_create(VALUE self, VALUE array_val, VALUE num_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_err flag = af_diag_create(&output->carray, input->carray, NUM2INT(num_val));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_diag_extract(VALUE self, VALUE array_val, VALUE num_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_err flag = af_diag_extract(&output->carray, input->carray, NUM2INT(num_val));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_join(VALUE self, VALUE dim_val, VALUE first_array_val, VALUE second_array_val){
  afstruct* first_array;
  afstruct* second_array;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(first_array_val, afstruct, first_array);
  Data_Get_Struct(second_array_val, afstruct, second_array);

  af_err flag = af_join(&output->carray, NUM2INT(dim_val), first_array->carray, second_array->carray);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_join_many(VALUE self){
  return Qnil;
}

static VALUE arf_tile(VALUE self, VALUE array_val, VALUE x_val, VALUE y_val, VALUE z_val, VALUE w_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_err flag = af_tile(&output->carray, input->carray, NUM2UINT(x_val), NUM2UINT(y_val), NUM2UINT(z_val), NUM2UINT(w_val));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_reorder(VALUE self, VALUE array_val, VALUE x_val, VALUE y_val, VALUE z_val, VALUE w_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_err flag = af_reorder(&output->carray, input->carray, NUM2UINT(x_val), NUM2UINT(y_val), NUM2UINT(z_val), NUM2UINT(w_val));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_shift(VALUE self, VALUE array_val, VALUE x_val, VALUE y_val, VALUE z_val, VALUE w_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_err flag = af_shift(&output->carray, input->carray, NUM2INT(x_val), NUM2INT(y_val), NUM2INT(z_val), NUM2INT(w_val));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_moddims(VALUE self){
  return Qnil;
}

static VALUE arf_flat(VALUE self, VALUE array_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_err flag = af_flat(&output->carray, input->carray);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_flip(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_err flag = af_flip(&output->carray, input->carray, NUM2UINT(dim_val));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_lower(VALUE self, VALUE array_val, VALUE is_unit_diag){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_err flag = af_lower(&output->carray, input->carray, RTEST(is_unit_diag));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_upper(VALUE self, VALUE array_val, VALUE is_unit_diag){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_err flag = af_upper(&output->carray, input->carray, RTEST(is_unit_diag));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_select(VALUE self, VALUE array_cond_val, VALUE array_a_val, VALUE array_b_val){
  afstruct* array_cond;
  afstruct* array_a;
  afstruct* array_b;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_cond_val, afstruct, array_cond);
  Data_Get_Struct(array_a_val, afstruct, array_a);
  Data_Get_Struct(array_b_val, afstruct, array_b);

  af_err flag = af_select(&output->carray, array_cond->carray, array_a->carray, array_b->carray);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_select_scalar_r(VALUE self, VALUE array_cond_val, VALUE array_a_val, VALUE b_val){
  afstruct* array_cond;
  afstruct* array_a;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_cond_val, afstruct, array_cond);
  Data_Get_Struct(array_a_val, afstruct, array_a);

  af_err flag = af_select_scalar_r(&output->carray, array_cond->carray, array_a->carray, NUM2DBL(b_val));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_select_scalar_l(VALUE self, VALUE array_cond_val, VALUE a_val, VALUE array_b_val){
  afstruct* array_cond;
  afstruct* array_b;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_cond_val, afstruct, array_cond);
  Data_Get_Struct(array_b_val, afstruct, array_b);

  af_err flag = af_select_scalar_l(&output->carray, array_cond->carray, NUM2DBL(a_val), array_b->carray);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_replace(VALUE self, VALUE array_input_val, VALUE array_cond_val, VALUE array_b_val){
  afstruct* input;
  afstruct* array_cond;
  afstruct* array_b;

  Data_Get_Struct(array_input_val, afstruct, input);
  Data_Get_Struct(array_cond_val, afstruct, array_cond);
  Data_Get_Struct(array_b_val, afstruct, array_b);

  af_err flag = af_replace(&input->carray, array_cond->carray, array_b->carray);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Qtrue;
}

static VALUE arf_replace_scalar(VALUE self, VALUE array_input_val, VALUE array_cond_val, VALUE b_val){
  afstruct* input;
  afstruct* array_cond;

  Data_Get_Struct(array_input_val, afstruct, input);
  Data_Get_Struct(array_cond_val, afstruct, array_cond);

  af_err flag = af_replace_scalar(&input->carray, array_cond->carray, NUM2DBL(b_val));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Qtrue;
}
