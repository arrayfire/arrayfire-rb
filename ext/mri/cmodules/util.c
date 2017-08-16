static VALUE arf_print_array(VALUE self, VALUE input_val){
  afstruct* input;

  Data_Get_Struct(input_val, afstruct, input);

  af_print_array(input->carray);
  return Qtrue;
}

static VALUE arf_print_array_gen(VALUE self){
  return Qnil;
}
static VALUE arf_save_array(VALUE self){
  return Qnil;
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
static VALUE arf_array_to_string(VALUE self){
  return Qnil;
}
static VALUE arf_example_function(VALUE self){
  return Qnil;
}
static VALUE arf_get_version(VALUE self){
  return Qnil;
}
static VALUE arf_get_revision(VALUE self){
  return Qnil;
}
static VALUE arf_get_size_of(VALUE self){
  return Qnil;
}
