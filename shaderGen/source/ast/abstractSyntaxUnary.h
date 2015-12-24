#pragma once
#ifndef __AST_UNARY_H__
#define __AST_UNARY_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTUnary : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpUnaryExpression;
    }

    static std::string ConstName()
    {
        return "ASTUnary";
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

    enum ASTUnaryType
    {
        IncPre,
        IncPost,
        DecrPre,
        DecrPost,
        Complement,
        Negation
    };

    ASTUnary(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, ASTUnaryType unType, ASTNode *target) :
        ASTNode(driver, index, line, file, ConstType(), "UnaryExpression", ASTDataType::TypeUnknown), mUnaryType(unType), mTarget(target)
    {
    }

private:

    ASTUnaryType mUnaryType;
    ASTNode * mTarget;
};

#endif