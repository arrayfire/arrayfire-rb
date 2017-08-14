require 'test_helper'

class ArrayFire::LAPACKTest < Minitest::Test

  def setup
    @array = ArrayFire::Af_Array.new 2, [2,2],[ 12, 21,-61, 48 ]
  end

  def test_svd
    matrix = ArrayFire::Af_Array.new 2, [4,2], [1,3,5,7,2,4,6,8]
    u = ArrayFire::Af_Array.new 2, [4,4], [-0.1524, -0.3499, -0.5473, -0.7447, -0.8226, -0.4213, -0.0201, 0.3811, -0.3945, 0.2427, 0.6979, -0.5462, -0.3799, 0.8006, -0.4614, 0.0407]
    s = ArrayFire::Af_Array.new 2, [2,1], [14.269095420837402, 0.6268]
    v = ArrayFire::Af_Array.new 2, [2,2], [-0.6414, 0.7671, -0.7671, -0.6414]
    svd_fac = ArrayFire::LAPACK.svd(matrix);
    assert(u.approx_equal svd_fac[0])
    assert(s.approx_equal svd_fac[1])
    assert(v.approx_equal svd_fac[2])
  end

  def test_lu
    matrix = ArrayFire::Af_Array.new 2, [3,3], [1,4,7,2,5,8,3,6,0]
    l = ArrayFire::Af_Array.new 2, [3,3], [1.0, 0.1428, 0.5714, 0.0, 1.0, 0.4999, 0.0, 0.0, 1.0]
    u = ArrayFire::Af_Array.new 2, [3,3], [7.0, 0.0, 0.0, 8.0, 0.8571, 0.0, 0.0, 3.0, 4.5000]
    p = ArrayFire::Af_Array.new 2, [3,1], [0, 0, 0]
    lu_fac = ArrayFire::LAPACK.lu(matrix);
    assert(l.approx_equal lu_fac[0])
    assert(u.approx_equal lu_fac[1])
    assert(p.approx_equal lu_fac[2])
  end

  def test_qr
    matrix = ArrayFire::Af_Array.new 2, [3,3], [12.0, -51.0,   4.0, 6.0, 167.0, -68.0, -4.0,  24.0, -41.0]
    q = ArrayFire::Af_Array.new 2, [3,3], [-0.2283, 0.9705, -0.0761, -0.6189, -0.0843, 0.7809, 0.7515, 0.2254, 0.6199]
    r = ArrayFire::Af_Array.new 2, [3,3], [-52.5452, 0.0, 0.0, 165.8952, -70.9068, 0.0, 27.3288, -31.5664, -23.015]
    p = ArrayFire::Af_Array.new 2, [3,1], [1.2283, 1.5734, 0.0]
    qr_fac = ArrayFire::LAPACK.qr matrix
    assert(q.approx_equal qr_fac[0])
    assert(r.approx_equal qr_fac[1])
    assert(p.approx_equal qr_fac[2])
  end

  def test_cholesky
    mat_upper = ArrayFire::Af_Array.new 2, [3,3], [1,0,0, 1,2,0, 1,2,6]
    res_upper =  ArrayFire::Af_Array.new 2, [3,3], [1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 2.0]
    upper = ArrayFire::LAPACK.cholesky(mat_upper)[0]
    assert_equal upper, res_upper

    mat_lower =  ArrayFire::Af_Array.new 2, [3,3], [1,1,1, 0,2,2, 0,0,6]
    res_lower = ArrayFire::Af_Array.new 2, [3,3], [1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 2.0]
    lower = ArrayFire::LAPACK.cholesky(mat_lower, false)[0]
    assert_equal lower, res_lower
  end

  def test_solve
    lhs = ArrayFire::Af_Array.new 2, [2,2], [3,1,1,2]
    rhs = ArrayFire::Af_Array.new 2, [2,1], [9,8]
    solution = ArrayFire::Af_Array.new 2, [2,1], [2,3]
    assert_equal solution, ArrayFire::LAPACK.solve(lhs, rhs)
  end

  def test_solve_lu
    # TODO
  end

  def test_inverse
    result = ArrayFire::Af_Array.new 2, [2,2], [0.0258, -0.0113, 0.0328, 0.0064]
    assert(result.approx_equal ArrayFire::LAPACK.inverse(@array));
  end

  def test_rank
    assert_equal ArrayFire::LAPACK.rank(@array), 2;
  end

  def test_det
    assert_equal ArrayFire::LAPACK.det(@array), 1857.0;
  end

  def test_norm
    assert((ArrayFire::LAPACK.norm(@array) - 81.3019).abs < 0.001);
  end

  def test_is_lapack_available
    assert(ArrayFire::LAPACK.is_lapack_available);
  end

end
