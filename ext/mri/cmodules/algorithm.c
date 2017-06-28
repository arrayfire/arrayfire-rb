static VALUE arf_sum(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_sum(&output->carray, input->carray, FIX2INT(dim_val));

  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_sum_nan(VALUE self, VALUE array_val, VALUE dim_val, VALUE nan_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_sum_nan(&output->carray, input->carray, FIX2INT(dim_val), NUM2DBL(nan_val));

  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_product(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_product(&output->carray, input->carray, FIX2INT(dim_val));

  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_product_nan(VALUE self, VALUE array_val, VALUE dim_val, VALUE nan_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_product_nan(&output->carray, input->carray, FIX2INT(dim_val), NUM2DBL(nan_val));

  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_min(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_min(&output->carray, input->carray, FIX2INT(dim_val));

  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_max(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_max(&output->carray, input->carray, FIX2INT(dim_val));

  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_all_true(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_sum(&output->carray, input->carray, FIX2INT(dim_val));

  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_any_true(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_sum(&output->carray, input->carray, FIX2INT(dim_val));

  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_count(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_sum(&output->carray, input->carray, FIX2INT(dim_val));

  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_sum_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_sum_all(&real_part, &imag_part, input->carray);

  return NUM2DBL(real_part);
}

static VALUE arf_sum_nan_all(VALUE self, VALUE array_val, VALUE nan_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_sum_nan_all(&real_part, &imag_part, input->carray, NUM2DBL(nan_val));

  return NUM2DBL(real_part);
}

static VALUE arf_product_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_product_all(&real_part, &imag_part, input->carray);

  return NUM2DBL(real_part);
}

static VALUE arf_product_nan_all(VALUE self, VALUE array_val, VALUE nan_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_product_nan_all(&real_part, &imag_part, input->carray, NUM2DBL(nan_val));

  return NUM2DBL(real_part);
}

static VALUE arf_min_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_min_all(&real_part, &imag_part, input->carray);

  return NUM2DBL(real_part);
}

static VALUE arf_max_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_max_all(&real_part, &imag_part, input->carray);

  return NUM2DBL(real_part);
}

static VALUE arf_all_true_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_all_true_all(&real_part, &imag_part, input->carray);

  return NUM2DBL(real_part);
}

static VALUE arf_any_true_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_any_true_all(&real_part, &imag_part, input->carray);

  return NUM2DBL(real_part);
}

static VALUE arf_count_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;

  Data_Get_Struct(array_val, afstruct, input);

  af_count_all(&real_part, &imag_part, input->carray);

  return NUM2DBL(real_part);
}

static VALUE arf_imin(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);
  afstruct* idx = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_imin(&output->carray, &idx->carray, input->carray, FIX2INT(dim_val));
  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_imax(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);
  afstruct* idx = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_imax(&output->carray, &idx->carray, input->carray, FIX2INT(dim_val));
  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
}

static VALUE arf_imin_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;
  uint idx;

  Data_Get_Struct(array_val, afstruct, input);

  af_imin_all(&real_part, &imag_part, &idx, input->carray);
  return NUM2DBL(real_part);
}

static VALUE arf_imax_all(VALUE self, VALUE array_val){
  afstruct* input;
  double real_part, imag_part;
  uint idx;

  Data_Get_Struct(array_val, afstruct, input);

  af_imax_all(&real_part, &imag_part, &idx, input->carray);
  return NUM2DBL(real_part);
}

static VALUE arf_accum(VALUE self, VALUE array_val, VALUE dim_val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);

  Data_Get_Struct(array_val, afstruct, input);

  af_accum(&output->carray, input->carray, FIX2INT(dim_val));

  return Data_Wrap_Struct(CLASS_OF(array_val), NULL, arf_free, output);
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