add_compile_options(-fexceptions)

add_llvm_library(LLVMAnnotation MODULE
  Annotation.cpp

  DEPENDS
  intrinsics_gen  
  PLUGIN_TOOL
  opt
  )


