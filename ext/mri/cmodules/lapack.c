static void cholesky_(afstruct *result, afstruct *matrix)
{
  array m = array(matrix->dimension[0], matrix->dimension[1], matrix->array);
  bool is_upper = true;
  array res;
  cholesky(res, m, is_upper);
  result->array = res.host<double>();
}

static void inverse_(afstruct *result, afstruct *matrix)
{
  array m = array(matrix->dimension[0], matrix->dimension[1], matrix->array);
  array res = inverse(m);
  result->array = res.host<double>();
}

static double norm_(afstruct *matrix)
{
  array m = array(matrix->dimension[0], matrix->dimension[1], matrix->array);
  return norm(m, AF_NORM_EUCLID, 1, 1);
}