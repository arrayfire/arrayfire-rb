require_relative 'mkmf.rb'

extension_name = 'arrayfire'

dir_config(extension_name)

$INSTALLFILES = [
  ['ruby_arrayfire.h'       , '$(archdir)'],
  ['ruby_arrayfire.hpp'     , '$(archdir)'],
  ['arrayfire_config.h', '$(archdir)'],
]

$DEBUG = true
$CFLAGS = ["-Wall -Werror=return-type",$CFLAGS].join(" ")
$CXXFLAGS = ["-Wall -Werror=return-type",$CXXFLAGS].join(" ")
$CPPFLAGS = ["-Wall -Werror=return-type",$CPPFLAGS].join(" ")

dir_config('arrayfire', '/usr/local/include/', '/usr/local/lib/')

# $LOCAL_LIBS =
LIBDIR      = RbConfig::CONFIG['libdir']
INCLUDEDIR  = RbConfig::CONFIG['includedir']

HEADER_DIRS = [INCLUDEDIR, '/usr/local/include/', '/usr/local/include/af/']

have_library('afcuda')
have_library('cusolver')
have_library('cudart')
have_library('cufft')
have_library('cublas')

basenames = %w{ruby_arrayfire}
$objs = basenames.map { |b| "#{b}.o"   }
$srcs = basenames.map { |b| "#{b}.cpp" }

create_conf_h("arrayfire_config.h")
create_makefile(extension_name)