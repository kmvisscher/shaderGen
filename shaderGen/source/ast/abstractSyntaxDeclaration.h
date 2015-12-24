#pragma once
#ifndef __AST_DECLARATION_H__
#define __AST_DECLARATION_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTDeclaration : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpDeclaration;
    }

    static std::string ConstName()
    {
        return "ASTDeclaration";
    }

    virtual const std::string GetNodeName() const override
    {
        return ConstName();
    }

    virtual bool IsLvalue() const override
    {
        return true;
    }

    virtual bool IsRvalue() const override
    {
        return true;
    }

    ASTDeclaration(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, const ASTDataType &dataType, const std::string &varName ) :
        ASTNode(driver, index, line, file, ConstType(), varName, dataType)
    {
        // Add a child node for the initializer list
        AddChild(driver->Create< ASTHub >(line, file, "InitializerList"));

        // Add a child for the meta data
        AddChild(driver->Create< ASTHub >(line, file, "MetaData"));
    }

    ASTHub * GetInitialerHub() const
    {
        return (ASTHub *)GetChild(0);
    }

    ASTHub * GetMetaDataHub() const
    {
        return (ASTHub *)GetChild(1);
    }

};


#endif