#pragma once
#ifndef __AST_CAST_H__
#define __AST_UNARY_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTCast : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpTypeCaseExpression;
    }

    static std::string ConstName()
    {
        return "ASTCast";
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

    ASTCast(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, ASTDataType dataType, ASTNode *target ) :
        ASTNode(driver, index, line, file, ConstType(), "Cast", dataType),  mTarget(target)
    {
    }

private:

    ASTNode * mTarget;
};

#endif