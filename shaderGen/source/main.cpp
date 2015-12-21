#include "shaderGen.h"

#include "ast/abstractSyntaxTree.h"
#include "ast/abstractSyntaxFunction.h"


int main()
{
    ASTDriver driver;
    ASTNode *function = driver.Create< ASTFunction >( 0, "TEST", ASTNode::ASTDataType::TypeComplex, "Foo"  );
    
    function->Print( "" );
    
    return 0;
}