static VALUE arf_get_backend_count(VALUE self){
  uint num_backends;
  af_get_backend_count(&num_backends);
  return UINT2NUM(num_backends);
}

static VALUE arf_get_available_backends(VALUE self){
  int backends;
  af_get_available_backends (&backends);
  return INT2NUM(backends);
}

static VALUE arf_get_backend_id(VALUE self, VALUE array_val){
  return Qnil;
}

static VALUE arf_get_active_backend(VALUE self){
  return Qnil;
}

static VALUE arf_get_backend_device_id(VALUE self, VALUE array_val){
  afstruct* input;
  int device_id;

  Data_Get_Struct(array_val, afstruct, input);

  af_get_device_id(&device_id, input->carray);

  return INT2NUM(device_id);
}

static VALUE arf_set_backend(VALUE self){
  return Qnil;
}
