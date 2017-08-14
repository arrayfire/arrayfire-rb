static VALUE arf_svd_func(VALUE self, VALUE u_val, VALUE s_val, VALUE vt_val, VALUE val){
  afstruct* input;
  afstruct* u;
  afstruct* s;
  afstruct* vt;

  Data_Get_Struct(val, afstruct, input);
  Data_Get_Struct(u_val, afstruct, u);
  Data_Get_Struct(s_val, afstruct, s);
  Data_Get_Struct(vt_val, afstruct, vt);

  af_svd(&u->carray, &s->carray, &vt->carray, input->carray);

  return Qtrue;
}

static VALUE arf_svd_inplace_func(VALUE self, VALUE val){
  afstruct* input;
  afstruct* u = ALLOC(afstruct);
  afstruct* s = ALLOC(afstruct);
  afstruct* vt = ALLOC(afstruct);

  Data_Get_Struct(val, afstruct, input);

  af_svd_inplace(&u->carray, &s->carray, &vt->carray, input->carray);

  return Data_Wrap_Struct(CLASS_OF(val), NULL, arf_free, u);
}

static VALUE arf_lu_func(VALUE self, VALUE lower_val, VALUE upper_val, VALUE pivot_val, VALUE val){
  afstruct* input;
  afstruct* lower;
  afstruct* upper;
  afstruct* pivot;

  Data_Get_Struct(val, afstruct, input);
  Data_Get_Struct(lower_val, afstruct, lower);
  Data_Get_Struct(upper_val, afstruct, upper);
  Data_Get_Struct(pivot_val, afstruct, pivot);

  af_lu(&lower->carray, &upper->carray, &pivot->carray, input->carray);
  return Qtrue;
}

static VALUE arf_lu_inplace_func(VALUE self){
  return Qnil;
}

static VALUE arf_qr_func(VALUE self, VALUE q_val, VALUE r_val, VALUE tau_val, VALUE val){
  afstruct* input;
  afstruct* q;
  afstruct* r;
  afstruct* tau;

  Data_Get_Struct(val, afstruct, input);
  Data_Get_Struct(q_val, afstruct, q);
  Data_Get_Struct(r_val, afstruct, r);
  Data_Get_Struct(tau_val, afstruct, tau);

  af_qr(&q->carray, &r->carray, &tau->carray, input->carray);
  return Qfalse;
}

static VALUE arf_qr_inplace_func(VALUE self){
  return Qnil;
}

static VALUE arf_cholesky_func(VALUE self, VALUE output_val, VALUE val, VALUE is_upper_val){
  afstruct* input;
  afstruct* output;
  int info;

  Data_Get_Struct(val, afstruct, input);
  Data_Get_Struct(output_val, afstruct, output);

  af_cholesky(&output->carray, &info, input->carray, is_upper_val);

  return INT2NUM(info);
}

static VALUE arf_cholesky_inplace_func(VALUE self){
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
  Data_Get_Struct(piv_val, afstruct, piv);

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
  double det_real, det_imag;

  Data_Get_Struct(val, afstruct, matrix);

  af_det(&det_real, &det_imag, matrix->carray);
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
  bool output;
  af_is_lapack_available(&output);
  return output ? Qtrue : Qfalse;
}
