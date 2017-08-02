require 'test_helper'

class ArrayFire::StatisticsTest < Minitest::Test

  def setup
    @array = ArrayFire::Af_Array.new 2, [3,3], [4, 3, 5, 6, -11, 9 , -22, 11, 1]
    @weighted_array = ArrayFire::Af_Array.new 2, [3,3], [1, 2, 2, 0, -2, 2 , 1, 3, 1]
  end

  def test_mean
    result = ArrayFire::Af_Array.new 2, [3,1], [-4, 1, 5]
    assert_equal result, ArrayFire::Statistics.mean(@array, 1)
  end

  def test_mean_weighted
    result = ArrayFire::Af_Array.new 2, [3,1], [-9.0, 20.333, 5.8]
    assert result.approx_equal ArrayFire::Statistics.mean_weighted(@array, @weighted_array, 1)
  end

  def test_var
    result = ArrayFire::Af_Array.new 2, [3,1], [162.6667, 82.6667, 10.6667]
    assert result.approx_equal ArrayFire::Statistics.var(@array, true, 1)
    result = ArrayFire::Af_Array.new 2, [3,1], [244.0, 124.0, 16.0]
    assert result.approx_equal ArrayFire::Statistics.var(@array, false, 1)
  end

  def test_var_weighted
    result = ArrayFire::Af_Array.new 2, [3,1], [169.0, -367.111, 8.960]
    assert result.approx_equal ArrayFire::Statistics.var_weighted(@array, @weighted_array, 1)
  end

  def test_stdev
    result = ArrayFire::Af_Array.new 2, [3,1], [12.7540, 9.0921, 3.2659]
    assert result.approx_equal ArrayFire::Statistics.stdev(@array, 1)
  end

  def test_median
    result = ArrayFire::Af_Array.new 2, [3,1], [4, 3, 5]
    assert_equal result, ArrayFire::Statistics.median(@array, 1)
  end

  def test_mean_all
    assert_in_delta 0.667, ArrayFire::Statistics.mean_all(@array)
  end

  def mean_all_weighted
    assert_in_delta 7.20, ArrayFire::Statistics.mean_all_weighted(@array, @weighted_array)
  end

  def test_var_all
    assert_in_delta 98.8888, ArrayFire::Statistics.var_all(@array, true)
    assert_in_delta 111.250, ArrayFire::Statistics.var_all(@array, false)
  end

  def var_all_weighted
    assert_in_delta 33.360, ArrayFire::Statistics.var_all_weighted(@array, @weighted_array)
  end

  def stdev_all_weighted
    assert_in_delta 9.9442, ArrayFire::Statistics.stdev_all(@array)
  end

  def test_median_all
    assert 4.0, ArrayFire::Statistics.median_all(@array)
  end

  def test_corrcoef
    array_second = ArrayFire::Af_Array.new 2, [3,3], [42, 1, -15, 52, -121, 9 , -22, 1, 7]
    assert_equal 1.0, ArrayFire::Statistics.corrcoef(@array, array_second)
  end

end