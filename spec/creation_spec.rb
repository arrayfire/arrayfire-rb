require 'spec_helper'

describe ArrayFire::Af_Array do
  context '#initialize' do
    let(:i) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    subject { i }
    it { expect(i.ndims).to eq 2 }
    it { expect(i.dimension).to eq [2,2] }
    it { expect(i.array).to eq [1,2,3,4] }
    it{
      pending("only float supported currently")
      expect(i.dtype).to eq :float64
    }
  end

  context '#addition' do
    let(:a) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:b) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:c) { ArrayFire::Af_Array.new 2, [2,2],[2,4,6,8] }
    subject {c}
    it {expect(a+b).to eq c}
    it {expect(c.ndims).to eq a.ndims}
    it {expect(c.dimension).to eq a.dimension}
  end

  context '#Equality' do
    let(:a) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:b) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    subject {c}
    it {expect(a).to eq b}
    it {expect(b.ndims).to eq a.ndims}
    it {expect(b.dimension).to eq a.dimension}
  end
end
