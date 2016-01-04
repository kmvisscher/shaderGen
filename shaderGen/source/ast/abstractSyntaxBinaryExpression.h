#pragma once
#ifndef __AST_BINARY_EXPRESSION_H__
#define __AST_BINARY_EXPRESSION_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTBinary : public ASTNode
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

    enum ASTBinaryType
    {
        Unknown,
        ExprAdd,
        ExprSubtract,
        ExprMul,
        ExprDiv,
        ExprAnd,
        ExprOr,
        ExprXor
    };

    ASTBinary( ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file ) :
        ASTNode( driver, index, line, file, ConstType(), "BinaryExpression", ASTDataType::TypeUnknown ),
        mBinaryType( ASTBinaryType::Unknown )
    {
        // Add a child node for the param 1
        AddChild( driver->Create< ASTHub >( line, file, "DummyTarget" ) );

        // Add a child node for the param 2
        AddChild( driver->Create< ASTHub >( line, file, "DummyTarget" ) );
    }

    ASTBinaryType GetBinaryType() const
    {
        return mBinaryType;
    }

    void SetBinaryType( ASTBinaryType type )
    {
        mBinaryType = type;
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

    ASTBinaryType mBinaryType;
};

#endif