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
  "afDevice",                                        ///< Device pointer
  "afHost"                                           ///< Host pointer
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

std::map<char*, size_t> BACKEND_TYPES = {
  {"AF_BACKEND_DEFAULT" , 0},                        ///< Default backend order: OpenCL -> CUDA -> CPU
  {"AF_BACKEND_CPU"     , 1},                        ///< CPU a.k.a sequential algorithms
  {"AF_BACKEND_CUDA"    , 2},                        ///< CUDA Compute Backend
  {"AF_BACKEND_OPENCL"  , 4}                         ///< OpenCL Compute Backend
};

std::map<char*, size_t> RANDOM_ENGINE_TYPES = {
  {"AF_RANDOM_ENGINE_PHILOX_4X32_10"   , 100},       //Philox variant with N = 4, W = 32 and Rounds = 10
  {"AF_RANDOM_ENGINE_THREEFRY_2X32_16" , 200},       //Threefry variant with N = 2, W = 32 and Rounds = 16
  {"AF_RANDOM_ENGINE_MERSENNE_GP11213" , 300},       //Mersenne variant with MEXP = 11213
  {"AF_RANDOM_ENGINE_PHILOX"           , 100},       //Resolves to Philox 4x32_10
  {"AF_RANDOM_ENGINE_THREEFRY"         , 200},       //Resolves to Threefry 2X32_16
  {"AF_RANDOM_ENGINE_MERSENNE"         , 300},       //Resolves to Mersenne GP 11213
  {"AF_RANDOM_ENGINE_DEFAULT"          , 100},       //Resolves to Philox
};

std::map<char*, size_t> ERROR_TYPES = {
  {"AF_SUCCESS"                ,   0},
  {"AF_ERR_NO_MEM"             , 101},
  {"AF_ERR_DRIVER"             , 102},
  {"AF_ERR_RUNTIME"            , 103},
  {"AF_ERR_INVALID_ARRAY"      , 201},
  {"AF_ERR_ARG"                , 202},
  {"AF_ERR_SIZE"               , 203},
  {"AF_ERR_TYPE"               , 204},
  {"AF_ERR_DIFF_TYPE"          , 205},
  {"AF_ERR_BATCH"              , 207},
  {"AF_ERR_DEVICE"             , 208},
  {"AF_ERR_NOT_SUPPORTED"      , 301},
  {"AF_ERR_NOT_CONFIGURED"     , 302},
  {"AF_ERR_NONFREE"            , 303},
  {"AF_ERR_NO_DBL"             , 401},
  {"AF_ERR_NO_GFX"             , 402},
  {"AF_ERR_LOAD_LIB"           , 501},
  {"AF_ERR_LOAD_SYM"           , 502},
  {"AF_ERR_ARR_BKND_MISMATCH"  , 503},
  {"AF_ERR_INTERNAL"           , 998},
  {"AF_ERR_UNKNOWN"            , 999}
};

const char* const STORAGE_TYPES[ARF_NUM_STORAGE_TYPES] = {
  "AF_STORAGE_DENSE",                                ///< Storage type is dense
  "AF_STORAGE_CSR",                                  ///< Storage type is CSR
  "AF_STORAGE_CSC",                                  ///< Storage type is CSC
  "AF_STORAGE_COO",                                  ///< Storage type is COO
};

void arf_handle_exception(af_err error_code){
  for(std::map<char*, size_t>::value_type& entry : ERROR_TYPES) {
    if (error_code == entry.second) {
      rb_raise(rb_eArgError, entry.first);
      break;
    }
  }
}

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

af_backend arf_backend_type_from_rbsymbol(VALUE sym) {
  ID sym_id = SYM2ID(sym);

  for(std::map<char*, size_t>::value_type& entry : BACKEND_TYPES) {
    if (sym_id == rb_intern(entry.first)) {
      return static_cast<af_backend>(entry.second);
    }
  }

  VALUE str = rb_any_to_s(sym);
  rb_raise(rb_eArgError, "invalid backend type symbol (:%s) specified", RSTRING_PTR(str));
}

af_random_engine_type arf_randome_engine_type_from_rbsymbol(VALUE sym) {
  ID sym_id = SYM2ID(sym);

  for(std::map<char*, size_t>::value_type& entry : RANDOM_ENGINE_TYPES) {
    if (sym_id == rb_intern(entry.first)) {
      return static_cast<af_random_engine_type>(entry.second);
    }
  }

  VALUE str = rb_any_to_s(sym);
  rb_raise(rb_eArgError, "invalid engine type symbol (:%s) specified", RSTRING_PTR(str));
}

af_storage arf_storage_type_from_rbsymbol(VALUE sym){
  ID sym_id = SYM2ID(sym);

  for (size_t index = 0; index < ARF_NUM_STORAGE_TYPES; ++index) {
    if (sym_id == rb_intern(STORAGE_TYPES[index])) {
      return static_cast<af_storage>(index);
    }
  }

  VALUE str = rb_any_to_s(sym);
  rb_raise(rb_eArgError, "invalid storage type symbol (:%s) specified", RSTRING_PTR(str));
}

const char* get_backend_name(af_backend backend){
  for(std::map<char*, size_t>::value_type& entry : BACKEND_TYPES) {
    if (backend == entry.second) {
      return entry.first;
    }
  }
  rb_raise(rb_eArgError, "Something went wrong!");
}

const char* get_random_engine_name(af_random_engine_type engine){
  for(std::map<char*, size_t>::value_type& entry : RANDOM_ENGINE_TYPES) {
    if (engine == entry.second) {
      return entry.first;
    }
  }
  rb_raise(rb_eArgError, "Something went wrong!");
}
