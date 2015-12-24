#include "shaderGen.h"

#include "ast/abstractSyntaxTree.h"
#include "ast/abstractSyntaxFunction.h"
#include "ast/abstractSyntaxDeclaration.h"
#include "ast/abstractSyntaxLoop.h"

#include "lex/zsl/lexer.h"

int main()
{
    /*
    ASTDriver driver;
    ASTFunction *function = driver.Create< ASTFunction >( 0, "TEST", ASTNode::ASTDataType::TypeComplex, "Foo"  );
    

    ASTHub *dummy1 = driver.Create< ASTHub >(1, "TEST", "stuff");

    ASTLoop *loop1 = driver.Create< ASTLoop >(1, "TEST", ASTLoop::ASTLoopType::LoopFor, dummy1);

    ASTDeclaration *exc1 = driver.Create< ASTDeclaration >(1, "TEST", ASTNode::ASTDataType::TypeInt32, "i");

    function->GetStatementHub()->AddChild(loop1);
    loop1->GetInitializerHub()->AddChild(exc1);

    function->Print( "" );
    */

    ZslLexer::ParseSource("../../test.zsl");

    return 0;
}