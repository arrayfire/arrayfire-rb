require 'test_helper'

class ArrayFire::LAPACKTest < Minitest::Test

  def setup
    @array = ArrayFire::Af_Array.new 2, [2,2],[ 12, 21,-61, 48 ]
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
