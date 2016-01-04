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

    enum ASTAssignmentType
    {
        Unknown,
        Assignment,
        SumCompound,
        DifferenceCompound,
        ProductCompound,
        QuotientCompound,
        RemainderCompound,
        LeftShiftCompound,
        RightShiftCompound,
        BitwiseAndCompound,
        BitwiseOrCompound,
        BitwiseXorCompound
    };

    ASTAssignment( ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file ) :
        ASTNode( driver, index, line, file, ConstType(), "Assignment", ASTDataType::TypeUnknown )
    {
        // Add a child node for the param 1
        AddChild( driver->Create< ASTHub >( line, file, "DummyTarget" ) );

        // Add a child node for the param 2
        AddChild( driver->Create< ASTHub >( line, file, "DummyTarget" ) );
    }

    ASTAssignmentType GetAssignmentType() const
    {
        return mType;
    }

    void SetAssignmentType( ASTAssignmentType type )
    {
        mType = type;
    }

    void SetTarget1( ASTNode *target )
    {
        ModifyChild( 0, target );
    }

    void SetTarget2( ASTNode *target )
    {
        ModifyChild( 1, target );
    }

private:

    ASTAssignmentType mType;
};

#endif