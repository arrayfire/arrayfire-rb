#define DEF_ELEMENTWISE_RUBY_ACCESSOR(name, oper)                          \
static VALUE arf_ew_##name(VALUE left_val, VALUE right_val) {              \
  afstruct* left;                                                          \
  afstruct* right;                                                         \
  afstruct* result = ALLOC(afstruct);                                      \
  Data_Get_Struct(left_val, afstruct, left);                               \
  Data_Get_Struct(right_val, afstruct, right);                             \
  af_##oper(&result->carray,  left->carray, right->carray, true);          \
  af_print_array(result->carray);                                          \
  return Data_Wrap_Struct(CLASS_OF(left_val), NULL, arf_free, result);     \
}

#define DEF_UNARY_RUBY_ACCESSOR(oper, name)                                \
static VALUE arf_unary_##name(VALUE self) {                                \
  afstruct* obj;                                                           \
  afstruct* result = ALLOC(afstruct);                                      \
  Data_Get_Struct(self, afstruct, obj);                                    \
  af_##oper(&result->carray, obj->carray);                                 \
  af_print_array(result->carray);                                          \
  return Data_Wrap_Struct(CLASS_OF(self), NULL, arf_free, result);         \
}

DEF_ELEMENTWISE_RUBY_ACCESSOR(add, add)
DEF_ELEMENTWISE_RUBY_ACCESSOR(subtract, sub)
DEF_ELEMENTWISE_RUBY_ACCESSOR(multiply, mul)
DEF_ELEMENTWISE_RUBY_ACCESSOR(divide, div)

DEF_ELEMENTWISE_RUBY_ACCESSOR(eqeq, eq)
DEF_ELEMENTWISE_RUBY_ACCESSOR(neq, neq)
DEF_ELEMENTWISE_RUBY_ACCESSOR(leq, le)
DEF_ELEMENTWISE_RUBY_ACCESSOR(geq, ge)
DEF_ELEMENTWISE_RUBY_ACCESSOR(lt, lt)
DEF_ELEMENTWISE_RUBY_ACCESSOR(gt, gt)

DEF_UNARY_RUBY_ACCESSOR(sin, sin)
DEF_UNARY_RUBY_ACCESSOR(cos, cos)
DEF_UNARY_RUBY_ACCESSOR(tan, tan)
DEF_UNARY_RUBY_ACCESSOR(asin, asin)
DEF_UNARY_RUBY_ACCESSOR(acos, acos)
DEF_UNARY_RUBY_ACCESSOR(atan, atan)
DEF_UNARY_RUBY_ACCESSOR(sinh, sinh)
DEF_UNARY_RUBY_ACCESSOR(cosh, cosh)
DEF_UNARY_RUBY_ACCESSOR(tanh, tanh)
DEF_UNARY_RUBY_ACCESSOR(asinh, asinh)
DEF_UNARY_RUBY_ACCESSOR(acosh, acosh)
DEF_UNARY_RUBY_ACCESSOR(atanh, atanh)
DEF_UNARY_RUBY_ACCESSOR(exp, exp)
DEF_UNARY_RUBY_ACCESSOR(log2, log2)
DEF_UNARY_RUBY_ACCESSOR(log1p, log1p)
DEF_UNARY_RUBY_ACCESSOR(log10, log10)
DEF_UNARY_RUBY_ACCESSOR(sqrt, sqrt)
DEF_UNARY_RUBY_ACCESSOR(erf, erf)
DEF_UNARY_RUBY_ACCESSOR(erfc, erfc)
DEF_UNARY_RUBY_ACCESSOR(cbrt, cbrt)
DEF_UNARY_RUBY_ACCESSOR(lgamma, lgamma)
DEF_UNARY_RUBY_ACCESSOR(tgamma, tgamma)
DEF_UNARY_RUBY_ACCESSOR(floor, floor)
DEF_UNARY_RUBY_ACCESSOR(ceil, ceil)
