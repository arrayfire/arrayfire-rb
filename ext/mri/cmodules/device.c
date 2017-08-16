static VALUE arf_info(VALUE self){
  af_info();
  return Qnil;
}

static VALUE arf_init2(VALUE self){
  af_init();
  return Qnil;
}

static VALUE arf_info_string(VALUE self, VALUE bool_val){
  char* str;
  af_info_string(&str, RTEST(bool_val));
  return rb_str_new_cstr(str);
}

static VALUE arf_device_info(VALUE self){
  char d_name, d_platform, d_toolkit, d_compute;
  af_device_info(&d_name, &d_platform, &d_toolkit, &d_compute);
  return Qnil;
}

static VALUE arf_get_device_count(VALUE self){
  int num_of_devices;
  af_get_device_count(&num_of_devices);
  return INT2NUM(num_of_devices);
}

static VALUE arf_get_dbl_support(VALUE self, VALUE device){
  bool available;
  af_get_dbl_support(&available, NUM2INT(device));
  return available ? Qtrue : Qfalse;
}

static VALUE arf_set_device(VALUE self, VALUE device){
  af_set_device(NUM2INT(device));
  return Qnil;
}

static VALUE arf_get_device(VALUE self){
  int device;
  af_get_device(&device);
  return INT2NUM(device);
}

static VALUE arf_sync(VALUE self, VALUE device_val){
  af_sync(NUM2INT(device_val));
  return Qnil;
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
  af_device_mem_info( &alloc_bytes, &alloc_buffers, &lock_bytes, &lock_buffers);
  printf("Allocated Bytes: %d\nAllocated buffers: %d\nLock Bytes: %d\nLock Buffers: %d\n",
          alloc_bytes, alloc_buffers, lock_bytes, lock_buffers);
  return Qnil;
}

static VALUE arf_print_mem_info(VALUE self, VALUE msg_val, VALUE device_id_val){
  const char* msg = StringValuePtr(msg_val);
  af_print_mem_info( msg, NUM2INT(device_id_val));
  return Qnil;
}

static void arf_device_gc(VALUE self){
  af_device_gc();
}

static VALUE arf_set_mem_step_size(VALUE self, VALUE step_bytes){
  af_set_mem_step_size(NUM2UINT(step_bytes));
  return Qtrue;
}

static VALUE arf_get_mem_step_size(VALUE self){
  size_t step_bytes;
  af_get_mem_step_size(&step_bytes);
  return UINT2NUM(step_bytes);
}

static VALUE arf_lock_device_ptr(VALUE self, VALUE array_val){
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_lock_device_ptr(input->carray);
  return Qnil;
}

static VALUE arf_unlock_device_ptr(VALUE self, VALUE array_val){
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_unlock_device_ptr(input->carray);
  return Qnil;
}

static VALUE arf_lock_array(VALUE self, VALUE array_val){
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_lock_array(input->carray);
  return Qnil;
}

static VALUE arf_unlock_array(VALUE self, VALUE array_val){
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_unlock_array(input->carray);
  return Qnil;
}

static VALUE arf_is_locked_array(VALUE self, VALUE array_val){
  bool res;
  afstruct* input;
  Data_Get_Struct(array_val, afstruct, input);
  af_is_locked_array(&res, input->carray);
  return res ? Qtrue : Qfalse;
}

static VALUE arf_get_device_ptr(VALUE self){
  return Qnil;
}
