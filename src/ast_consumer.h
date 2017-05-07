#pragma once

#include "ast_visitor.h"
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Rewrite/Core/Rewriter.h>

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser.
class MyASTConsumer : public clang::ASTConsumer {
public:
  MyASTConsumer(clang::Rewriter &R) : visitor_(R) {}

  // Override the method that gets called for each parsed top-level
  // declaration.
  bool HandleTopLevelDecl(clang::DeclGroupRef DR) override {
    for (clang::DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
      // Traverse the declaration using our AST visitor.
      visitor_.TraverseDecl(*b);
      (*b)->dump();
    }
    return true;
  }

private:
  MyASTVisitor visitor_;
};
