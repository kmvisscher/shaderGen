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

    virtual const std::string GetNodeName() const override
    {
        return ConstName();
    }

    virtual bool IsLvalue() const override
    {
        return false;
    }

    virtual bool IsRvalue() const override
    {
        return false;
    }

    ASTFunction(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, const ASTDataType &dataType, const std::string &functionName) :
        ASTNode(driver, index, line, file, ConstType(), functionName, dataType)
    {
        // Add a child node for the parameters
        AddChild(driver->Create< ASTHub >(line, file, "Parameters"));

        // Add a child for the statements
        AddChild(driver->Create< ASTHub >(line, file, "Statements"));

        // Add a child for the meta data
        AddChild(driver->Create< ASTHub >(line, file, "MetaData"));
    }

    ASTHub * GetParameterHub() const
    {
        return (ASTHub *)GetChild(0);
    }

    ASTHub * GetStatementHub() const
    {
        return (ASTHub *)GetChild(1);
    }

    ASTHub * GetMetaDataHub() const
    {
        return (ASTHub *)GetChild(2);
    }

};

#endif