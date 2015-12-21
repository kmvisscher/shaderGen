#pragma once
#ifndef __AST_SYNTAX_FUNCTION_H__
#define __AST_SYNTAX_FUNCTION_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTFunction : public ASTNode
{
public:

    static ASTNodeType ConstType() 
    {
        return ASTNodeType::OpFunctionDeclaration;
    }

    static std::string ConstName() 
    {
        return "ASTFunction";
    }

    virtual const std::string &GetNodeName() const override
    {
        return ConstName();
    }

    ASTFunction( ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, const ASTDataType &dataType, const std::string &functionName ) :
                 ASTNode( driver, index, line, file, ConstType(), dataType ), mFunctionName( functionName )
    {
        // Add a child node for the parameters
        AddChild( driver->Create< ASTHub >( line, file ) );
        
        // Add a child for the statements
        AddChild( driver->Create< ASTHub >( line, file ) );
    }
    
    ASTHub * GetParameterHub() const
    {
        return (ASTHub *)GetChild( 0 );
    }
    
    ASTHub * GetStatementHub() const
    {
        return (ASTHub *)GetChild( 1 );
    }
    
private:

    std::string mFunctionName;
   
};

#endif