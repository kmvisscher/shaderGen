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
        Unknown,
        CmpLT,
        CmpLE,
        CmpEQ,
        CmpNEQ,
        CmpGT,
        CmpGE
    };

    ASTComparison( ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file ) :
        ASTNode( driver, index, line, file, ConstType(), "Comparison", ASTDataType::TypeUnknown ),
        mCompType( ASTComparisonType::Unknown )
    {
        // Add a child node for the param 1
        AddChild( driver->Create< ASTHub >( line, file, "DummyTarget" ) );

        // Add a child node for the param 2
        AddChild( driver->Create< ASTHub >( line, file, "DummyTarget" ) );
    }

    ASTComparisonType GetCompType() const
    {
        return mCompType;
    }

    void SetCompType( ASTComparisonType type )
    {
        mCompType = type;
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

    ASTComparisonType mCompType;
};

#endif