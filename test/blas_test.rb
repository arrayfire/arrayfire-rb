require 'test_helper'

class ArrayFire::BLASTest < Minitest::Test

  def setup
    @a = ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4]
    @b = ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4]
  end

  def test_matmul
    c =  ArrayFire::Af_Array.new 2, [2,2],[7.0,10.0,15.0,22.0]
    assert_equal c, ArrayFire::BLAS.matmul(@a,@b)
  end

end
