static VALUE arf_matmul(VALUE self, VALUE left_val, VALUE right_val, VALUE left_prop_val, VALUE right_prop_val){

  afstruct* left;
  afstruct* right;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(left_val, afstruct, left);
  Data_Get_Struct(right_val, afstruct, right);

  af_mat_prop left_mat_prop = arf_mat_type_from_rbsymbol(left_prop_val);
  af_mat_prop right_mat_prop = arf_mat_type_from_rbsymbol(right_prop_val);

  af_matmul(&result->carray, left->carray, right->carray, left_mat_prop, right_mat_prop);

  return Data_Wrap_Struct(CLASS_OF(left_val), NULL, arf_free, result);
}

static VALUE arf_dot(VALUE self, VALUE left_val, VALUE right_val, VALUE left_prop_val, VALUE right_prop_val){
  afstruct* left;
  afstruct* right;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(left_val, afstruct, left);
  Data_Get_Struct(right_val, afstruct, right);

  af_mat_prop left_mat_prop = arf_mat_type_from_rbsymbol(left_prop_val);
  af_mat_prop right_mat_prop = arf_mat_type_from_rbsymbol(right_prop_val);

  af_dot(&result->carray, left->carray, right->carray, left_mat_prop, right_mat_prop);

  return Data_Wrap_Struct(CLASS_OF(left_val), NULL, arf_free, result);
}

static VALUE arf_transpose(VALUE self, VALUE input){
  afstruct* obj;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(input, afstruct, obj);

  af_transpose(&result->carray, obj->carray, false);

  return Data_Wrap_Struct(CLASS_OF(input), NULL, arf_free, result);
}

static VALUE arf_transpose_inplace(VALUE self, VALUE input){
  afstruct* obj;

  Data_Get_Struct(input, afstruct, obj);

  af_transpose_inplace(obj->carray, false);

  return Data_Wrap_Struct(CLASS_OF(input), NULL, arf_free, obj);
}
