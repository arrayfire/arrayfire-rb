static VALUE arf_constant(int argc, VALUE* argv)
{
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