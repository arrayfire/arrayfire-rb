require 'test_helper'

class ArrayFire::AlgorithmTest < Minitest::Test

  def setup
    @input = ArrayFire::Af_Array.new 2, [3,3], [4, 1, 5, 6, -11, 9 , -22, 11, 1]
    @input2 = ArrayFire::Af_Array.new 2, [3,3], [4, 1, 5, 6, -11, 9 , -22, 11, 0]
    @inf_array = @input / @input2
    @nan_array = @inf_array / @inf_array
  end

  def test_sum
    sum_arr = ArrayFire::Af_Array.new 1, [3], [-12.0, 1.0, 15.0]
    result = ArrayFire::Algorithm.sum(@input, 1)
    assert_equal(sum_arr, result)
  end

  def test_sum_nan
    sum_nan_arr = ArrayFire::Af_Array.new 1, [3], [3.0, 3.0, 8.0]
    result = ArrayFire::Algorithm.sum_nan(@nan_array, 1, 6)
    assert_equal(sum_nan_arr, result)
  end

  def test_product
    product_arr = ArrayFire::Af_Array.new 1, [3], [-528.0, -121.0, 45.0]
    result = ArrayFire::Algorithm.product(@input, 1)
    assert_equal(product_arr, result)
  end

  def test_product_nan
    product_nan_arr = ArrayFire::Af_Array.new 1, [3], [1.0, 1.0, 6.0]
    result = ArrayFire::Algorithm.product_nan(@nan_array, 1, 6)
    assert_equal(product_nan_arr, result)
  end

  def test_min
    min_arr = ArrayFire::Af_Array.new 1, [3], [-22.0, -11.0, 1]
    result = ArrayFire::Algorithm.min(@input, 1)
    assert_equal(min_arr, result)
  end

  def test_max
    max_arr = ArrayFire::Af_Array.new 1, [3], [6.0, 11.0, 9.0]
    result = ArrayFire::Algorithm.max(@input, 1)
    assert_equal(max_arr, result)
  end

  def test_all_true
    all_true_arr = ArrayFire::Af_Array.new 1, [3], [1.0, 1.0, 1.0]
    result = ArrayFire::Algorithm.all_true(@input, 1)
    assert_equal(all_true_arr, result)
  end

  def test_any_true
    any_true_arr = ArrayFire::Af_Array.new 1, [3], [1.0, 1.0, 1.0]
    result = ArrayFire::Algorithm.any_true(@input, 1)
    assert_equal(any_true_arr, result)
  end

  def test_count
    count_arr = ArrayFire::Af_Array.new 1, [3], [3.0, 3.0, 3.0]
    result = ArrayFire::Algorithm.count(@input, 1)
    assert_equal(count_arr, result)
  end

  def test_sum_all
    assert_equal 4, ArrayFire::Algorithm.sum_all(@input)
  end

  def test_sum_nan_all
    assert_equal 18, ArrayFire::Algorithm.sum_nan_all(@nan_array, 10)
  end

  def test_product_all
    assert_equal 2874960.0, ArrayFire::Algorithm.product_all(@input)
  end

  def test_product_nan_all
    assert_equal 10, ArrayFire::Algorithm.product_nan_all(@nan_array, 10)
  end

  def test_min_all
    assert_equal -22, ArrayFire::Algorithm.min_all(@input)
  end

  def test_max_all
    assert_equal 11, ArrayFire::Algorithm.max_all(@input)
  end

  def test_all_true_all
    assert_equal 1, ArrayFire::Algorithm.all_true_all(@input)
  end

  def test_any_true_all
    assert_equal 1, ArrayFire::Algorithm.any_true_all(@input)
  end

end
