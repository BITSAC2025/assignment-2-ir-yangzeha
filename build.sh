name: Patch SVF for LLVM 16 compatibility
  run: |
    # 修复 BasicTypes.h 中的兼容性问题
    sed -i '76s/.*/#if LLVM_VERSION_MAJOR >= 16\
    typedef llvm::UnifyFunctionExitNodesPass UnifyFunctionExitNodes;\
    #else\
    typedef llvm::UnifyFunctionExitNodesLegacyPass UnifyFunctionExitNodes;\
    #endif/' SVF/svf-llvm/include/SVF-LLVM/BasicTypes.h
    
    # 如果有其他兼容性问题，也一并修复
    echo "Applied LLVM 16 compatibility patch"
#!/bin/bash

rm -rf build/

# shellcheck disable=SC2164
mkdir build && cd build/

cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4
