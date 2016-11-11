file(REMOVE_RECURSE
  "testcv.pdb"
  "testcv"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/testcv.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
