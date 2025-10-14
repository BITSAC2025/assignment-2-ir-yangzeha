/**
 * SVFIR.cpp
 * @author kisslune
 * 
 * 编译方法示例（需替换为实际的SVF安装路径）：
 * g++ SVFIR.cpp -o svfir_generator \
 *   -I/path/to/SVF/include \
 *   -L/path/to/SVF/lib \
 *   -lSVFLLVM -lSVF -lz3 \
 *   `llvm-config --cxxflags --ldflags --system-libs --libs core`
 */

#include "Graphs/SVFG.h"
#include "Graphs/PAG.h"
#include "Graphs/ICFG.h"
#include "Graphs/CallGraph.h"
#include "SVF-LLVM/SVFIRBuilder.h"
#include "Util/Options.h"
#include "Util/PTAStat.h"

using namespace SVF;
using namespace llvm;
using namespace std;

int main(int argc, char** argv)
{
    int arg_num = 0;
    int extraArgc = 4;
    char** arg_value = new char*[argc + extraArgc];
    for (; arg_num < argc; ++arg_num) {
        arg_value[arg_num] = argv[arg_num];
    }
    std::vector<std::string> moduleNameVec;

    int orgArgNum = arg_num;
    arg_value[arg_num++] = (char*)"-model-arrays=true";
    arg_value[arg_num++] = (char*)"-pre-field-sensitive=false";
    arg_value[arg_num++] = (char*)"-model-consts=true";
    arg_value[arg_num++] = (char*)"-stat=false";
    assert(arg_num == (orgArgNum + extraArgc) && "more extra arguments? Change the value of extraArgc");

    // 解析命令行选项并获取模块名称
    moduleNameVec = OptionBase::parseOptions(arg_num, arg_value, "SVF IR", "[options] <input-bitcode...>");

    // 构建LLVM模块集合
    LLVMModuleSet* moduleSet = LLVMModuleSet::getLLVMModuleSet();
    moduleSet->buildSVFModule(moduleNameVec);

    // 实例化SVFIR构建器
    SVFIRBuilder builder;
    cout << "Generating SVFIR(PAG), call graph and ICFG ..." << endl;

    // 生成PAG (程序分配图)
    PAG* pag = builder.build();
    assert(pag && "Failed to build PAG!");

    // 生成调用图
    CallGraph* callGraph = pag->getCallGraph();
    assert(callGraph && "Failed to get CallGraph!");

    // 生成ICFG ( interprocedural control-flow graph )
    ICFG* icfg = pag->getICFG();
    assert(icfg && "Failed to get ICFG!");

    // 获取生成的SVFIR
    SVFIR* svfir = SVFIR::getSVFIR();
    assert(svfir && "Failed to get SVFIR!");

    // 将图形结构导出到文件
    cout << "Dumping graphs to files ..." << endl;
    
    // 导出PAG
    pag->dump("pag.dot");
    
    // 导出调用图
    callGraph->dump("callgraph.dot");
    
    // 导出ICFG
    icfg->dump("icfg.dot");
    
    // 导出SVFIR
    svfir->dump("svfir.dot");

    // 释放资源
    delete[] arg_value;
    SVFIR::releaseSVFIR();
    PAG::releasePAG();
    LLVMModuleSet::releaseLLVMModuleSet();

    cout << "All graphs generated successfully!" << endl;
    return 0;
}
