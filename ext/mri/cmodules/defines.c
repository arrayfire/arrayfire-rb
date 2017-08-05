const char* const DTYPE_NAMES[ARF_NUM_DTYPES] = {
  "f32",
  "c32",
  "f64",
  "c64",
  "b8",
  "s32",
  "u32",
  "u8",
  "s64",
  "u64",
  "s16",
  "u16"
};

af_dtype arf_dtype_from_rbsymbol(VALUE sym) {
  ID sym_id = SYM2ID(sym);

  for (size_t index = 0; index < ARF_NUM_DTYPES; ++index) {
    if (sym_id == rb_intern(DTYPE_NAMES[index])) {
      return static_cast<af_dtype>(index);
    }
  }

  VALUE str = rb_any_to_s(sym);
  rb_raise(rb_eArgError, "invalid data type symbol (:%s) specified", RSTRING_PTR(str));
}
