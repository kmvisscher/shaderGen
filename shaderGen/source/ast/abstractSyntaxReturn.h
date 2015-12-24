#pragma once
#ifndef __AST_RETURN_H__
#define __AST_RETURN_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTReturn : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpReturn;
    }

    static std::string ConstName()
    {
        return "ASTReturn";
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

    ASTReturn(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, ASTNode *target ) :
        ASTNode(driver, index, line, file, ConstType(), "Return", ASTDataType::TypeUnknown), mTarget(target)
    {
    }

private:

    ASTNode * mTarget;
};

#endif