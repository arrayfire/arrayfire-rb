require 'test_helper'

class ArrayFire::ArithTest < Minitest::Test

  def setup
    @a = ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4]
    @b = ArrayFire::Af_Array.new 2, [2,2],[2,4,6,8]
  end

  def test_addition
    c = ArrayFire::Af_Array.new 2, [2,2],[3,6,9,12]
    assert_equal c, @a + @b
  end

  def test_subtraction
    assert_equal @a, @b - @a
  end

  def test_multiplication
    c = ArrayFire::Af_Array.new 2, [2,2],[2,8,18,32]
    assert_equal c, @b * @a
  end

  def test_division
    c = ArrayFire::Af_Array.new 2, [2,2],[2,2,2,2]
    assert_equal c, @b / @a
  end

end
