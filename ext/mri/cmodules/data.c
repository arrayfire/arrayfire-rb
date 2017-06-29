static VALUE arf_constant(int argc, VALUE* argv){
  afstruct* output = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = (dim_t*)malloc(ndims * sizeof(dim_t));
  dim_t count = 1;
  for (size_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }
  float data = NUM2DBL(argv[2]);
  af_constant(&output->carray, data, 2, dimensions, f32);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_constant_complex(VALUE self){
  return Qnil;
}

static VALUE arf_constant_long(int argc, VALUE* argv){
  afstruct* output = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = (dim_t*)malloc(ndims * sizeof(dim_t));
  dim_t count = 1;
  for (size_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }
  float data = NUM2LONG(argv[2]);
  af_constant_long(&output->carray, data, 2, dimensions);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_constant_ulong(int argc, VALUE* argv){
  afstruct* output = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = (dim_t*)malloc(ndims * sizeof(dim_t));
  dim_t count = 1;
  for (size_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }
  float data = NUM2LONG(argv[2]);
  af_constant_ulong(&output->carray, data, 2, dimensions);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_range(int argc, VALUE* argv){
  afstruct* output = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = (dim_t*)malloc(ndims * sizeof(dim_t));
  dim_t count = 1;
  for (size_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }
  int seq_dim = NUM2INT(argv[2]);
  af_range(&output->carray, ndims, dimensions, seq_dim, f32);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_iota(VALUE self){
  return Qnil;
}

static VALUE arf_identity(int argc, VALUE* argv){
  afstruct* output = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(argv[0]);
  dim_t* dimensions = (dim_t*)malloc(ndims * sizeof(dim_t));
  dim_t count = 1;
  for (size_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(argv[1], index));
    count *= dimensions[index];
  }
  af_identity(&output->carray, ndims, dimensions, f32);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_diag_create(VALUE self, VALUE array_val, VALUE num_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_diag_create(&output->carray, input->carray, NUM2INT(num_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_diag_extract(VALUE self, VALUE array_val, VALUE num_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_diag_extract(&output->carray, input->carray, NUM2INT(num_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_join(VALUE self, VALUE dim_val, VALUE first_array_val, VALUE second_array_val){
  afstruct* first_array;
  afstruct* second_array;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(first_array_val, afstruct, first_array);
  Data_Get_Struct(second_array_val, afstruct, second_array);

  af_join(&output->carray, NUM2INT(dim_val), first_array->carray, second_array->carray);
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

  af_tile(&output->carray, input->carray, NUM2UINT(x_val), NUM2UINT(y_val), NUM2UINT(z_val), NUM2UINT(w_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_reorder(VALUE self, VALUE array_val, VALUE x_val, VALUE y_val, VALUE z_val, VALUE w_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_reorder(&output->carray, input->carray, NUM2UINT(x_val), NUM2UINT(y_val), NUM2UINT(z_val), NUM2UINT(w_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_shift(VALUE self, VALUE array_val, VALUE x_val, VALUE y_val, VALUE z_val, VALUE w_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_shift(&output->carray, input->carray, NUM2INT(x_val), NUM2INT(y_val), NUM2INT(z_val), NUM2INT(w_val));
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

  af_flat(&output->carray, input->carray);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_flip(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_flip(&output->carray, input->carray, NUM2UINT(dim_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_lower(VALUE self){
  return Qnil;
}

static VALUE arf_upper(VALUE self){
  return Qnil;
}

static VALUE arf_select(VALUE self, VALUE array_cond_val, VALUE array_a_val, VALUE array_b_val){
  afstruct* array_cond;
  afstruct* array_a;
  afstruct* array_b;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_cond_val, afstruct, array_cond);
  Data_Get_Struct(array_a_val, afstruct, array_a);
  Data_Get_Struct(array_b_val, afstruct, array_b);

  af_select(&output->carray, array_cond->carray, array_a->carray, array_b->carray);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_select_scalar_r(VALUE self, VALUE array_cond_val, VALUE array_a_val, VALUE b_val){
  afstruct* array_cond;
  afstruct* array_a;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_cond_val, afstruct, array_cond);
  Data_Get_Struct(array_a_val, afstruct, array_a);

  af_select_scalar_r(&output->carray, array_cond->carray, array_a->carray, NUM2DBL(b_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_select_scalar_l(VALUE self, VALUE array_cond_val, VALUE a_val, VALUE array_b_val){
  afstruct* array_cond;
  afstruct* array_b;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_cond_val, afstruct, array_cond);
  Data_Get_Struct(array_b_val, afstruct, array_b);

  af_select_scalar_l(&output->carray, array_cond->carray, NUM2DBL(a_val), array_b->carray);
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_replace(VALUE self){
  return Qnil;
}

static VALUE arf_replace_scalar(VALUE self){
  return Qnil;
}
