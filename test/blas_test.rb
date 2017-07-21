require 'spec_helper'

describe ArrayFire::BLAS do
  context '#matmul' do
    let(:a) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:b) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:c) { ArrayFire::Af_Array.new 2, [2,2],[7.0,10.0,15.0,22.0] }
    subject {ArrayFire::BLAS.matmul(a,b)}
    it {is_expected.to eq c}
  end
end
