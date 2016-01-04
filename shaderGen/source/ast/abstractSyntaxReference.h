#pragma once
#ifndef __AST_REFERENCE_H__
#define __AST_REFERENCE_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

#include "common/types.h"
#include "common/util.h"

class ASTReference : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpReference;
    }

    static std::string ConstName()
    {
        return "ASTReference";
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

    ASTReference( ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file ) :
        ASTNode( driver, index, line, file, ConstType(), "UNDEFINED_REFERENCE",
                 ASTDataType::TypeUnknown )
    {
    }
};

#endif