module ArrayFire
  class LAPACK

    def self.svd(af_array)
      u =  ArrayFire::Af_Array.new
      s =  ArrayFire::Af_Array.new
      vt = ArrayFire::Af_Array.new
      ArrayFire::LAPACK.svd_func(u, s, vt, af_array)
      return u, s, vt
    end

    def self.lu(af_array)
      lower =  ArrayFire::Af_Array.new
      upper =  ArrayFire::Af_Array.new
      pivot = ArrayFire::Af_Array.new
      ArrayFire::LAPACK.lu_func(lower, upper, pivot, af_array)
      return lower, upper, pivot
    end

    def self.qr(af_array)
      q =  ArrayFire::Af_Array.new
      r =  ArrayFire::Af_Array.new
      tau = ArrayFire::Af_Array.new
      ArrayFire::LAPACK.qr_func(q, r, tau, af_array)
      return q, r, tau
    end

    def self.cholesky(af_array, is_upper=true)
      out =  ArrayFire::Af_Array.new
      info = ArrayFire::LAPACK.cholesky_func(out, af_array, is_upper)
      return out, info
    end

  end
end

