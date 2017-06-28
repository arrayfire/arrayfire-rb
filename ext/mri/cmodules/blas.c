static void matmul(afstruct *result, afstruct *left, afstruct *right)
{
  array l = array(left->dimension[0], left->dimension[1], left->array);
  array r = array(right->dimension[0], right->dimension[1], right->array);
  array res = matmul(l,r);
  result->array = res.host<double>();
}
