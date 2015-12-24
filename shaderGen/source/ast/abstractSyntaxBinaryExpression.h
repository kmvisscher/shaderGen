#pragma once
#ifndef __AST_BINARY_EXPRESSION_H__
#define __AST_BINARY_EXPRESSION_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTBinaryExpression : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpBinaryExpression;
    }

    static std::string ConstName()
    {
        return "ASTBinaryExpression";
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

    enum ASTBinaryExpr
    {
        ExprAdd,
        ExprSubtract,
        ExprMul,
        ExprDiv,
        ExprAnd,
        ExprOr,
        ExprXor
    };

    ASTBinaryExpression(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, 
                        ASTBinaryExpr exprType, ASTNode *rhs1, ASTNode *rhs2) :
        ASTNode(driver, index, line, file, ConstType(), "BinaryExpression", ASTDataType::TypeUnknown), mExprType(exprType), mRhs1(rhs1), mRhs2(rhs2)
    {
    }

private:

    ASTBinaryExpr mExprType;
    ASTNode * mRhs1;
    ASTNode * mRhs2;
};

#endif