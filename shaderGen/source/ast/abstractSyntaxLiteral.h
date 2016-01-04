#pragma once
#ifndef __AST_LITERAL_H__
#define __AST_LITERAL_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

#include "common/types.h"
#include "common/util.h"

class ASTLiteral : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpLiteralExpression;
    }

    static std::string ConstName()
    {
        return "ASTLiteral";
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

    ASTLiteral( ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file ) :
        ASTNode( driver, index, line, file, ConstType(), Util::Format( "Literal%u", ( U32 ) index ),
                 ASTDataType::TypeUnknown )
    {
    }

    void SetData( S32 val )
    {
        SetDataType( ASTDataType::TypeInt32 );
        mData.i = val;
    }

    void SetData( U32 val )
    {
        SetDataType( ASTDataType::TypeUint32 );
        mData.ui = val;
    }

    void SetData( F32 val )
    {
        SetDataType( ASTDataType::TypeFloat );
        mData.f = val;
    }

    void SetData( F64 val )
    {
        SetDataType( ASTDataType::TypeDouble );
        mData.d = val;
    }

    void SetData( bool val )
    {
        SetDataType( ASTDataType::TypeBool );
        mData.b = val;
    }

private:

    union
    {
        S32 i;
        U32 ui;
        F32 f;
        F64 d;
        bool b;
    } mData;
};

#endif