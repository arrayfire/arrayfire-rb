static VALUE arf_svd(VALUE self, VALUE val){
  afstruct* input;
  afstruct* u = ALLOC(afstruct);
  afstruct* s = ALLOC(afstruct);
  afstruct* vt = ALLOC(afstruct);

  Data_Get_Struct(val, afstruct, input);

  af_svd(&u->carray, &s->carray, &vt->carray, input->carray);

  return Data_Wrap_Struct(CLASS_OF(val), NULL, arf_free, u);
}

static VALUE arf_svd_inplace(VALUE self, VALUE val){
  afstruct* input;
  afstruct* u = ALLOC(afstruct);
  afstruct* s = ALLOC(afstruct);
  afstruct* vt = ALLOC(afstruct);

  Data_Get_Struct(val, afstruct, input);

  af_svd_inplace(&u->carray, &s->carray, &vt->carray, input->carray);

  return Data_Wrap_Struct(CLASS_OF(val), NULL, arf_free, u);
}

static VALUE arf_lu(VALUE self, VALUE val){
  afstruct* input;
  afstruct* lower = ALLOC(afstruct);
  afstruct* upper = ALLOC(afstruct);
  afstruct* pivot = ALLOC(afstruct);

  Data_Get_Struct(val, afstruct, input);

  af_lu(&lower->carray, &upper->carray, &pivot->carray, input->carray);
  return Data_Wrap_Struct(CLASS_OF(val), NULL, arf_free, lower);
}

static VALUE arf_lu_inplace(VALUE self){
  return Qnil;
}

static VALUE arf_qr(VALUE self, VALUE val){
  afstruct* input;
  afstruct* q = ALLOC(afstruct);
  afstruct* r = ALLOC(afstruct);
  afstruct* tau = ALLOC(afstruct);

  Data_Get_Struct(val, afstruct, input);

  af_qr(&q->carray, &r->carray, &tau->carray, input->carray);
  return Data_Wrap_Struct(CLASS_OF(val), NULL, arf_free, q);
}

static VALUE arf_qr_inplace(VALUE self){
  return Qnil;
}

static VALUE arf_cholesky(VALUE self, VALUE val){
  afstruct* input;
  afstruct* output = ALLOC(afstruct);
  int* info;

  Data_Get_Struct(val, afstruct, input);

  af_cholesky(&output->carray, info, input->carray, true);
  return Data_Wrap_Struct(CLASS_OF(val), NULL, arf_free, output);
}

static VALUE arf_cholesky_inplace(VALUE self){
  return Qnil;
}

static VALUE arf_solve(VALUE self, VALUE lhs_val, VALUE rhs_val){

  afstruct* lhs;
  afstruct* rhs;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(lhs_val, afstruct, lhs);
  Data_Get_Struct(rhs_val, afstruct, rhs);

  af_solve(&result->carray, lhs->carray, rhs->carray, AF_MAT_NONE);
  return Data_Wrap_Struct(CLASS_OF(lhs_val), NULL, arf_free, result);

}

static VALUE arf_solve_lu(VALUE self, VALUE lhs_val, VALUE rhs_val, VALUE piv_val){
  afstruct* lhs;
  afstruct* rhs;
  afstruct* piv;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(lhs_val, afstruct, lhs);
  Data_Get_Struct(rhs_val, afstruct, rhs);

  af_solve_lu(&result->carray, lhs->carray, piv->carray, rhs->carray, AF_MAT_NONE);
  return Data_Wrap_Struct(CLASS_OF(lhs_val), NULL, arf_free, result);
}

static VALUE arf_inverse(VALUE self, VALUE val){

  afstruct* matrix;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(val, afstruct, matrix);

  af_inverse(&result->carray, matrix->carray, AF_MAT_NONE);

  return Data_Wrap_Struct(CLASS_OF(val), NULL, arf_free, result);
}

static VALUE arf_rank(VALUE self, VALUE val){
  afstruct* matrix;
  uint rank;

  Data_Get_Struct(val, afstruct, matrix);

  af_rank(&rank, matrix->carray, 0.001);
  return UINT2NUM(rank);
}

static VALUE arf_det(VALUE self, VALUE val){
  afstruct* matrix;
  uint a;
  double det_real;
  // double det_image;

  Data_Get_Struct(val, afstruct, matrix);

  af_rank(&a, matrix->carray, det_real);
  return DBL2NUM(det_real);
}

static VALUE arf_norm(VALUE self, VALUE val){
  afstruct* matrix;
  double norm;
  double p = 0;
  double q = 0;
  Data_Get_Struct(val, afstruct, matrix);
  af_norm(&norm, matrix->carray, AF_NORM_EUCLID, p, q);
  return DBL2NUM(norm);
}

static VALUE arf_is_lapack_available(VALUE self){
  bool* output;
  // af_is_lapack_available(output);
  return Qfalse;
}
