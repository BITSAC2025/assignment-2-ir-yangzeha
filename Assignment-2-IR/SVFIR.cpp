/**
 * SVFIR.cpp
 * @author kisslune
 */

#include "Graphs/SVFG.h"
#include "SVF-LLVM/SVFIRBuilder.h"
#include <Graphs/CallGraph.h>
#include <vector>
#include <string>
#include <cassert>

using namespace SVF;
using namespace llvm;
using namespace std;

int main(int argc, char** argv)
{
    // 使用vector管理参数，避免手动内存管理
    vector<string> args;
    vector<char*> arg_ptrs;
    
    // 复制原始参数
    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    
    // 添加额外参数
    args.push_back("-model-arrays=true");
    args.push_back("-pre-field-sensitive=false"); 
    args.push_back("-model-consts=true");
    args.push_back("-stat=false");
    
    // 准备char*数组
    for (auto& arg : args) {
        arg_ptrs.push_back(const_cast<char*>(arg.c_str()));
    }
    
    // 解析选项
    vector<string> moduleNameVec = OptionBase::parseOptions(
        arg_ptrs.size(), arg_ptrs.data(), "SVF IR", "[options] <input-bitcode...>");

    // 检查是否有输入模块
    if (moduleNameVec.empty()) {
        cerr << "Error: No input module specified" << endl;
        return 1;
    }

    LLVMModuleSet::getLLVMModuleSet()->buildSVFModule(moduleNameVec);

    SVFIRBuilder builder;
    cout << "Generating SVFIR(PAG), call graph and ICFG ..." << endl;

    SVFIR* pag = builder.build();
    CallGraph* cg = pag->getCallGraph();
    ICFG* icfg = pag->getICFG();
    
    pag->dump();
    cg->dump(); 
    icfg->dump();
    
    return 0;
}