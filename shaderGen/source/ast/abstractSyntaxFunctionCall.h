#pragma once
#ifndef __AST_SYNTAX_FUNCTIONCALL_H__
#define __AST_SYNTAX_FUNCTIONCALL_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTFunctionCall : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpFunctionCall;
    }

    static std::string ConstName()
    {
        return "ASTFunctionCall";
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
        return true;
    }

    ASTFunctionCall(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, const ASTDataType &dataType, const std::string &functionName) :
        ASTNode(driver, index, line, file, ConstType(), functionName, dataType)
    {
        // Add a child node for the parameters
        AddChild(driver->Create< ASTHub >(line, file, "Parameters"));
    }

    ASTHub * GetParameterHub() const
    {
        return (ASTHub *)GetChild(0);
    }
};

#endif