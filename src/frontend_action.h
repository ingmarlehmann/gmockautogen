#pragma once

#include "ast_consumer.h"
#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>

// For each source file provided to the tool, a new FrontendAction is created.
class MyFrontendAction : public clang::ASTFrontendAction {
public:
    MyFrontendAction() {}
    void EndSourceFileAction() override {
        clang::SourceManager &SM = rewriter_.getSourceMgr();
        llvm::errs() << "** EndSourceFileAction for: "
                     << SM.getFileEntryForID(SM.getMainFileID())->getName() << "\n";

        // Now emit the rewritten buffer.
        rewriter_.getEditBuffer(SM.getMainFileID()).write(llvm::outs());
    }

    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI,
            StringRef file) override {
        llvm::errs() << "** Creating AST consumer for: " << file << "\n";
        rewriter_.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
        return llvm::make_unique<MyASTConsumer>(rewriter_);
    }

private:
    clang::Rewriter rewriter_;
};
