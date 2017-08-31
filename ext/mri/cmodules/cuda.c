static VALUE arf_get_stream(VALUE self, VALUE id){
  // cudaStream_t* stream;
  // afcu_get_stream  (stream, NUM2INT(id));
  return Qnil;
}

static VALUE arf_get_native_id(VALUE self, VALUE cuda_device_id){
  int native_id;
  af_err flag = afcu_get_native_id(&native_id, NUM2INT(cuda_device_id));
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return INT2NUM(native_id);
}

static VALUE arf_set_native_id(VALUE self, VALUE native_id){
  af_err flag = afcu_set_native_id(native_id);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}
