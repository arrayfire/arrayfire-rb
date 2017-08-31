static VALUE arf_af_array_to_nmatrix(VALUE self) {
  afstruct* input;
  Data_Get_Struct(self, afstruct, input);
  dim_t count;
  uint ndims;
  af_get_numdims(&ndims, input->carray);

  dim_t* dims = ALLOC_N(dim_t, ndims);

  af_get_dims(&dims[0], &dims[1], &dims[2], &dims[3], input->carray);

  size_t* shape = ALLOC_N(size_t, ndims);
  for (dim_t index = 0; index < ndims; index++){
    shape[index] = (size_t)(dims[index]);
  }

  af_get_elements(&count, input->carray);

  double* elements = ALLOC_N(double, count);
  af_get_data_ptr(elements, input->carray);

  return rb_nmatrix_dense_create(nm::FLOAT64, shape, ndims, elements, (int)count);
}

extern VALUE arf_nmatrix_to_af_array_method(VALUE nmatrix) {
  if (NM_DIM(nmatrix) > 4) {
    rb_raise(rb_eStandardError,
      "NMatrix must not have greater than 4 dimensions.");
  }

  if (NM_DTYPE(nmatrix) == nm::FLOAT64) {
    return Data_Wrap_Struct(Af_Array, NULL, arf_free, arf_nmatrix_to_af_array(nmatrix));
  }
  else {
    rb_raise(rb_eStandardError,
      "NMatrix should be either :complex64, :complex128, :int32 or :float64 type.");
  }
  return Qnil;
}


afstruct* arf_nmatrix_to_af_array(VALUE nm) {
  DENSE_STORAGE* nmat = NM_STORAGE_DENSE(nm);
  afstruct* output = ALLOC(afstruct);

  if (nmat->dtype != nm::FLOAT64) {
    rb_raise(rb_eStandardError, "requires dtype of :float64 to convert to an Af_Array");
  }

  dim_t* shape = ALLOC_N(dim_t, nmat->dim);
  for (size_t index = 0; index < nmat->dim; index++){
    shape[index] = (size_t)(nmat->shape[index]);
  }

  af_create_array(&output->carray, nmat->elements, nmat->dim, shape, f64);

  return output;
}
