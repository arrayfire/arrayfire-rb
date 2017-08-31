static VALUE arf_info(VALUE self){
  af_err flag = af_info();
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}

static VALUE arf_init2(VALUE self){
  af_err flag = af_init();
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}

static VALUE arf_info_string(VALUE self, VALUE bool_val){
  char* str;
  af_err flag = af_info_string(&str, RTEST(bool_val));
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return rb_str_new_cstr(str);
}

static VALUE arf_device_info(VALUE self, VALUE name_val, VALUE platform_val, VALUE toolkit_val, VALUE compute_val){
  char* d_name     = ALLOC_N(char, sizeof(char) * 64);
  char* d_platform = ALLOC_N(char, sizeof(char) * 10);
  char* d_toolkit  = ALLOC_N(char, sizeof(char) * 64);
  char* d_compute  = ALLOC_N(char, sizeof(char) * 10);

  af_err flag = af_device_info(d_name, d_platform, d_toolkit, d_compute);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  rb_str_cat2(name_val,     d_name);
  rb_str_cat2(platform_val, d_platform);
  rb_str_cat2(toolkit_val,  d_toolkit);
  rb_str_cat2(compute_val,  d_compute);

  return Qtrue;
}

static VALUE arf_get_device_count(VALUE self){
  int num_of_devices;
  af_err flag = af_get_device_count(&num_of_devices);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return INT2NUM(num_of_devices);
}

static VALUE arf_get_dbl_support(VALUE self, VALUE device){
  bool available;
  af_err flag = af_get_dbl_support(&available, NUM2INT(device));
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return available ? Qtrue : Qfalse;
}

static VALUE arf_set_device(VALUE self, VALUE device){
  af_err flag = af_set_device(NUM2INT(device));
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}

static VALUE arf_get_device(VALUE self){
  int device;
  af_err flag = af_get_device(&device);
  return INT2NUM(device);
}

static VALUE arf_sync(VALUE self, VALUE device_val){
  af_err flag = af_sync(NUM2INT(device_val));
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}

static VALUE arf_alloc_device(VALUE self){
  return Qnil;
}

static VALUE arf_free_device(VALUE self){
  return Qnil;
}

static VALUE arf_alloc_pinned(VALUE self){
  return Qnil;
}

static VALUE arf_free_pinned(VALUE self){
  return Qnil;
}

static VALUE arf_alloc_host(VALUE self){
  return Qnil;
}

static VALUE arf_free_host(VALUE self){
  return Qnil;
}

static VALUE arf_device_array(VALUE self){
  return Qnil;
}

static VALUE arf_device_mem_info(VALUE self){
  size_t alloc_bytes, alloc_buffers, lock_bytes, lock_buffers;
  af_err flag = af_device_mem_info( &alloc_bytes, &alloc_buffers, &lock_bytes, &lock_buffers);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  printf("Allocated Bytes: %d\nAllocated buffers: %d\nLock Bytes: %d\nLock Buffers: %d\n",
          alloc_bytes, alloc_buffers, lock_bytes, lock_buffers);
  return Qtrue;
}

static VALUE arf_print_mem_info(VALUE self, VALUE msg_val, VALUE device_id_val){
  const char* msg = StringValuePtr(msg_val);
  af_err flag = af_print_mem_info( msg, NUM2INT(device_id_val));
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}

static void arf_device_gc(VALUE self){
  af_err flag = af_device_gc();
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
}

static VALUE arf_set_mem_step_size(VALUE self, VALUE step_bytes){
  af_err flag = af_set_mem_step_size(NUM2UINT(step_bytes));
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}

static VALUE arf_get_mem_step_size(VALUE self){
  size_t step_bytes;
  af_err flag = af_get_mem_step_size(&step_bytes);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return UINT2NUM(step_bytes);
}

static VALUE arf_lock_device_ptr(VALUE self, VALUE array_val){
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_err flag = af_lock_device_ptr(input->carray);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}

static VALUE arf_unlock_device_ptr(VALUE self, VALUE array_val){
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_err flag = af_unlock_device_ptr(input->carray);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}

static VALUE arf_lock_array(VALUE self, VALUE array_val){
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_err flag = af_lock_array(input->carray);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}

static VALUE arf_unlock_array(VALUE self, VALUE array_val){
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_err flag = af_unlock_array(input->carray);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qtrue;
}

static VALUE arf_is_locked_array(VALUE self, VALUE array_val){
  bool res;
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_err flag = af_is_locked_array(&res, input->carray);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return res ? Qtrue : Qfalse;
}

static VALUE arf_get_device_ptr(VALUE self){
  return Qnil;
}
