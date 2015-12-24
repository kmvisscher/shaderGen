#pragma once
#ifndef __AST_COMPARISON_H__
#define __AST_COMPARISON_H__


#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTComparison : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpComparisonOperator;
    }

    static std::string ConstName()
    {
        return "ASTComparison";
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

    enum ASTComparisonType
    {
        CmpLT,
        CmpLE,
        CmpEQ,
        CmpGT,
        CmpGE
    };

    ASTComparison( ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, 
                   ASTComparisonType comptype, ASTNode * lhs, ASTNode *rhs ) :
                   ASTNode(driver, index, line, file, ConstType(), "Comparison", ASTDataType::TypeUnknown), 
                   mCompType( comptype ), mLhs(lhs), mRhs( rhs )
    {
    }

private:

    ASTComparisonType mCompType;
    ASTNode * mLhs;
    ASTNode * mRhs;
};

#endif