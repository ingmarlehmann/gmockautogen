#pragma once

#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/AST/RecursiveASTVisitor.h>

// By implementing RecursiveASTVisitor, we can specify which AST nodes
// we're interested in by overriding relevant methods.
class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor> {
public:
  MyASTVisitor(clang::Rewriter &R) : rewriter_(R) {}

  bool VisitStmt(clang::Stmt *s) {
    // Only care about If statements.
    if (clang::isa<clang::IfStmt>(s)) {
      clang::IfStmt *IfStatement = clang::cast<clang::IfStmt>(s);
      clang::Stmt *Then = IfStatement->getThen();

        rewriter_.InsertText(Then->getLocStart(), "// the 'if' part\n", true,
                             true);

      clang::Stmt *Else = IfStatement->getElse();
      if (Else)
          rewriter_.InsertText(Else->getLocStart(), "// the 'else' part\n",
                               true, true);
    }

    return true;
  }

  bool VisitFunctionDecl(clang::FunctionDecl *f) {
    // Only function definitions (with bodies), not declarations.
    if (f->hasBody()) {
      clang::Stmt *FuncBody = f->getBody();

      // Type name as string
      clang::QualType QT = f->getReturnType();
      std::string TypeStr = QT.getAsString();

      // Function name
      clang::DeclarationName DeclName = f->getNameInfo().getName();
      std::string FuncName = DeclName.getAsString();

      // Add comment before
      std::stringstream SSBefore;
      SSBefore << "// Begin function " << FuncName << " returning " << TypeStr
               << "\n";
      clang::SourceLocation ST = f->getSourceRange().getBegin();
        rewriter_.InsertText(ST, SSBefore.str(), true, true);

      // And after
      std::stringstream SSAfter;
      SSAfter << "\n// End function " << FuncName;
      ST = FuncBody->getLocEnd().getLocWithOffset(1);
        rewriter_.InsertText(ST, SSAfter.str(), true, true);
    }

    return true;
  }

private:
  clang::Rewriter &rewriter_;
};
