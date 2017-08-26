module ArrayFire
  class Device
    def self.device_info
      d_name     = ""
      d_platform = ""
      d_toolkit  = ""
      d_compute  = ""
      ArrayFire::Device.device_info_func(d_name, d_platform, d_toolkit, d_compute);
      return d_name, d_platform, d_toolkit, d_compute
    end
  end
end
