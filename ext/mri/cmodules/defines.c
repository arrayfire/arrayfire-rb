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

const char* const SOURCE_NAMES[ARF_NUM_SOURCES] = {
  "afDevice",   ///< Device pointer
  "afHost"     ///< Host pointer
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

const char* const NORM_TYPES[ARF_NUM_NORM_TYPES] = {
  "AF_NORM_VECTOR_1",      ///< treats the input as a vector and returns the sum of absolute values
  "AF_NORM_VECTOR_INF",    ///< treats the input as a vector and returns the max of absolute values
  "AF_NORM_VECTOR_2",      ///< treats the input as a vector and returns euclidean norm
  "AF_NORM_VECTOR_P",      ///< treats the input as a vector and returns the p-norm
  "AF_NORM_MATRIX_1",      ///< return the max of column sums
  "AF_NORM_MATRIX_INF",    ///< return the max of row sums
  "AF_NORM_MATRIX_2",      ///< returns the max singular value). Currently NOT SUPPORTED
  "AF_NORM_MATRIX_L_PQ",   ///< returns Lpq-norm
  "AF_NORM_EUCLID"         ///< The default. Same as AF_NORM_VECTOR_2
};

std::map<char*, size_t> MOMENT_TYPES = {
  {"AF_MOMENT_M00", 1},
  {"AF_MOMENT_M01", 2},
  {"AF_MOMENT_M10", 4},
  {"AF_MOMENT_M11", 8}
  //AF_MOMENT_FIRST_ORDER = AF_MOMENT_M00 | AF_MOMENT_M01 | AF_MOMENT_M10 | AF_MOMENT_M11
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

af_source arf_source_from_rbsymbol(VALUE sym) {
  ID sym_id = SYM2ID(sym);

  for (size_t index = 0; index < ARF_NUM_SOURCES; ++index) {
    if (sym_id == rb_intern(SOURCE_NAMES[index])) {
      return static_cast<af_source>(index);
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

af_norm_type arf_norm_type_from_rbsymbol(VALUE sym) {
  ID sym_id = SYM2ID(sym);

  for (size_t index = 0; index < ARF_NUM_NORM_TYPES; ++index) {
    if (sym_id == rb_intern(NORM_TYPES[index])) {
      return static_cast<af_norm_type>(index);
    }
  }

  VALUE str = rb_any_to_s(sym);
  rb_raise(rb_eArgError, "invalid norm type symbol (:%s) specified", RSTRING_PTR(str));
}

af_moment_type arf_moment_type_from_rbsymbol(VALUE sym) {
  ID sym_id = SYM2ID(sym);

  for(std::map<char*, size_t>::value_type& entry : MOMENT_TYPES) {
    if (sym_id == rb_intern(entry.first)) {
      return static_cast<af_moment_type>(entry.second);
    }
  }

  VALUE str = rb_any_to_s(sym);
  rb_raise(rb_eArgError, "invalid moment type symbol (:%s) specified", RSTRING_PTR(str));
}
