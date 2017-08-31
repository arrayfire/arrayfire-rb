require 'test_helper'

class ArrayFire::DataTest < Minitest::Test

  def setup
    @first = ArrayFire::Af_Array.new 2, [3,3], [4, 1, 5, 6, -11, 9 , -22, 11, 1]
    @second = ArrayFire::Af_Array.new 2, [3,3], [-14, 27, 15, 6, -11, 9 , 22, 0, 61]
    @diagonal = ArrayFire::Af_Array.new 1, [4,1], [1, 2, 3, 4]
    @order_array = ArrayFire::Af_Array.new 2, [3,3], [1, 2, 3, 4, 5, 6 , 7, 8 , 9]
  end

  def test_constant
    result = ArrayFire::Af_Array.new 2, [3,3], [4, 4, 4, 4, 4, 4, 4, 4, 4]
    assert_equal result, ArrayFire::Data.constant( 2, [3,3], 4 );
  end

  def test_constant_complex
    # ArrayFire::Data.constant_complex
  end

  def test_constant_long
    result = ArrayFire::Af_Array.new 2, [3,3], [4, 4, 4, 4, 4, 4, 4, 4, 4]
    assert_equal result, ArrayFire::Data.constant_long( 2, [3,3],4 )
  end

  def test_constant_ulong
    result = ArrayFire::Af_Array.new 2, [3,3], [4, 4, 4, 4, 4, 4, 4, 4, 4]
    assert_equal result, ArrayFire::Data.constant_ulong( 2, [3,3], 4 )
  end

  def test_range
    result = ArrayFire::Af_Array.new 2, [4,4], [0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 2.0, 2.0, 3.0, 3.0, 3.0, 3.0]
    assert_equal result, ArrayFire::Data.range( 2, [4,4], 1 )
  end

  def test_iota
    # ArrayFire::Data.iota
  end

  def test_identity
    result = ArrayFire::Af_Array.new 2, [4,5], [1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0]
    assert_equal result, ArrayFire::Data.identity( 2, [4,5] )
  end

  def test_diag_create
    result = ArrayFire::Af_Array.new 2, [4,4], [1.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 4.0]
    assert_equal result, ArrayFire::Data.diag_create( @diagonal, 0 )
  end

  def test_diag_extract
    diag_matrix = ArrayFire::Data.diag_create @diagonal, 0
    assert_equal @diagonal, ArrayFire::Data.diag_extract( diag_matrix, 0 )
  end

  def test_join
    result = ArrayFire::Af_Array.new 2, [3, 6], [4.0, 1.0, 5.0, 6.0, -11.0, 9.0, -22.0, 11.0, 1.0,
                                                -14.0, 27.0, 15.0, 6.0, -11.0, 9.0, 22.0,0.0, 61.0]

    assert_equal result, ArrayFire::Data.join(1, @first, @second)
  end

  def test_join_many
    # result = ArrayFire::Af_Array.new 2, [3, 6], [4.0, 1.0, 5.0, 6.0, -11.0, 9.0, -22.0, 11.0, 1.0,
    #                                             -14.0, 27.0, 15.0, 6.0, -11.0, 9.0, 22.0,0.0, 61.0]

    # assert_equal result, ArrayFire::Data.join_many(1, @first, @second)
  end

  def test_tile
    result = ArrayFire::Af_Array.new 2, [6,9], [1.0,2.0,3.0,1.0,2.0,3.0,4.0,5.0,6.0,
                                                4.0,5.0,6.0,7.0,8.0,9.0,7.0,8.0,9.0,
                                                1.0,2.0,3.0,1.0,2.0,3.0,4.0,5.0,6.0,
                                                4.0,5.0,6.0,7.0,8.0,9.0,7.0,8.0,9.0,
                                                1.0,2.0,3.0,1.0,2.0,3.0,4.0,5.0,6.0,
                                                4.0,5.0,6.0,7.0,8.0,9.0,7.0,8.0,9.0]

    assert_equal result.elements, ArrayFire::Data.tile( @order_array, 2, 3, 1, 1 ).elements
  end

  def test_reorder
    result = ArrayFire:: Af_Array.new 2, [3,3], [1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0]
    assert_equal result, ArrayFire::Data.reorder( @order_array, 1, 0, 2, 3 )
  end

  def test_shift
    first_shift = ArrayFire::Af_Array.new 2, [3,3], [3.0, 1.0, 2.0, 6.0, 4.0, 5.0, 9.0, 7.0, 8.0]
    second_shift = ArrayFire::Af_Array.new 2, [3,3], [6.0, 4.0, 5.0, 9.0, 7.0, 8.0, 3.0, 1.0, 2.0]
    assert_equal first_shift, ArrayFire::Data.shift( @order_array, 1, 0, 0, 0 )
    assert_equal second_shift, ArrayFire::Data.shift( @order_array, 1, 2, 0, 0 )
  end

  def test_moddims
    # result = ArrayFire::Af_Array.new 2, [9,1], [4, 1, 5, 6, -11, 9 , -22, 11, 1]
    # assert_equal result, ArrayFire::Data.moddims( @input, 2, [9,1] )
  end

  def test_flat
    result = ArrayFire::Af_Array.new 1, [9], [4.0, 1.0, 5.0, 6.0, -11.0, 9.0, -22.0, 11.0, 1.0]
    assert_equal result, ArrayFire::Data.flat(@first)
  end

  def test_flip
    result = ArrayFire::Af_Array.new 2, [3,3], [-22.0, 11.0, 1.0, 6.0, -11.0, 9.0, 4.0, 1.0, 5.0]
    assert_equal result, ArrayFire::Data.flip(@first, 1)
  end

  def test_lower
    result = ArrayFire::Af_Array.new 2, [3,3], [4.0, 1.0, 5.0, 0.0, -11.0, 9.0, 0.0, 0.0, 1.0]
    assert_equal result, ArrayFire::Data.lower(@first, false)

    #unit_diagonal
    result = ArrayFire::Af_Array.new 2, [3,3], [1.0, 1.0, 5.0, 0.0, 1.0, 9.0, 0.0, 0.0, 1.0]
    assert_equal result, ArrayFire::Data.lower(@first, true)
  end

  def test_upper
    result = ArrayFire::Af_Array.new 2, [3,3], [4.0, 0.0, 0.0, 6.0, -11.0, 0.0, -22.0, 11.0, 1.0]
    assert_equal result, ArrayFire::Data.upper(@first, false)

    #unit_diagonal
    result = ArrayFire::Af_Array.new 2, [3,3], [1.0, 0.0, 0.0, 6.0, 1.0, 0.0, -22.0, 11.0, 1.0]
    assert_equal result, ArrayFire::Data.upper(@first, true)
  end

  def test_select
    # ArrayFire::Data.select
  end

  def test_select_scalar_r
    # ArrayFire::Data.select_scalar_r
  end

  def test_select_scalar_l
    # ArrayFire::Data.select_scalar_l
  end

  def test_replace
    # ArrayFire::Data.replace
  end

  def test_replace_scalar
    # ArrayFire::Data.replace_scalar
  end

end
