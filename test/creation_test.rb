require 'test_helper'

class ArrayFire::Af_ArrayTest < Minitest::Test

  def setup
    @i = ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4]
  end

  def test_ndims
    assert_equal 2, @i.ndims
  end

  def test_dims
    assert_equal [2,2], @i.dims
  end

  def test_elements
    assert_equal [1, 2, 3, 4], @i.elements
  end

end
