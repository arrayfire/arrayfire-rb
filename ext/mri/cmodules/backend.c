static VALUE arf_get_backend_count(VALUE self){
  uint num_backends;

  af_err flag = af_get_backend_count(&num_backends);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return UINT2NUM(num_backends);
}

// int backends = af::getAvailableBackends();
// bool cpu    = backends & AF_BACKEND_CPU;
// bool cuda   = backends & AF_BACKEND_CUDA;
// bool opencl = backends & AF_BACKEND_OPENCL;

static VALUE arf_get_available_backends(VALUE self){
  int backends;

  af_err flag = af_get_available_backends(&backends);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return INT2NUM(backends);
}

static VALUE arf_get_backend_id(VALUE self, VALUE array_val){
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_backend backend;

  af_err flag = af_get_backend_id (&backend, input->carray);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  const char* backend_name = get_backend_name(backend);
  return rb_str_new_cstr(backend_name);
}

static VALUE arf_get_active_backend(VALUE self){
  af_backend backend;

  af_err flag = af_get_active_backend(&backend);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  const char* backend_name = get_backend_name(backend);
  return rb_str_new_cstr(backend_name);
}

static VALUE arf_get_backend_device_id(VALUE self, VALUE array_val){
  afstruct* input;
  int device_id;

  Data_Get_Struct(array_val, afstruct, input);

  af_err flag = af_get_device_id(&device_id, input->carray);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return INT2NUM(device_id);
}

static VALUE arf_set_backend(VALUE self, VALUE backend_val){
  af_backend backend = arf_backend_type_from_rbsymbol(backend_val);

  af_err flag = af_set_backend(backend);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Qtrue;
}
