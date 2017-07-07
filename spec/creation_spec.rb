require 'spec_helper'

describe ArrayFire::Af_Array do
  context '#initialize' do
    let(:i) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    subject { i }
    its(:ndims) { is_expected.to eq 2 }
    its(:dims) { is_expected.to eq [2,2] }
    its(:elements) {is_expected.to eq [1,2,3,4]}
  end

  context '#addition' do
    let(:a) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:b) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:c) { ArrayFire::Af_Array.new 2, [2,2],[2,4,6,8] }
    subject {a+b}
    it {is_expected.to eq c}
  end

end
