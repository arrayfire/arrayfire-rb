static VALUE arf_print_array(VALUE self, VALUE input_val){
  afstruct* input;

  Data_Get_Struct(input_val, afstruct, input);

  af_err flag = af_print_array(input->carray);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Qtrue;
}

static VALUE arf_print_array_gen(VALUE self){
  return Qnil;
}

static VALUE arf_save_array(VALUE self, VALUE key_val, VALUE array_val, VALUE fn_val, VALUE append){
  afstruct* input;

  Data_Get_Struct(array_val, afstruct, input);
  const char* key = StringValueCStr(key_val);
  const char* filename = StringValueCStr(fn_val);
  int index;

  af_err flag = af_save_array (&index, key, input->carray, filename, RTEST(append));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return INT2NUM(index);
}

static VALUE arf_read_array_index(VALUE self){
  return Qnil;
}

static VALUE arf_read_array_key(VALUE self){
  return Qnil;
}

static VALUE arf_read_array_key_check(VALUE self){
  return Qnil;
}

static VALUE arf_array_to_string(VALUE self, VALUE exp_val, VALUE array_val, VALUE precision, VALUE transpose){
  char* output;
  afstruct* input;

  Data_Get_Struct(array_val, afstruct, input);
  const char* exp = StringValueCStr(exp_val);

  af_err flag = af_array_to_string(&output, exp, input->carray, NUM2INT(precision), RTEST(transpose));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return rb_str_new_cstr(output);
}

static VALUE arf_example_function(VALUE self){
  return Qnil;
}

static VALUE arf_get_version(VALUE self){
  int major, minor, patch;

  af_err flag = af_get_version(&major, &minor, &patch);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  VALUE hash = rb_hash_new();
  rb_hash_aset(hash, rb_str_new_cstr("major"), INT2NUM(major));
  rb_hash_aset(hash, rb_str_new_cstr("minor"), INT2NUM(minor));
  rb_hash_aset(hash, rb_str_new_cstr("patch"), INT2NUM(patch));

  return hash;
}

static VALUE arf_get_revision(VALUE self){
  const char* revision = af_get_revision();
  return rb_str_new_cstr(revision);
}

static VALUE arf_get_size_of(VALUE self, VALUE dtype_val){
  size_t size;

  af_err flag = af_get_size_of(&size, arf_dtype_from_rbsymbol(dtype_val));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return ULL2NUM(size);
}
