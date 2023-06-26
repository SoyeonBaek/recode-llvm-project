# If we don't need RTTI or EH, there's no reason to export anything
# from the hello plugin.
if( NOT LLVM_REQUIRES_RTTI )
  if( NOT LLVM_REQUIRES_EH )
    set(LLVM_EXPORTED_SYMBOL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Hello.exports)
  endif()
endif()

if(WIN32 OR CYGWIN)
  set(LLVM_LINK_COMPONENTS Core Support)
endif()

LINK_DIRECTORIES("/Users/soyeonbaek/Soyeon/flatten")
# LINK_DIRECTORIES("/Users/soyeonbaek/Soyeon/ocaml")
LINK_DIRECTORIES("/Users/soyeonbaek/Soyeon/ocaml/runtime")
# INCLUDE_DIRECTORIES("/Users/soyeonbaek/Soyeon/ocaml")
INCLUDE_DIRECTORIES("/Users/soyeonbaek/Soyeon/ocaml/runtime")

LINK_LIBRARIES(test)
LINK_LIBRARIES(asmrun)
LINK_LIBRARIES(m)
LINK_LIBRARIES(dl)


add_llvm_library( LLVMHello MODULE BUILDTREE_ONLY
  Hello.cpp

  DEPENDS
  intrinsics_gen
  PLUGIN_TOOL
  opt
  )
