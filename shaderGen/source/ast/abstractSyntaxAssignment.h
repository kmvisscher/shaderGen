#pragma once
#ifndef __AST_ASSIGNMENT_H__
#define __AST_ASSIGNMENT_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTAssignment : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpAssignmentExpression;
    }

    static std::string ConstName()
    {
        return "ASTAssignment";
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

    ASTAssignment( ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file,
                   ASTNode *rhs1, ASTNode *rhs2) :
                   ASTNode(driver, index, line, file, ConstType(), "Assignment", ASTDataType::TypeUnknown), 
                   mRhs1(rhs1), mRhs2(rhs2)
    {
    }

private:

    ASTNode * mRhs1;
    ASTNode * mRhs2;
};

#endif