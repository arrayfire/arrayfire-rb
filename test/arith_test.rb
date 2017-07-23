require 'test_helper'

class ArrayFire::ArithTest < Minitest::Test

  def setup
    @a = ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4]
    @b = ArrayFire::Af_Array.new 2, [2,2],[2,4,6,8]
    @elements = [10, -11, 48, 21, 65, 0, 1, -7, 112]
    @af_array =  ArrayFire::Af_Array.new 2, [3,3], @elements
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

  [:sin, :cos, :tan, :sinh, :cosh, :tanh].each do |method|
    define_method("test_#{method}") do
      x = @elements.map{ |e| Math.send(method, e) }
      res_arr =  ArrayFire::Af_Array.new 2, [3,3], x
      assert res_arr.approx_equal @af_array.send method
    end
  end

end
