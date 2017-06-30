static VALUE arf_create_array(VALUE self){
  return Qnil;
}

static VALUE arf_create_handle(VALUE self){
  return Qnil;
}

static VALUE arf_copy_array(VALUE self){
  return Qnil;
}

static VALUE arf_write_array(VALUE self){
  return Qnil;
}

static VALUE arf_get_data_ptr(VALUE self){
  return Qnil;
}

static VALUE arf_release_array(VALUE self){
  return Qnil;
}

static VALUE arf_retain_array(VALUE self){
  return Qnil;
}

static VALUE arf_get_data_ref_count(VALUE self){
  return Qnil;
}

static VALUE arf_eval(VALUE self){
  return Qnil;
}

static VALUE arf_eval_multiple(VALUE self){
  return Qnil;
}

static VALUE arf_set_manual_eval_flag(VALUE self){
  return Qnil;
}

static VALUE arf_get_manual_eval_flag(VALUE self){
  return Qnil;
}

static VALUE arf_get_elements(VALUE self){
  afstruct* input;

  dim_t elems;

  Data_Get_Struct(self, afstruct, input);

  af_get_elements(&elems, input->carray);
  return ULONG2NUM(elems);
}

static VALUE arf_get_type(VALUE self){
  afstruct* input;
  af_dtype type;

  Data_Get_Struct(self, afstruct, input);

  af_get_type(&type, input->carray);
  return Qnil;
}

static VALUE arf_get_dims(VALUE self){
  afstruct* input;
  dim_t d0, d1, d2, d3;

  Data_Get_Struct(self, afstruct, input);

  af_get_dims(&d0, &d1, &d2, &d3, input->carray);
  return Qnil;
}

static VALUE arf_get_numdims(VALUE self){
  afstruct* input;
  uint result;

  Data_Get_Struct(self, afstruct, input);

  af_get_numdims(&result, input->carray);
  return UINT2NUM(result);
}

static VALUE arf_is_empty(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_empty(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_scalar(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_scalar(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_row(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_row(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_column(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_column(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_vector(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_vector(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_complex(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_complex(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_real(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_real(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_double(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_double(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_single(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_single(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_realfloating(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_realfloating(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_floating(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_floating(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_integer(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_integer(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_bool(VALUE self){
  afstruct* input;
  bool result;

  Data_Get_Struct(self, afstruct, input);

  af_is_bool(&result, input->carray);
  return result ? Qtrue : Qfalse;
}

static VALUE arf_is_sparse(VALUE self){
  afstruct* input;
  bool result = false;

  Data_Get_Struct(self, afstruct, input);

  //FIXME
  // af_is_bool(&result, input->carray);
  return result ? Qtrue : Qfalse;
}
