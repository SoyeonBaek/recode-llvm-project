# If we don't need RTTI or EH, there's no reason to export anything
# from the hello plugin.

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


add_llvm_library( LLVMDeob MODULE BUILDTREE_ONLY
  Deob.cpp

  DEPENDS
  intrinsics_gen
  PLUGIN_TOOL
  opt
  )
