#pragma once
#ifndef __AST_LITERAL_H__
#define __AST_LITERAL_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

#include "common/types.h"

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

    ASTLiteral(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, const std::string &name, S32 val ) :
        ASTNode(driver, index, line, file, ConstType(), name, ASTDataType::TypeInt32)
    {
        mData.i = val;
    }

    ASTLiteral(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, const std::string &name, U32 val) :
        ASTNode(driver, index, line, file, ConstType(), name, ASTDataType::TypeUint32)
    {
        mData.ui = val;
    }

    ASTLiteral(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, const std::string &name, F32 val) :
        ASTNode(driver, index, line, file, ConstType(), name, ASTDataType::TypeFloat)
    {
        mData.f = val;
    }

    ASTLiteral(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, const std::string &name, F64 val) :
        ASTNode(driver, index, line, file, ConstType(), name, ASTDataType::TypeDouble)
    {
        mData.d = val;
    }

    ASTLiteral(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, const std::string &name, bool val) :
        ASTNode(driver, index, line, file, ConstType(), name, ASTDataType::TypeBool)
    {
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