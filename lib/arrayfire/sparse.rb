module ArrayFire
  class Sparse

    def self.sparse_get_info(af_array)
      values = ArrayFire::Af_Array.new
      rowIdx =  ArrayFire::Af_Array.new
      colIdx =  ArrayFire::Af_Array.new
      stype = ArrayFire::Sparse.sparse_get_info_func(values, rowIdx, colIdx, af_array)
      return values, rowIdx, colIdx, stype
    end

  end
end
