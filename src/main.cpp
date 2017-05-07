
//------------------------------------------------------------------------------
// Automatic mock generator for google mock
// - gmockautogen
//
// Ingmar Lehmann (lehmann.ingmar@gmail.com)
//
// Thanks to Eli Bendersky (eliben@gmail.com) for the excellent
// example(s) on how to get started with clang + libTooling
// You can find them here: https://github.com/eliben/llvm-clang-samples
//------------------------------------------------------------------------------
#include <sstream>
#include "ast_consumer.h"
#include "frontend_action.h"

#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

static llvm::cl::OptionCategory GoogleMockAutoGenOptions("gmockautogen");

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser op(argc, argv, GoogleMockAutoGenOptions);
    clang::tooling::ClangTool Tool(op.getCompilations(), op.getSourcePathList());

    // ClangTool::run accepts a FrontendActionFactory, which is then used to
    // create new objects implementing the FrontendAction interface. Here we use
    // the helper newFrontendActionFactory to create a default factory that will
    // return a new MyFrontendAction object every time.
    // To further customize this, we could create our own factory class.
    return Tool.run(clang::tooling::newFrontendActionFactory<MyFrontendAction>().get());
}
