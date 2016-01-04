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
        Unknown,
        Inc,
        IncPost,
        Decr,
        DecrPost,
        Complement,
        Not,
        Plus,
        Minus
    };

    ASTUnary( ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file ) :
        ASTNode( driver, index, line, file, ConstType(), "UnaryExpression", ASTDataType::TypeUnknown ),
        mUnaryType( ASTUnaryType::Unknown )
    {
        // Add a child node for the parameters
        AddChild( driver->Create< ASTHub >( line, file, "DummyTarget" ) );
    }

    ASTUnaryType GetUnaryType() const
    {
        return mUnaryType;
    }

    void SetUnaryType( ASTUnaryType type )
    {
        mUnaryType = type;
    }

    void SetTarget( ASTNode *target )
    {
        ModifyChild( 0, target );
    }

private:

    ASTUnaryType mUnaryType;
};

#endif