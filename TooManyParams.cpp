   #include "clang/AST/AST.h"
   #include "clang/Frontend/FrontendPluginRegistry.h"
   #include "clang/Frontend/CompilerInstance.h"
   #include "clang/AST/RecursiveASTVisitor.h"
   #include "clang/Basic/Diagnostic.h"

   using namespace clang;

   namespace {

   class TooManyParamsVisitor : public RecursiveASTVisitor<TooManyParamsVisitor> {
   public:
       explicit TooManyParamsVisitor(ASTContext *Context)
           : Context(Context) {}

       bool VisitFunctionDecl(FunctionDecl *D) {
           if (D->param_size() > 3) {
               DiagnosticsEngine &Diag = Context->getDiagnostics();
               unsigned DiagID = Diag.getCustomDiagID(DiagnosticsEngine::Warning, "Function has too many parameters");
               Diag.Report(D->getLocation(), DiagID);
           }
           return true;
       }

   private:
       ASTContext *Context;
   };

   class TooManyParamsConsumer : public ASTConsumer {
   public:
       explicit TooManyParamsConsumer(ASTContext *Context)
           : Visitor(Context) {}

       void HandleTranslationUnit(ASTContext &Context) override {
           Visitor.TraverseDecl(Context.getTranslationUnitDecl());
       }

   private:
       TooManyParamsVisitor Visitor;
   };

   class TooManyParamsAction : public PluginASTAction {
   protected:
       std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, llvm::StringRef) override {
           return std::make_unique<TooManyParamsConsumer>(&CI.getASTContext());
       }

       bool ParseArgs(const CompilerInstance &CI, const std::vector<std::string> &args) override {
           return true;
       }
   };

   }

   static FrontendPluginRegistry::Add<TooManyParamsAction> 
   X("too-many-params", "warn about functions with too many parameters");
