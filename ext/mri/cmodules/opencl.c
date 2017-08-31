std::map<char*, size_t> AFCL_DEVICE_TYPES = {
  {"AFCL_DEVICE_TYPE_CPU",       0},
  {"CL_DEVICE_TYPE_CPU",         1},
  {"AFCL_DEVICE_TYPE_GPU",       2},
  {"CL_DEVICE_TYPE_GPU",         3},
  {"AFCL_DEVICE_TYPE_ACC",       4},
  {"CL_DEVICE_TYPE_ACCELERATOR", 5},
  {"AFCL_DEVICE_TYPE_UNKNOWN",  -1}
};

std::map<char*, size_t> AFCL_PLATFORM_TYPES = {
  {"AFCL_PLATFORM_AMD",      0},
  {"AFCL_PLATFORM_APPLE",    1},
  {"AFCL_PLATFORM_INTEL",    2},
  {"AFCL_PLATFORM_NVIDIA",   3},
  {"AFCL_PLATFORM_BEIGNET",  4},
  {"AFCL_PLATFORM_POCL",     5},
  {"AFCL_PLATFORM_UNKNOWN", -1}
};


static VALUE arf_get_context(VALUE self){
  return Qnil;
}

static VALUE arf_get_queue(VALUE self){
  return Qnil;
}

static VALUE arf_get_device_id(VALUE self){
  cl_device_id id;
  af_err flag = afcl_get_device_id(&id);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return Qnil;
}

static VALUE arf_set_device_id(VALUE self){
  return Qnil;
}

static VALUE arf_add_device_context(VALUE self){
  return Qnil;
}

static VALUE arf_set_device_context(VALUE self){
  return Qnil;
}

static VALUE arf_delete_device_context(VALUE self){
  return Qnil;
}

static VALUE arf_get_device_type(VALUE self){
  afcl_device_type device;
  af_err flag = afcl_get_device_type(&device);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return rb_str_new_cstr(get_cl_device_name(device));
}

static VALUE arf_get_platform(VALUE self){
  afcl_platform platform;
  af_err flag = afcl_get_platform(&platform);
  if (flag != AF_SUCCESS) arf_handle_exception(flag);
  return rb_str_new_cstr(get_cl_platform_name(platform));
}

const char* get_cl_device_name(afcl_device_type device){
  for(std::map<char*, size_t>::value_type& entry : AFCL_DEVICE_TYPES) {
    if (device == entry.second) {
      return entry.first;
    }
  }
  rb_raise(rb_eArgError, "Couldn't detect device!");
}

const char* get_cl_platform_name(afcl_platform platform){
  for(std::map<char*, size_t>::value_type& entry : AFCL_PLATFORM_TYPES) {
    if (platform == entry.second) {
      return entry.first;
    }
  }
  rb_raise(rb_eArgError, "Couldn't detect platform!");
}
