require 'test_helper'

class ArrayFire::BLASTest < Minitest::Test

  def setup
    @matrix_left  = ArrayFire::Af_Array.new 2, [2,2],[ 12, 21,-61, 48]
    @matrix_right = ArrayFire::Af_Array.new 2, [2,2],[-15, 41, 30 , 7 ]
    @vector_left  = ArrayFire::Af_Array.new 2, [4,1],[-15, 41, 30 , 7 ]
    @vector_right = ArrayFire::Af_Array.new 2, [4,1],[ 25, 141, 17 , 7 ]
  end

  def test_matmul
    result = ArrayFire::Af_Array.new 2, [2,2],[-2681.0, 1653.0, -67.0, 966.0]
    assert_equal result, ArrayFire::BLAS.matmul(@matrix_left, @matrix_right, :AF_MAT_NONE)
  end

  def test_dot
    result = ArrayFire::Af_Array.new 1,[1],[5965.0]
    assert_equal result, ArrayFire::BLAS.dot(@vector_left, @vector_right)
  end

  def test_transpose
    result = ArrayFire::Af_Array.new 2, [2,2], [12.0, -61.0, 21.0, 48.0]
    assert_equal result, ArrayFire::BLAS.transpose(@matrix_left)
  end

end
