static VALUE arf_create_sparse_array(VALUE self, VALUE shape_array, VALUE values_array, VALUE rowIdx_val, VALUE colIdx_val, VALUE stype_val){
  afstruct* output = ALLOC(afstruct);
  afstruct* values;
  afstruct* rowIdx;
  afstruct* colIdx;

  Data_Get_Struct(values_array, afstruct, values);
  Data_Get_Struct(rowIdx_val, afstruct, rowIdx);
  Data_Get_Struct(colIdx_val, afstruct, colIdx);

  af_storage stype = arf_storage_type_from_rbsymbol(stype_val);

  dim_t nRows = (dim_t)FIX2LONG(RARRAY_AREF(shape_array, 0));
  dim_t nCols = (dim_t)FIX2LONG(RARRAY_AREF(shape_array, 1));

  af_create_sparse_array(&output->carray, nRows, nCols, values->carray, rowIdx->carray, colIdx->carray, stype);

  af_print_array(output->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_create_sparse_array_from_ptr(VALUE self){
  return Qnil;
}

static VALUE arf_create_sparse_array_from_dense(VALUE self, VALUE dense_val, VALUE stype_val){
  afstruct* output = ALLOC(afstruct);
  afstruct* dense;

  Data_Get_Struct(dense_val, afstruct, dense);

  af_storage stype = arf_storage_type_from_rbsymbol(stype_val);

  af_create_sparse_array_from_dense(&output->carray, dense->carray, stype);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_sparse_convert_to(VALUE self){
  return Qnil;
}

static VALUE arf_sparse_to_dense(VALUE self){
  return Qnil;
}

static VALUE arf_sparse_get_info(VALUE self){
  return Qnil;
}

static VALUE arf_sparse_get_values(VALUE self, VALUE input_val){
  afstruct* output = ALLOC(afstruct);
  afstruct* input;

  Data_Get_Struct(input_val, afstruct, input);
  af_sparse_get_values(&output->carray, input->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_sparse_get_row_idx(VALUE self, VALUE input_val){
  afstruct* output = ALLOC(afstruct);
  afstruct* input;

  Data_Get_Struct(input_val, afstruct, input);
  af_sparse_get_row_idx(&output->carray, input->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_sparse_get_col_idx(VALUE self, VALUE input_val){
  afstruct* output = ALLOC(afstruct);
  afstruct* input;

  Data_Get_Struct(input_val, afstruct, input);
  af_sparse_get_col_idx(&output->carray, input->carray);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, output);
}

static VALUE arf_sparse_get_nnz(VALUE self){
  return Qnil;
}

static VALUE arf_sparse_get_storage(VALUE self, VALUE input_val){
  afstruct* input;
  Data_Get_Struct(input_val, afstruct, input);

  af_storage storage;
  af_sparse_get_storage(&storage , input->carray);

  return rb_str_new_cstr(STORAGE_TYPES[storage]);
}
