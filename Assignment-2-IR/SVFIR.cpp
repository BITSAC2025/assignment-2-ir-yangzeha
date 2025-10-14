/**
 * SVFIR.cpp
 * @author kisslune
 * 功能：加载LLVM位码文件，生成并输出SVFIR(PAG)、调用图(Call Graph)和过程间控制流图(ICFG)
 */

#include "Graphs/SVFG.h"
#include "SVF-LLVM/SVFIRBuilder.h"

using namespace SVF;
using namespace llvm;
using namespace std;

int main(int argc, char** argv)
{
    int arg_num = 0;
    int extraArgc = 4;
    // 分配参数数组（原始参数 + 额外默认参数）
    char** arg_value = new char*[argc + extraArgc];
    
    // 复制用户输入的原始参数
    for (; arg_num < argc; ++arg_num) {
        arg_value[arg_num] = argv[arg_num];
    }

    // 添加默认分析参数
    int orgArgNum = arg_num;
    arg_value[arg_num++] = (char*)"-model-arrays=true";    // 启用数组建模
    arg_value[arg_num++] = (char*)"-pre-field-sensitive=false";  // 禁用预字段敏感分析
    arg_value[arg_num++] = (char*)"-model-consts=true";    // 启用常量建模
    arg_value[arg_num++] = (char*)"-stat=false";           // 禁用统计信息输出
    
    // 验证参数数量正确性
    assert(arg_num == (orgArgNum + extraArgc) && "参数数量不匹配，请调整extraArgc值");

    // 解析参数，获取输入的LLVM位码文件列表
    std::vector<std::string> moduleNameVec = OptionBase::parseOptions(arg_num, arg_value, "SVF IR", "[options] <input-bitcode...>");
    
    // 释放动态分配的参数数组（修复内存泄漏）
    delete[] arg_value;

    // 加载LLVM位码文件，构建SVF模块
    LLVMModuleSet::buildSVFModule(moduleNameVec);

    // 创建SVFIR构建器并生成分析图
    SVFIRBuilder builder;
    cout << "Generating SVFIR(PAG), call graph and ICFG ..." << endl;

    // 生成PAG（指针赋值图）并输出
    auto pag = builder.build();
    pag->dump();

    // 生成调用图并输出
    auto cg = pag->getCallGraph();
    cg->dump();

    // 生成ICFG（过程间控制流图）并输出
    auto icfg = pag->getICFG();
    icfg->dump();

    // 释放LLVM模块资源
    LLVMModuleSet::releaseLLVMModuleSet();
    return 0;
}
