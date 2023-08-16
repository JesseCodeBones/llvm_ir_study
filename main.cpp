#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <system_error>
#include <vector>

int main(int, char **) {
  llvm::LLVMContext context;
  llvm::IRBuilder<> builder(context);
  std::string moduleName("jesse module");
  llvm::Module module(moduleName, context);
  std::vector<llvm::Type *> integers(2, llvm::Type::getInt32Ty(context));
  auto functionType =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(context), integers, false);
  auto function =
      llvm::Function::Create(functionType, llvm::Function::ExternalLinkage,
                             "main", &module);
  llvm::BasicBlock *basicBlock =
      llvm::BasicBlock::Create(context, "entry", function);
  builder.SetInsertPoint(basicBlock);
  auto value = llvm::ConstantInt::get(context, llvm::APInt(32, 69));
  auto * helloWorld = llvm::ConstantDataArray::getString(context, "hello world\n");
  std::vector<llvm::Value *> ArgsV;    
  ArgsV.push_back(helloWorld);
  std::vector<llvm::Type *> printfArgTypes(1, llvm::Type::getInt8PtrTy(context));
  auto *printfType = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), printfArgTypes, false);
  printf("hello world");
  auto printfFunc = module.getOrInsertFunction("printf", printfType);
  builder.CreateCall(printfFunc, ArgsV, "printf");
  builder.CreateRet(value);
  llvm::verifyFunction(*function);
  module.print(llvm::errs(), nullptr);
  std::error_code errorCode;
  llvm::raw_fd_ostream os("module", errorCode);
  llvm::WriteBitcodeToFile(module, os);
  std::cout << "finish\n";
}
