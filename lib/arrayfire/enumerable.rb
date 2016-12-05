class Af_Array
  include Enumerable

  def each(&bl)
    Enumerator.new do |yielder|
      self.each_with_indices do |params|
        yielder.yield params
      end
    end
  end

end