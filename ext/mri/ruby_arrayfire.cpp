#include <ruby.h>
#include <algorithm> // std::min
#include <fstream>
#include <arrayfire.h>
#include <af/cuda.h>
#include <af/opencl.h>
#include <stdio.h>
#include <math.h>
#include <map>

/*
 * Project Includes
 */

#include "arrayfire.h"
#include "ruby_arrayfire.h"

namespace arf {

}
extern "C" {
  #include "arrayfire.c"
}
