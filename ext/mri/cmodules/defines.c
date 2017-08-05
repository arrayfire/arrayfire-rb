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

std::map<char*, size_t> MAT_PROPERTIES = {
  {"AF_MAT_NONE", 0},
  {"AF_MAT_TRANS", 1},
  {"AF_MAT_CTRANS", 2},
  {"AF_MAT_CONJ", 4},
  {"AF_MAT_UPPER", 32},
  {"AF_MAT_LOWER", 64},
  {"AF_MAT_DIAG_UNIT", 128},
  {"AF_MAT_SYM", 512},
  {"AF_MAT_POSDEF", 1024},
  {"AF_MAT_ORTHOG", 2048},
  {"AF_MAT_TRI_DIAG", 4096},
  {"AF_MAT_BLOCK_DIAG", 8192}
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

af_mat_prop arf_mat_type_from_rbsymbol(VALUE sym) {
  ID sym_id = SYM2ID(sym);

  for(std::map<char*, size_t>::value_type& entry : MAT_PROPERTIES) {
    if (sym_id == rb_intern(entry.first)) {
      return static_cast<af_mat_prop>(entry.second);
    }
  }

  VALUE str = rb_any_to_s(sym);
  rb_raise(rb_eArgError, "invalid matrix type symbol (:%s) specified", RSTRING_PTR(str));
}
