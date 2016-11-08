// #include "ruby.h"

#include "arrayfire.h"
#include <stdio.h>
#include <math.h>

#include "ruby_arrayfire.h"

VALUE ArrayFire = Qnil;
VALUE Af_Array = Qnil;
VALUE Device = Qnil;
VALUE Blas = Qnil;
VALUE Lapack = Qnil;

typedef struct AF_STRUCT
{
  size_t dimension;     // Method of storage (csc, dense, etc).
  size_t array;
}afstruct;



// prototypes
// void Init_arrayfire();
static VALUE test1(VALUE self);
// VALUE method_arf_init(VALUE self, VALUE val);
static VALUE arf_init(int argc, VALUE* argv, VALUE self);
static VALUE arf_alloc(VALUE klass);
static void arf_free(afstruct* af);
static VALUE dimension(VALUE self);
static VALUE array(VALUE self);
static VALUE get_info(VALUE self);

void Init_arrayfire() {
  ArrayFire = rb_define_module("ArrayFire");
  rb_define_method(ArrayFire, "test1", (METHOD)test1, 0);

  Af_Array = rb_define_class_under(ArrayFire, "Af_Array", rb_cObject);
  rb_define_alloc_func(Af_Array, arf_alloc);
  rb_define_method(Af_Array, "initialize", (METHOD)arf_init, -1);
  rb_define_method(Af_Array, "dimension", (METHOD)dimension, 0);
  rb_define_method(Af_Array, "array", (METHOD)array, 0);

  Device = rb_define_class_under(ArrayFire, "Device", rb_cObject);
  rb_define_method(Device, "getInfo", (METHOD)get_info, 0);

  Blas = rb_define_class_under(ArrayFire, "BLAS", rb_cObject);

  Lapack = rb_define_class_under(ArrayFire, "LAPACK", rb_cObject);
}

VALUE test1(VALUE self) {
  VALUE x;
  x = rb_str_new_cstr("Hello, world!");
  return x;
}

VALUE arf_init(int argc, VALUE* argv, VALUE self)
{

  afstruct* afarray;
  Data_Get_Struct(self, afstruct, afarray);
  afarray->dimension = argv[0];
  afarray->array = argv[1];


  return self;
}

static VALUE arf_alloc(VALUE klass)
{
  /* allocate */
  afstruct* af = ALLOC(afstruct);
  /* wrap */
  return Data_Wrap_Struct(klass, NULL, arf_free, af);
}


static void arf_free(afstruct* af)
{
  free(af);
}

static VALUE dimension(VALUE self)
{
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);

  return af->dimension;
}

static VALUE array(VALUE self)
{
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);

  return af->array;
}

static VALUE get_info(VALUE self)
{
  VALUE x;
  af_info();
  arf::matmul_benchmark();
  return x;
}

