static VALUE arf_mean(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_mean(&output->carray, input->carray, NUM2UINT(dim_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_mean_weighted(VALUE self, VALUE array_val, VALUE weighted_array_val, VALUE dim_val){
  afstruct* input;
  afstruct* weighted_array;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);
  Data_Get_Struct(weighted_array_val, afstruct, weighted_array);

  af_mean_weighted(&output->carray, input->carray, weighted_array->carray, NUM2UINT(dim_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_var(VALUE self, VALUE array_val, VALUE is_biased, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_var(&output->carray, input->carray,  RTEST(is_biased), NUM2UINT(dim_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_var_weighted(VALUE self, VALUE array_val, VALUE weighted_array_val, VALUE dim_val){
  afstruct* input;
  afstruct* weighted_array;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);
  Data_Get_Struct(weighted_array_val, afstruct, weighted_array);

  af_var_weighted(&output->carray, input->carray, weighted_array->carray, NUM2UINT(dim_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_stdev(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_stdev(&output->carray, input->carray, NUM2UINT(dim_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_cov(VALUE self, VALUE first_array_val, VALUE second_array_val, VALUE is_biased){
  afstruct* output = ALLOC(afstruct);

  afstruct* first_array;
  afstruct* second_array;

  Data_Get_Struct(first_array_val, afstruct, first_array);
  Data_Get_Struct(second_array_val, afstruct, second_array);

  af_cov(&output->carray, first_array->carray, second_array->carray, RTEST(is_biased));

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_median(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_median(&output->carray, input->carray, NUM2UINT(dim_val));
  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_mean_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_mean_all(&real_part, &imag_part, input->carray);

  return DBL2NUM(real_part);
}

static VALUE arf_mean_all_weighted(VALUE self, VALUE array_val, VALUE weighted_array_val){
  afstruct* input;
  afstruct* weighted_array;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);
  Data_Get_Struct(weighted_array_val, afstruct, weighted_array);

  // af_mean_all_weigheted(&real_part, &imag_part, input->carray, weighted_array->carray);

  return DBL2NUM(real_part);
}

static VALUE arf_var_all(VALUE self, VALUE array_val, VALUE is_biased){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_var_all(&real_part, &imag_part, input->carray, RTEST(is_biased));

  return DBL2NUM(real_part);
}

static VALUE arf_var_all_weighted(VALUE self, VALUE array_val, VALUE weighted_array_val){
  afstruct* input;
  afstruct* weighted_array;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);
  Data_Get_Struct(weighted_array_val, afstruct, weighted_array);

  // af_var_all_weigheted(&real_part, &imag_part, input->carray, weighted_array->carray);

  return DBL2NUM(real_part);
}

static VALUE arf_stdev_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  // af_stddev_all(&real_part, &imag_part, input->carray);

  return DBL2NUM(real_part);
}

static VALUE arf_median_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_median_all(&real_part, &imag_part, input->carray);

  return DBL2NUM(real_part);
}

static VALUE arf_corrcoef(VALUE self, VALUE first_array_val, VALUE second_array_val){
  afstruct* first_array;
  afstruct* second_array;
  double real_part, imag_part;

  Data_Get_Struct(first_array_val, afstruct, first_array);
  Data_Get_Struct(first_array_val, afstruct, first_array);

  af_corrcoef(&real_part, &imag_part, first_array->carray, second_array->carray);

  return DBL2NUM(real_part);
}
